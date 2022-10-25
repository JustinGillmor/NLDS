#include <vector>
#include <chrono>
#include <iostream>

std::vector<int> generateRandomVector(int listSize, int max)
{
    std::vector<int> randomList(listSize);
    for (int i = 0; i < listSize; i++)
    {
        // Multiply by MAX_NUM + 1 and integer divide by RAND_MAX + 1 to get
        // back a random integer between 0 and MAX_NUM
        randomList.at(i) = rand() * (max + 1) / (RAND_MAX + 1);
    }
    return randomList;
}

void printVector(const std::vector<int>& numbers) 
{
    for (unsigned int j = 0; j < numbers.size(); j++)
    {
        std::cout << numbers.at(j) << " ";
    }
    std::cout << std::endl << std::endl;
}

void seedRand()
{
    auto seedTime = std::chrono::system_clock::now();
    unsigned int seed = std::chrono::duration_cast<std::chrono::milliseconds>(seedTime.time_since_epoch()).count() % UINT_MAX;
    std::srand(seed);
}