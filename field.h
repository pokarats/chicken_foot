/*
Summer 2017 - Assignment2 of Project 1 - CS261 - Noon Pokaratsiri
*/

#ifndef FIELD_H
#define FIELD_H

#include <array>
#include "bone.h"
#include "freeList.h"
#include "playedList.h"

class Field

{
public:
	// if there are 4 sides to each bone, this constant should be 4 + 1 == 5
	// the first array element stores only 1 piece, the highest double
	static const int BONE_SIDES{5};
	
	// constructor, destructor, NEED copy constructor and assignment operator overload
	Field();
	~Field();
	
	// implementation functions
	bool 		addBone(Bone* aBone, const int& keyNum);
	FreeList*	getFreeList() const;
	void		displayField() const;


private:
	// Field class has an array of pointers to Node* (hence Node**) called fieldMap
	// each pointer to Node* represent 1 of 4 sides of the first piece of domino bone
	// laid down by the starting player
	// the size of the array is initilized to 4 + 1 and is fixed
	// change the const BONE_SIDES if a domino bone were to allow more/less sides
	// the + 1 is to accommodate the first piece played:
	/*
		fieldMap[0] --> points to a Node with highest double in the boneNodeData
		fieldMap[1]-fieldMap[4] --> points to a Node with a bone that matches the highest double
	*/

	// by default, each array element is pointing to nullptr until anther bone is added

	
	std::array<PlayedList*, BONE_SIDES>		fieldMap;
	
	int										count;	// # bones played in the field
	
	FreeList*								regularFree;
	FreeList*								doubleFree;

	// private functions:
	int		setFreeEnd(Bone* playedBone, const int& key);

	// dummy copy constructor and operator = overload for unintended future use 
	Field(const Field& aField);
	Field& operator=(const Field& aField);
};
#endif
