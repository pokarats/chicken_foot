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
	bool	add(Bone* playedBone, const int& free, const int& keyNum);
	int		getFreeEnd();
	bool	findKey(const int& keyNum);
	bool	isEmpty() const;
	void	display() const;
//	void	deleteHeadNode();
	// overload operator<< to cout PlayedList
	friend std::ostream& operator<<(std::ostream& out, PlayedList* PlayedList);
private:
	// each chain of linked list represent a chain of domino bones
	// from one side of the first bone, aka the highest double

	// each chain of linked list will model a tree, albeit not balanced
	// Node* head is the highest double
	// Node* next1 is the default connection for a regular bone --> this is the connection that
	// will be allowed
	// Node* next2 and next3 is always null, and will not be allowed to be changed unless is a double Bone
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
		~Node();
	};
	
	Node*	head;
	Node*	tail1;
	Node*	tail2;
	Node*	tail3;
	int		length;	
	
	//private functions

	void	deleteNode(Node*& aHead);
	void	displayList(Node* aHead) const;
};
#endif
