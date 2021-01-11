                                                                        /*
      WRITE(*,1)
1     FORMAT("This is a C program, you moron!")
      END
                                                                        */
                                                                        #include <stdlib.h>
                                                                        #include <curses.h>
                                                                        #include <pthread.h>

                                                                        void commandM(void);
                                                                        void insertM(void);

                                                                        void insertM(void){
                                                                        	while(1){
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

                                                                        void commandM(void){
                                                                        	int ch;
                                                                        	int y;
                                                                        	int x;
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
                                                                        				goto exit;
                                                                        		}
                                                                        	}
                                                                        exit:
                                                                        	endwin();
                                                                        	exit(0);
                                                                        }

                                                                        int main(void){
                                                                        	initscr();
                                                                        	cbreak();
                                                                        	noecho();
                                                                        	keypad(stdscr, TRUE);
                                                                        	pthread_t command_m_workers[10];
                                                                        	for (int i = 0; i < 10; i++) {
                                                                        		pthread_create(&command_m_workers[i], NULL, (void *)commandM, NULL);
                                                                        		pthread_join(command_m_workers[i], NULL);
                                                                        	}
                                                                        }
