#include <iostream>

#define MAXLEN 100

extern "C"
{
	void strncpyAsm(char* dst, char* src, int size); // Функция strncpy на ассемблере
}

int strlenAsm(const char* mystr)
{
	int len = 0;

	__asm 
	{
		xor ecx, ecx
		mov ecx, MAXLEN
		mov edi, mystr
		xor al, al
		repne scasb

		mov eax, MAXLEN
		sub eax, ecx
		dec eax
		mov len, eax
	}

	return len;
}

int main()
{
	std::cout << strlenAsm("1234") << std::endl;

	char a[MAXLEN] = "123456";
	char *b = a + 2;

	strncpyAsm(b, a, 3);
	std::cout << b;

	return 0;
}
