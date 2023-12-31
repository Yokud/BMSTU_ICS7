#include "utils.h"

int print_dir_fork(const char *const filename, size_t offset, const ino_t inode)
{
    fprintf(stdout, " ");

    for (size_t i = 0; i < offset; i++)
    {
    	if (i == 0)
    	{
            if (i != offset - 1)
    	    	fprintf(stdout, "├───");
    	    else
    	    	fprintf(stdout, "├─── ");
    	}
    	else if (i != offset - 1)
    	    fprintf(stdout, "───");
    	else
            fprintf(stdout, "─── ");
    }

    if (offset == 0)
    {
        fprintf(stdout, "Root: %s - inode: %li\n", filename, inode);
    }
    else
    {
        fprintf(stdout, "%s - inode: %li\n", filename, inode);
    }

    return OK;
}

char *join_path(const char *base, const char *const file)
{
    int len = strlen(base);
    char *path = malloc(len + strlen(file) + 2);

    if (!path)
    {
        exit(ALLOCATION_ERROR);
    }

    strcpy(path, base);
    path[len] = '/';
    strcpy(path + len + 1, file);

    return path;
}

char *get_dynamic_str(const char *const string, const size_t size)
{
    char *dynamic_str = malloc(size + 1);

    if (!dynamic_str)
    {
        exit(ALLOCATION_ERROR);
    }

    strcpy(dynamic_str, string);
    return dynamic_str;
}
