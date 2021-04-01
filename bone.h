/*
Summer 2017 - Assignment2 of Project 1 - CS261 - Noon Pokaratsiri
*/

#ifndef BONE_H
#define BONE_H

#include <iostream>

class Bone
{
public:
	Bone();					  // default constructor
	Bone(int num1, int num2); // constructor with arguments
	Bone 	(const Bone& aBone); // copy constructor
	~Bone();				  // destructor - not needed
	int 	getNum1() const;
	int 	getNum2() const;
	int 	getBoneScore() const; 	// sum of num1 and num2 
	bool	isDouble() const;		// returns true if num1 == num2

	// assignment operator overload
	Bone& 	operator=(const Bone& aBone);

	//overloading operator<< to print a bone
	friend std::ostream& operator<<(std::ostream& out, Bone* aBone);

private:
	int 	num1;
	int 	num2;

// private functions:

	
//	void 	displayBone() const;

};
#endif
