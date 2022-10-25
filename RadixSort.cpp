#include <iostream>
#include <vector>
#include <chrono>
using namespace std::chrono;
using namespace std;

const int MAX_NUM = 999;

vector<int> generateRandomVector(int listSize, int max_num);
void printVector(const vector<int>& numbers);
void seedRand();
void radixSort(vector<int>& numbers);
int radixGetMaxLength(const vector<int>& numbers);
int radixGetLength(int value);

//int main()
//{
//    seedRand();
//    vector<int> list;
//    list = generateRandomVector(100, MAX_NUM);
//    printVector(list);
//    radixSort(list);
//    printVector(list);
//}

void radixSort(vector<int>& numbers) 
{
    const int RADIX = 10;
    // Store buckets of numbers as a vector of vectors
    vector<vector<int>> buckets(RADIX);

    int maxDigits = radixGetMaxLength(numbers);

    // Start with least significant digit
    int pow10 = 1;
    //printVector(numbers);
    for (int digitIndex = 0; digitIndex < maxDigits; digitIndex++) 
    {
        
        // Place entries into buckets
        for (unsigned int i = 0; i < numbers.size(); i++) 
        {
            int bucketIndex = abs(numbers.at(i) / pow10) % 10;
            buckets.at(bucketIndex).push_back(numbers.at(i));
        }

        // Copy entries back from buckets into vector
        int arrayIndex = 0;
        for (int i = 0; i < RADIX; i++) 
        {
            for (unsigned int j = 0; j < buckets.at(i).size(); j++) 
            {
                numbers.at(arrayIndex) = buckets.at(i).at(j);
                arrayIndex++;
            }

            // Clear the bucket since we're now done with it
            buckets.at(i).clear();
        }
        pow10 *= 10;
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