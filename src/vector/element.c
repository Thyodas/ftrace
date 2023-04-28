/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** element.c
*/

#include "ftrace/vector.h"

/**
 * @brief Add element pointer to the back of the array.
 * @param array The array. It MUST have been init with vector_init.
 * @param element Pointer to a malloced element
 * @return -1 in case of error else 0
 */
int vector_push_back(vector_template_t *array, void *element)
{
    if (vector_resize(array, array->len + 1))
        return -1;
    array->content[array->len - 1] = element;
    return 0;
}

/**
 * @brief Remove last element of the array.
 * @param array The array. It MUST have been init with vector_init.
 * @return NULL in case of error, else the removed element.
 */
void *vector_pop_back(vector_template_t *array)
{
    if (array->len == 0)
        return NULL;
    return vector_remove_by_pos(array, array->len - 1);
}

/**
 * @brief Add a copy of data from element to the back of the array.
 * This function uses malloc to duplicate data from element.
 * @param array The array. It MUST have been init with vector_init.
 * @param element Pointer
 * @return -1 in case of error else 0
 */
int vector_push_back_copy(vector_template_t *array, void *element)
{
    if (vector_resize(array, array->len + 1))
        return -1;
    void *new_element = malloc(array->element_size);
    memcpy(new_element, element, array->element_size);
    array->content[array->len - 1] = new_element;
    return 0;
}

/**
 * @brief Remove an element at index pos from the array.
 * @param array The array. It MUST have been init with vector_init.
 * @param pos Index of the element to remove from the vectorize.
 * @return NULL in case of error, else the removed element.
 */
void *vector_remove_by_pos(vector_template_t *array, size_t pos)
{
    if (pos >= array->len)
        return NULL;
    void *removed = array->content[pos];
    memmove(array->content + pos, array->content + pos + 1,
        (array->len - pos - 1) * sizeof(void *));
    --array->len;
    return removed;
}

/**
 * @brief Remove a pointer to an element from the array.
 * @param array The array. It MUST have been init with vector_init.
 * @param ptr The pointer to remove
 * @return NULL in case of error, else the removed element.
 */
void *vector_remove_by_ptr(vector_template_t *array, void *ptr)
{
    size_t i = 0;
    if (array->len == 0)
        return NULL;
    for (; array->content[i] != ptr; ++i)
        if (i >= array->len)
            return NULL;
    return vector_remove_by_pos(array, i);
}
