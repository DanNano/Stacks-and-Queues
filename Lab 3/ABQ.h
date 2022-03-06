//Trying similar approach but with the template more in connected to each function

#pragma once
//#include "ABS.h" Causes issues if you include it. 
#include <iostream>
//#include "leaker.h"
//Leaker.h will cause issues if you remove backscript. 

template <typename T>

class ABQ
{
	//Variable declaration
private:
	float _ScaleF = 2.0f;
	unsigned int _TSize = 0;
	unsigned int _MaxC = 1;
	T* _Data;

	//They're declared differently just in case it causes issues. 
public:

	ABQ() //Default constructor, sets the default values for generic settings
	{
		_Data = nullptr;
		_MaxC = 1; //As laid out in pdf
		_TSize = 0; //As laid out in pdf
	}

#if 0
	ABQ(int capacity) //Constructor for ABQ where the capacity is set by a determined amount
	{
		_MaxC = capacity;
		_TSize = 0;
		_Data = new T[_MaxC];
	}
#endif // 0


	ABQ(const ABQ& d) //Copy Constructor for ABQ. Was this supposed to be ABQ, as the lab paper said ABQ and that gave me an error
	{
		_MaxC = d._MaxC;
		_Data = nullptr; //Setting to null pointer as I think that caused me some issues on the ABS run where I didn't direction them until I needed to.
		_TSize = d._TSize;

		_Data = new T[d._MaxC];

		for (unsigned int i = 0; i < d._MaxC; i++)
		{
			_Data = d._Data[i]; //Copy into a new array so that it can be resized.
		}
	}

	ABQ& operator=(const ABQ& d) //Copy assignment operator
	{
		delete[] _Data;

		//Copy old variables to d variables
		_MaxC = d._MaxC;
		_TSize = d._TSize;
		_Data = nullptr;

		T* _Data2 = new T[_MaxC];
		for (unsigned int i = 0; i < _MaxC; i++)
		{
			_Data2 = d._Data[i];
		}

		return *this; 
	}

	~ABQ() //Destructor operator
	{
		delete[] _Data;
	}

	void enqueue(T data) //Adds a new element to the end of the queue + resize
	{

		if (_Data == nullptr) //Change the base values so that elements can be added properly
		{
			_Data = new T[1];
			_Data[0] = data; //Hopefully this removes the amount of errors like I had in the first part
			_TSize = 1;
			_MaxC = 1;
		}
		else if (_MaxC == _TSize) //Resize if necessary
		{
			T* ReSizeArrayE = new T[(int)(_MaxC * (_ScaleF))];
			for (unsigned int j = 0; j < _TSize; j++)
			{
				ReSizeArrayE[j] = _Data[j];
			}
			ReSizeArrayE[_TSize] = data;
			_TSize++; //Increase size if
			_MaxC = (int)(_MaxC * (_ScaleF));

			delete[] _Data; //Used to clear up leaker list
			_Data = ReSizeArrayE;
		}
		else if (_TSize < _MaxC)
		{
			_Data[_TSize] = data;
			_TSize++; //Increase size
		}
	}

	T dequeue() //Removes the item at the front of the queue, resizes the queue, and will throw an exception if the queue is empty
	{
		if (_TSize == 0)
		{
			throw std::runtime_error("The Queue is empty! Please add to it before running dequeue again!"); //RunTime Error 1
		}
		else
		{
			T DQ = _Data[0];
			_Data[_TSize] = 0;
			_TSize--;

			T* ReSizeArrayD = new T[_MaxC];
			for (unsigned int i = 0; i < _MaxC; i++)
			{
				ReSizeArrayD[i] = _Data[i + 1];
			}

			if (((float)(_TSize) / (float)(_MaxC)) < (1.0 / (_ScaleF)))
			{
				_MaxC = (int)(_MaxC / (int)(_ScaleF));
			}

			delete[] _Data;

			_Data = ReSizeArrayD;

			return DQ;
		}
	}

	T peek() //View the item at the front of the queue without removing, throws a runtime error if there is no queue
	{
		if (_TSize == 0)
		{
			throw std::runtime_error("The Queue is empty! Please add to it before peeking again!"); //RunTime Error 2
		}
		else
		{
			return _Data[0];
		}
	}
	
	unsigned int getSize() //Returns the current number of items that are in the queue
	{
		return _TSize;
	}

	unsigned int getMaxCapacity() //Returns the current max capacity of the queue
	{
		return _MaxC;
	}

	T* getData() //Returns the array representing the queue
	{
		return _Data;
	}


};

