/* Driver function.
Summer 2017 - Assignment2 of Project 1 - CS261 - Noon Pokaratsiri

For comments: see below after function main.
*/
#include <iostream>
#include <cstring>

#include "game.h"

using namespace std;

int main(int argc, char** argv)
{
	// jam cout if argc > 1
	if (argc > 1)
		cout.setstate(ios_base::badbit);

	Game 	game;

	cout << endl << endl;
	cout << "CS261 - Project1: Part II (Assignment 2) - " << Game::MY_NAME << endl << endl;
	cout << "Simulation of a Domino Game 'Chicken Foot'" << endl << endl;

	game.initDeck();
	game.initPlayers();
	game.startGame();
	
	cout << endl << endl << "End of Game Simulation. " << endl << endl;
//	cout << "Please ignore the output beyond this point..." << endl;
	return 0;
}

/*
Proj1 - Assignment2 will simulate the following:

1. Initial deck of 45 domino bones, each holding combination of integers from 1 - 9; all bones are unique and there are no repeats. i.e. [1:9] and [9:1] are considered identical.
2. Shuffling of the deck
3. Initial hand of each player; each player is dealt 7 bones.
4. Simulation of the game per game rules as played by 2 Players.
5. Game will follow the following rules:
	- Starting player is the player with the highest double
	- Game will end and user will need to re-start the program if neither player has a double
	- The first bone (aka the highest double) can have 4 connections.
	- Except for the first piece, other double bones can only take 3 connections, not counting the connection to the previous bone. 
	- When a double is played, other than the first piece, this is the beginning of a ChickenFoot; 
	- If there is a double bone(a ChickenFoot beginning) played, no other connections can be made except to the double bone with free ends. This includes the first bone (the highest double).
	- Game will end:
		- when deck is empty OR
		- when either Player is out of bones.
	- The Player who has the LOWEST score wins.
6. Display:
	- Each bone is displayed in this format: [num1:num2] (total score/bone)
	- The field of played bones is displayed in the following way:
	Side 0 : This is the highest double, no chain here, one piece only.
	Side 1 - 4 each represents a chain of bones off the 4 sides of the first bone
	- Each chain is is displayed as in the diagram below:
	- The first bone on each chain is the bone cloested to the left of the screen ([bone1] () here).
	- Each bone has space to hold up to 3 connections, each free connection is represented by |* for connection1, |** for connection2, and so forth.
	- Unless a bone is a double bone/ChickenFoot, ONLY |* can be occupied. Thus, all regular bones at each level will show |** and |***
	- When a connection is occupied/coupled with the next bone, it is represented by |->
	- |-> or |* are lined up according to the "parent" bone similar to a tree strucrture
	- e.g. [bone 4], [bone 5], and [bone 6] are connected to the [double bone 3]

		|[bone1] ()
		|->[bone2] ()
					|->[double bone 3] ()
										|->[bone 4] ()
													  |*
													  |**
													  |***
										|->[bone 5] ()
													  |->[bone7] ()
													  |**
													  |***
										|->[bone 6] ()
													  |*
													  |**
													  |***
					|**
					|***
		|**
		|***

7. Please refer to design.txt for discussions of the roles of the different classes. Briefly, the classes used in this program are:
- Game class will keep track of the actual game from initialization, playing and ending
- Field class will keep track of the list of free ends and directing where the player should add the bone to the field
- PlayedList class will keep track of the played pieces and the connections from each side of the first piece
- Player class will be responsible for playing the bones
- Hand class will keep track of the bones each player has throughout the game
- FreeList class will keep track of the numbers that are the free ends
- ChickenYard class will keep track of the deck of domino bones
- Bone class will model each domino bone that compose a deck, the ChickenYard class, and the Hand class
*/
