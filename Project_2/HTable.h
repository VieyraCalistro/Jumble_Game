#pragma once
#include "SLList.h"
#include <fstream>
#include <string>


template <typename Type>
class HTable
{
public:
	HTable();

	unsigned int (*pointerFunction) (const Type &v);

	SLList<Type>* ArrayOfBuckets = nullptr;

	unsigned int _bucketCount;

		/////////////////////////////////////////////////////////////////////////////
		// Function : Constructor 
		// Parameters : numOfBuckets - the number of buckets
		//              hFunction - pointer to the hash function for this table
		// Notes : constructs an empty hash table
		/////////////////////////////////////////////////////////////////////////////
		HTable(unsigned int numOfBuckets, unsigned int(*hFunction) (const Type &v));

		/////////////////////////////////////////////////////////////////////////////
		// Function : Destructor
		// Notes : destroys a hash table
		/////////////////////////////////////////////////////////////////////////////
		~HTable();

		/////////////////////////////////////////////////////////////////////////////
		// Function : Assignment Operator
		/////////////////////////////////////////////////////////////////////////////
		HTable<Type>& operator=(const HTable<Type>& that);

		/////////////////////////////////////////////////////////////////////////////
		// Function : Copy Constructor
		/////////////////////////////////////////////////////////////////////////////
		HTable(const HTable<Type>& that);

		/////////////////////////////////////////////////////////////////////////////
		// Function : insert
		// Parameters : v - the item to insert into the hash table
		/////////////////////////////////////////////////////////////////////////////
		void insert(const Type& v);

		/////////////////////////////////////////////////////////////////////////////
		// Function : findAndRemove
		// Parameters : v - the item to remove(if it is found)
		/////////////////////////////////////////////////////////////////////////////
		bool findAndRemove(const Type& v);



		/////////////////////////////////////////////////////////////////////////////
		// Function : clear
		// Notes : clears the hash table
		/////////////////////////////////////////////////////////////////////////////
		void clear();

		/////////////////////////////////////////////////////////////////////////////
		// Function : find
		// Parameters : v - the item to look for
		// Return : the bucket we found the item in or -1 if we didn’t find the item.
		/////////////////////////////////////////////////////////////////////////////
		int find(const Type& v) const;

		void printSomeStuff(const char* filePath = "hashdata.txt");

};




template<typename Type>
inline HTable<Type>::HTable()
{
}

template<typename Type>
inline HTable<Type>::HTable(unsigned int numOfBuckets, unsigned int(*hFunction)(const Type &v))
{

	ArrayOfBuckets = new SLList <Type>[numOfBuckets];

	pointerFunction = hFunction;

	_bucketCount = numOfBuckets;

}

template<typename Type>
inline HTable<Type>::~HTable()
{
	clear();
}

template<typename Type>
inline HTable<Type>& HTable<Type>::operator=(const HTable<Type>& that)
{
	if (this != &that)
	{
		clear();

		_bucketCount = that._bucketCount;

		ArrayOfBuckets = new SLList<Type>[_bucketCount];

		for (unsigned int index = 0; index < that._bucketCount; index++)
		{
			ArrayOfBuckets[index] = that.ArrayOfBuckets[index];
		}

		pointerFunction = that.pointerFunction;

		
	}


	return *this;
}

template<typename Type>
inline HTable<Type>::HTable(const HTable<Type>& that)
{
	_bucketCount = that._bucketCount;

	for (unsigned int index = 0; index < that._bucketCount; index++)
	{
		ArrayOfBuckets[index] = that.ArrayOfBuckets[index];
	}
	

	pointerFunction = that.pointerFunction;


}

template<typename Type>
inline void HTable<Type>::insert(const Type & v)
{

	unsigned int drawer = pointerFunction(v);

	SLLIter<Type> iter(ArrayOfBuckets[drawer]);

	ArrayOfBuckets[drawer].addHead(v);
}

template<typename Type>
inline bool HTable<Type>::findAndRemove(const Type & v)
{

	// Grab the return integer of foundOrNot.
	int foundOrNot = find(v);

	SLLIter<Type> iter(ArrayOfBuckets[foundOrNot]);

	// If result is not -1 that means the item was found.
	if (foundOrNot != -1)
	{
		while (!iter.end())
		{
			if (iter.current() == v)
			{

				ArrayOfBuckets[foundOrNot].remove(iter);

				return true;
			}

			++iter;
		}
		
	}


	return false;
}

template<typename Type>
inline void HTable<Type>::clear()
{
	
	delete[] ArrayOfBuckets;

	ArrayOfBuckets = nullptr;

}

template<typename Type>
int HTable<Type>::find(const Type & v) const
{

	unsigned int drawer = pointerFunction(v);

	SLLIter<Type> iter(ArrayOfBuckets[drawer]);

	iter.begin();

	while (iter.CurrentNodeptr != nullptr)
	{
		if (iter.current() == v)
		{
			return drawer;
		}

		++iter;
	}


	return -1;
}

template<typename Type>
inline void HTable<Type>::printSomeStuff(const char * filePath)
{
	// we're gonna need to open a file for all this data
	ofstream outFile(filePath);

	// let's make sure the file got opened
	if (outFile.is_open())
	{
		// number of empty buckets, total count of elements, index of emptiest bucket, index of fullest bucket
		unsigned int empty = 0;
		unsigned int totalCount = 0;
		unsigned int loIndex = 0;
		unsigned int hiIndex = 0;

		// loop through all the buckets
		for (unsigned int i = 0; i < _bucketCount; ++i)
		{
			// add the number of elements in each bucket to the total count
			totalCount += ArrayOfBuckets[i].size();
			// print the index of this bucket and its size to the file
			outFile << i << " : " << ArrayOfBuckets[i].size() << '\n';

			// if this list is empty, increment the empty count
			if (ArrayOfBuckets[i].size() == 0)
				++empty;

			// if this list has less elements than the lowest one recorded so far, store this as the new lowest
			if (ArrayOfBuckets[i].size() < ArrayOfBuckets[loIndex].size())
				loIndex = i;
			// else, if this list has more elements than the highest one recorded so far, store this as the new highest
			else if (ArrayOfBuckets[i].size() > ArrayOfBuckets[hiIndex].size())
				hiIndex = i;
		}

		// print the total count of items and number of buckets to the file
		outFile << '\n' << totalCount << " Total items stored in " << _bucketCount << " buckets\n";
		// print the number of empty buckets
		outFile << '\n' << empty << " Buckets are empty\n\n";
		// get the number of elements in the emptiest bucket
		unsigned int Low = ArrayOfBuckets[loIndex].size();
		// get the range fullest-emptiest+1
		unsigned int range = ArrayOfBuckets[hiIndex].size() - Low + 1;
		// print this info to the file
		outFile << "each bucket contains between " << Low << " and " << Low + range - 1 << " items.\n\n";

		// make a new array to count how many buckets contain each number of items between the emptiest and fullest
		// and initialize each cell to 0
		unsigned int* arr = new unsigned int[range];
		for (unsigned int j = 0; j < range; ++j)
			arr[j] = 0;

		// now we go through and count how many buckets contain each number of items...
		// 3 buckets have 15 items
		// 5 buckets have 16 items
		// etc.
		for (unsigned int k = 0; k < _bucketCount; ++k)
			++arr[ArrayOfBuckets[k].size() - Low];

		// now print this data to the file
		for (unsigned int p = 0; p < range; ++p)
			outFile << arr[p] << " buckets have " << p + Low << " items\n";

		// delete the array we made a minute ago, we are done with it
		delete[] arr;
	}
}


