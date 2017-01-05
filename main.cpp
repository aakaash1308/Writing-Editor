#include "keypad.h"

using namespace std;

//
// Used to get every key and call appropriate function
//
int useKey(int current)
{
	int x,y;
 	getyx(stdscr, y, x);

	switch (current)
	{
		// For delete and backspace
		case 8 : backspace(current, y, x); return 0;
		case 127 : backspace(current, y, x); return 0;

		// For escape exit
		case 27 : return 1;

		// For enter key
		case 10: enter(current, y, x); return 0;

		// For arrow key manupilation
		case KEY_LEFT: left(y, x); return 0;
		case KEY_UP: up(y, x); return 0;
		case KEY_RIGHT: right(y, x); return 0;
		case KEY_DOWN: down(y, x); return 0;

		// For any other print
		default : print(current, y, x); return 0; 
	}
	return 0;


}

//
// The function called through main when it all begins
//
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

//
//
//
 int main()
 {
 	// Initializing the interface for ncurses 
 	initscr();
 	noecho();
 	keypad(stdscr, TRUE);
 
 	start();


 	endwin();
 	system("clear");
 	return 0;
 }