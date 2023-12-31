#include "walk.h"

static int process_entry(stack_t *const stack, const size_t level, const char *const curr_path, const char *const curr_file)
{
    struct stat statbuf;
    char *path = join_path(curr_path, curr_file);

    if (lstat(path, &statbuf) < 0)
    {
        return LSTAT_ERROR;
    }

    if (S_ISDIR(statbuf.st_mode) != 0)
    {
        item_t element = { path, level };
        push(stack, element);
        return OK;
    }

    free(path);
    return print_dir_fork(curr_file, level, statbuf.st_ino);
}

static void process_dir(stack_t *const stack, const item_t current_element, DIR *dp, struct dirent *dirp)
{
    if ((dp = opendir(current_element.dir)) != NULL)
    {
        while ((dirp = readdir(dp)) != NULL)
        {
            if (strcmp(dirp->d_name, ".") != 0 && strcmp(dirp->d_name, "..") != 0)
            {
                process_entry(stack, current_element.level + 1, current_element.dir, dirp->d_name);
            }
        }
    }
}

int walk_dir(char *pathname)
{
    struct dirent *dirp = NULL;
    DIR *dp = NULL;
    size_t level = 0;

    char *fullpath = get_dynamic_str(pathname, PATH_MAX + 1);
    item_t current_element = { fullpath, level };
    stack_t stack = init();
    push(&stack, current_element);
    struct stat statbuf;

    while (stack.size)
    {
        current_element = pop(&stack);
        char *file;
	
		if (lstat(current_element.dir, &statbuf) < 0)
    	{
    		fprintf(stdout, "Can't get stat from %s\n", current_element.dir);
        	return LSTAT_ERROR;
    	}
    		
        if ((file = strrchr(current_element.dir, '/')))
        {
            print_dir_fork(file + 1, current_element.level, statbuf.st_ino);
        }
        else
        {
            print_dir_fork(current_element.dir, current_element.level, statbuf.st_ino);
        }

        process_dir(&stack, current_element, dp, dirp);
        free(current_element.dir);

        if (dp != NULL && closedir(dp) < 0)
        {
            fprintf(stderr, "Can't close directory %s\n", fullpath);
        }
    }

    free_stack(&stack);
    return OK;
}
