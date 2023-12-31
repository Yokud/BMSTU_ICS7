#include "graphs.h"


int main(void)
{
    graph_t *graph;
    int rc = OK;
    int capital, T;

    setbuf(stdout, NULL);

    printf("Программа предназначена для вычисления множества городов, находящиеся на расстоянии от столицы больше, чем на T.\n"
            "На вход подаётся неорграф, номер вершины(столица) и расстояние Т.\n\n");

    if ((rc = input_graph(&graph)))
    {
        printf("Возникли проблемы с созданием графа\n");
        return rc;
    }
    
    print_graph(graph);

    printf("\nВведите столицу (выберите номер вершины [0, %d]): ", graph->vertexes_count - 1);
    if (scanf("%d", &capital) != 1 || capital < 0 || capital >= graph->vertexes_count)
    {
        printf("Ошибка выбора столицы\n");
        free_graph(graph);
        return INPUT_ERROR;
    }

    printf("Введите минимальное расстояние от столицы(T): ");
    if (scanf("%d", &T) != 1 || T <= 0)
    {
        printf("Ошибка ввода расстояния\n");
        free_graph(graph);
        return INPUT_ERROR;
    }

    cities_on_dist_at_least_T(graph, capital, T);

    free_graph(graph);

    return rc;
}