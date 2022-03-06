#pragma once
#include <iostream>
//#include "leaker.h"

template <typename T> //Template Creation
class ABS
{
private:
	float _ScaleF = 2.0f; //Initializing the scale factor to 2.0
	unsigned int _TSize = 0; //Initial size is zero
	unsigned int _MaxC = 1; //Initial capacity is 1 so that items can be added
	T* _Data;
public:

	ABS() //Default constructor that uses values that are pre-defined
	{
		_Data = new T[_MaxC];
	}

	ABS(int capacity) //Constructor for ABS that starts with a specific value
	{
		_MaxC = capacity;
		_Data = new T[_MaxC];
	}

	ABS(const ABS& d) //Copy Constructor. In Visual Studio, the & sign keeps jumping away.
	{
		_MaxC = d._MaxCapacity;
		_TSize = d._TSize;
		_ScaleF = d._ScaleF;

		_Data = new T[_MaxC];

		for (unsigned int i = 0; i < _TSize; i++)
		{
			_Data[i] = d._Data[i]; //Copy the _Data array to a new array (d) to resize it.
		}
	}

	ABS& operator=(const ABS& d) //Copy Assignment Constructor. 
	{
		_MaxC = d._MaxC;
		_TSize = d._TSize;
		_ScaleF = d._ScaleF;

		_Data = new T[_MaxC];

		for (unsigned int i = 0; i < _TSize; i++)
		{
			_Data[i] = d._Data[i]; //Same with the regular copy constructor, the _Data array is being copied to a new array to resize it.
		}

		return *this;
	}

	~ABS() //Destructor
	{
		delete[] _Data; //Deletes _Data array
	}

	void push(T data) //Adds a new item to the top of the stack
	{
		if (_MaxC < _TSize + 1)
		{
			_MaxC = _MaxC * _ScaleF; //Increase the size of Capacity based on the scale factor

			T* newArray = new T[_MaxC];

			for (unsigned int i = 0; i < _TSize; i++)
			{
				newArray[i] = _Data[i]; //Copies into a new Temporary array
			}

			delete[] _Data;
			_Data = newArray;
		}

		_Data[_TSize++] = data;

	}

	T pop() //Removes the item at the top of the stack
	{
		if (_TSize != 0 && _MaxC != 1)
		{
			T TempT = _Data[_TSize - 1];
			_TSize--;

			if ((_MaxC / _ScaleF) > _TSize)
			{
				_MaxC = _MaxC / _ScaleF;

				T* SizeArray = new T[_MaxC];

				for (unsigned int i = 0; i < _TSize; i++)
				{
					SizeArray[i] = _Data[i];
				}

				delete[] _Data;
				_Data = SizeArray;
			}
			return TempT;

		}
		else
		{
			throw std::runtime_error("You're popping an empty ABS!");
		}
	}


	T peek() //Returns the value that is at the top of the array that but doesn't remove it from the stack
	{
		if (_TSize < 1)
		{
			throw std::runtime_error("You're peeking an empty ABS");
		}
		return _Data[_TSize];
	}

	unsigned int getSize() //Returns the number of items currently in the ABS
	{
		return _TSize;
	}

	unsigned int getMaxCapacity() //Returns the current max capacity of the ABS
	{
		return _MaxC;
	}

	T* getData() //Returns the array representing the stack
	{
		return _Data;
	}

};

//ABS.h file for COP3503 by Daniel Laforce
//Bugs: Cannot get leaker to not give me errors. 