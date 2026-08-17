#include "vector.h"
#include <stdlib.h>

struct Vector {
  int *ptr;
  size_t capacity;
  size_t size;
};

Vector *vec_init(size_t size) {
  Vector *vec = malloc(sizeof(Vector));
  if (!vec) {
    return NULL;
  }
  vec->ptr = malloc(size * sizeof(int));
  if (!vec->ptr) {
    free(vec);
    return NULL;
  }
  vec->capacity = size;
  vec->size = 0;

  return vec;
}

void vec_free(Vector *vec_ptr) {
  free(vec_ptr->ptr);
  free(vec_ptr);
  return;
}

int vec_reserve(Vector *vec_ptr, size_t size) {
  if (vec_ptr->capacity >= size) {
    return 0;
  }
  int *real = realloc(vec_ptr->ptr, size * sizeof(int));
  if (real == NULL) {
    return -1;
  }

  vec_ptr->ptr = real;
  vec_ptr->capacity = size;
  return 0;
}

int vec_get(Vector *vec_ptr, size_t index, int *out_value) {
  if (index >= vec_ptr->size) {
    return -1;
  }
  *out_value = vec_ptr->ptr[index];
  return 0;
}

int vec_insert(Vector *vec_ptr, int value, size_t index) {
  if (index > vec_ptr->size) {
    return -1;
  }

  if (vec_ptr->size >= vec_ptr->capacity) {
    size_t new_cap = vec_ptr->capacity == 0 ? 1 : vec_ptr->capacity * 2;
    if (vec_reserve(vec_ptr, new_cap) != 0) {
      return -1;
    }
  }

  for (size_t i = vec_ptr->size; i > index; --i) {
    vec_ptr->ptr[i] = vec_ptr->ptr[i - 1];
  }

  vec_ptr->ptr[index] = value;
  vec_ptr->size++;
  return 0;
}

int vec_append(Vector *vec_ptr, int value) {
  return vec_insert(vec_ptr, value, vec_ptr->size);
}

int vec_pop(Vector *vec_ptr, int *out_value) {
  if (vec_ptr->size == 0) {
    return -1;
  }
  vec_get(vec_ptr, vec_ptr->size - 1, out_value);
  --vec_ptr->size;
  return 0;
}

int vec_set(Vector *vec_ptr, int value, size_t index) {
  if (index >= vec_ptr->size) {
    return -1;
  }
  vec_ptr->ptr[index] = value;
  return 0;
}

size_t vec_size(Vector *vec_ptr) { return vec_ptr->size; }

size_t vec_capacity(Vector *vec_ptr) { return vec_ptr->capacity; }

void vec_clear(Vector *vec_ptr) { vec_ptr->size = 0; }

int vec_remove(Vector *vec_ptr, size_t index) {
  if (index >= vec_ptr->size) {
    return -1;
  }
  --vec_ptr->size;
  for (size_t i = index; i < vec_ptr->size; ++i) {
    vec_ptr->ptr[i] = vec_ptr->ptr[i + 1];
  }
  return 0;
}

int vec_resize(Vector *vec_ptr, size_t new_size, int value) {
  if (vec_ptr->size == new_size) {
    return 0;
  }
  if (vec_ptr->size > new_size) {
    vec_ptr->size = new_size;
    return 0;
  }
  if (vec_reserve(vec_ptr, new_size) != 0) {
    return -1;
  }
  for (size_t i = vec_ptr->size; i < new_size; ++i) {
    vec_ptr->ptr[i] = value;
  }
  vec_ptr->size = new_size;
  return 0;
}

int vec_is_empty(Vector *vec_ptr) {
  if (vec_ptr->size == 0) {
    return 1;
  } else {
    return 0;
  }
}

int vec_front(Vector *vec_ptr, int *out_value) {
  if (vec_ptr->size == 0) {
    return -1;
  }
  *out_value = vec_ptr->ptr[0];
  return 0;
}

int vec_back(Vector *vec_ptr, int *out_value) {
  if (vec_ptr->size == 0) {
    return -1;
  }
  *out_value = vec_ptr->ptr[vec_ptr->size - 1];
  return 0;
}
