#ifndef PUZZLES_LEETCODE_UTILS_H
#define PUZZLES_LEETCODE_UTILS_H

#include <vector>

#define convert_arr2vec(arr, type) \
  std::vector<type>(arr, arr + sizeof(arr) / sizeof(type))

#endif // PUZZLES_LEETCODE_UTILS_H
