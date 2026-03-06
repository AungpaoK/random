#include "sort_utils.h"
#include <algorithm>
#include <omp.h>

namespace sortArr
{
  void shellSort(std::vector<long long>& vec)
  {
    size_t n = vec.size();
    for (size_t gap = n/2; gap > 0; gap /=2)
    {
      for (size_t i = gap; i < n; i++)
      {
        long long temp = vec[i];
        size_t j;
        for (j = i; j >= gap && vec[j-gap] > temp; j -= gap)
        {
          vec[j] = vec[j-gap];
        }
        vec[i] = temp;
      }
    }
  }

  void merge(long long* begin, long long* mid, long long* end, long long* aux)
  {
    long long* left = begin;
    long long* right = mid;
    long long* target = aux;

    while(left < mid && right < end)
    {
      if(*left <= *right)
      {
        *target = *left;
        left++;
      } 
      else 
      {
        *target = *right;
        right++;
      }
      target++;
    }
    
    while(left < mid)
    {
      *target = *left;
      left++;
      target++;

    }
    
    while(right < end)
    {
      *target = *right;
      right++;
      target++;
    }
    std::copy(aux, target, begin);
  }

  void mergeSortRecursive(long long* begin, long long* end, long long* aux)
  {
    long long size = end - begin;
    if (size < 1000)
    {
        std::sort(begin, end);
        return;
    }

    long long* mid = begin + size / 2;

    #pragma omp task shared(begin, mid, aux)
    mergeSortRecursive(begin, mid, aux);
    
    #pragma omp task shared(mid, end, aux)
    mergeSortRecursive(mid, end, aux + (mid - begin));

    #pragma omp taskwait
    merge(begin, mid, end, aux);
  }

  void parallelMergeSort(std::vector<long long>& vec)
  {
    std::vector<long long> aux(vec.size());
    #pragma omp parallel
    {
      #pragma omp single
      mergeSortRecursive(vec.data(), vec.data() + vec.size(), aux.data());
    }
  }
}
