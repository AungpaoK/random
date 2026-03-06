#ifndef SORT_UTILS_H
#define SORT_UTILS_H

#include <vector>
#include <string>

namespace sortArr {
  struct SortResult {
    std::string name;
    size_t size;
    double durationSeconds;
    long long maxValue;
  };
  
  void shellSort(std::vector<long long>& vec);
  void parallelMergeSort(std::vector<long long>& vec);
  void printResults(const SortResult& res);
}

#endif // SORT_UTILS_H
