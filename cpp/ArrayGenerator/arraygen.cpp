#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <chrono>

void findMax(const std::vector<long long>& vec, long long &findMaxTime, long long &maxValue){
    auto start = std::chrono::high_resolution_clock::now();
    maxValue = vec[0];
    for (size_t i = 1; i < vec.size(); i++){
        if (vec[i] > maxValue){
            maxValue = vec[i];
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    findMaxTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

void merge(std::vector<long long>&vec, long long left, long long right, long long mid){
    long long sizeLeft = mid - left + 1;
    long long sizeRight = right - mid;

    std::vector<long long> leftArr(sizeLeft);
    std::vector<long long> rightArr(sizeRight);
    
    for (long long i = 0; i < sizeLeft; i ++){
        leftArr[i] = vec[left + i];
    }

    for (long long j = 0; j < sizeRight; j ++){
        rightArr[j] = vec[mid + 1 + j];
    }
    long long i = 0;
    long long j = 0;
    long long k = left;

    while (i < sizeLeft && j < sizeRight){
        if (leftArr[i] <= rightArr[j]){
            vec[k] = leftArr[i];
            i++;
        } else {
            vec[k] = rightArr[j];
            j++;
        }   
        k++;
    }
    while (i < sizeLeft){
        vec[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < sizeRight){
        vec[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<long long>& vec, long long left, long long right){
    if (left < right) {
        long long mid = left +(right-left)/2;
        mergeSort(vec, left, mid);
        mergeSort(vec, mid+1, right);
        merge(vec, left, right, mid);
    }
}

void mergeSortTimed(std::vector<long long>& vec, long long left, long long right,long long &mergeSortTime){    
    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(vec, left, right);
    auto end = std::chrono::high_resolution_clock::now();
    mergeSortTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

void bubbleSort(std::vector<long long>& vec, long long &bubbleSortTime){
    auto start = std::chrono::high_resolution_clock::now();
    int n = vec.size();
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (vec[j] > vec[j+1]){
                std::swap(vec[j], vec[j+1]);
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    bubbleSortTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

int main(){
    auto start = std::chrono::high_resolution_clock::now();

    //random number using time seed
    unsigned long long seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);
    std::uniform_int_distribution<long long> bubbleDist_size(10000000, 15000000);
    std::uniform_int_distribution<long long> mergeDist_size(10000000, 15000000);

    long long bubbleSize = bubbleDist_size(rng);
    long long mergeSize  = mergeDist_size(rng);
    
    //dynamic array size
    std::cout << ("----------------------------------") << std::endl;
    std::cout << ("Creating array for numbers ...") << std::endl;
    std::cout << ("----------------------------------") << std::endl;
    std::vector<long long> vec1(bubbleSize);
    std::vector<long long> vec2(mergeSize);

    std::uniform_int_distribution<long long> dist_value(10, 100000000000);
    for (long long i = 0; i < bubbleSize; i++){
        vec1[i] = dist_value(rng);
    }

    for (long long j = 0; j < mergeSize; j++){
        vec2[j] = dist_value(rng);
    }

    auto endAppend = std::chrono::high_resolution_clock::now();
    auto durationLoop = std::chrono::duration_cast<std::chrono::milliseconds>(endAppend - start);


    std::cout << "Bubble sort array size: " << bubbleSize << std::endl;
    std::cout << "Merge sort array size: " << mergeSize << std::endl;
    std::cout << "Last value of array 1 before sort: " << vec1.back() << std::endl;
    std::cout << "Last value of array 2 before sort: " << vec2.back() << std::endl;
    std::cout << ("----------------------------------") << std::endl;
    std::cout << "Sorting ..." << std::endl;
    std::cout << ("----------------------------------") << std::endl;

    long long bubbleSortTime = 0;
    long long mergeSortTime = 0;
    long long findMaxTime = 0;
    long long max1 = 0;
    long long max2 = 0;

    findMax(vec1, findMaxTime, max1);
    findMax(vec2, findMaxTime, max2);

    std::thread t1(bubbleSort, std::ref (vec1), std::ref(bubbleSortTime));
    std::thread t2(mergeSortTimed, std::ref(vec2), 0, mergeSize - 1, std::ref(mergeSortTime));

    t1.join();
    t2.join();

    std::cout << ("Sorted!") << std::endl;
    std::cout << ("----------------------------------") << std::endl;
    std::cout << "Last value after bubble sort: " << vec1.back() << std::endl;
    std::cout << "The max value of array 1: " << max1 << std::endl;
    std::cout << "Last value afte merge sort: " << vec2.back() << std::endl;
    std::cout << "The max value of array 2: " << max2 << std::endl;
    std::cout << ("----------------------------------") << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << ("Results") << std::endl;
    std::cout << ("----------------------------------") << std::endl;
    std::cout << "Program execution time: " << duration.count() << " milliseconds" << std::endl;
    std::cout << "Loop process took: " << durationLoop.count() << " milliseconds" << std::endl;
    std::cout << "Finding max value took: " << findMaxTime << " milliseconds" << std::endl;
    std::cout << "Bubble sort took: " << bubbleSortTime << " milliseconds" << std::endl;
    std::cout << "Merge sort took: " << mergeSortTime << " milliseconds" << std::endl;
    std::cout << ("----------------------------------") << std::endl;

    return 0;
}
