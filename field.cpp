/*
Summer 2017 - Assignment2/Program1 of Project 1 - CS261 - Noon Pokaratsiri
*/

#include <iostream>
#include "field.h"

using namespace std;


Field::Field() :
	fieldMap{},
	count{0},
	regularFree{new FreeList()},
	doubleFree{new FreeList()}
{
	
	for (auto it = fieldMap.begin(); it != fieldMap.end(); it++)
	{
		*it = new PlayedList();
	}
}

Field::~Field()
{
//	cout << "Calling ~Field() " << endl;
	
	// Starting from fieldMap[0], which points to root for tree/linked list
	// traverse that tree in post-order, deleting each node
	// repeat for each element/linked list in the array
	
	for (auto it = fieldMap.begin(); it != fieldMap.end(); it++)
	{
		delete (*it);
	}
	
	delete regularFree;
	delete doubleFree;
}

bool Field::addBone(Bone* aBone, const int& keyNum)
{
	int		index{0};
	int		aFreeEnd{setFreeEnd(aBone, keyNum)};


	// add higest double to the first array slot if array is empty
	if (fieldMap.at(index)->isEmpty()) 
	{
		// add highest bone to linked list in fieldMap.at(0);
		// add aFreeEnd to the doubleFree list 4x to reflect the 4 free sides
		if (fieldMap.at(index)->add(aBone, aFreeEnd, keyNum))
		{
			for (int i = 0; i < 4; i++)
			{
				doubleFree->addNum(aFreeEnd);
			}
			cout << "Successfully added " << aBone << " to field. " << endl;
			count++;
			return true;
		}	
	}
	// if array is not empty, add to the first list that matches
	// starting at fieldMap.at(1);
	// if list is empty, just add
	else
	{
		// itSkipFactor is advanced only if there's aChickenFoot found in any of the link
		// this is to prioritize the add, to add to this chain and not other chains that
		// may also contain a free end matching the key
		// if there's no ChickenFoot in any of the chains, itSkipFactor will reset to 0;
		int	itSkipFactor{0};

		for (auto it = (fieldMap.begin() + 1); it!= fieldMap.end(); it++)
		{	
			if ((*it)->hasChickenFoot())
				break;
			else
				itSkipFactor++;
		}

		if (itSkipFactor > 3)
			itSkipFactor = 0;

		for (auto it = (fieldMap.begin() + 1 + itSkipFactor); it != fieldMap.end(); it++)
		{
			if ((*it)->add(aBone, aFreeEnd, keyNum))
			{
				if (!doubleFree->isEmpty())
					doubleFree->removeNum(keyNum);
				else
					regularFree->removeNum(keyNum);
				if (aBone->isDouble())
				{
					// each doulbe added to field, yields 3 free sides
					for (int i = 0; i < 3; i++)
					{
						doubleFree->addNum(aFreeEnd);
					}
				}
				else
				{
					regularFree->addNum(aFreeEnd);
				}
				cout << "Successfully added " << aBone << " to field. " << endl;
				count++;
				return true;
			}
		}
	}
	cout << "Unable to add " << aBone << " to field. " << endl;
	return false;
}

// return ptr to doubleFree if not empty, otherwise return regularFree
FreeList* Field::getFreeList() const
{
	return (doubleFree->isEmpty() ? regularFree : doubleFree);
}

int	Field::setFreeEnd(Bone* playedBone, const int& key)
{
	// determine which of the num1 or num2 in aBone is the freeEnd
	// the one not matching keyNum is the freEnd, in the case of a double,
	// num1 and num2 are the same.
	if (playedBone->getNum1() == key)
		return playedBone->getNum2();
	else
		return playedBone->getNum1();	
}

void Field::displayField() const
{
	cout << "\nAvailable Free Ends in Field: " << endl;
	cout << "Doubles Free Ends: " << *doubleFree << endl;
	cout << "Regular Free Ends: " << *regularFree << endl;
	cout << "\n*** Displaying Field ***" << endl;
	cout << "*** Field Contains: " << count << " Bones. ***" << endl;
	cout << "Side 0 is the first piece/highest double played." << endl;

	int side{0};
	for (auto it = fieldMap.begin(); it != fieldMap.end(); it++, side++)
	{
		cout << "** Displaying played bones from side " << side << " ** " << endl;
		(*it)->display();
	}
}

// definition for the dummy copy constructor
// there should not be a Field(anotherField) copy in this program
Field::Field(const Field& aField)
{
}

// definition for the dummy assignment operator=
// define this function when needed
Field& Field:: operator=(const Field& aField)
{
	return *this;
}
