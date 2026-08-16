#include "vector.h"
#include <assert.h>
#include <stdio.h>

void test_initialization_and_append() {
  printf("-> Running: Initialization and Append Test\n");

  // Initialize with a tiny capacity to force quick growth cycles
  Vector *v = vec_init(2);
  assert(v != NULL);
  assert(vec_size(v) == 0);
  assert(vec_capacity(v) == 2);
  assert(vec_is_empty(v) == 1);

  // Append items and watch structural metrics adapt
  assert(vec_append(v, 10) == 0);
  assert(vec_append(v, 20) == 0);
  assert(vec_size(v) == 2);
  assert(vec_capacity(v) == 2); // Perfectly full

  // Trigger explicit geometric expansion (capacity doubles from 2 to 4)
  assert(vec_append(v, 30) == 0);
  assert(vec_size(v) == 3);
  assert(vec_capacity(v) == 4);
  assert(vec_is_empty(v) == 0);

  // Verify values match internal sequence layout
  int val = 0;
  assert(vec_get(v, 0, &val) == 0);
  assert(val == 10);
  assert(vec_get(v, 1, &val) == 0);
  assert(val == 20);
  assert(vec_get(v, 2, &val) == 0);
  assert(val == 30);

  vec_free(v);
}

void test_bounds_and_safety() {
  printf("-> Running: Safety and Bounds Checking Test\n");
  Vector *v = vec_init(4);
  vec_append(v, 100);
  vec_append(v, 200);

  int val = 0;
  // Verify positive out-of-bounds protection
  assert(vec_get(v, 2, &val) == -1);
  assert(vec_set(v, 500, 5) == -1);

  // Verify negative index vulnerability defense via explicit unsigned
  // wrap-around simulation
  assert(vec_get(v, (size_t)-1, &val) == -1);
  assert(vec_set(v, 500, (size_t)-3) == -1);
  assert(vec_remove(v, (size_t)-1) == -1);

  // Verify clean front/back lookup guards
  assert(vec_front(v, &val) == 0);
  assert(val == 100);
  assert(vec_back(v, &val) == 0);
  assert(val == 200);

  vec_free(v);

  // Ensure empty vector guards work correctly
  Vector *empty_v = vec_init(4);
  assert(vec_front(empty_v, &val) == -1);
  assert(vec_back(empty_v, &val) == -1);
  assert(vec_pop(empty_v, &val) == -1);
  vec_free(empty_v);
}

void test_insert_and_shift() {
  printf("-> Running: Insertion and Memory Shifting Test\n");
  Vector *v = vec_init(4);
  vec_append(v, 10);
  vec_append(v, 30);

  // Insert 20 directly between 10 and 30 (index 1)
  assert(vec_insert(v, 20, 1) == 0);
  assert(vec_size(v) == 3);

  int val = 0;
  vec_get(v, 0, &val);
  assert(val == 10);
  vec_get(v, 1, &val);
  assert(val == 20); // Verification of right-shift data allocation
  vec_get(v, 2, &val);
  assert(val == 30);

  vec_free(v);
}

void test_remove_and_pop() {
  printf("-> Running: Remove and Pop Performance Test\n");
  Vector *v = vec_init(4);
  vec_append(v, 10);
  vec_append(v, 20);
  vec_append(v, 30);

  int val = 0;
  // Test constant time pop optimization
  assert(vec_pop(v, &val) == 0);
  assert(val == 30);
  assert(vec_size(v) == 2);

  // Test shifting remove logic
  vec_append(v, 40);             // Layout: [10, 20, 40]
  assert(vec_remove(v, 1) == 0); // Erase index 1 (20)
  assert(vec_size(v) == 2);

  vec_get(v, 0, &val);
  assert(val == 10);
  vec_get(v, 1, &val);
  assert(val == 40); // 40 successfully shifted left

  vec_free(v);
}

void test_resize_and_reserve() {
  printf("-> Running: Logical Resize and Physical Reserve Test\n");
  Vector *v = vec_init(4);
  vec_append(v, 5);
  vec_append(v, 6);

  // Test physical capacity preservation
  assert(vec_reserve(v, 10) == 0);
  assert(vec_capacity(v) == 10);
  assert(vec_size(v) == 2);

  // Test layout growth with safe placeholder values
  assert(vec_resize(v, 5, 99) == 0);
  assert(vec_size(v) == 5);

  int val = 0;
  vec_get(v, 2, &val);
  assert(val == 99); // Verifies loops populated safe initialization values
  vec_get(v, 3, &val);
  assert(val == 99);
  vec_get(v, 4, &val);
  assert(val == 99);

  // Test logical truncation functionality
  assert(vec_resize(v, 1, 0) == 0);
  assert(vec_size(v) == 1);
  assert(vec_capacity(v) == 10); // Physical memory overhead stays intact for
                                 // quick recycle optimization

  vec_free(v);
}

int main() {
  printf("===========================================\n");
  printf("STARTING DYNAMIC VECTOR VALIDATION SUITE\n");
  printf("===========================================\n");

  test_initialization_and_append();
  test_bounds_and_safety();
  test_insert_and_shift();
  test_remove_and_pop();
  test_resize_and_reserve();

  printf("===========================================\n");
  printf("SUCCESS: All library units cleared safely!\n");
  printf("===========================================\n");
  return 0;
}
