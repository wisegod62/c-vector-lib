#include "vector.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct Vector {
  unsigned char *ptr;
  size_t element_size;
  size_t capacity;
  size_t size;
};

Vector *vec_init(size_t size, size_t element_size) {
  if (element_size == 0) {
    return NULL;
  }
  Vector *vec = malloc(sizeof *vec);
  if (!vec) {
    return NULL;
  }
  vec->ptr = NULL;

  if (size != 0) {
    size_t bytes;

    if (size > SIZE_MAX / element_size) {
      free(vec);
      return NULL;
    }

    bytes = size * element_size;
    vec->ptr = malloc(bytes);

    if (!vec->ptr) {
      free(vec);
      return NULL;
    }
  }

  vec->element_size = element_size;
  vec->capacity = size;
  vec->size = 0;

  return vec;
}

void vec_free(Vector *vec_ptr) {
  if (vec_ptr == NULL) {
    return;
  }

  free(vec_ptr->ptr);
  free(vec_ptr);
}

int vec_reserve(Vector *vec_ptr, size_t size) {
  if (vec_ptr->capacity >= size) {
    return 0;
  }
  unsigned char *real = realloc(vec_ptr->ptr, size * vec_ptr->element_size);
  if (real == NULL) {
    return -1;
  }

  vec_ptr->ptr = real;
  vec_ptr->capacity = size;
  return 0;
}

int vec_shrink_to_fit(Vector *vec_ptr) {
  vec_ptr->ptr = realloc(vec_ptr->ptr, vec_ptr->size * vec_ptr->element_size);
  vec_ptr->capacity = vec_ptr->size;
  return 0;
}

int vec_get(const Vector *vec_ptr, size_t index, void *out_value) {
  if (index >= vec_ptr->size || out_value == NULL) {
    return -1;
  }
  memcpy(out_value, vec_ptr->ptr + (index * vec_ptr->element_size),
         vec_ptr->element_size);
  return 0;
}

int vec_insert(Vector *vec_ptr, size_t index, const void *value) {
  if (index > vec_ptr->size) {
    return -1;
  }

  if (vec_ptr->size >= vec_ptr->capacity) {
    size_t new_cap = vec_ptr->capacity == 0 ? 1 : vec_ptr->capacity * 2;
    if (vec_reserve(vec_ptr, new_cap) != 0) {
      return -1;
    }
  }

  memmove(vec_ptr->ptr + ((index + 1) * vec_ptr->element_size),
          vec_ptr->ptr + (index * vec_ptr->element_size),
          vec_ptr->element_size * (vec_ptr->size - index));
  memcpy(vec_ptr->ptr + (index * vec_ptr->element_size), value,
         vec_ptr->element_size);

  ++vec_ptr->size;
  return 0;
}

int vec_append(Vector *vec_ptr, const void *value) {
  return vec_insert(vec_ptr, vec_ptr->size, value);
}

int vec_pop(Vector *vec_ptr, void *out_value) {
  if (vec_ptr->size == 0 || out_value == NULL) {
    return -1;
  }
  memcpy(out_value, vec_ptr->ptr + (vec_ptr->size - 1) * vec_ptr->element_size,
         vec_ptr->element_size);
  --vec_ptr->size;
  return 0;
}

int vec_set(Vector *vec_ptr, size_t index, const void *value) {
  if (index >= vec_ptr->size) {
    return -1;
  }
  memcpy(vec_ptr->ptr + (index * vec_ptr->element_size), value,
         vec_ptr->element_size);
  return 0;
}

size_t vec_size(const Vector *vec_ptr) { return vec_ptr->size; }

size_t vec_capacity(const Vector *vec_ptr) { return vec_ptr->capacity; }

void vec_clear(Vector *vec_ptr) { vec_ptr->size = 0; }

int vec_remove(Vector *vec_ptr, size_t index) {
  if (index >= vec_ptr->size) {
    return -1;
  }
  memmove(vec_ptr->ptr + (index * vec_ptr->element_size),
          vec_ptr->ptr + ((index + 1) * vec_ptr->element_size),
          (vec_ptr->size - index - 1) * vec_ptr->element_size);
  --vec_ptr->size;
  return 0;
}

int vec_resize(Vector *vec_ptr, size_t new_size, const void *value) {
  if (new_size == vec_ptr->size) {
    return 0;
  }

  if (new_size < vec_ptr->size) {
    vec_ptr->size = new_size;
    return 0;
  }

  if (vec_reserve(vec_ptr, new_size) != 0) {
    return -1;
  }

  for (size_t i = vec_ptr->size; i < new_size; ++i) {
    memcpy(vec_ptr->ptr + i * vec_ptr->element_size, value,
           vec_ptr->element_size);
  }

  vec_ptr->size = new_size;
  return 0;
}

int vec_is_empty(const Vector *vec_ptr) { return vec_ptr->size == 0; }

int vec_front(const Vector *vec_ptr, void *out_value) {
  if (vec_ptr->size == 0 || out_value == NULL) {
    return -1;
  }

  memcpy(out_value, vec_ptr->ptr, vec_ptr->element_size);

  return 0;
}

int vec_back(const Vector *vec_ptr, void *out_value) {
  if (vec_ptr->size == 0 || out_value == NULL) {
    return -1;
  }

  memcpy(out_value, vec_ptr->ptr + (vec_ptr->size - 1) * vec_ptr->element_size,
         vec_ptr->element_size);

  return 0;
}
