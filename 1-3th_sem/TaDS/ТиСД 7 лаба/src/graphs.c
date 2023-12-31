#include "graphs.h"

int input_graph(graph_t **graph)
{
    if (!graph)
        return INPUT_ERROR;

    *graph = malloc(sizeof(graph_t));
    if (!(*graph))
        return ALLOC_ERROR;

    printf("\nВведите кол-во городов(число вершин): ");
    if (scanf("%ld", &(*graph)->vertexes_count) != 1 || (*graph)->vertexes_count <= 1)
        return INPUT_ERROR;

    (*graph)->adjacency = calloc((*graph)->vertexes_count, sizeof(int *));
    (*graph)->markers = malloc((*graph)->vertexes_count * sizeof(int));

    if (!(*graph)->adjacency || !(*graph)->markers)
    {
        free(*graph);
        *graph = NULL;
        return ALLOC_ERROR;
    }

    for (int i = 0; i < (*graph)->vertexes_count; i++)
    {
        (*graph)->adjacency[i] = calloc((*graph)->vertexes_count, sizeof(int));

        if (!(*graph)->adjacency[i])
        {
            free_graph(*graph);
            *graph = NULL;
            return ALLOC_ERROR;
        }
    }

    printf("\nВНИМАНИЕ: Нулевое или отрицательное значение стоимости - отсутствие ребра между вершинами.\n");

    for (int i = 0; i < (*graph)->vertexes_count - 1; i++)
    {
        printf("Ввод рёбер от %d-й вершины:\n", i);
        for (int j = i + 1; j < (*graph)->vertexes_count; j++)
        {
            int value;
            printf("\tВведите стоимость ребра от %ld-й вершины до %ld-й: ", i, j);
            if (scanf("%d", &value) != 1)
            {
                free_graph(*graph);
                *graph = NULL;
                return INPUT_ERROR;
            }
            else if (value > 0)
                (*graph)->adjacency[i][j] = (*graph)->adjacency[j][i] = value;
        }
    }

    return OK;
}

int is_connective(graph_t *graph)
{
    for (int i = 0; i < graph->vertexes_count; i++)
    {
        int has_zero_str = 0;
        for (int j = 0; j < graph->vertexes_count; j++)
            has_zero_str += graph->adjacency[i][j];
        
        if (!has_zero_str)
            return 0;
    }

    return 1;
}

int get_min_costs(graph_t *graph, int num_of_vrtx)
{
    if (!is_connective(graph))
    {
        printf("Ошибка: граф не является связным\n");
        return GRAPH_ERROR;
    }

    int *is_visited = calloc(graph->vertexes_count, sizeof(int));

    if (!is_visited)
        return ALLOC_ERROR;

    for (int i = 0; i < graph->vertexes_count; i++)
        graph->markers[i] = INT_MAX;
    
    graph->markers[num_of_vrtx] = 0;

    for (int i = 0; i < graph->vertexes_count; i++)
    {
        int v = -1;
        for (int j = 0; j < graph->vertexes_count; j++)
        {
            if (!is_visited[j] && (v == -1 || graph->markers[j] < graph->markers[v]))
                v = j;
        }
        
        is_visited[v] = 1;
        for (int e = 0; e < graph->vertexes_count; e++)
            if (graph->adjacency[v][e] && graph->markers[v] + graph->adjacency[v][e] < graph->markers[e])
                graph->markers[e] = graph->markers[v] + graph->adjacency[v][e];
    }

    free(is_visited);

    return OK;
}

void print_graph(graph_t *graph)
{
    if (!graph)
    {
        printf("Попытка печати пустого графа!\n");
        return;
    }

    FILE *f = fopen("Cities.gv", "w");
    char *send_to_system = malloc(150 * sizeof(char));

    fprintf(f, "digraph %s {\n", "Cities");

    for (int i = 0; i < graph->vertexes_count - 1; i++)
    {
        for (int j = i + 1; j < graph->vertexes_count; j++)
        {
            if (graph->adjacency[i][j])
            {
                fprintf(f, "%d -> %d [dir = none, label = %d];\n", i, j, graph->adjacency[i][j]);
           }
        }
    }

    for (int i = 0; i < graph->vertexes_count; i++)
        fprintf(f, "%d;\n", i);

    fprintf(f, "}\n");

    fclose(f);
    

    snprintf(send_to_system, 150, "dot %s -Tpng -o %s\n", "Cities.gv", "Cities.png");
    system(send_to_system);
}

void cities_on_dist_at_least_T(graph_t *graph, int capital, int T)
{
    if (!graph)
    {
        printf("Пустой граф!\n");
        return;
    }

    uint64_t start, end, time;
    start = tick();
    int rc = get_min_costs(graph, capital);
    end = tick();

    if (rc)
    {
        printf("Возникли проблемы с поиском городов\n");
        return;
    }

    int *cities = calloc(graph->vertexes_count, sizeof(int));
    if (!cities)
    {
        printf("Ошибка выделения памяти\n");
        return;
    }

    printf("\nГорода, находящиеся от города %d дальше, чем на %d: ", capital, T);
    int has_cities = 0;
    for (int i = 0; i < graph->vertexes_count; i++)
        if (graph->markers[i] > T)
        {
            printf("%d ", i);
            cities[i] = 1;
            has_cities = 1;
        }
    if (!has_cities)
        printf("таких городов нет");
    putchar('\n');

    time = end - start;
    size_t volume = sizeof(graph_t) + (graph->vertexes_count + 1) * graph->vertexes_count * sizeof(int);
    printf("\nВремя выполнения программы(в тактах): %llu\nЗанимаемый объём памяти(в байтах): %zu\n", time, volume);

    FILE *f = fopen("Answer.gv", "w");
    char *send_to_system = malloc(150 * sizeof(char));

    fprintf(f, "digraph %s {\n", "Cities");

    for (int i = 0; i < graph->vertexes_count - 1; i++)
    {
        for (int j = i + 1; j < graph->vertexes_count; j++)
        {
            if (graph->adjacency[i][j])
                fprintf(f, "%d -> %d [dir = none, label = %d];\n", i, j, graph->adjacency[i][j]);
        }
    }

    fprintf(f, "%d [style=filled, color=red]\n", capital);

    for (int i = 0; i < graph->vertexes_count; i++)
        if (cities[i])
            fprintf(f, "%d [style=filled, color=blue];\n", i, graph->markers[i]);
        else
            fprintf(f, "%d;\n", i, graph->markers[i]);

    fprintf(f, "}\n");

    fclose(f);
    

    snprintf(send_to_system, 150, "dot %s -Tpng -o %s\n", "Answer.gv", "Answer.png");
    system(send_to_system);
}

void free_graph(graph_t *graph)
{
    if (!graph)
        return;

    for (size_t i = 0; i < graph->vertexes_count; i++)
        free(graph->adjacency[i]);

    free(graph->adjacency);
    free(graph);
}