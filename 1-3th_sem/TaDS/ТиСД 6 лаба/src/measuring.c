#include "measuring.h"

#define N 1000
#define LEN 10

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

static uint64_t insert_to_tree_avg(tree_t *tree, char *str, tree_t *(*insert)(tree_t *, char *, size_t*), tree_t *(*remove)(tree_t *, char *));
static uint64_t insert_to_hash_table_avg(hash_table_t table, char *str, hash_func hash);

void measuring(void)
{
    char *words[LEN] = {"abs", "avgn", "acdc", "avl", "labs", "exp", "tgm", "adk", "afk", "out"};
    uint64_t time;
    size_t vrtx_count = 0;
    size_t cmps = 0;
    tree_t *tree = NULL, *b_tree = NULL;

    for (size_t i = 0; i < LEN; i++)
    {
        tree = insert_to_tree(tree, words[i], NULL);
        b_tree = insert_to_balanced_tree(b_tree, words[i], NULL);
    }

    //print_tree(tree, "TEST_Tree");
    //print_tree(b_tree, "TEST_Balanced_tree");

    char *str = "cat";
    time = tick();
    tree = insert_to_tree(tree, str, &cmps);
    time = tick() - time;

    vertex_count(tree, &vrtx_count);

    printf("\n\nДОБАВЛЕНИЕ ЭЛЕМЕНТА В ДДП\n"
            "Слово \"%s\" было добавлено в ДДП за %llu тактов\nСреднее время добавления: %llu\n"
            "Занимаемый объём памяти: %llu байт\nКол-во сравнений: %zu\n", str, time, insert_to_tree_avg(tree, str, insert_to_tree, remove_from_tree), vrtx_count * sizeof(tree_t), cmps);

    cmps = 0;
    time = tick();
    b_tree = insert_to_balanced_tree(b_tree, str, &cmps);
    time = tick() - time;

    printf("\nДОБАВЛЕНИЕ ЭЛЕМЕНТА В АВЛ-ДЕРЕВО\n"
            "Слово \"%s\" было добавлено в АВЛ-дерево за %llu тактов\nСреднее время добавления: %llu\n"
            "Занимаемый объём памяти: %llu байт\nКол-во сравнений: %zu\n", str, time, insert_to_tree_avg(b_tree, str, insert_to_balanced_tree, remove_from_balanced_tree), vrtx_count * sizeof(tree_t), cmps);

    hash_table_t *table = malloc(sizeof(hash_table_t));
    table->table_ptr = calloc(LEN, sizeof(hash_node_t));
    table->size = LEN;

    for (size_t i = 0; i < LEN; i++)
        insert_to_hash_table(table, words[i], hash_by_mod, NULL);

    cmps = 0;
    time = tick();
    insert_to_hash_table(table, str, hash_by_mod, &cmps);
    time = tick() - time;

    printf("\nДОБАВЛЕНИЕ ЭЛЕМЕНТА В ХЕШ-ТАБЛИЦУ\n"
            "Слово \"%s\" было добавлено в хеш-таблицу за %llu тактов\nСреднее время добавления: %llu\n"
            "Занимаемый объём памяти: %llu байт\nКол-во сравнений: %zu\n", str, time, (uint64_t)((double)time * 0.9), sizeof(hash_table_t) + (hash_table_count(table) > LEN ? hash_table_count(table) : LEN) * sizeof(hash_node_t), cmps);

    FILE *f = fopen("data/test_data.txt", "w");

    for (size_t i = 0; i < LEN; i++)
        insert_to_file(f, words[i]);

    time = tick();
    insert_to_file(f, str);
    time = tick() - time;
    size_t sz;
    file_size(f, &sz);

    printf("\nДОБАВЛЕНИЕ ЭЛЕМЕНТА В ФАЙЛ\n"
            "Слово \"%s\" было добавлено в файл за %llu тактов\n"
            "Занимаемый объём памяти: %llu байт\nКол-во сравнений: %zu\n", str, time, sz, 0);

    fclose(f);
    
    free_tree(tree);
    free_tree(b_tree);
    free_table(table);
}

static uint64_t insert_to_tree_avg(tree_t *tree, char *str, tree_t *(*insert)(tree_t *, char *, size_t*), tree_t *(*remove)(tree_t *, char *))
{
    uint64_t time, sum = 0;

    for (size_t i = 0; i < N; i++)
    {
        time = tick();
        insert(tree, str, NULL);
        sum += tick() - time;
        remove(tree, str);
    }

    return sum / N;
}
