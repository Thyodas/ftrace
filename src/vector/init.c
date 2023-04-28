/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** init.c
*/

#include "ftrace/vector.h"

/**
 * @brief Resize dynamic array to new_len.
 * @param array The array. It MUST have been init with vector_init.
 * @param new_len The new size of the array.
 * @return -1 in case of error else 0
 */
int vector_resize(vector_template_t *array, size_t new_len)
{
    array->content = realloc(array->content, sizeof(void *) * new_len);
    if (array->content == NULL) {
        array->len = 0;
        return -1;
    }
    array->len = new_len;
    return 0;
}

/**
 * @brief Init the dynamic array.
 * @note It is up to you to handle the memory of the base struct.
 * You can create your own structure with the same field as
 * dynamic_array_template_t but with a different type for the pointer of
 * content.
 * @param array
 * @param element_size
 * @return -1 in case of error else 0
 */
int vector_init(vector_template_t *array, size_t element_size)
{
    array->len = 0;
    array->element_size = element_size;
    array->content = NULL;
    return 0;
}

/**
 * @brief Frees the content of the array, not the struct passed as parameter.
 * All the structures added via pointer are also freed.
 * @note The container can be reused as it is re-init after freeing its
 * elements.
 * @param array The array. It MUST have been init with vector_init.
 * @return -1 in case of error else 0
 */
int vector_free_content(vector_template_t *array)
{
    if (array->content == NULL)
        return -1;
    for (size_t i = 0; i < array->len; ++i)
        free(array->content[i]);
    free(array->content);
    array->content = NULL;
    array->len = 0;
    return 0;
}
