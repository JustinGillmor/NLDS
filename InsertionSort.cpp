#include <iostream>
#include <vector>
#include <chrono>
using namespace std::chrono;
using namespace std;

const int MAX_NUM = 999;

vector<int> generateRandomVector(int listSize, int max_num);
void insertionSort(vector<int>& numbers);
void printVector(const vector<int>& numbers);
void seedRand();


int main()
{
    seedRand();
    vector<int> list;
    list = generateRandomVector(100, MAX_NUM);
    printVector(list);
    insertionSort(list);
    printVector(list);
}


void insertionSort(vector<int>& numbers) 
{
    int temp = 0;
    for (unsigned int i = 1; i < numbers.size(); i++) 
    {
        int j = i;
        // Insert numbers[i] into sorted part
        // stopping once numbers[i] in correct position
        while (j > 0 && numbers.at(j) < numbers.at(j - 1)) 
        {
            temp = numbers.at(j);
            numbers.at(j) = numbers.at(j - 1);
            numbers.at(j - 1) = temp;
            j--;
        }
    }
}