/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** save.c
*/

#include "ftrace/vector.h"
#include <unistd.h>

/**
 * Save the content of a vector to a file.
 * To later retrieve the content you should use the function
 * vector_load_content.
 * @param array The vector to save
 * @param file The file to save to
 * @param save_func The function that will be applied to each element
 * of the vector. This function will write the content of an element
 * of the vector at its own discretion.
 * @note save_func will write the elements, remember to create an equivalent
 * of this function for vector_load_content to load an
 * element using the same data scheme.
 * @return 1 on error, 0 otherwise
 */
int vector_save_content(vector_template_t *array, FILE *file,
    vector_func_save_t save_func)
{
    if (s_fwrite(&array->len, sizeof(array->len), file))
        return 1;
    for (size_t i = 0; i < array->len; ++i) {
        if (save_func(array->content[i], file))
            return 1;
    }
    return 0;
}

/**
 * Load the content of a file to a vector.
 * The content of the part of the file to read should have been
 * written by the vector_save_content function.
 * @warning array must already be init!
 * @param array The vector in which data should be loaded
 * @param file The file to read
 * @param load_func The function that will be applied to each element
 * of the file. This function will parse each part of the file at
 * its own discretion.
 * @return 1 on error, 0 otherwise
 */
int vector_load_content(vector_template_t *array, FILE *file,
    vector_func_load_t load_func)
{
    size_t len = 0;
    if (s_fread(&len, sizeof(len), file))
        return 1;
    void *el;
    for (size_t i = 0; i < len; ++i) {
        el = load_func(file);
        if (el == NULL)
            return 1;
        vector_push_back(array, el);
    }
    if (array->len != len)
        return 1;
    return 0;
}
