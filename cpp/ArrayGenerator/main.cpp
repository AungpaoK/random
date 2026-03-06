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
  long long itemsAmount;
  double speedup;

  std::cout << "--------------------------------------------------\n";
  std::cout << "Insert items amount: ";
  std::cin >> itemsAmount;
  
  if(itemsAmount <= 1)
  {
    std::cout << "Invalid Input!";
    return 1;
  }

  std::cout << "--------------------------------------------------\n";
  std::cout << "Starting Benchmarks with " << omp_get_max_threads() << " threads...\n";
  std::cout << "--------------------------------------------------\n";

  SortResult resShell = runBenchmark("Shell Sort", itemsAmount, shellSort);
  SortResult resMerge = runBenchmark("Parallel Merge", itemsAmount, parallelMergeSort);

  // Output Results
  auto display = [](const SortResult& r)
  {
    std::cout << r.name << " [" << r.size << " elements]\n";
    std::cout << "  Time: " << r.durationSeconds << " seconds\n";
    std::cout << "  Max:  " << r.maxValue << "\n";
  };

  display(resShell);
  display(resMerge);

  std::cout << "--------------------------------------------------\n";

  if(resMerge.durationSeconds < 0)
  {
    std::cout << "MergeSort was too fast to measure accurately\n";
  }
  else 
  {
    speedup = resShell.durationSeconds / resMerge.durationSeconds;
  }
  std::cout << "Merge Sort is " << speedup << " times faster than Shell Sort\n";
  std::cout << "--------------------------------------------------\n";
  return 0;
}
