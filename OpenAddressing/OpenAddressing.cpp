#include <iostream>
#include <chrono>
#include <vector>

class Entry
{
private:
	int value;
	bool isEmpty;
	bool isDeleted;

public:
	Entry() : value(0), isEmpty(true), isDeleted(false)
	{

	}

	friend class HashTable;
};

class HashTable
{
private:
	const int INITIAL_SIZE = 10;
	std::vector<Entry> table;

	const float maxLoadFactor = 0.75f;
	int numberOfElements;

public:
	HashTable()
	{
		table.resize(INITIAL_SIZE);
		numberOfElements = 0;
	}

	void Insert(int value)
	{
		int index = GetHash(value);

		while (!(table[index].isEmpty || table[index].isDeleted))
		{
			index = GetNextIndex(index);
		}

		table[index].value = value;
		table[index].isEmpty = false;
		table[index].isDeleted = false;
		numberOfElements++;

		if (GetLoadFactor() >= maxLoadFactor)
		{
			Rehash();
		}
	}

	int Search(int value)
	{
		int index = GetHash(value);

		// We keep probing until...
		// we find an empty slot...
		// or...
		// we find a slot with the value that we are looking for (this slot cannot be marked as deleted).
		while (!(table[index].isEmpty || (table[index].value == value && !table[index].isDeleted)))
		{
			index = GetNextIndex(index);
		}

		if (table[index].isEmpty)
		{
			index = -1;	// If -1 is returned it means that the value we are looking for is not in the table
		}

		return index;
	}

	void Delete(int value)
	{
		int index = Search(value);

		if (index != -1)
		{
			table[index].isDeleted = true;
			numberOfElements--;
		}
	}

	void Display()
	{
		for (int i = 0; i < table.size(); i++)
		{
			std::cout << i << ":\t";

			if (table[i].isEmpty || table[i].isDeleted)
			{
				std::cout << std::endl;
			}
			else
			{
				std::cout << table[i].value << std::endl;
			}
		}
	}

private:
	int GetHash(int value)
	{
		return abs(value) % table.size();
	}

	int GetNextIndex(int currentIndex)
	{
		return (currentIndex + 1) % table.size();
	}

	float GetLoadFactor()
	{
		return (float)numberOfElements / (float)table.size();
	}

	void Rehash()
	{
		std::vector<Entry> copy = table;

		int previousSize = table.size();
		table.clear();
		table.resize(previousSize + INITIAL_SIZE);

		numberOfElements = 0;

		for (Entry e : copy)
		{
			if (e.isEmpty || e.isDeleted)
			{
				continue;
			}
			else
			{
				Insert(e.value);
			}
		}
	}
};

int main()
{
	HashTable hashTable;

	hashTable.Display();
	std::cout << std::endl;

	hashTable.Insert(7);
	hashTable.Insert(20);
	hashTable.Insert(8);
	hashTable.Insert(-7);
	hashTable.Insert(9);
	hashTable.Insert(1);
	hashTable.Insert(0);

	hashTable.Display();
	std::cout << std::endl;

	int value = -7;
	int foundIndex = hashTable.Search(value);
	if (foundIndex != -1)
	{
		std::cout << "Found " << value << "\n\n";
	}
	else
	{
		std::cout << value << " not found\n\n";
	}

	hashTable.Delete(-7);
	hashTable.Delete(20);
	hashTable.Delete(-7);

	hashTable.Display();
	std::cout << std::endl;

	value = -7;
	foundIndex = hashTable.Search(value);
	if (foundIndex != -1)
	{
		std::cout << "Found " << value << "\n\n";
	}
	else
	{
		std::cout << value << " not found\n\n";
	}

	//int size = 10000;
	//HashTable hashTable;
	//std::vector<int> randomValues;

	//for (int i = 0; i < size; i++)
	//{
	//	randomValues.push_back((rand() % 101) - 50);
	//}

	//auto start = std::chrono::high_resolution_clock::now();
	//for (int value : randomValues)
	//{
	//	hashTable.Insert(value);
	//}
	//auto end = std::chrono::high_resolution_clock::now();
	//std::chrono::duration<double, std::milli> milliseconds = end - start;
	//std::cout << "Insert: " << milliseconds.count() << std::endl;

	//start = std::chrono::high_resolution_clock::now();
	//for (int value : randomValues)
	//{
	//	hashTable.Search(value);
	//}
	//end = std::chrono::high_resolution_clock::now();
	//milliseconds = end - start;
	//std::cout << "Search: " << milliseconds.count() << std::endl;

	//start = std::chrono::high_resolution_clock::now();
	//for (int value : randomValues)
	//{
	//	hashTable.Delete(value);
	//}
	//end = std::chrono::high_resolution_clock::now();
	//milliseconds = end - start;
	//std::cout << "Delete: " << milliseconds.count() << std::endl;

	return 0;
}
