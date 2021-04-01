/*
CS 261 - Summer 2017 - Assignment 2 of Project 1 - Noon Pokaratsiri
*/

#ifndef PLAYEDLIST_H
#define PLAYEDLIST_H

#include <iostream>
#include "bone.h"
#include "chickenYard.h"

class PlayedList
{
public:

	PlayedList();
	~PlayedList();
	bool	add(Bone* playedBone, const int& newFree, const int& keyNum);
	bool	isEmpty() const;
	bool	hasChickenFoot() const;
	void	display() const;
	
	// overload operator<< to cout PlayedList
	friend std::ostream& operator<<(std::ostream& out, PlayedList* PlayedList);
private:
	// each chain of linked list represent a chain of domino bones
	// from one side of the first bone, aka the highest double

	// each chain of linked list will model a tree, albeit not balanced
	// Node* head is the first bone that matches the highet double in the fieldMap[0] PlayedList
	// Node* next1 is the default connection for a regular bone --> this is the only connection
	// that will allowed.
	// Node* next2 and next3 is always null, and will not be allowed to be changed unless 
	// Node is a double/chickFoot, then it must be filled.

	struct Node 
	{
		Bone*	nodeData;
		bool	chickenFoot;
		int		freeEnd;

		Node*	next1;
		Node*	next2;
		Node*	next3;
	
		Node();
		Node(Bone* aBonePtr, int aFreeEnd);
		// copy and = operator overload for struct Node
		Node(const Node& sNode);
		Node& operator=(const Node& node2);
		~Node();
	};
	
	Node*	head;
	int		length;	// length of each chain
	
	//private functions
	bool	recursiveAdd(Node* aHead, Bone* playedBone, const int& newFree, const int& key);
	void	deleteNode(Node*& aHead);
	Node*	makeNewNode(Bone* playedBone, const int& newFree);
	bool	findChickenFoot(Node* aHead) const;
	void	displayList(Node* aHead, int level) const;
	void 	printLevelSpacers(std::ostream& out, int spacers) const; // to format ouput
};
#endif
