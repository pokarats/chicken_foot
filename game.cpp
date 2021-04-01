/*
Summer 2017 - Assignment2 of Project 1 - CS261 - Noon Pokaratsiri
*/

#include "game.h"
#include <iostream>
#include <cstring>

using namespace std;

const char	Game::MY_NAME[]{"Noon Pokaratsiri"};
const int	Game::INIT_BONES{7};
const int	Game::NUM_PLAYERS{2};

Game::Game() :
	player1{new Player("Player 1")},
	player2{new Player("Player 2")},
	deck{new ChickenYard()},
	field{new Field()}
{
}

Game::~Game()
{
//	cout << "Calling ~Game() " << endl;
	delete player1;
	delete player2;
	delete deck;
	delete field;	
}

// definition for the copy constructor
// there should not be a Game(anotherGame) copy in this program
Game::Game(const Game& aGame)
{
}

// definition for the dummy assignment operator=
// define this function when needed
Game& Game:: operator=(const Game& aGame)
{
	return *this;
}

// operator<< is overloaded in ChickenYard class to allow cout << deck;
inline void Game::showDeckStatus()
{
	cout << "Deck Status (from bottom to top of stack): " << endl;
	cout << deck;
	cout << endl << endl;
}

inline void Game::showHandStatus()
{
	player1->displayPlayersHand();
	player2->displayPlayersHand();
	cout << endl << endl;
}

void Game::initDeck()
{
	// Display the deck before and after shuffling 
	cout << "Initializing Deck..." << endl;
	showDeckStatus();
	deck->shuffleBones();
	cout << "After shuffling..." << endl;
	showDeckStatus();
}

void Game::initPlayers()
{
	// display each player's hand before being dealt bones
	showHandStatus();

	// deal 7 Bones to player1 and player2 from the shuffled deck
	cout << "Dealing " << INIT_BONES << " bones to each player..."
		 << endl << endl;
	for (int i = 0; i < INIT_BONES; i++)
	{
		player1->drawBone(*deck);
		player2->drawBone(*deck);
	}

	// display each player's hand after being dealt bones
	cout << endl << "After dealing..." << endl;
	showHandStatus();
}

void Game::startGame()
{	
	cout << "Deck Status: " << endl;
	showDeckStatus();
	cout << "Starting game... " << endl << endl;
	
	// game control flow done by private functions
	controlGame();
}

// this function determines who has the starting player is
// calls private startPlayer() function
void Game::controlGame()
{
	Player*		startingPlayer{nullptr};
	
	// Determine startingPlayer
	cout << "The starting player is the player with the highest double bone. " << endl << endl;
	startingPlayer = startPlayer();
	
	if (startingPlayer == nullptr)
	{
		cout << "Neither player has double!!!" << endl;
		endGame();
	}
	else 
	{
		cout << startingPlayer->getPlayersName() << " is the Starting Player. " << endl;
		playGame(startingPlayer);
	}		
}

// control the logic of the game
void Game::playGame(Player* aPlayer)
{
	Player*		currPlayer{aPlayer};
	bool		stuck{false};
	bool		found{false};
	int			currRound{1};
	int			aFreeEnd{ChickenYard::MIN_NUM - 1};
	Bone*		playedBone{nullptr};
	FreeList*	keyList{nullptr};


	// currPlayer for Round # 1 is the player with highest double passed in from controlGame
	// a Round allows each player to play once 
	if (currPlayer == player1)
		currPlayer = player1;
	else
		currPlayer = player2;

	do
	{
		cout << endl << endl;
		cout << "------------	Playing Round # " << currRound << " ------------" << endl;		
		/*
		1. currPlayer playCard:
			a. if currRound == 1, play the highest double
			b. for all other plays: play a card that matches any num in the keyList
			c. keyList is determine by field, is always the double free unless it's empty
		2. 
			a.if player playCard is true (player has a matching card), add bone to Field
			b. if playCard is false (means player either has an empty hand or no match)
				b.1 handEmpty --> endGame
				b.2 drawCard
					b.2.1 if drawBone is false --> endGame
		3. swapPlayer and repeat 1->3
		4. next round
		5. The played bones are displayed after each player has played.
		*/
		for (int i = 0; i < NUM_PLAYERS; i++)
		{
			cout << endl << currPlayer->getPlayersName() << "'s Turn to play..." << endl;
			// first round starts with playing the highest double
			if (currRound == 1)
			{
				playedBone = currPlayer->getHighestDouble();
				aFreeEnd = playedBone->getNum1();
				if (currPlayer->playHighestDouble(playedBone))
				{
					if (field->addBone(playedBone, aFreeEnd))
					{
						cout << "Hihest double bone added to field. " << endl;
					}
					else 
					{
						// this shoudn't happen!! If it does, game over...
						cout  << "Unable to add double bone to field!! " << endl;
						currPlayer->addBone(playedBone);
						stuck = true;
					}
				}
				swapPlayer(currPlayer);
				cout << endl << currPlayer->getPlayersName() << "'s Turn to play..." << endl;
				i++; // this is so that the for loop is advanced 1 extra round 
				goto playRegular;
			} 
			else if (currRound > 1)
			{
				// regular play starts from the 2nd player in first round
				// and all players in the subsequent rounds
				playRegular:
				{
					// Field will return either doubleFree if not empty
					// or regularFree
					// aFreeEnd is a number from either of the freeList
					// if freeList isEmpty, aFreeEnd is assigned an out of bound number
					keyList = field->getFreeList();
					for (int index = 0; index < keyList->getSize(); index++)
					{
						// aFreeEnd refers to num that one of the freeEnds available to play
						aFreeEnd = keyList->getNum(index);
						if (currPlayer->playBone(playedBone, aFreeEnd))
						{
							found = true;
							cout << "Adding " << playedBone << " to field. " << endl;
							if (!field->addBone(playedBone, aFreeEnd))
							{
								cout << "Problem with adding " << playedBone << " to field!!\n";
								currPlayer->addBone(playedBone);
								found = false;
							}
							break;
						}
						else
							found = false;
					}
					if (!found)
					{	
						if (!currPlayer->hasBones())
						{	
							cout << currPlayer->getPlayersName() << " is out of bones. " << endl;
							stuck = true;
							break;
						}
						else if (!currPlayer->drawBone(*deck))
						{
							cout << "Deck is out of bones. " << endl;
							stuck = true;
							break;
						}
					}	
				}
			}
			// if currPlayer == player1, now currPlayer == player2
			swapPlayer(currPlayer);
		}
		field->displayField();
		currRound++;
	} while (!stuck);

	endGame();
}

// show each player's hand and state the winning player
// also show deck
inline void Game::endGame()
{
	cout << endl << "Ending game..." << endl << endl;
	cout << "Showing Players' Hands: " << endl << endl;
	showHandStatus();

	cout << "WINNER IS: ";
	if (player1->getTotalScore() < player2->getTotalScore())
		cout << player1->getPlayersName() << endl;
	else if (player2->getTotalScore() < player1->getTotalScore())
		cout << player2->getPlayersName() << endl;
	else if (player1->getTotalScore() == player2->getTotalScore())
		cout << "TIED!! " << endl;

	cout << endl << "Showing Deck: " << endl;
	showDeckStatus();
	field->displayField();
}

inline void Game::swapPlayer(Player*& aPlayer)
{
	(player1 == aPlayer) ? aPlayer = player2 : aPlayer = player1;
}

// determine who has the higest double and return the pointer to that player
Player* Game::startPlayer()
{
	// local variables:
	Player*		startingPlayer{nullptr};
	Bone*		player1HDouble{nullptr};
	Bone*		player2HDouble{nullptr};

	/*
	Determine who has a double. 
	1. If both have double, determine who has highest double.
	2. if neither has double, return nullptr.
	*/
	
	// get each player's highest double
	player1HDouble = player1->getHighestDouble();
	player2HDouble = player2->getHighestDouble();
	
	// both players have double
	if (player1HDouble && player2HDouble)
	{
		(player1HDouble->getBoneScore() > player2HDouble->getBoneScore()) ? 
		startingPlayer = player1 : startingPlayer = player2;

		cout << player1->getPlayersName() << "'s highest double is: " 
			 << player1HDouble << endl;
		cout << player2->getPlayersName() << "'s highest double is: " 
			 << player2HDouble << endl << endl;
	
	}
	// only one of the players has double
	else if (player1HDouble || player2HDouble)
	{
		if (player1HDouble)
		{
			startingPlayer = player1;
			cout << startingPlayer->getPlayersName() << "'s highest double is: " 
				 << player1HDouble << endl << endl;
		} 
		else if (player2HDouble)
		{
			startingPlayer = player2;
			cout << startingPlayer->getPlayersName() << "'s highest double is: " 
				 << player2HDouble << endl << endl;
		}
	}
	// otherwise startingPlayer remains nullptr

	return startingPlayer;
}

