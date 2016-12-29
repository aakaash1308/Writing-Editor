#include <ncurses.h>
#include <cctype>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

string allOfIt = "";

void print(int current)
{
	printw("%c",current);
	allOfIt += current;
}

void backspace()
{
	clear();
	allOfIt = allOfIt.substr(0, allOfIt.length()-1);

	for(int i = 0; i < allOfIt.length(); i++)
		printw("%c", allOfIt[i]);
}

int useKey(int current)
{
	int option;

	if (current == 8 || current == 127) // delete or backspace
		option = 2;
	else if (current == 27) // escape
		option = 3;
	else
		option = 1;

	switch (option)
	{
		case 1 : print(current); return 0;
		case 2 : backspace(); return 0;
		case 3 : return 1;
	}
	return 0;


}

void start()
{
	int current = 0, exit = 0;
	while(!exit) // wating for escape
	{
		current = getch();
		exit = useKey(current);
		refresh();
	}
 	
}
 int main()
 {
 	initscr();
 	noecho();
 	start();
 	endwin();
 	return 0;
 }