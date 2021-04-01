/*
Summer 2017 - Assignment2 of Project 1 - CS261 - Noon Pokaratsiri
*/

#include "freeList.h"
#include <iostream>

using namespace std;

FreeList::FreeList()
{
}

FreeList::~FreeList()
{
//	cout << "Calling ~FreeList() " << endl;	
	freeEnds.clear();
}

// definition for the dummy copy constructor
// there should not be a FreeList(anotherFreeList) copy in this program
FreeList::FreeList(const FreeList& aFreeList)
{
}

// definition for the dummy assignment operator=
// define this function when needed
FreeList& FreeList:: operator=(const FreeList& aFreeList)
{
	return *this;
}

bool FreeList::isEmpty() const
{
	return (freeEnds.size() == 0);
}

bool FreeList::addNum(const int& freeNum)
{
	freeEnds.push_back(freeNum);
	return true;
}

bool FreeList::removeNum(const int& rmNum)
{
	if (isEmpty())
		return false;
	else
	{
		for (vector<int>::iterator it = freeEnds.begin(); it != freeEnds.end(); it++)
		{	
			if ((*it) == rmNum)
			{
				//rmNum = (*it);
				freeEnds.erase(it);
				freeEnds.shrink_to_fit();
				return true;
			}
		}
		// if the for loop exits here, it means rmNum was not found
		return false;
	}
}

int FreeList::getNum(const int& position)
{
	if (isEmpty() || position > getSize())
		return 0;
	else
	{
		return freeEnds.at(position);
	}
}

/*
bool FreeList::findNum(int& position, const Num*& aNum) const
{
	// sort first?
	// find() return iterator
	// find aNum's position from iterator (i.e. hbones[5] = 5
	// function will update position to reflect this
	// returns true
	// if not found, return false
	return false;
}
*/

int FreeList::getSize() const
{
	return freeEnds.size();
}

ostream& operator<<(ostream& out, const FreeList& aFreeList)
{
	if (aFreeList.isEmpty())
		out << "<NONE!!!>" << endl << endl;
	else
	{
		for (auto it = aFreeList.freeEnds.begin(); it != aFreeList.freeEnds.end(); it++)
		{
			// the iterator points to each element of freeEnds, which is an int*
			out << (*it) << ", ";
		}
		out << endl;
	}
	return out;
}
