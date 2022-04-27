#include <iostream>
#include <vector>
#include <chrono>
using namespace std::chrono;
using namespace std;

const int MAX_NUM = 999;

vector<int> generateRandomVector(int listSize); 
void insertionSort(vector<int>& numbers);
void printVector(const vector<int>& numbers);

/*
int main()
{
    auto seedTime = system_clock::now();
    unsigned int seed = duration_cast<milliseconds>(seedTime.time_since_epoch()).count() % UINT_MAX;
    std::srand(seed);
    vector<int> list;
    list = generateRandomVector(100);
    printVector(list);
    insertionSort(list);
    printVector(list);
}
*/

void insertionSort(std::vector<int>& numbers) 
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

vector<int> generateRandomVector(int listSize) 
{
    vector<int> randomList(listSize);
    for (int i = 0; i < listSize; i++) 
    {
        // Multiply by MAX_NUM + 1 and integer divide by RAND_MAX + 1 to get
        // back a random integer between 0 and MAX_NUM
        randomList.at(i) = rand() * (MAX_NUM + 1) / (RAND_MAX + 1);
    }
    return randomList;
}

void printVector(const std::vector<int>& numbers) {
    for (unsigned int j = 0; j < numbers.size(); j++)
    {
        cout << numbers.at(j) << " ";
    }
    cout << endl << endl;
}