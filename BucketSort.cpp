#include <iostream>
#include <vector>
#include <chrono>
using namespace std::chrono;
using namespace std;

const int MAX_NUM = 999;
const int MAX_BUCKETS = 10;

vector<int> generateRandomVector(int listSize, int max_num);
void printVector(const vector<int>& numbers);
void seedRand();
void bucketSort(vector<int>& numbers, int numBuckets);
//void insertionSortForBuckets(const vector<int>& numbers);

//int main()
//{
//    seedRand();
//    vector<int> list;
//    list = generateRandomVector(100, MAX_NUM);
//    printVector(list);
//    bucketSort(list, MAX_BUCKETS);
//    printVector(list);
//}

void bucketSort(vector<int>& numbers, int numBuckets) 
{
    // Store buckets of numbers as a vector of vectors
    vector<vector<int>> buckets(numBuckets);

    // Find the maximum value
    int maxValue = numbers.at(0);
    for (unsigned int i = 1; i < numbers.size(); i++) 
    {
        if (numbers.at(i) > maxValue)
            maxValue = numbers.at(i);
    }

    // Put each number in a bucket
    unsigned int index = 0;
    for (unsigned int i = 0; i < numbers.size(); i++) 
    {
        index = numbers.at(i) * numBuckets / (maxValue + 1);
        buckets.at(index).push_back(numbers.at(i));
    }

    // Sort each bucket
    for (index = 0; index < buckets.size(); index++) 
    {
        //insertionSortForBuckets(buckets.at(index));
    }

    // Combine all buckets back into numbers list
    int i = 0;
    for (index = 0; index < buckets.size(); index++) 
    {
        for (unsigned int j = 0; j < buckets.at(index).size(); j++) 
        {
            numbers.at(i) = buckets.at(index).at(j);
            i++;
        }
    }
}

//void insertionSortForBuckets(vector<int>& numbers)
//{
//    int temp = 0;
//    for (unsigned int i = 1; i < numbers.size(); i++)
//    {
//        int j = i;
//        while (j > 0 && numbers.at(j) < numbers.at(j - 1))
//        {
//            temp = numbers.at(j);
//            numbers.at(j) = numbers.at(j - 1);
//            numbers.at(j - 1) = temp;
//            j--;
//        }
//    }
//}