/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** dynamic_list.h
*/

#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

/**
 * @brief Representation of a dynamic list
 * @note It is recommended to use another struct that follows the same layout
 * but with another type than void.
 * e.g.: my_struct_t **content;
 */
typedef struct {
    size_t len;
    size_t element_size;
    void **content;
} vector_template_t;

int vector_resize(vector_template_t *array, size_t new_len);
int vector_push_back(vector_template_t *array, void *element);
void *vector_pop_back(vector_template_t *array);
int vector_push_back_copy(vector_template_t *array, void *element);
void *vector_remove_by_pos(vector_template_t *array, size_t pos);
void *vector_remove_by_ptr(vector_template_t *array, void *ptr);
int vector_init(vector_template_t *array, size_t element_size);
int vector_free_content(vector_template_t *array);

/**
 * Safely write to a file.
 * This function is similar to fwrite but returns an error if EOF was reached
 * or if the buffer wasn't fully written.
 * @param buffer The buffer to write
 * @param n The size of the buffer
 * @param file The file to write to
 * @return 1 in case of error, 0 otherwise.
 */
static inline int s_fwrite(void *buffer, size_t n, FILE *file)
{
    size_t written = fwrite(buffer, 1, n, file);
    if (written != n) {
        errno = EIO;
        return 1;
    }
    return feof(file) || ferror(file);
}

/**
 * Safely read a file.
 * This function is similar to fread but returns an error if EOF was reached
 * or if the buffer wasn't fully read (read bytes != n).
 * @param buffer The buffer to write read data to
 * @param n The size to read
 * @param file The file to read from
 * @return 1 in case of error, 0 otherwise.
 */
static inline int s_fread(void *buffer, size_t n, FILE *file)
{
    size_t read = fread(buffer, 1, n, file);
    if (read != n) {
        errno = EIO;
        return 1;
    }
    return feof(file) || ferror(file);
}

/**
 * @brief Function pointer to a function that saves a certain type of element.
 * @param data An element of the vector
 * @param file The file to write the element to
 * @return 1 on error, 0 otherwise
 */
typedef int (*vector_func_save_t)(void *data, FILE *file);
int vector_save_content(vector_template_t *array, FILE *file,
    vector_func_save_t save_func);

/**
 * @brief Function pointer to a function that loads a certain type of element.
 * @param data An element of the vector
 * @param file The file to write the element to
 * @return NULL on error, the loaded (malloc'd) data otherwise
 */
typedef void *(*vector_func_load_t)(FILE *file);
int vector_load_content(vector_template_t *array, FILE *file,
    vector_func_load_t save_func);

/**
 * @brief Casts a pointer to a vector template.
 * Useful to use the generic vector functions on a user defined vector struct.
 */
#define vectorize(ptr) ((vector_template_t *)(ptr))

/**
 * @brief Generate a struct according to template vector_template_t
 * with the type as input.
 * @param type The type of the content to store.
 */
#define vector_struct(type)  \
    struct type##_s {         \
        size_t len;          \
        size_t element_size; \
        type **content;      \
    }
