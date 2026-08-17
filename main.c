#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

struct Person {
  char name[32];
  int age;
};

void test_int_vector(void) {
  printf("-> Running: Generic int vector test\n");

  Vector *v = vec_init(2, sizeof(int));

  assert(v != NULL);
  assert(vec_size(v) == 0);
  assert(vec_capacity(v) == 2);
  assert(vec_is_empty(v) == 1);

  int value = 10;
  assert(vec_append(v, &value) == 0);

  value = 20;
  assert(vec_append(v, &value) == 0);

  value = 30;
  assert(vec_append(v, &value) == 0);

  assert(vec_size(v) == 3);
  assert(vec_capacity(v) == 4);
  assert(vec_is_empty(v) == 0);

  int out = 0;

  assert(vec_get(v, 0, &out) == 0);
  assert(out == 10);

  assert(vec_get(v, 1, &out) == 0);
  assert(out == 20);

  assert(vec_get(v, 2, &out) == 0);
  assert(out == 30);

  vec_free(v);
}

void test_double_vector(void) {
  printf("-> Running: Generic double vector test\n");

  Vector *v = vec_init(2, sizeof(double));

  assert(v != NULL);

  double value = 3.14;
  assert(vec_append(v, &value) == 0);

  value = 6.28;
  assert(vec_append(v, &value) == 0);

  double out = 0.0;

  assert(vec_get(v, 0, &out) == 0);
  assert(out == 3.14);

  assert(vec_get(v, 1, &out) == 0);
  assert(out == 6.28);

  assert(vec_size(v) == 2);

  vec_free(v);
}

void test_struct_vector(void) {
  printf("-> Running: Generic struct vector test\n");

  Vector *v = vec_init(2, sizeof(struct Person));

  assert(v != NULL);

  struct Person alice = {"Alice", 25};
  struct Person bob = {"Bob", 31};

  assert(vec_append(v, &alice) == 0);
  assert(vec_append(v, &bob) == 0);

  struct Person out;

  assert(vec_get(v, 0, &out) == 0);
  assert(strcmp(out.name, "Alice") == 0);
  assert(out.age == 25);

  assert(vec_get(v, 1, &out) == 0);
  assert(strcmp(out.name, "Bob") == 0);
  assert(out.age == 31);

  vec_free(v);
}

void test_bounds(void) {
  printf("-> Running: Bounds checking test\n");

  Vector *v = vec_init(4, sizeof(int));

  int value = 100;
  assert(vec_append(v, &value) == 0);

  value = 200;
  assert(vec_append(v, &value) == 0);

  int out = 0;

  assert(vec_get(v, 2, &out) == -1);
  assert(vec_get(v, (size_t)-1, &out) == -1);

  value = 500;
  assert(vec_set(v, 2, &value) == -1);
  assert(vec_set(v, (size_t)-1, &value) == -1);

  assert(vec_remove(v, 2) == -1);
  assert(vec_remove(v, (size_t)-1) == -1);

  vec_free(v);

  Vector *empty = vec_init(4, sizeof(int));

  assert(vec_front(empty, &out) == -1);
  assert(vec_back(empty, &out) == -1);
  assert(vec_pop(empty, &out) == -1);

  vec_free(empty);
}

void test_front_back(void) {
  printf("-> Running: Front and back test\n");

  Vector *v = vec_init(4, sizeof(int));

  int value = 10;
  vec_append(v, &value);

  value = 20;
  vec_append(v, &value);

  value = 30;
  vec_append(v, &value);

  int out = 0;

  assert(vec_front(v, &out) == 0);
  assert(out == 10);

  assert(vec_back(v, &out) == 0);
  assert(out == 30);

  vec_free(v);
}

void test_insert(void) {
  printf("-> Running: Insert and shifting test\n");

  Vector *v = vec_init(4, sizeof(int));

  int value = 10;
  vec_append(v, &value);

  value = 30;
  vec_append(v, &value);

  value = 20;
  assert(vec_insert(v, 1, &value) == 0);

  assert(vec_size(v) == 3);

  int out;

  vec_get(v, 0, &out);
  assert(out == 10);

  vec_get(v, 1, &out);
  assert(out == 20);

  vec_get(v, 2, &out);
  assert(out == 30);

  vec_free(v);
}

void test_remove_and_pop(void) {
  printf("-> Running: Remove and pop test\n");

  Vector *v = vec_init(4, sizeof(int));

  int value = 10;
  vec_append(v, &value);

  value = 20;
  vec_append(v, &value);

  value = 30;
  vec_append(v, &value);

  int out;

  assert(vec_pop(v, &out) == 0);
  assert(out == 30);
  assert(vec_size(v) == 2);

  value = 40;
  vec_append(v, &value);

  assert(vec_remove(v, 1) == 0);
  assert(vec_size(v) == 2);

  vec_get(v, 0, &out);
  assert(out == 10);

  vec_get(v, 1, &out);
  assert(out == 40);

  vec_free(v);
}

void test_resize(void) {
  printf("-> Running: Resize and reserve test\n");

  Vector *v = vec_init(4, sizeof(int));

  int value = 5;
  vec_append(v, &value);

  value = 6;
  vec_append(v, &value);

  assert(vec_reserve(v, 10) == 0);
  assert(vec_capacity(v) == 10);
  assert(vec_size(v) == 2);

  int fill_value = 99;

  assert(vec_resize(v, 5, &fill_value) == 0);
  assert(vec_size(v) == 5);
  assert(vec_capacity(v) == 10);

  int out;

  vec_get(v, 2, &out);
  assert(out == 99);

  vec_get(v, 3, &out);
  assert(out == 99);

  vec_get(v, 4, &out);
  assert(out == 99);

  assert(vec_resize(v, 1, &fill_value) == 0);
  assert(vec_size(v) == 1);
  assert(vec_capacity(v) == 10);

  vec_free(v);
}

void test_clear(void) {
  printf("-> Running: Clear test\n");

  Vector *v = vec_init(4, sizeof(double));

  double value = 1.5;
  vec_append(v, &value);

  value = 2.5;
  vec_append(v, &value);

  assert(vec_size(v) == 2);
  assert(vec_is_empty(v) == 0);

  vec_clear(v);

  assert(vec_size(v) == 0);
  assert(vec_is_empty(v) == 1);

  assert(vec_capacity(v) == 4);

  vec_free(v);
}

int main(void) {
  printf("===========================================\n");
  printf("STARTING GENERIC VECTOR TEST SUITE\n");
  printf("===========================================\n");

  test_int_vector();
  test_double_vector();
  test_struct_vector();

  test_bounds();
  test_front_back();
  test_insert();
  test_remove_and_pop();
  test_resize();
  test_clear();

  printf("===========================================\n");
  printf("SUCCESS: ALL TESTS PASSED!\n");
  printf("===========================================\n");

  return 0;
}
