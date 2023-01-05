#ifndef PUZZLES_LEETCODE_UTILS_H
#define PUZZLES_LEETCODE_UTILS_H

#include <vector>

#define convert_arr2vec(arr, type) \
  std::vector<type>(arr, arr + sizeof(arr) / sizeof(type))

static __inline__ long long get_time_ns() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

#endif // PUZZLES_LEETCODE_UTILS_H
