#include "trees.h"

tree_t* create_node(char *val)
{
    tree_t *node = malloc(sizeof(struct tree_node));
    if (node)
    {
        node->word = str_dup(val);
        node->height = 0;
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

void vertex_count(tree_t *root, size_t *n)
{
    if (!root)
        return;
    
    (*n)++;

    vertex_count(root->left, n);
    vertex_count(root->right, n);
}

tree_t *insert_to_tree(tree_t *tree, char *val, size_t *cmps)
{
    int diff;

    if (!tree)
        return create_node(val);
    if (!val)
        return tree;

    diff = strcmp(tree->word, val);
    cmps ? (*cmps)++ : 0;

    if (diff < 0)
    {
        tree->left = insert_to_tree(tree->left, val, cmps);
        tree->left->height = tree->height + 1;
    }
    else if (diff > 0)
    {
        tree->right = insert_to_tree(tree->right, val, cmps);
        tree->right->height = tree->height + 1;
    }

    return tree;
}

tree_t *create_tree(FILE *f)
{ 
    if (!f)
        return NULL;

    tree_t *tree = NULL;
    char *temp_word;
    size_t word_len;

    while (!feof(f))
    {
        if (!getline(&temp_word, &word_len, f))
            tree = insert_to_tree(tree, temp_word, NULL);
        else
        {
            free_tree(tree);
            tree = NULL;
            break;
        }
    }

    return tree;
}

static void print_node(tree_t *node, FILE *f);

void print_tree(tree_t *root, char *name)
{
    if (!root)
    {
        printf("Попытка печати пустого дерева\n");
        return;
    }

    char *gv_name = str_dup(name);
    gv_name = realloc(gv_name, (strlen(gv_name) + 3) * sizeof(char));
    gv_name = strcat(gv_name, ".gv");

    FILE *f = fopen(gv_name, "w");
    char *send_to_system = malloc(150 * sizeof(char));

    fprintf(f, "digraph %s {\n", "Words");

    print_node(root, f);

    fprintf(f, "}\n");

    fclose(f);
    
    char *png_name = str_dup(name);
    png_name = realloc(png_name, (strlen(png_name) + 3) * sizeof(char));
    png_name = strcat(png_name, ".png");

    snprintf(send_to_system, 150, "dot %s -Tpng -o %s\nopen %s\n", gv_name, png_name, png_name);
    free(gv_name);
    free(png_name);
    system(send_to_system);
}

static void print_node(tree_t *node, FILE *f)
{
    if (!node)
        return;

    if (node->left)
        fprintf(f, "%s -> %s [color = red];\n", node->word, node->left->word);

    if (node->right)
        fprintf(f, "%s -> %s [color = blue];\n", node->word, node->right->word);

    print_node(node->left, f);
    print_node(node->right, f);
}

static void fixheight(tree_t *p);

tree_t *insert_to_balanced_tree(tree_t *node, char *val, size_t *cmps)
{
    if (!node)
        return create_node(val);
    if (!val)
        return node;
    cmps ? (*cmps)++ : 0;
    if (strcmp(node->word, val) < 0)
    {
        node->left = insert_to_balanced_tree(node->left, val, cmps);
        fixheight(node->left);
    }
    else
    {
        node->right = insert_to_balanced_tree(node->right, val, cmps);
        fixheight(node->right);
    }

    return balance_tree(node);
}

void free_tree(tree_t *node)
{
    if (!node)
        return;
    
    free(node->word);
    free_tree(node->left);
    free_tree(node->right);

    free(node);
}

tree_t *search_in_tree(tree_t *root, char *word)
{
    int cmp;

    if (!root)
        return NULL;

    cmp = strcmp(root->word, word);
    if (cmp == 0)
        return root;
    else if (cmp < 0)
        return search_in_tree(root->left, word);
    else
        return search_in_tree(root->right, word);
}

void traversal_tree(tree_t *root)
{
    if (!root)
        return;
    
    printf("%s ", root->word, root->height);

    traversal_tree(root->left);
    traversal_tree(root->right);
}

static size_t height(tree_t *p)
{
	return p ? p->height : 0;
}

static long long bfactor(tree_t *p)
{
	return height(p->right) - height(p->left);
}

static void fixheight(tree_t *p)
{
	size_t hl = height(p->left);
	size_t hr = height(p->right);
	p->height = ( hl > hr ? hl : hr ) + 1;
}

static tree_t *rotateright(tree_t *p)
{
	tree_t *q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

static tree_t *rotateleft(tree_t *q)
{
	tree_t *p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

tree_t *create_balance_tree(FILE *f)
{
    if (!f)
        return NULL;

    tree_t *tree = NULL;
    char *temp_word;
    size_t word_len;

    while (!feof(f))
    {
        if (!getline(&temp_word, &word_len, f))
            tree = insert_to_balanced_tree(tree, temp_word, NULL);
        else
        {
            free_tree(tree);
            tree = NULL;
            break;
        }
    }

    return tree;
}

tree_t *balance_tree(tree_t *p)
{
    if (!p)
        return NULL;

	fixheight(p);
	if(bfactor(p) >= 2)
	{
		if(bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if(bfactor(p) <= -2)
	{
		if(bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}

	return p;
}

static tree_t *minimum(tree_t *root)
{
    if (!root->left)
        return root;
    
    return minimum(root->left);
}

tree_t *remove_from_tree(tree_t *root, char *val)
{
    if (!root)
        return NULL;

    if (strcmp(root->word, val) < 0)
        root->left = remove_from_tree(root->left, val);
    else if (strcmp(root->word, val) > 0)
        root->right = remove_from_tree(root->right, val);
    else if (root->left && root->right)
    {
        root->word = minimum(root->right)->word;
        root->right = remove_from_tree(root->right, root->word);
    }
    else
    {
        tree_t *temp;

        if (root->left)
        {
            temp = root;
            root = root->left;
            free(temp);
        }
        else if (root->right)
        {
            temp = root;
            root = root->right;
            free(temp);
        }
        else
        {
            free(root);
            root = NULL;
        }
    }
    
    return root;
}

static tree_t *removemin(tree_t *p)
{
	if(!p->left)
		return p->right;
	p->left = removemin(p->left);
	return balance_tree(p);
}

tree_t *remove_from_balanced_tree(tree_t *root, char *val)
{
    if(!root)
        return NULL;

	if (strcmp(root->word, val) < 0)
        root->left = remove_from_balanced_tree(root->left, val);
    else if (strcmp(root->word, val) > 0)
        root->right = remove_from_balanced_tree(root->right, val);	
	else
	{
		tree_t *q = root->left;
		tree_t *r = root->right;
		free(root);

		if(!r) 
            return q;

		tree_t *min = minimum(r);
		min->right = removemin(r);
		min->left = q;
		return balance_tree(min);
	}
	return balance_tree(root);
}