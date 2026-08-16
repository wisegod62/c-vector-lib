#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct Vector Vector;

Vector *vec_init(size_t size);

void vec_free(Vector *vec_ptr);

int vec_reserve(Vector *vec_ptr, size_t size);

int vec_get(Vector *vec_ptr, size_t index, int *out_value);

int vec_insert(Vector *vec_ptr, int value, size_t index);

int vec_append(Vector *vec_ptr, int value);

int vec_pop(Vector *vec_ptr, int *out_value);

int vec_set(Vector *vec_ptr, int value, size_t index);

size_t vec_size(Vector *vec_ptr);

size_t vec_capacity(Vector *vec_ptr);

void vec_clear(Vector *vec_ptr);

int vec_remove(Vector *vec_ptr, size_t index);

int vec_resize(Vector *vec_ptr, size_t new_size, int value);

int vec_is_empty(Vector *vec_ptr);

int vec_front(Vector *vec_ptr, int *out_value);

int vec_back(Vector *vec_ptr, int *out_value);

#endif
