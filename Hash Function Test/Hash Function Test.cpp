#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>

int Hash(int i)
{
	return i / sqrt(1 + pow(i / 1099999999.0, 2)) + 1099999999;
}

int main()
{
	/*
	srand(time(0));

	int numbersInFile = 1000;
	std::vector<int> randomNumbers;

	for (int i = 0; i < numbersInFile; i++)
	{
		randomNumbers.push_back(rand() % 100001);
	}

	std::ofstream numbersWriter("C:\\Users\\kocha\\Desktop\\Numbers.txt");

	for (int randomNumber : randomNumbers)
	{
		numbersWriter << randomNumber << "\n";
	}

	numbersWriter.close();
	*/

	int hashTableSize = 10000;
	std::vector<int> hashTable(hashTableSize);

	for (int i = 0; i < hashTableSize; i++)
	{
		hashTable[i] = 0;
	}

	std::ifstream numbersReader("C:\\Users\\kocha\\Desktop\\hash_contest_filtered.txt");
	std::string stringNumber;
	int number;
	int index;

	while (getline(numbersReader, stringNumber))
	{
		number = std::stoi(stringNumber);
		index = Hash(number) % hashTableSize;
		hashTable[index]++;
	}

	numbersReader.close();

	double sum1 = 0, sum2 = 0;

	for (int i = 0; i < hashTableSize; i++)
	{
		sum1 += hashTable[i];
		sum2 += (hashTable[i] * hashTable[i]);
	}

	sum1 /= hashTableSize;
	sum2 /= hashTableSize;

	std::cout << "sum1 = " << sum1 << "\n";
	std::cout << "sum2 - (sum1 * sum1) = " << sum2 - (sum1 * sum1) << "\n";

	return 0;
}
