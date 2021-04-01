#include <iostream>

#include "playedList.h"
//#include "bone.h"

using namespace std;

PlayedList::PlayedList() :
	head{nullptr},
	tail1{nullptr},
	tail2{nullptr},
	tail3{nullptr},
	length{0}
{
}

PlayedList::~PlayedList()
{
	cout << "Calling ~PlayedList()" << endl;

	deleteNode(head);

}



PlayedList::Node::Node() : // initialization list for Node without parameters
	nodeData{nullptr},
	chickenFoot{false},
	freeEnd{ChickenYard::MIN_NUM - 1},
	next1{nullptr},
	next2{nullptr},
	next3{nullptr}
{
}

PlayedList::Node::Node(Bone* aBonePtr, int aFreeEnd) :// initialization list for Node with Bone* as parameter
	nodeData{aBonePtr},
	chickenFoot{false},
	freeEnd{aFreeEnd},
	next1{nullptr},
	next2{nullptr},
	next3{nullptr}
{
}

PlayedList::Node::~Node()		
{
	cout << "Trying to delete node" << endl;
	if (nodeData)
	{
		cout << "Deleting nodeData...(aBone)" << endl;
		delete nodeData;
		nodeData = nullptr;
	}
}

// recursively traverse the list to deallocate each node 
// private
void PlayedList::deleteNode(Node*& aHead)
{
	Node* curr{aHead};

	if (curr)
	{
		deleteNode(curr->next3);
		deleteNode(curr->next2);
		deleteNode(curr->next1);
		delete curr;
		curr = nullptr;
		length--;
	}
}

/*void PlayedList::deleteHeadNode()
{
	if (head)
	{
		cout << "Trying to deallocate memory for head nodeData" << endl;
		delete head->nodeData;
		head->nodeData = nullptr;
		head = nullptr;
	}
}*/

bool PlayedList::add(Bone* playedBone, const int& free, const int& keyNum)
{
	Node* newNode{new Node(playedBone, free)};
	
	if (tail1 == nullptr) // adding the highestDouble first piece
	{
		//cout << "Adding Highest Double to linked list. " << endl;
		head = tail1 = newNode;
		length++;
		return true;
	}
	else // all the other pieces
	{
		if (newNode->nodeData->isDouble())
			newNode->chickenFoot = true;
		// if either of the tails is a chickenfoot
		// initially tail2 and tail3 are null
		if (tail1->chickenFoot || (tail2 && tail2->chickenFoot) || (tail3 && tail3->chickenFoot)) 
		{
			if (tail1->chickenFoot)
			{
				if (tail1->next1 == nullptr)
				{
					tail1->next1 = newNode;
				}
				else if (tail1->next2 == nullptr)
				{
					tail1->next2 = newNode;
				}
				else if (tail1->next3 == nullptr)
				{
					tail1->next3 = newNode;
					// if adding to this node, that means chicken foot is filled,
					// can move tail 1, 2, 3, to the last nodes off the former "tail1"
					// which was the chicken foot.
					tail1 = tail1->next1;
					tail2 = tail1->next2;
					tail3 = newNode;
					cout << "Filling ChickenFoot" << endl;
				}
			} 
			else if (tail2 && tail2->chickenFoot)
			{
				if (tail2->next1 == nullptr)
				{
					tail2->next1 = newNode;
				}
				else if (tail2->next2 == nullptr)
				{
					tail2->next2 = newNode;
				}
				else if (tail2->next3 == nullptr)
				{
					tail2->next3 = newNode;
					// if adding to this node, that means chicken foot is filled,
					// can move tail 1, 2, 3, to the last nodes off the former "tail1"
					// which was the chicken foot.
					tail1 = tail2->next1;
					tail2 = tail2->next2;
					tail3 = newNode;
					cout << "Filling ChickenFoot" << endl;
				}
			}
			else if (tail3 && tail3->chickenFoot)
			{
				if (tail3->next1 == nullptr)
				{
					tail3->next1 = newNode;
				}
				else if (tail3->next2 == nullptr)
				{
					tail3->next2 = newNode;
				}
				else if (tail3->next3 == nullptr)
				{
					tail3->next3 = newNode;
					// if adding to this node, that means chicken foot is filled,
					// can move tail 1, 2, 3, to the last nodes off the former "tail1"
					// which was the chicken foot.
					tail1 = tail3->next1;
					tail2 = tail3->next2;
					tail3 = newNode;
					cout << "Filling ChickenFoot" << endl;
				}
			}
			cout << "Bone added to a double/ChickenFoot..." << endl;
		}
		else
		{
			// adding to a regular non chicken foot bone
			if (tail1->freeEnd == keyNum)
			{
				tail1->next1 = newNode;
				tail1 = newNode;
			}
			else if (tail2 && tail2->freeEnd == keyNum)
			{
				tail2->next1 = newNode;
				tail2 = newNode;
			}
			else if (tail3 && tail3->freeEnd == keyNum)
			{
				tail3->next1 = newNode;
				tail3 = newNode;
			}
			else
			{
				cout << "Cannot match bone to any free ends!!!" << endl;
				return false;		
			}
		}
	}
	cout << "Finished adding piece to the list. " << endl;
	length++;
	return true;
}

int PlayedList::getFreeEnd()
{
	if (tail1 || tail2 || tail3)
	{
		if (tail1)
			return tail1->freeEnd;
		else if (tail2)
			return tail2->freeEnd;
		else if (tail3)
			return tail3->freeEnd;
	}
	return ChickenYard::MIN_NUM - 1;
}

bool PlayedList::findKey(const int& keyNum)
{
	if ((tail1 && tail1->freeEnd == keyNum) || (tail2 && tail2->freeEnd == keyNum)
	|| (tail3 && tail3->freeEnd == keyNum))
	{
		return true;
	}
	else
		return false;
}

bool PlayedList::isEmpty() const
{
	return (head) ? false : true;
}

// public access display, calls private display to recursively display the list
void PlayedList::display() const
{
	displayList(head);
}


void PlayedList::displayList(Node* aHead) const
{
	if (aHead)
	{
		cout << aHead->nodeData << "-> ";
		displayList(aHead->next1);
		displayList(aHead->next2);
		displayList(aHead->next3);
		cout << endl;
	}
}

// overload operator<< to cout PlayedList
ostream& operator<<(ostream& out, PlayedList* aPlayedList)
{

	aPlayedList->display();

	return out;
}
