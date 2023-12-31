#ifndef TREES_H
#define TREES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alloc_strings.h"

#define OK 0
#define INPUT_ERROR -1

typedef struct tree_node
{
    char *word;
    size_t height;
    struct tree_node *left;
    struct tree_node *right;
} tree_t;

tree_t *create_node(char *val);
tree_t *create_tree(FILE *f);
tree_t *insert_to_tree(tree_t *tree, char *val, size_t *cmps);
tree_t *search_in_tree(tree_t *root, char *word);
tree_t *remove_from_tree(tree_t *root, char *val);
void vertex_count(tree_t *root, size_t *n);

tree_t *balance_tree(tree_t *root);
tree_t *create_balance_tree(FILE *f);
tree_t *insert_to_balanced_tree(tree_t *node, char *val, size_t *cmps);
tree_t *remove_from_balanced_tree(tree_t *root, char *val);
void free_tree(tree_t *node);
void print_tree(tree_t *root, char *name);
void traversal_tree(tree_t *root);


#endif