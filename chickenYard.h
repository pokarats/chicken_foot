/*
Summer 2017 - Assignment2 of Project 1 - CS261 - Noon Pokaratsiri
*/

#ifndef CHICKENYARD_H
#define CHICKENYARD_H

#include "bone.h"
#include <vector>

class ChickenYard

{
public:
	static const int MIN_NUM;	//min number on bone
	static const int MAX_NUM;	//max number on bone

	ChickenYard();
	ChickenYard(const ChickenYard& aChickenYard);	// copy constructor
	~ChickenYard();
	bool	isEmpty();
	bool	dealBone(Bone*& aBone);
	void	shuffleBones();
	int		getSize();

	// operator = overload for unintended future use 
	ChickenYard& operator=(const ChickenYard& aChickenYard);
	// overloading << for class ChickenYard to print an instance of ChickenYard
	friend std::ostream& operator<<(std::ostream& out, ChickenYard* deck);

private:
	std::vector<Bone*>	bones;

// private functions:
	

};
#endif
