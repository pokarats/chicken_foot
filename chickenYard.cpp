/*
Summer 2017 - Assignment2 Project 1 - CS261 - Noon Pokaratsiri
*/

#include "chickenYard.h"
#include <algorithm> // need this class for shuffle function
#include <random> // need this for deafult_random_engine
#include <chrono> // need this to get time based seed

using namespace std;

const int ChickenYard::MIN_NUM{1};
const int ChickenYard::MAX_NUM{9};

// default constructor, each instance of ChickYard gives a deck of 45 Bones
// from 1:1....to 9:9, no repeats.
ChickenYard::ChickenYard()
{
	for (int aNum1 = MIN_NUM; aNum1 <= MAX_NUM; aNum1++)
	{
		for (int aNum2 = aNum1; aNum2 <= MAX_NUM; aNum2++)
		{
			bones.push_back(new Bone(aNum1,aNum2));
		}
	}
}

ChickenYard::~ChickenYard()
{
//	cout << "Calling ~ChickenYard() " << endl;
//	int count{0};
	for (vector<Bone*>::iterator it = bones.begin(); it != bones.end(); it++)
	{
		delete *it;
		*it = nullptr;
//		count++;
//		cout << count << "bone * deleted." << endl;
	}
	bones.clear();
//	bones.shrink_to_fit();
//	cout << bones.size() << " size" << endl;
//	cout << bones.capacity() << " capacity" << endl;
}

// definition for the dummy copy constructor
// there should not be a ChickenYard(anotherChickenYard) copy in this program
ChickenYard::ChickenYard(const ChickenYard& aChickenYard)
{
	cout << "Calling ChickenYard copy constructor" << endl;
	for (auto it = aChickenYard.bones.begin(); it != aChickenYard.bones.end(); it++)
	{
		this->bones.push_back(new Bone(**it));
	}
}

// definition for the assignment operator=
// define this function when needed
ChickenYard& ChickenYard:: operator=(const ChickenYard& aChickenYard)
{
	cout << "Calling = operator overlaod" << endl;
	if (this == &aChickenYard)
		return *this;
	else 
	{
		auto itt = this->bones.cbegin();	
		for (auto it = aChickenYard.bones.cbegin(); it != aChickenYard.bones.cend() &&
		itt != this->bones.cend(); it++, itt++)
		{
			itt = it;
		}
	}
	return *this;
}

bool ChickenYard::isEmpty()
{
	return (bones.size() == 0);
}

bool ChickenYard::dealBone(Bone*& aBone)
{
	if (bones.size() == 0)
		return false;

	// assign value of last element of bones to aBone, updated by reference
	// delete the last element of bones
	aBone = bones.back(); 
	bones.pop_back();
	return true;
}

void ChickenYard::shuffleBones()
{
	// using time lapsed since epoch to now as seed for the random generator
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();

	// standard library shuffle algorithm
	shuffle(bones.begin(), bones.end(), default_random_engine(seed));
}

int ChickenYard::getSize()
{
	return bones.size();
}

ostream& operator<<(ostream& out, ChickenYard* deck)
{
	if (deck->isEmpty())
		out << "<DECK IS EMPTY!>" << endl;
	else
	{
		for (auto it = deck->bones.begin(); it != deck->bones.end(); it++)
		{
			out << (*it);
		}
		out << endl << "Deck contains:	" << deck->getSize() << "	bones." << endl << endl;
	}

	return out;
}

