#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <omp.h>
#include "sort_utils.h"

using namespace sortArr;

SortResult runBenchmark(std::string name, size_t size, void (*sortFunc)(std::vector<long long>&))
{
  std::vector<long long> vec(size);
  std::random_device rd;
  std::mt19937_64 rng(rd());
  std::uniform_int_distribution<long long> dist(1, 1000000000);

  for (auto& x : vec) x = dist(rng);

  // Find max value before sorting
  long long maxVal = *std::max_element(vec.begin(), vec.end());

  double startTime = omp_get_wtime();
  sortFunc(vec);
  double endTime = omp_get_wtime();

  return {name, size, (endTime - startTime), maxVal};
}

int main ()
{
  std::cout << "Starting Benchmarks with " << omp_get_max_threads() << " threads...\n";
  std::cout << "--------------------------------------------------\n";

  // 100k items for Shell Sort
  SortResult resShell = runBenchmark("Shell Sort", 100000, shellSort);
    
  // 10 Million items for Parallel Merge Sort
  SortResult resMerge = runBenchmark("Parallel Merge", 10000000, parallelMergeSort);

  // Output Results
  auto display = [](const SortResult& r)
  {
    std::cout << r.name << " [" << r.size << " elements]\n";
    std::cout << "  Time: " << r.durationSeconds << " seconds\n";
    std::cout << "  Max:  " << r.maxValue << "\n\n";
  };

  display(resShell);
  display(resMerge);

  std::cout << "--------------------------------------------------\n";
  return 0;
}
