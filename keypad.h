#include <ncurses.h>
#include <cctype>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

// Globals
int length[2000];
int len = 0;
int check = -1;
//


//
//	Function for getting the current line characters
//
string getCurrentline(int y, int x)
{
	string currentLine = "";
	char temp = ' ';

	for(int i = 0; i < length[y]; i++)
	{
		move(y, i);
		temp = inch();
		currentLine += temp;
	}
	//cout << '('<< length[y] << ')' << endl;

	return currentLine;
}


//
// Function for printing a character based on cursor position
//
void print(int current, int y, int x)
{
	string currentLine = getCurrentline(y, x); // For storing the current line
	move(y, 0); // Start of the line
	clrtoeol(); // Clear the line

	// For Putting in Character at position
	char temp = current;
	string temp2;
	temp2.push_back(temp);
	currentLine.insert(x, temp2);


	for(int i = 0; i < currentLine.length(); i++) // Going through and printing
		printw("%c", currentLine[i]);

	if(current != 10)
		{
			move(y, ++x);
		}
	else
		move(++y, 0);

	length[y]++; // maintaining number of characters in a line
}


//
// Function for when backspace is pressed
//
void backspace(int current, int y, int x)
{
	
	if(x != 0)
	{
		string currentLine = getCurrentline(y, x); // For storing the current line
		move(y, 0); // Start of the line
		clrtoeol(); // Clear the line

		currentLine.erase(currentLine.begin() + (x-1)); // Deleting the character

		for(int i = 0; i < currentLine.length(); i++) // Going Through and printing
			printw("%c", currentLine[i]);

		length[y]--;
		move(y, --x);
	}
	
	else
	{
		if(!y)
			return;
		string currentLine = getCurrentline(y, x); // current line
		string previousLine = getCurrentline(y - 1, x); // previous line

		move(y - 1, length[y - 1]); // moving cursor to right position

		for(int i = 0; i < currentLine.length(); i++) // Going Through and printing
			printw("%c", currentLine[i]);

		move(y, 0);
		clrtoeol(); // clearing that line

		// declaring variables for line delete
		int temp = len;
		string prev = getCurrentline(temp, x);
		int prev_val = length[temp];
		int curr;
		string cur;

		while(temp != y) // from the last line move every line one one forward
		{
			cur = getCurrentline(temp - 1, 0); // storing current string
			curr = length[temp - 1]; // storing current length

			move(temp - 1, 0);
			clrtoeol(); // clearing each line

			move(temp - 1, 0); // to back of the line

			for(int i = 0; i < prev.length(); i++) // Going Through and printing
				printw("%c", prev[i]);

			length[temp - 1] = prev_val;

			prev = cur; // storing previous string 
			prev_val = curr; // storing previous length

			temp--; // previous line
		}

		move(len, 0); // making one line empty
		clrtoeol();

		length[y - 1] = previousLine.length() + currentLine.length(); // making length right
		move(y - 1, length[y - 1]); // moving cursor to the right position

		length[len] = 0; // making last line empty
	}
}

//
// Function for when enter is pressed
//
void enter(int current, int y, int x)
{
	if(x == length[y] && y == len) // end of line and text
	{
		printw("%c", current);
	}

	else if(x == length[y]) // end of a line and not text
	{
		int temp = len;
		while(temp != y) // from the last line move every line one one forward
		{
			print(current,temp,0); 
			length[temp + 1] = length[temp]; // updating length of each line
			temp--;
		}

		length[temp + 1] = 0; // for empty line
		move(y + 1, 0); // cursor to new spot
	}

	else // for anywhere in the middle of the line
	{
		int temp = len;
		while(temp != y) // from the last line move every line one forward
		{
			print(current,temp,0); 
			length[temp + 1] = length[temp]; // updating length of each line
			temp--;
		}

		string currentLine = getCurrentline(y, x); // For storing the current line
		string lastPart = currentLine.substr(x); 
		string firstPart = currentLine.substr(0, x);

		move(y, 0); // Start of first line
		clrtoeol(); // Clear the line
		for(int i = 0; i < firstPart.length(); i++) // Going Through and printing
			printw("%c", firstPart[i]);

		move(y + 1, 0);// new line
		for(int i = 0; i < lastPart.length(); i++) // Going Through and printing
			printw("%c", lastPart[i]);

		length[y] = firstPart.length(); // for line to split
		length[y + 1] = lastPart.length(); // for new line

		move(y + 1, 0); // cursor to new spot
	}

	len++; // Incrementing no of written lines
}

//
// Function for when right arrow is pressed
//
void right(int y, int x)
{
	if(x < length[y]) // normal movement
		move(y, ++x);
	else if(x == length[y] && y < len) // next line movement
		move(++y, 0); 
	check = -1;

}

//
// Function for when left arrow is pressed
//
void left(int y, int x)
{
	if(x > 0) // normal movement
		move(y, --x);
	else if(x == 0 && y > 0) // previous line movement
		move(y - 1, length[y - 1]); 
	check = -1;
}

//
// Function for when up arrow is pressed
//
void up(int y, int x)
{
	if (y == 0) // error checking
		return;

	if (check != -1)
		x = check;

	if(x <= length[y - 1]) // normal movement
		move(--y, x);
	else // movement to end of last sentence
		move(y - 1, length[y - 1]); 

	check = x;

}

//
// Function for when down arrow is pressed
//
void down(int y, int x)
{
	if(y == len) // error
		return;

	if (check != -1)
		x = check;
	
	if(x <= length[y + 1]) // normal movement
		move(++y, x);
	else // movement to end of last sentence
		move(y + 1, length[y + 1]); 

	check = x;

}

