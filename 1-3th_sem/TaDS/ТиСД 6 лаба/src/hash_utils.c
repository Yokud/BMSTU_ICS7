#include "hash_utils.h"

size_t hash_by_mod(char *word, size_t m)
{
    size_t sum = 0;

    while (*word)
        sum += *word++;

    return sum % m;
}

size_t hash_by_ring_polynom(char *word, size_t m)
{
    size_t hash = 0;

    while (*word)
        hash = ((hash << 6) + *word++) % m;

    return hash;
}

size_t hash_table_count(hash_table_t *table)
{
    size_t count = 0;

    if (table && table->table_ptr)
        for (size_t i = 0; i < table->size; i++)
            if (table->table_ptr[i].value)
            {
                count++;

                if (table->table_ptr[i].next_elem)
                {
                    hash_node_t *temp = table->table_ptr[i].next_elem;
                    while (temp != NULL)
                    {
                        count++;
                        temp = temp->next_elem;
                    }
                }
            }

    return count;
}

int insert_to_hash_table(hash_table_t *table, char *word, hash_func hash, size_t *cmps)
{
    size_t temp_hash = hash(word, table->size);

    if (!table->table_ptr[temp_hash].value)
    {
        cmps ? (*cmps)++ : 0;
        table->table_ptr[temp_hash].value = str_dup(word);
        table->table_ptr[temp_hash].next_elem = NULL;
    }
    else
    {
        hash_node_t *temp;
        for (temp = &table->table_ptr[temp_hash]; temp->next_elem; temp = temp->next_elem)
            cmps ? (*cmps)++ : 0;

        temp->next_elem = malloc(sizeof(hash_node_t));

        if (!temp->next_elem)
            return ALLOC_ERROR;
        else
            temp = temp->next_elem;
        
        temp->value = str_dup(word);
        temp->next_elem = NULL;
    }
    
    return OK;
}

hash_table_t *create_hash_table(FILE *f, size_t size, hash_func hash)
{
    if (!f)
        return NULL;

    hash_table_t *table = malloc(sizeof(hash_table_t));
    table->table_ptr = calloc(size, sizeof(hash_node_t));
    table->size = size;

    char *temp_word;
    size_t word_len;

    while (!feof(f))
    {
        if (!getline(&temp_word, &word_len, f))
            insert_to_hash_table(table, temp_word, hash, NULL);
        else
        {
            free_table(table);
            table = NULL;
        }
    }

    return table;
}

hash_node_t *search_in_hash_table(hash_table_t *table, char *word, hash_func hash)
{
    if (!table)
        return NULL;

    size_t temp_hash = hash(word, table->size);

    if ((table->table_ptr + temp_hash)->value)
    {
        if (strcmp(word, (table->table_ptr + temp_hash)->value))
        {
            for (hash_node_t *temp = (table->table_ptr + temp_hash)->next_elem; temp; temp = temp->next_elem)
                if (!strcmp(temp->value, word))
                    return temp;
            
            return NULL;
        }
        else
            return table->table_ptr + temp_hash;
    }
    else
        return NULL;
}

void print_hash_table(hash_table_t *table)
{
    if (!table)
    {
        printf("Хеш-таблица пуста\n");
        return;
    }

    printf("\n\tХЕШ-ТАБЛИЦА\n");
    printf("==============================\n");
    printf("\tКЛЮЧ | СЛОВО\n");
    for (size_t i = 0; i < table->size; i++)
    {
        if (table->table_ptr[i].value)
        {
            printf("%12zu | %s", i, table->table_ptr[i].value);

            if (table->table_ptr[i].next_elem)
            {
                hash_node_t *temp = table->table_ptr[i].next_elem;
                while (temp != NULL)
                {
                    printf(" %s", temp->value);
                    temp = temp->next_elem;
                }
            }
            printf("\n");
        }
        else
            printf(" %s | %s\n", "(нет ключа)", "(пусто)");
    }
    printf("\n");
}

static void free_list(hash_node_t *head)
{
    hash_node_t *next;

    for (; head; head = next)
    {
        next = head->next_elem;
        free(head);
    }
}

void free_table(hash_table_t *table)
{
    if (!table)
        return;

    for (size_t i = 0; i < table->size; i++)
        free_list((table->table_ptr + i)->next_elem);

    free(table->table_ptr);
    free(table);
}
