#include "service_unit.h"
#include "assert.h"


double gen_time(double min, double max)
{
    return (double)rand() / (double)RAND_MAX * (max - min) + min;
}

double min(double a, double b)
{
    return a < b ? a : b;
}

double max(double a, double b)
{
    return a > b ? a : b;
}

void printer(stats_t *stats)
{
    printf("Текущая длина первой очереди: %zu\n", stats->in_t1 - stats->out_t1);
    printf("Средняя длина первой очереди: %.1lf\n\n", stats->person_time_t1 / stats->full_work_time);
    printf("Текущая длина второй очереди: %zu\n", stats->in_t2 - stats->out_t2);
    printf("Средняя длина второй очереди: %.1lf\n\n", stats->person_time_t2 / stats->full_work_time);
}

void tick(double *time_t1, double *time_t2, double *su_remain, stats_t *stats)
{
    double diff;

    if (fabs(*su_remain) < EPS)
    {
        diff = min(*time_t1, *time_t2);
        stats->wait_time += diff;
    }
    else
    {
        diff = min(min(*time_t1, *time_t2), *su_remain);
        *su_remain -= diff;
    }

    *time_t1 -= diff;
    *time_t2 -= diff;
    stats->full_work_time += diff;

    stats->person_time_t1 += diff * (stats->in_t1 - stats->out_t1);
    stats->person_time_t2 += diff * (stats->in_t2 - stats->out_t2);
}

void init(stats_t *stats)
{
    stats->in_t1 = stats->in_t2 = stats->out_t1 = stats->out_t2 = 0;
    stats->dumped = 0;

    stats->person_time_t1 = stats->person_time_t2 = 0.0;
    stats->wait_time = stats->full_work_time = 0.0;
}

int unit_sim(void *q1, void *q2, push_fp push, pop_fp pop, empt_fp is_empty, full_fp is_full, size_t count, size_t step, bool verbose, preset_t t, stats_t *stats)
{
    int first_type = FIRST, second_type = SECOND;
    int rc;

    double time_t1 = gen_time(t.ENTRY_TIME_T1_MIN, t.ENTRY_TIME_T1_MAX);
    double time_t2 = gen_time(t.ENTRY_TIME_T2_MIN, t.ENTRY_TIME_T2_MAX);

    double su_remain = 0.0;
    int current_req = 0;

    init(stats);

    while (stats->out_t1 < count)
    {
        if (fabs(time_t1) < EPS)
        {
            if (stats->in_t1 < count)
            {
                stats->in_t1++;
                if (is_full(q1))
                    return QUEUE_OVERFLOW;

                if ((rc = push(q1, &first_type)) != EXIT_SUCCESS)
                    return rc;
            }
            time_t1 = gen_time(t.ENTRY_TIME_T1_MIN, t.ENTRY_TIME_T1_MAX);
        }
        
        if (fabs(time_t2) < EPS)
        {
            if (stats->in_t2 < (t.ENTRY_TIME_T2_MAX + t.PROC_TIME_T2_MAX) * 2 * count)
            {
                stats->in_t2++;
                if (is_full(q2))
                    return QUEUE_OVERFLOW;

                if ((rc = push(q2, &second_type)) != EXIT_SUCCESS)
                    return rc;
            }

            time_t2 = gen_time(t.ENTRY_TIME_T2_MIN, t.ENTRY_TIME_T2_MAX);
        }

        if (fabs(su_remain) < EPS)
        {
            if ((current_req == first_type || (current_req == second_type && is_empty(q2))) && !is_empty(q1))
            {
                su_remain = gen_time(t.PROC_TIME_T1_MIN, t.PROC_TIME_T1_MAX);
                current_req = first_type;

                if ((rc = pop(q1, &current_req)) != EXIT_SUCCESS)
                    return rc;
                stats->out_t1++;

                if (stats->out_t1 % step == 0  && verbose)
                {
                    printf("\nОбработано %zu заявок:\n", stats->out_t1);
                    printer(stats);
                }
            }
            else if ((current_req == second_type || (current_req == first_type && is_empty(q1))) && !is_empty(q2))
            {
                su_remain = gen_time(t.PROC_TIME_T2_MIN, t.PROC_TIME_T2_MAX);
                current_req = second_type;

                if ((rc = pop(q2, &current_req)) != EXIT_SUCCESS)
                    return rc;
                stats->out_t2++;
            }
        }

        tick(&time_t1, &time_t2, &su_remain, stats);
    }
    if (verbose)
    {
        printf("\nВЫЧИСЛЕНИЕ\n");

        double entry_first_type_reqs_time = (t.ENTRY_TIME_T1_MIN + t.ENTRY_TIME_T1_MAX) / 2.0 * count;
        double entry_second_type_reqs_count = entry_first_type_reqs_time / ((t.ENTRY_TIME_T2_MIN + t.ENTRY_TIME_T2_MAX) / 2.0);
        double proc_all_reqs = count * ((t.PROC_TIME_T1_MIN + t.PROC_TIME_T1_MAX) / 2.0) + entry_second_type_reqs_count * ((t.PROC_TIME_T2_MIN + t.PROC_TIME_T2_MAX) / 2.0);
        entry_second_type_reqs_count = stats->in_t2 == (t.ENTRY_TIME_T2_MAX + t.PROC_TIME_T2_MAX) * 2 * count ? stats->in_t2 : entry_second_type_reqs_count;
        double max_proc_time = max(max(entry_first_type_reqs_time, count * (t.PROC_TIME_T1_MIN + t.PROC_TIME_T1_MAX) / 2.0), max(entry_second_type_reqs_count * ((t.PROC_TIME_T2_MIN + t.PROC_TIME_T2_MAX) / 2.0), entry_second_type_reqs_count * ((t.ENTRY_TIME_T2_MIN + t.ENTRY_TIME_T2_MAX) / 2.0)));

        double mod_time = fabs(entry_first_type_reqs_time - proc_all_reqs) < EPS ? proc_all_reqs : max_proc_time;
        printf("Ожидаемое время моделирования: %.1lf\n", mod_time);

        printf("\nМОДЕЛИРОВАНИЕ\n");

        printf("Время моделирования: %.1lf\n", stats->full_work_time);
        printf("Время простоя: %.1lf\n", stats->wait_time);
        printf("Среднее время обслуживания заявки: %4.1lf\n\n", (stats->full_work_time - stats->wait_time) / (double)(stats->in_t1 + stats->in_t2));

        printf("       ПЕРВАЯ   ВТОРАЯ\n");
        printf("Вошло: %5zu    %5zu\n", stats->in_t1, stats->in_t2);
        printf("Вышло: %5zu    %5zu\n\n", stats->out_t1, stats->out_t2);

        printf("ПОГРЕШНОСТЬ: %.3lf%%\n\n", fabs(stats->full_work_time - mod_time) / mod_time * 100.0);
    }
    return EXIT_SUCCESS;
} 
