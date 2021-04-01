# Chicken Foot
This project was part of 2017 CS261 Programming Assignments. It is a text based simulation of the game “chicken foot”.  

## How the Game Chicken Foot is Normally Played
It starts with a deck of “cards” in our case. The cards have different numbers on the two ends (simulating a domino). Each card is called a “bone”. Each player is dealt 7 bones and the bones remaining are left in the “chicken yard”. The player that has the largest double (where both numbers on a card are the same) place this bone in the field first. The players then rotate placing a bone that matches one of the numbers with a free side on the field. Any time a double is played, players attach up to 3 bones to the double (making for a “chicken foot”). In fact, when a double is played the ONLY bones that can be played are those that match the double otherwise the player has to draw once. A chicken foot must be filled with 3 bones before the game may proceed. The initial double however is played to all four sides. The player who uses all of their bones wins. There is a point system for the other players based on the bones left in each player’s hands. The goal is to get the fewest points possible.

## Instructions

1. clone the repository
2. Run `make` inside the project directory where the makefile is to compile the executable
3. Run the program `./proj1`

## Program Design Analysis: Design Overview & Object Oriented Principles

### The simulation of the domino game “Chicken Foot” comprises the following classes to manage the different responsibilities and data:

#### Game

The Game Class manages the control of the game, determining the steps from initializing the game by initializing a deck of domino bones, shuffling, dealing the initial bones, and determining the starting player. It also directs the transfer of bones between ChickenYard, Player, and Field. For instance, the Game Class receives information from the Field Class about what bones have free ends that can be played. It passes on that information to the Player Class to determine if a player has a bone that can be played. The class contains pointers to a Field, ChickenYard, Player, to accomplish this.

#### Field
The Field Class models the board of bones that have been played showing the connections between all bones and the free ends. It keeps track of whether or not any double bones have free ends as well as which numbers from regular bones are connectable. When a new bone is added, it directs the bone to the appropriate chain of linked list and prioritizes the location based on the game rules. For instance, if a linked list off one side has a double bone with free connections, i.e. the beginning of an incomplete “Chicken Foot,” the Field Class will direct the played bone to this list before the other lists. Field class has pointers to two instances of FreeList objects and an STL array object containing pointers to PlayedList objects.

#### PlayedList

The PlayedList Class models each chain of bones off each side of the fist piece (the highest double.) It is a triple-threaded singly linked list. It determines where a played bone should be connected based on the game rules. For example, for each new bone, it finds a match between one of the numbers on the new bone and the available free ends. If there is a “Chicken Foot,” the PlayedList Class also makes sure that the new bones connect here first before finding matches with any other free ends. It also determines when a “Chicken Foot” is completed.

#### FreeList
The FreeList Class stores the numbers that are on the free ends as recognized by the Field Class. Each time a new bone is added to the PlayedList Class, the Field Class determines which numbers are the new free ends that need to be added to and removed from the FreeList Class. This class uses a vector to model an array-implemented stack of int datatype. 

#### Player
The Player Class models each player. It interacts with the Game Class, the Hand Class, the ChickenYard Class to pass around the domino bones. For instance, when the Game Class initiates the play, the ChickenYard Class removes a bone that the Player Class adds to the Hand Class. During each round of play, the Player removes a bone from the Hand Class to pass it to the Game Class, which in turns passes it to the Field Class to determine where the bone will connect based on the played bones and the game rules. Bones are passed as pointers to bones not the objects themselves.

#### Hand
The Hand Class models the list of bones that each player holds from the beginning to the end of the game. It is a member in the Player Class. It takes bones from the deck (the ChickenYard Class) and gives it to Player to play the game. It holds the bones in the order which it receives, unsorted. It uses a vector to model an array-implemented stack of Bone* datatype.

#### ChickenYard
The ChickenYard Class simulates a deck of domino bones. It creates a collection of bones that fits client’s specifications for the game and distributes them to the players. It gives the bones to the players when needed and serves as one of the controls to terminate the game — an empty deck stops the play. 

#### Bone
The Bone Class models each domino bone, holding two numbers from a specified minimum to maximum values. This is the object that passes through the other classes to simulate the game playing.

From the list of classes shown in the design overview, each class has clear responsibilities. There are classes whose pointers/or instances are members within other classes such as the Bone Class, the FreeList Class, and the Hand class; however, each of these classes has distinct responsibilities. Changes made to one will not alter how the related classes perform their tasks. For instance, if the specifications for the members in the Bone Class change, the ChickenYard and Hand classes can still add and remove their instances of the Bone Class without needing to be reprogrammed. In addition, by separating out the Player from the Hand Class, it allows for future modifications to simulate the game differently by altering only one of the classes, e.g. deriving multiple types of players from the Player Class, without changing the implementations of the other classes. Similarly, the FreeList Class is simply a stack of numbers and can be utilized in any other program applications not specific to this game. 

The Game, Field, and PlayedList Classes are more specific to this program application and may not be as object oriented as classes within a program can be. The Game Class functions more as a driver/wrapper function that interacts with the other classes to simulate the game. Similarly, the Field Class manages how information from the Bone Class is transferred and stored. Some of the information such as the free ends and the number used as the match key are stored in both the PlayedList Class and the FreeList Class. A more object oriented approach would be to have the PlayedList Class retrieve information from the FreeList Class to perform data comparison instead of redundantly storing the data that are already managed by the other classes. 

### Data Structure Analysis
	
The main data structure that simulates the board to keep track of all the played bones is an array of linked list. This structure is utilized in the Field Class. For this project, the array is allocated to hold 5 members: one slot to hold the highest double bone played and the other four slots to hold each chain of linked list that represents the domino bones off each side of the first bone. The linked lists are used to model a tree in a way that each node can have up to three children to accommodate for the “Chicken Foot” configuration.  

An array of linked lists works well for this application as there are fixed sides to a domino bone and the array will not need to grow during the play. The sides can be made changeable based on client specifications, if desired, by changing the array capacity. Since it is anticipated that there will be varying numbers of bones added to each side of the first bone, a linked list is appropriate as it is by nature self-expanding. A linked list is also simple to add as it does not require the user to specify the location in order to add new pieces of information to the end. Due to the game rules, a list traversal is unavoidable. Although the linked list is used to model a tree, because most bones are non-doubles and the data are not sorted, it performs most of the time at the worst-case-scenario efficiency of O(N) for traversal and searching. Despite having three possible connecting points as a tree node having three children, each node in the linked list that models a regular bone can only have one connection; ergo, the tree is not balanced and a search algorithm needs to visit each subtree until the node with the right key is located.

In order to minimize retrieval time and the necessity to traverse through the entire data structure, another solution that can be explored is to map out the played bones utilizing an array-implemented directed graph. This alternative solution may offer the ability to locate a bone matching certain keys more efficiently by benefiting from array indexing. However, since the number of bones played on each side of the first bone is not predictable, it may be inevitable to grow the array at some point during the game, possibly requiring more memory usage and processing time (to copy arrays) than the current solution.

Another structure used by the Hand, FreeList, and ChickenYard Classes is a stack, which is implemented as a dynamic array using the STL Vector container. For the ChickenYard Class that represents a deck that only requires removal from the top, the stack data structure provides an ideal solution. In comparison, the Hand Class may benefit from a different structure. First of all, instead of simply storing the bones in the order that is received, a strategic player would have sorted the bones to maximize the chance of winning. For instance, the program can store the bones in the hand in a hierarchical tree, from highest to lowest, just as an intelligent domino player may have done each time the player adds a new bone to their hand. In addition, each list of free ends can also be sorted from the highest to the lowest scores to simulate a more realistic behavior of players scanning the field to find the available connections where they can dispose of the highest-scoring bone first. In this way, when a player searches for the highest bone that matches a free end, the search will start from the highest number in the free list as well as the highest bone in the player’s hand, thereby maximizing the probability that the match is found earlier without completing a sequential search through the entire structure.

