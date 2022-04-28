// sortComparison.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <vector>
#include <chrono>
using namespace std::chrono;

std::vector<int> generateRandomVector(int listSize);
// Prints the contents of a vector to the console
void printVector(const std::vector<int>& numbers);
void insertionSort(std::vector<int>& numbers);
void bucketSort(std::vector<int>& numbers, int numBuckets);

// Returns the maximum length, in number of digits, out of all elements in the array
int radixGetMaxLength(const std::vector<int>& numbers);
// Returns the length, in number of digits, of value
int radixGetLength(int value);
void radixSort(std::vector<int>& numbers);

// Maximum random integer to generate
const int MAX_NUM = 999;
const int NUM_BUCKETS = 10;

int main()
{
    int listSizes[] = { 10, 100, 1000, 10000 };
    const int NUM_LIST_SIZES = 4;
    const int NUM_RUNS = 10;
    double timesInsertion[NUM_LIST_SIZES][NUM_RUNS];
    double timesBucket[NUM_LIST_SIZES][NUM_RUNS];
    double timesRadix[NUM_LIST_SIZES][NUM_RUNS];
    double avgTimesInsertion[NUM_LIST_SIZES];
    double avgTimesBucket[NUM_LIST_SIZES];
    double avgTimesRadix[NUM_LIST_SIZES];

    // Set the seed for the random number generator based on the current time
    auto seedTime = system_clock::now();
    unsigned int seed = duration_cast<seconds>(seedTime.time_since_epoch()).count()
        % UINT_MAX;
    std::srand(seed);

    for (int iSize = 0; iSize < NUM_LIST_SIZES; iSize++) {
        std::cout << "N = " << listSizes[iSize] << std::endl;
        avgTimesInsertion[iSize] = avgTimesBucket[iSize] = avgTimesRadix[iSize] = 0;
        for (int iRun = 0; iRun < NUM_RUNS; iRun++) {
            std::cout << "Run " << iRun + 1 << std::endl;

            std::vector<int> list, listInsertion, listBucket, listRadix;
            list = generateRandomVector(listSizes[iSize]);
            listInsertion = listBucket = listRadix = list;

            // Time insertion sort
            auto start = high_resolution_clock::now();
            insertionSort(listInsertion);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            timesInsertion[iSize][iRun] = duration.count() / 1000.0;

            // Time bucket sort
            start = high_resolution_clock::now();
            bucketSort(listBucket, NUM_BUCKETS);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            timesBucket[iSize][iRun] = duration.count() / 1000.0;

            // Time radix sort
            start = high_resolution_clock::now();
            radixSort(listRadix);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            timesRadix[iSize][iRun] = duration.count() / 1000.0;

            avgTimesInsertion[iSize] += timesInsertion[iSize][iRun] / NUM_RUNS;
            avgTimesBucket[iSize] += timesBucket[iSize][iRun] / NUM_RUNS;
            avgTimesRadix[iSize] += timesRadix[iSize][iRun] / NUM_RUNS;
        }
        std::cout << "Insertion sort: " << avgTimesInsertion[iSize] << " ms";
        if (iSize > 0) {
            std::cout << " (Growth rate: " << avgTimesInsertion[iSize]
                / avgTimesInsertion[iSize - 1] << ")";
        }
        std::cout << std::endl;

        std::cout << "Bucket sort: " << avgTimesBucket[iSize] << " ms";
        if (iSize > 0) {
            std::cout << " (Growth rate: " << avgTimesBucket[iSize]
                / avgTimesBucket[iSize - 1] << ")";
        }
        std::cout << std::endl;

        std::cout << "Radix sort: " << avgTimesRadix[iSize] << " ms";
        if (iSize > 0) {
            std::cout << " (Growth rate: " << avgTimesRadix[iSize]
                / avgTimesRadix[iSize - 1] << ")";
        }
        std::cout << std::endl;
    }

    // Code below was used to test the sorts for correctness before running
    // the entire program
    /*
    std::vector<int> list, listInsertion, listBucket, listRadix;
    list = generateRandomVector(100);
    listInsertion = listBucket = listRadix = list;
    printVector(list);
    std::cout << std::endl;

    insertionSort(listInsertion);
    printVector(listInsertion);
    std::cout << std::endl;

    bucketSort(listBucket, NUM_BUCKETS);
    printVector(listBucket);
    std::cout << std::endl;

    radixSort(listRadix);
    printVector(listRadix);
    */

    return 0;
}

std::vector<int> generateRandomVector(int listSize) {
    std::vector<int> randomList(listSize);

    for (int i = 0; i < listSize; i++) {
        // Multiply by MAX_NUM + 1 and integer divide by RAND_MAX + 1 to get
        // back a random integer between 0 and MAX_NUM
        randomList.at(i) = rand() * (MAX_NUM + 1) / (RAND_MAX + 1);
    }
    return randomList;
}

void printVector(const std::vector<int>& numbers) {
    for (unsigned int j = 0; j < numbers.size(); j++)
        std::cout << numbers.at(j) << " ";
    std::cout << std::endl;
}

void insertionSort(std::vector<int>& numbers) {
    int temp = 0;

    for (unsigned int i = 1; i < numbers.size(); i++) {
        int j = i;
        // Insert numbers[i] into sorted part
        // stopping once numbers[i] in correct position
        while (j > 0 && numbers.at(j) < numbers.at(j - 1)) {
            temp = numbers.at(j);
            numbers.at(j) = numbers.at(j - 1);
            numbers.at(j - 1) = temp;
            j--;
        }
    }
}

void bucketSort(std::vector<int>& numbers, int numBuckets) {
    // Store buckets of numbers as a vector of vectors
    std::vector<std::vector<int>> buckets(numBuckets);

    // Find the maximum value
    int maxValue = numbers.at(0);
    for (unsigned int i = 1; i < numbers.size(); i++) {
        if (numbers.at(i) > maxValue)
            maxValue = numbers.at(i);
    }

    // Put each number in a bucket
    unsigned int index = 0;
    for (unsigned int i = 0; i < numbers.size(); i++) {
        index = numbers.at(i) * numBuckets / (maxValue + 1);
        buckets.at(index).push_back(numbers.at(i));
    }

    // Sort each bucket
    for (index = 0; index < buckets.size(); index++) {
        //printVector(buckets.at(index));
        insertionSort(buckets.at(index));
        //printVector(buckets.at(index));
    }

    // Combine all buckets back into numbers list
    int i = 0;
    for (index = 0; index < buckets.size(); index++) {
        for (unsigned int j = 0; j < buckets.at(index).size(); j++) {
            //std::cout << "j = " << j << std::endl;
            numbers.at(i) = buckets.at(index).at(j);
            i++;
        }
        //std::cout << "Completed bucket " << index << std::endl;
    }
}

void radixSort(std::vector<int>& numbers) {
    const int RADIX = 10;
    // Store buckets of numbers as a vector of vectors
    std::vector<std::vector<int>> buckets(RADIX);

    int maxDigits = radixGetMaxLength(numbers);

    // Start with least significant digit
    int pow10 = 1;
    //printVector(numbers);
    for (int digitIndex = 0; digitIndex < maxDigits; digitIndex++) {
        // Place entries into buckets
        for (unsigned int i = 0; i < numbers.size(); i++) {
            int bucketIndex = abs(numbers.at(i) / pow10) % 10;
            buckets.at(bucketIndex).push_back(numbers.at(i));
        }

        // Copy entries back from buckets into vector
        int arrayIndex = 0;
        for (int i = 0; i < RADIX; i++) {
            for (unsigned int j = 0; j < buckets.at(i).size(); j++) {
                numbers.at(arrayIndex) = buckets.at(i).at(j);
                arrayIndex++;
            }

            // Clear the bucket since we're now done with it
            buckets.at(i).clear();
        }

        pow10 *= 10;
        //printVector(numbers);
    }
}

int radixGetMaxLength(const std::vector<int>& numbers) {
    int maxDigits = 0;
    for (unsigned int i = 0; i < numbers.size(); i++) {
        int digitCount = radixGetLength(numbers.at(i));
        if (digitCount > maxDigits)
            maxDigits = digitCount;
    }
    return maxDigits;
}

int radixGetLength(int value) {
    if (value == 0)
        return 1;

    int digits = 0;
    while (value != 0) {
        digits++;
        value /= 10;
    }
    return digits;
}