#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "sscan.h"
#include "l_queue.h"
#include "a_queue.h"
#include "service_unit.h"
#include <time.h>

#define N 1000
#define STEP 100

int main(void)
{
    setbuf(stdout, NULL);

    printf("Эта программа предназначена для моделирования работы обслуживающего автомата с двумя очередями с заявками разного типа.\n"
            "Очередь реализована с использованием как списка, так и массива, что позволяет сравнить эти два способа реализации очереди.\n\n");

    preset_t preset = {1.0, 5.0, 0.0, 3.0, 0.0, 4.0, 0.0, 1.0};
    stats_t stats;

    int key = 1;
    int rc;
    while (key)
    {
        printf("Команды:\n"
            "\t1 - смоделировать процесс с очередями в виде массива\n"
            "\t2 - смоделировать процесс с очередями в виде списка\n"
            "\t3 - изменить интервалы времени\n"
            "\t4 - сравнить время работы и занимаемую память реализаций очереди\n"
            "\t0 - выход\n\n");
        
        printf("Введите команду: ");
        if (int_sscan(stdin, &key) != EXIT_SUCCESS)
            printf("\n<ОШИБКА> неверная команда\n");
        else
            switch (key)
            {
            case 0:
                printf("\nЗавершение работы\n");
                break;

            case 1:
            {
                a_queue *a_q1 = a_create(N, sizeof(int)), *a_q2 = a_create(N, sizeof(int));
                assert(a_q1 && a_q2);

                rc = unit_sim(a_q1, a_q2, a_push, a_pop, a_is_empty, a_is_full, N, STEP, true, preset, &stats);

                if (rc)
                    printf("\n<ОШИБКА> ПЕРЕПОЛНЕНИЕ ОЧЕРЕДИ\n");

                a_destroy(a_q1);
                a_destroy(a_q2);
                break;
            }
            case 2:
            {
                bool faddr = false;
                printf("Вы хотите печатать освобождённые участки памяти? (0/1): ");
                if (bool_sscan(stdin, &faddr) != EXIT_SUCCESS)
                {
                    printf("\n<ОШИБКА> неверный ввод\n");
                    break;
                }

                l_queue *l_q1 = l_create(sizeof(int)), *l_q2 = l_create(sizeof(int));
                assert(l_q1 && l_q2);

                rc = unit_sim(l_q1, l_q2, l_push, l_pop, l_is_empty, l_is_full, N, STEP, true, preset, &stats);

                if (rc)
                    printf("\n<ОШИБКА> ПЕРЕПОЛНЕНИЕ ОЧЕРЕДИ\n");

                if (faddr)
                {
                    printf("Освобождённые участки памяти:\n");
                    print_addr_list();
                    printf("\n");
                }

                l_destroy(l_q1);
                l_destroy(l_q2);
                break;
            }
            case 3:
            {
                double buf1, buf2;
				printf("Введите интервал входа заявок в первую очередь(T1): ");
				if (scanf("%lf%lf", &buf1, &buf2) != 2 || buf2 < buf1 || buf1 < 0.0 || buf2 < 0.0)
				{
					printf("\n<ОШИБКА> неверный ввод\n");
					break;
				}
				preset.ENTRY_TIME_T1_MIN = buf1;
				preset.ENTRY_TIME_T1_MAX = buf2;
				
				printf("Введите интервал входа заявок во вторую очередь(T2): ");
				if (scanf("%lf%lf", &buf1, &buf2) != 2 || buf2 < buf1 || buf1 < 0.0 || buf2 < 0.0)
				{
					printf("\n<ОШИБКА> неверный ввод\n");
					break;
				}
				preset.ENTRY_TIME_T2_MIN = buf1;
				preset.ENTRY_TIME_T2_MAX = buf2;
				
				printf("Введите интервал обработки заявок первого типа(T3): ");
				if (scanf("%lf%lf", &buf1, &buf2) != 2 || buf2 < buf1 || buf1 < 0.0 || buf2 < 0.0)
				{
					printf("\n<ОШИБКА> неверный ввод\n");
					break;
				}
				preset.PROC_TIME_T1_MIN = buf1;
				preset.PROC_TIME_T1_MAX = buf2;
				
				printf("Введите интервал обработки заявок второго типа(T4): ");
				if (scanf("%lf%lf", &buf1, &buf2) != 2 || buf2 < buf1 || buf1 < 0.0 || buf2 < 0.0)
				{
					printf("\n<ОШИБКА> неверный ввод\n");
					break;
				}
				preset.PROC_TIME_T2_MIN = buf1;
				preset.PROC_TIME_T2_MAX = buf2;
                printf("Настройка интервалов успешно завершена\n");
				break;
            }

            case 4:
            {
                int rep;
                printf("Введите кол-во повторений: ");
                if (int_sscan(stdin, &rep) != EXIT_SUCCESS || rep < 1)
                {
                    printf("\n<ОШИБКА> неверный ввод\n");
                    break;
                }

                clock_t total_arr = 0, total_list = 0, temp; 
                double max_mem_list = 0.0;

                for (int i = 0; i < rep; i++)
                {
                    l_queue *l_q1 = l_create(sizeof(int)), *l_q2 = l_create(sizeof(int));
                    a_queue *a_q1 = a_create(N, sizeof(int)), *a_q2 = a_create(N, sizeof(int));
                    if (!l_q1 || !l_q2 || !a_q1 || !a_q2)
                    {
                        printf("\n<ОШИБКА> ОШИБКА ВЫДЕЛЕНИЯ ПАМЯТИ\n");
                        l_destroy(l_q1);
                        l_destroy(l_q2);
                        a_destroy(a_q1);
                        a_destroy(a_q1);
                    }

                    temp = clock();
                    rc = unit_sim(l_q1, l_q2, l_push, l_pop, l_is_empty, l_is_full, N, STEP, false, preset, &stats);
                    total_list += clock() - temp;

                    if (rc)
                        printf("\n<ОШИБКА> ПЕРЕПОЛНЕНИЕ ОЧЕРЕДИ\n");

                    if (((stats.full_work_time - stats.wait_time) / (double)(stats.in_t1 + stats.in_t2)) > max_mem_list)
                        max_mem_list = (stats.full_work_time - stats.wait_time) / (double)(stats.in_t1 + stats.in_t2);

                    temp = clock();
                    rc = unit_sim(a_q1, a_q2, a_push, a_pop, a_is_empty, a_is_full, N, STEP, false, preset, &stats);
                    total_arr += clock() - temp;

                    if (rc)
                        printf("\n<ОШИБКА> ПЕРЕПОЛНЕНИЕ ОЧЕРЕДИ\n");

                    l_destroy(l_q1);
                    l_destroy(l_q2);
                    a_destroy(a_q1);
                    a_destroy(a_q2);
                }

                printf("\nИтоговое время работы очереди в виде списка: %ld\n", (long)total_list);
                printf("Итоговое время работы очереди в виде массива: %ld\n\n", (long)total_arr);

                printf("Максимальная занимаемая память очередью в виде списка: %zu б\n", ((long)max_mem_list * (sizeof(node_t) + sizeof(long)) + sizeof(l_queue)) * 2);
                printf("Максимальная занимаемая память очередью в виде массива: %zu б\n\n", (N * sizeof(long) + sizeof(a_queue)) * 2);

                break;
            }
            default:
                printf("\n<ОШИБКА> неизвестная команда\n");
            }
    }
    return EXIT_SUCCESS;
}
