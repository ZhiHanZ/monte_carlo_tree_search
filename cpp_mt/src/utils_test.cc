#include "utils.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>
using randpicker::random_element;
using std::vector;
TEST(test, eval) {
  std::vector<int> v = {10, 15, 20, 25, 30};
  std::random_device random_device;
  std::mt19937 engine{random_device()};
  std::uniform_int_distribution<int> dist(0, v.size() - 1);
  std::cout << v[dist(engine)];
}
// test whether we can add elements (if key exists, do nothing)
int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
