# SE_Mini_Projects


## Object Oriented Programming (Phonebook Directory)

### 1.	ABSTRACT

Phone Directory system is a small application developed using C++. In older days we stored all our important contact details in books and papers. Here we propose a new system, using this application we can store all the details in central repository. In manual method if we forget information book then it very difficult to get the contact details. In manual mode it also becomes very difficult to update a particular record, also this system of storing numbers is inefficient. Some of the disadvantages of this manual system are:

•	Takes Up a Lot of Space. The biggest downfall to manual document filing is the amount of place it takes.
•	Prone to Damage and Being Misplaced. Manual document filing means you are placing faith in the people handling the files. 
•	Hard to Make Changes. 
•	Access Time.
•	Lack of Security. 

•	Higher Cost
 
By using our application, we can see our contacts whenever we want, here we will have options like search record by name or using their number, insert new record and so on. In this project we can save our contacts, their telephone number, we can see all of these at a time. This system is developed keeping in mind the general needs of the user while using the phone directory book. In order to keep Phone Directory updated, the user will have the authority to add and delete as well as modify the existing records within the phone book directory.

### 2	INTRODUCTION

We have to implement a phone directory using C++ programming language. To accomplish this task, we will have to use some kind of database which will store all the records and will maintain the records as well. As our phone directory has limited fields using a File to store this data will be a good choice. SQL database can also be used for this task but as the scale of the project is small, we do not need a proper database to store our information.

To access, modify, insert record in our directory we will be making use of a Doubly Linked List with an internal node structure with 3 fields:
•	Name
•	Phone Number 
•	Telephone Number
A DLL makes all the operations of the directory very easy and efficient. As DLL do not require continuous memory locations to maintain the data our application can easily handle a large amount of data without any problem as well.


### 2.1	SCOPE

•	Maintaining Phone Records
•	Updating Phone Records
•	Checking Validity of a Record
•	Inserting New Records
•	Deleting Records
•	Providing a Brief Summary of the Directory


### 2.2	REQUIREMENT ANALYSIS

For this project we will require a data file at the backend which will store all the data. We can achieve this using File Handling. We will also require some C++ libraries for handling the string operations.

As our project is a phone directory it is possible that the array data structure will run out of memory as it stores data in consecutive memory locations but to tackle this issue we will be using DLL as DLL can use all the memory available in the RAM the memory problem will be solve also, DLL makes storing data with different data types easy.

### 2.3	SOFTWARE AND HARDWARE DETAILS

SOFTWARE:

•	Windows OS / Linux
•	DEV C++ IDE
•	C++ Compiler
              
HARDWARE:

•	Laptop / PC
•	GB Ram
•	1 GB Storage


### 2.4	LIBRARIES / PACKAGES USED:

- #include<iostream>
-	#include<fstream>
-	#include<cstring>
-	#include<conio.h>
-	#include<algorithm>
-	#include<stdlib.h>
-	#include<lexical_cast.h>
-	#include<string>
-	#include<iomanip>

### 3	SOURCE CODE FUNCTIONS

Functions in the code are:

•	new_contact(): Adds new contacts to the phonebook.

•	search_contact_by_name(): Searches for a name in the phonebook.

•	search_contact_by_number(): Searches for a phone number in the phonebook.

•	update_contact(): Finds a contact by name and shows options to update its different values.

•	display(): Displays the content of the phonebook.

•	del_contact(): Finds a contact by name and deletes it.

•	get_data(): Extracts data from the txt phonebook file into the program.

•	feed_data():  Writes all the changes to the file.


•	summary(): Displays summary of the phonebook like the total number of contacts, total number of contacts with telephone number, and the most frequent first letter.

•	validate_phone(): Checks validity of the entered phone number. 

•	partial_name_search(): Checks if a name starts with the entered string.

•	sort(): sorts the directory in ascending order.

•	partial_number_search(): Checks if a number starts with the entered number




## Data Structure Lab (SUDOKU GAME)

### INTRODUCTIONS

We have to implement a Sudoku Game using Python/C/C++. For this task I will be using Python Programming Language as Python gives us features which will help us implement this game easily. Sudoku Game can be implemented using 2 main algorithms:

1.	Brute force
2.	Back Tracking 

I have decided to use Back Tracking to solve this problem as it is far more efficient than Brute Force algorithm. 

The Project will consist of 2 main modules:

•	Player Flow
•	Solution

The final Output will be a Terminal Based UI where the user will input the row column and the Number they want to input in that position.

There are 3 levels to the game:
1.	Easy
2.	Medium
3.	Hard

The user will get an option to choose the level, quit the game whenever he wants and the user can also keep checking if his solution is correct or not.
The game will have a timer which will tell you how much time you have taken to complete the puzzle.


### ALGORITHM AND FLOWCHART

For this Problem I have Created 3 Modules:

1.	Boards: Contains the 3 Boards used in Game
2.	Player: Contains the Player Game Flow 
3.	Solution: Contains the Puzzle Solver

Player Module:

1.	Step 1:  Start

2.	Step 2: User Input (Easy/Med/Hard)

3.	Step 3: While Quit != Yes

4.	Step 4: Display Board

5.	Step 5: Take Player Input

6.	Step 6: Check if Input is Valid

7.	Step 7: If Valid -> Go to Step 7 Else Go to Step 4

8.	Step 8: User Input (Submit) 

9.	Step 9: If Submit == Yes -> Go to Step 13 Else Go to Step 10

10.	Step 10: User Input (Quit)

11.	Step 11: If Quit == Yes -> Go to Step Else Go to Step 12

12.	Step 12: End While Go to Step 16

13.	Step 13: Compare Solution Board and Player Board

14.	Step 14: If Solution Board == Player Board Print “Congratulations!” Go to Step 12

15.	Step 15:  If Solution Board == Player Board Print “Your solution is not correct please try other solutions!!” Go to Step 10

16.	Step 16: End




Solution Module (Back Tracking Algorithm):

1.	Start

2.	Create a function that checks after assigning the current index the grid becomes unsafe or not –> Check Conditions.

3.	Create a Recursive function.

4.	Check for any Empty Location. 

5.	If present, then assign a number from 1 to 9, check if assigning the number to current index makes the grid unsafe or not

6.	If safe then Recursively call the function for all safe cases from 0 to 9.

7.	If any recursive call returns true, end the loop and return true. If no recursive call returns true then return false.

8.	If there is no unassigned location then return true.

9.	End

### REQUIREMENTS


4.1	SOFTWARE REQUIREMENTS

•	Python V (3.6 or Higher)
•	Windows OS/ Linux


4.2	LIBRARIES/PACKAGES USED

•	Time Module




 ## Computer Graphics (Space Wars)
 
 ### 1.	Introduction

We are planning to make a game using python. The game will be a kind of a stress buster and will be easy to play. The game is a space adventure game where the user controls the spaceship and they have to blast the obstacles with the help of the laser shooters which will be provided to the user the user can also dodge the obstacles, whenever he crashes into an obstacle the life of the user will reduce.

### 2.	Motivation

We often watch sci fi movies and it fascinates us. So, we took inspiration from the sci fi movies like The Guardians of the Galaxy, Avengers and decided to make a game which had a space war theme to it.

### 3.	Objectives

We have a good experience with programming in python and we have used libraries like pygame and turtle to make other projects in the past.
We plan to add maximum functionality to our game to make it easy to use and fun to play.

### 4.	Proposed Method 

We will be using python to write the code for this game we have graphics libraries like pygame, turtle, kite etc. in python to help us with this project but we plan to use pygame only.

### References

•	Pygame Documentation
•	Stackoverflow
•	Geek for Geeks 
•	Google 
•	Youtube.

