/*
Summer 2017 - Assignment2 of Project 1 - CS261 - Noon Pokaratsiri
*/

#ifndef FREELIST_H
#define FREELIST_H

#include<iostream>
#include <vector>

class FreeList
{
public:
	FreeList();
	~FreeList();
	bool	isEmpty() const;
	bool	addNum(const int& freeNum);
	bool	removeNum(const int& rmNum); // find rmNum and erase from vector, update rmNum with *it
	int		getNum(const int& position); // returns an int stored at certain position in vector
//	bool	findBone(int& position, const Bone*& aBone) const;
	int		getSize() const;
	
	// overload operator<< to cout hand
	friend std::ostream& operator<<(std::ostream& out, const FreeList& aFreeList);
private:
	std::vector<int> freeEnds;

// private functions
	
	// dummy copy constructor and operator = overload for unintended future use 
	FreeList(const FreeList& aFreeList);
	FreeList& operator=(const FreeList& aFreeList);

};
#endif
