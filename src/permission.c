/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** permission.c
*/

#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

static bool check_permission(const char *path)
{
    struct stat sb;
    if (stat(path, &sb) == -1)
        return false;
    bool is_directory = (sb.st_mode & S_IFMT) == S_IFDIR;
    return (!is_directory && access(path, X_OK) == 0);
}

/**
 * Get malloced absolute path of the executable in argument.
 * This function will check for the executable name in all directories
 * referenced in the PATH env variable.
 * If executable cannot be executed it will not be taken into account.
 * @param executable_name Name of the executable to find in PATH and execute.
 * @return Malloced absolute path of the executable. NULL is returned in case
 * of error.
 */
char *get_executable_absolute_path(const char *executable_name)
{
    char *path_env = getenv("PATH");
    if (path_env == NULL)
        return NULL;
    char *path_env_copy = strdup(path_env);
    if (path_env_copy == NULL)
        return NULL;
    for (char *dir = strtok(path_env_copy, ":"); dir != NULL;
        dir = strtok(NULL, ":")) {
        char p_path[FILENAME_MAX];
        snprintf(p_path, sizeof(p_path), "%s/%s", dir, executable_name);
        if (check_permission(p_path)) {
            free(path_env_copy);
            return strdup(p_path);
        }
    }
    free(path_env_copy);
    return NULL;
}

/**
 * Get malloced executable path.
 * If executable doesn't start with . or / it will try to find it in PATH.
 * @param executable_name The path or name of the executable.
 * @return Malloced path to executable.
 */
char *get_executable(const char *executable_name)
{
    if (executable_name[0] == '.' || executable_name[0] == '/') {
        if (check_permission(executable_name))
            return strdup(executable_name);
        else
            return NULL;
    }
    return get_executable_absolute_path(executable_name);
}
