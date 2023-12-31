#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 0

#define READERS_CNT 5
#define WRITERS_CNT 5

#define WITER_CNT 8
#define RITER_CNT 7

#define WRITE_TIMEOUT 300
#define READ_TIMEOUT 300
#define DIFF 4000


HANDLE mutex1, mutex2;
HANDLE can_read;
HANDLE can_write;

LONG active_readers = 0;
LONG waiting_writers = 0;
LONG waiting_readers = 0;

BOOL active_writer = 0;
static int value = 0;

void start_read(void) 
{
	InterlockedIncrement(&waiting_readers);
	WaitForSingleObject(mutex1, INFINITE);

	if (active_writer == 1 || (WaitForSingleObject(can_write, 0) == WAIT_OBJECT_0 && waiting_writers > 0))
		WaitForSingleObject(can_read, INFINITE);

	InterlockedDecrement(&waiting_readers);
	InterlockedIncrement(&active_readers);

	SetEvent(can_read);
	ReleaseMutex(mutex1);
}

void stop_read(void) 
{
	InterlockedDecrement(&active_readers);
	if (active_readers == 0)
	{
		ResetEvent(can_read);
		SetEvent(can_write);
	}
}

DWORD WINAPI reader(CONST LPVOID lpParams) 
{
	srand(time(NULL) + WRITERS_CNT);
	int sleep_time;

	for (size_t i = 0; i < RITER_CNT; i++)
	{
		sleep_time = READ_TIMEOUT + rand() % DIFF;
		Sleep(sleep_time);
		start_read();
		printf("Reader %d read: %d\n", (int)lpParams, value);
		stop_read();
	}

	return OK;
}

void start_write(void) 
{
	InterlockedIncrement(&waiting_writers);
	WaitForSingleObject(mutex2, INFINITE);

	if (active_writer == 1 || active_readers > 0)
		WaitForSingleObject(can_write, INFINITE);

	InterlockedDecrement(&waiting_writers);
	active_writer = 1;

	ReleaseMutex(mutex2);
}

void stop_write(void) 
{
	active_writer = 0;

	if (waiting_readers > 0)
		SetEvent(can_read);
	else
		SetEvent(can_write);
}

DWORD WINAPI writer(CONST LPVOID lpParams) 
{
	srand(time(NULL) + READERS_CNT);
	int sleep_time;

	for (int i = 0; i < WITER_CNT; i++)
	{
		sleep_time = WRITE_TIMEOUT + rand() % DIFF;
		Sleep(sleep_time);
		start_write();

		printf("Writer %d write: %d\n", (int)lpParams, ++value);
		stop_write();
	}

	return OK;
}

int main(void) 
{
	HANDLE writers_threads[WRITERS_CNT];
	HANDLE readers_threads[READERS_CNT];

	if ((mutex1 = CreateMutex(NULL, 0, NULL)) == NULL || (mutex2 = CreateMutex(NULL, 0, NULL)) == NULL) 
	{
		perror("CreateMutex error.\n");
		return GetLastError();
	}

	if ((can_read = CreateEvent(NULL, 1, 0, NULL)) == NULL || (can_write = CreateEvent(NULL, 0, 0, NULL)) == NULL) 
	{
		perror("CreateEvent error.\n");
		return GetLastError();
	}

	for (int i = 0; i < READERS_CNT; i++)
	{
		if ((readers_threads[i] = CreateThread(NULL, 0, reader, (LPVOID)i, 0, NULL)) == NULL) 
		{
			perror("CreateThread error.\n");
			return GetLastError();
		}
	}

	for (int i = 0; i < WRITERS_CNT; i++)
	{
		if ((writers_threads[i] = CreateThread(NULL, 0, writer, (LPVOID)i, 0, NULL)) == NULL) 
		{
			perror("CreateThread error.\n");
			return GetLastError();
		}
	}

	WaitForMultipleObjects(READERS_CNT, readers_threads, 1, INFINITE);
	WaitForMultipleObjects(WRITERS_CNT, writers_threads, 1, INFINITE);

	CloseHandle(mutex1);
	CloseHandle(can_read);
	CloseHandle(can_write);

	return OK;
}
