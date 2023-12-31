#include "trees.h"
#include "file_utils.h"
#include "hash_utils.h"
#include "measuring.h"

int main(void)
{
    int op = -1, rc;
    tree_t *tree = NULL, *balanced_tree = NULL;
    hash_table_t *hash_table = NULL;
    long size;
    hash_func hash = hash_by_mod;
    char *string = NULL;
    size_t string_len;
    FILE *f;
    uint64_t tick_temp;
    tree_t *temp_tree_node;
    hash_node_t *temp_hash_node;
    char c;

    setbuf(stdout, NULL);

    printf("Программа предназначена для работы с деревом и хеш-таблицей. Дерево и хеш-таблица состоят из слов, записанные в "
            "текстовый файл. Каждое слово в файле должно быть записано с новой строки.\nПрограмма позволяет выводить"
            " текущие деревья в файлы формата .gv, где они представлены графическим изображением. Также программа позволяет "
            "сравнить эффективность работы обычных и сбалансированных деревьев, хеш-таблицы и файла.\n");

    while (op)
    {
        printf("\nДействия:"
                "\n\t 1 - Создать дерево и сбалансированное дерево по данным из файла"
                "\n\t 2 - Вывести деревья в файлы .gv"
                "\n\t 3 - Произвести прямой обход по деревьям"
                "\n\t 4 - Добавить слово в деревья"
                "\n\t 5 - Удалить из деревьев слово"
                "\n\t 6 - Найти слово в дереве"
                "\n\n\t 7 - Создать хеш-таблицу по данным из файла"
                "\n\t 8 - Вывести хеш-таблицу на экран"
                "\n\t 9 - Добавить слово в хеш-таблицу"
                "\n\t 10 - Найти слово в хеш-таблице"
                "\n\t 11 - Изменить хеш-функцию и (пере)создать таблицу"
                "\n\n\t 12 - Сравнить эффективность работы обычных и сбалансированных деревьев, хеш-таблицы и файла"
                "\n\t 0 - Выход");
        
        printf("\n\nВаше действие: ");
        
        if (scanf("%d", &op) != 1)
        {
            printf("Ошибка ввода команды\n");
            fflush(stdin);
            continue;
        }
        fflush(stdin);
        switch (op)
        {
            case 1:
                printf("\nВведите название файла: ");
                if ((rc = getline(&string, &string_len, stdin)))
                {
                    printf("Ошибка ввода названия\n");
                    free(string);
                    string = NULL;
                    break;
                }

                if ((f = fopen(string, "r")))
                {
                    tree = create_tree(f);
                    rewind(f);
                    balanced_tree = create_balance_tree(f);

                    if (tree && balanced_tree)
                        printf("\nДеревья успешно созданы\n");
                    else
                    {
                        printf("Возникли проблемы с созданием деревьев\n");
                        free_tree(tree);
                        free_tree(balanced_tree);
                    }

                    fclose(f);
                }
                else
                    printf("Файл не найден\n");
                free(string);
                string = NULL;
                break;

            case 2:
                print_tree(tree, "Tree");
                print_tree(balanced_tree, "Balanced_tree");
                printf("\nЕсли не возникло ошибок, то деревья успешно распечатаны в файлы \"Tree.png\" и \"Balanced_tree.png\".\n"
                "P. S. Красная дуга - левое поддерево, синяя дуга - правое поддерево\n");
                break;

            case 3:
                printf("\nРезультат:\n");
                printf("\tИсходное дерево: ");
                traversal_tree(tree);
                putchar('\n');
                printf("\tСбалансированное дерево: ");
                traversal_tree(balanced_tree);
                putchar('\n');
                break;

            case 4:
                printf("Введите слово: ");
                if (getline(&string, &string_len, stdin))
                {
                    printf("Ошибка ввода слова\n");
                    free(string);
                    string = NULL;
                    break;
                }

                tree = insert_to_tree(tree, string, NULL);
                balanced_tree = insert_to_balanced_tree(balanced_tree, string, NULL);
                printf("\nСлово \"%s\" успешно вставлено в деревья\n", string);
                free(string);
                string = NULL;
                break;

            case 5:
                printf("Введите слово: ");
                if (getline(&string, &string_len, stdin))
                {
                    printf("Ошибка ввода слова\n");
                    free(string);
                    string = NULL;
                    break;
                }

                temp_tree_node = search_in_tree(tree, string);
                if (!temp_tree_node)
                    printf("\nТакого слова в деревьях нет");
                else
                {
                    tree = remove_from_tree(tree, string);
                    balanced_tree = remove_from_balanced_tree(balanced_tree, string);
                    printf("\nСлово \"%s\" из деревьев успешно удалено\n", string);
                }
                free(string);
                string = NULL;
                break;

            case 6:
                printf("Введите слово: ");
                if (getline(&string, &string_len, stdin))
                {
                    printf("Ошибка ввода слова\n");
                    free(string);
                    string = NULL;
                    break;
                }
                tick_temp = tick();
                temp_tree_node = search_in_tree(tree, string);
                tick_temp = tick() - tick_temp;

                if (!temp_tree_node)
                {
                    printf("\nТакого слова в дереве нет\n\nХотите его добавить? (Y/n): ");
                    c = getchar();

                    if (c == 'Y')
                    {
                        tree = insert_to_tree(tree, string, NULL);
                        balanced_tree = insert_to_balanced_tree(balanced_tree, string, NULL);
                        printf("Слово \"%s\" успешно вставлено в деревья\n", string);
                    }
                    else if (c == 'n')
                        printf("Как пожелаете\n");
                    else
                        printf("Ошибка ввода ответа\n");
                }
                else
                {
                    uint64_t tick_temp_1 = tick();
                    tree_t *temp_tree_node_1 = search_in_tree(balanced_tree, string);
                    tick_temp_1 = tick() - tick_temp_1;
                    printf("\nСлово \"%s\" было найдено в ДДП за %llu тактов на высоте %zu\n", temp_tree_node->word, tick_temp, temp_tree_node->height);
                    printf("Слово \"%s\" было найдено в АВЛ-дереве за %llu тактов на высоте %zu\n", temp_tree_node_1->word, tick_temp_1, temp_tree_node_1->height);
                }
                free(string);
                string = NULL;
                break;

            case 7:
                printf("\nВведите название файла: ");
                if (getline(&string, &string_len, stdin))
                {
                    printf("Ошибка ввода названия\n");
                    free(string);
                    string = NULL;
                    break;
                }

                printf("Введите размерность хеш-таблицы: ");
                if (scanf("%ld", &size) != 1 || size <= 0)
                {
                    printf("Ошибка ввода размерности\n");
                    free(string);
                    string = NULL;
                    break;
                }

                if ((f = fopen(string, "r")))
                {
                    hash_table = create_hash_table(f, size, hash);

                    if (hash_table)
                        printf("Хеш-таблица успешно создана\n");
                    else
                        printf("Возникли проблемы с созданием хеш-таблицы\n");

                    fclose(f);
                }
                else
                    printf("Файл не найден\n");
                free(string);
                string = NULL;
                break;

            case 8:
                print_hash_table(hash_table);
                break;

            case 9:
                printf("Введите слово: ");
                if (getline(&string, &string_len, stdin))
                {
                    printf("Ошибка ввода слова\n");
                    free(string);
                    string = NULL;
                    break;
                }
                if (!insert_to_hash_table(hash_table, string, hash, NULL))
                    printf("Слово \"%s\" было успешно добавлено в хеш-таблицу\n", string);
                else
                    printf("Возникла ошибка при вставки слова\n");
                free(string);
                string = NULL;
                break;

            case 10:
                printf("Введите слово: ");
                if (getline(&string, &string_len, stdin))
                {
                    printf("Ошибка ввода слова\n");
                    free(string);
                    string = NULL;
                    break;
                }
                tick_temp = tick();
                temp_hash_node = search_in_hash_table(hash_table, string, hash);
                tick_temp = tick() - tick_temp;
                if (!temp_hash_node)
                    printf("Такого слова в хеш-таблице нет\n");
                else
                    printf("Слово \"%s\" было найдено с хешем %zu за %llu тактов\n", temp_hash_node->value, hash(temp_hash_node->value, hash_table->size), tick_temp);
                free(string);
                string = NULL;
                break;

            case 11:
                printf("По умолчанию для вычисления хеша используется метод деления.\n Хотите его заменить на метод Горнера? (Y/n): ");
                c = getchar();
                if (c == 'Y')
                {
                    hash = hash_by_ring_polynom;
                    printf("Хеш-функция успешно изменена\n");
                    free(hash_table);
                    printf("\nВведите название файла: ");
                    fflush(stdin);
                    if (getline(&string, &string_len, stdin))
                    {
                        printf("Ошибка ввода названия %d\n", rc);
                        free(string);
                        string = NULL;
                        break;
                    }

                    printf("Введите размерность хеш-таблицы: ");
                    if (scanf("%ld", &size) != 1 || size <= 0)
                    {
                        printf("Ошибка ввода размерности\n");
                        free(string);
                        string = NULL;
                        break;
                    }

                    if ((f = fopen(string, "r")))
                    {
                        hash_table = create_hash_table(f, size, hash);
                        if (hash_table)
                            printf("Хеш-таблица успешно создана\n");
                        else
                            printf("Возникли проблемы с созданием хеш-таблицы\n");

                        fclose(f);
                    }
                    else
                        printf("Файл не найден\n");
                    free(string);
                    string = NULL;
                }
                else if (c == 'n')
                    printf("Как пожелаете\n");
                else
                    printf("Ошибка ввода ответа\n");
                break;

            case 12:
                measuring();
                break;

            case 0:
                printf("Завершение работы\n");
                free_tree(tree);
                free_tree(balanced_tree);
                free_table(hash_table);
                free(string);
                break;

            default:
                printf("Неизвестное действие\n");
                break;
        }
    }
}