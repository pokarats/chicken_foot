/*
Summer 2017 - Assignment1/Program1 of Project 1 - CS261 - Noon Pokaratsiri
*/

#include "hand.h"
#include <algorithm>

using namespace std;

Hand::Hand()
{
}

Hand::~Hand()
{
//	int count{0};
//	cout << "Calling ~Hand() " << endl;	
	for (vector<Bone*>::iterator it = hBones.begin(); it != hBones.end(); it++)
	{
		delete *it;
		*it = nullptr;
//		count++;
//		cout << count << " deleted." << endl;
	}
	hBones.clear();
//	hBones.size();
//	hBones.capacity();
}

// definition for the copy constructor
// there should not be a Hand(anotherHand) copy in this program
Hand::Hand(const Hand& aHand)
{
	for (auto it = aHand.hBones.begin(); it != aHand.hBones.end(); it++)
	{
		this->hBones.push_back(new Bone(**it));
	}
}

// definition for the assignment operator=
// define this function when needed
Hand& Hand:: operator=(const Hand& aHand)
{
	if (this == &aHand)
		return *this;
	else
	{	
		auto itt = this->hBones.cbegin();	
		for (auto it = aHand.hBones.cbegin(); it != aHand.hBones.cend() &&
		itt != this->hBones.cend(); it++, itt++)
		{
			itt = it;
		}

	}
	return *this;
}

bool Hand::isEmpty() const
{
	return (hBones.size() == 0);
}

bool Hand::addBone(Bone* aBone)
{
	hBones.push_back(aBone);
	return true;
}

// in order for removeBone to have been called, aBone would have been found 
// as a match in hand
bool Hand::removeBone(Bone*& rmBone, const int& keyNum)
{
	if (isEmpty())
		return false;
	else
	{
		// search through hand from beginning to end
		for (vector<Bone*>::iterator it = hBones.begin(); it != hBones.end(); it++)
		{	
			// if Bone num1 or num2 matches int
			// remove that Bone
			if ((*it)->getNum1() == keyNum || (*it)->getNum2() == keyNum)
			{
				// update rmBone with the bone removed from hand
				// remove it from hand
				// update hand size to reflect the removal
				rmBone = (*it);
				hBones.erase(it);
				hBones.shrink_to_fit();
				return true;
			}
		}
		// if the for loop exits here, it means keyNum was not found
		return false;
	}
}

// same as removeBone but match has to be exact
bool Hand::removeExactBone(Bone*& rmBone)
{
	if (isEmpty() || !rmBone)
		return false;
	else
	{
		for (vector<Bone*>::iterator it = hBones.begin(); it != hBones.end(); it++)
		{	
			if ((*it)->getNum1() == rmBone->getNum1() && (*it)->getNum2() == rmBone->getNum2())
			{
				// update rmBone with the bone removed from hand
				rmBone = (*it);
				hBones.erase(it);
				hBones.shrink_to_fit();
				return true;
			}
		}
		// if the for loop exits here, it means rmBone was not found
		return false;
	}
}

// return true if double is found, highestDouble is updated
// otherwise, return false, highestDouble points to nullptr
bool Hand::containsDouble(Bone*& highestDouble) const
{
	Bone* 	aDouble{nullptr};
	int		countDouble{0};
	
	for (auto it = hBones.begin(); it != hBones.end(); it++)
	{
		if ((*it)->isDouble())
		{
			// the first double bone found, assign the pointer to this bone to aDouble
			if (aDouble == nullptr)
				aDouble = (*it);
			// otherwise, if it's the subsequent one, reassign aDouble pointer ONLY IF
			// *it points to a bone with higher bone score
			// by the end of the loop, if there is more than one doulbe, 
			// aDouble will point to the highest double in the hand
			else if (aDouble->getBoneScore() < (*it)->getBoneScore())
				aDouble = (*it);
			
			countDouble++;
		}
	}
	
	highestDouble = aDouble;

	if (aDouble == nullptr)
	{
		cout << "Hand does not contain a double! " << endl;
		return false;
	} 
	else
	{
		cout << "Hand contains " << countDouble << " doubles. " << endl;
		cout << "Hand's higest double is: " << highestDouble << endl;
		return true;
	}
}

/*
bool Hand::findBone(int& position, const Bone*& aBone) const
{
	// sort first?
	// find() return iterator
	// find aBone's position from iterator (i.e. hbones[5] = 5
	// function will update position to reflect this
	// returns true
	// if not found, return false
	return false;
}
*/

int Hand::getSize() const
{
	return hBones.size();
}

// call private getHandScore to tally totalScore
int Hand::getTotalScore() const
{
	return getHandScore(hBones.cbegin());
}

// recursively go through hand and add up total score from each Bone
// starting from beginning of vector, passed in iterator from .cbegin()
int	Hand::getHandScore(const vector<Bone*>::const_iterator& it) const
{
	int sum{0};

	if (it != hBones.cend())
	{
		sum = (*it)->getBoneScore();
		sum = sum + getHandScore(it + 1);
		return sum;
	}
	return sum;
}

ostream& operator<<(ostream& out, const Hand& aHand)
{
	if (aHand.isEmpty())
		out << "<NO BONES>" << endl << endl;
	else
	{
		for (auto it = aHand.hBones.begin(); it != aHand.hBones.end(); it++)
		{
			// the iterator points to each element of hBones, which is a Bone*
			// operator<< is also overloaded in the Bone class
			out << (*it);
		}
	}
	return out;
}
