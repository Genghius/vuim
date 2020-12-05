#include <stdlib.h>
#include <curses.h>

void insertM();
void commandM();

int main(){
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	commandM();
	return 0;
}

void insertM(){
	while(true){
		int ch = getch();
		int y, x;
		switch (ch){
			case KEY_BACKSPACE:
				nocbreak();
				getyx(stdscr, y, x);
				if(x != 0){
					move(y, --x);
					delch();
				}
				cbreak();
				break;
			case KEY_DC:
				nocbreak();
				delch();
				cbreak();
				break;
			case 27: //<ESC> key 
				commandM();
				break;
			case KEY_DOWN:
				getyx(stdscr, y, x);
				move(++y, x);
				break;
			case KEY_UP:
				getyx(stdscr, y, x);
				move(--y, x);
				break;
			case KEY_LEFT:
				getyx(stdscr, y, x);
				move(y, --x);
				break;
			case KEY_RIGHT:
				getyx(stdscr, y, x);
				move(y, ++x);
				break;
			case KEY_END:
				exit(0);
				break;
			default:
				waddch(stdscr, ch);
				break;
		}
	}
}

void commandM(){
	int ch;
	int y, x;
	char modifier = 'm'; // m for move, d for delete.
	while(true){
		ch = getch();
		getyx(stdscr, y, x);
		switch(ch){
			case '0':
				move(y, 0);
				break;
			case '$':
				while(winch(stdscr) != '\n'){
					move(y, ++x);
				}
				break;
			case 'i':
				insertM();
				break;
			case 'k':
				move(--y, x);
				break;
			case 'j':
				move(++y, x);
				break;
			case 'h':
				move(y, --x);
				break;
			case 'l':
				move(y, ++x);
				break;
			case 'd':
				modifier = 'd';
				break;
			case 'w':
				switch(modifier){
					case 'm':
						if(winch(stdscr) == ' '){
							do{
								move(y, ++x);
							}while(winch(stdscr) == ' ');
						}
						do{
							move(y, ++x);
						}while(winch(stdscr) != ' ');
						break;
					case 'd':
						if(winch(stdscr) == ' '){
							do{
								delch();
							}while(winch(stdscr) == ' ');
						}
						do{
							delch();
						}while(winch(stdscr) != ' ');
						modifier = 'm';
						break;
				}
				break;
			case 'q':
				exit(0);
		}
	}
}
