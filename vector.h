#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct Vector Vector;

Vector *vec_init(size_t size, size_t element_size);
void vec_free(Vector *vec);

int vec_reserve(Vector *vec, size_t capacity);
int vec_shrink_to_fit(Vector *vec_ptr);

int vec_get(const Vector *vec, size_t index, void *out_value);
int vec_set(Vector *vec, size_t index, const void *value);

int vec_insert(Vector *vec, size_t index, const void *value);
int vec_append(Vector *vec, const void *value);

int vec_pop(Vector *vec, void *out_value);
int vec_remove(Vector *vec, size_t index);

int vec_resize(Vector *vec, size_t new_size, const void *value);

size_t vec_size(const Vector *vec);
size_t vec_capacity(const Vector *vec);

void vec_clear(Vector *vec);
int vec_is_empty(const Vector *vec);

int vec_front(const Vector *vec, void *out_value);
int vec_back(const Vector *vec, void *out_value);

// The pointer returned by these functions will become invalid after successful
// calls of vec_reserve vec_append and vec_insert will call vec_reserve when
// they run out of space
void *vec_data(Vector *vec);
const void *vec_const_data(const Vector *vec);

#endif
