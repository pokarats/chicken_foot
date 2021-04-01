/*
Summer 2017 - Assignment2 of Project 1 - CS261 - Noon Pokaratsiri
*/

#include "bone.h" 
#include <iostream>

using namespace std;

Bone::Bone() :
	num1{0},
	num2{0}
{
}

Bone::Bone(int num1, int num2) :
	num1{num1},
	num2{num2}
{
}

Bone::~Bone()
{
	// do nothing destructor as no dynamic memory allocation in this class
}

// definition for the copy constructor
Bone::Bone(const Bone& aBone) :
	num1{aBone.num1},
	num2{aBone.num2}
{
}

// definition for the  assignment operator=
// define only when needed
Bone& Bone:: operator=(const Bone& aBone)
{
	if (this == &aBone)
		return *this;
	else
	{
		this->num1 = aBone.getNum1();
		this->num2 = aBone.getNum2();
	}
	return *this;
}

int Bone::getNum1() const
{
	return num1;
}


int Bone::getNum2() const
{
	return num2;
}

int Bone::getBoneScore() const
{
	return num1 + num2;
}

bool Bone::isDouble() const
{
	return (num1 == num2);
}

/*
void Bone::displayBone(ostream& out) const
{

	out << "[ " << num1 << " : " << num2 << " ]" << endl;
	out << "Total Score/Bone: " << getBoneScore() << endl << endl; 
}
*/

ostream& operator<<(ostream& out, Bone* aBone)
{
	out << "[" << aBone->num1 << ":" << aBone->num2 << "]";
	out << "(" << aBone->getBoneScore() << ")  ";

	return out;
}
