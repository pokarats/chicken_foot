/*
Summer 2017 - Assignment2 of Project 1 - CS261 - Noon Pokaratsiri
*/

#ifndef HAND_H
#define HAND_H

#include "bone.h"

#include <vector>

class Hand
{
public:
	Hand();
	~Hand();
	bool	isEmpty() const;
	bool	addBone(Bone* aBone);
			// find aBone whose num1 or num2 matches keyNum and erase Bone from vector, 
			// update rmBone with *it
	bool	removeBone(Bone*& rmBone, const int& keyNum); 
	bool	containsDouble(Bone*& highestDouble) const;
	bool	removeExactBone(Bone*& rmBone); // find exact match of rmBone and remove
//	bool	findBone(int& position, const Bone*& aBone) const;
	int		getSize() const;
	int		getTotalScore() const;

	// copy constructor and operator = overload for
	Hand(const Hand& aHand);
	Hand& operator=(const Hand& aHand);

	// overload operator<< to cout hand
	friend std::ostream& operator<<(std::ostream& out, const Hand& aHand);
private:
	std::vector<Bone*> hBones;

// private functions
	int	getHandScore(const std::vector<Bone*>::const_iterator& it) const;
	

};
#endif
