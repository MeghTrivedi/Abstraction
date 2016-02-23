/***************************************************************************
Student Name: Megh Trivedi			Student Number:0886172  
Date: 01/14/16                  		Course Name: cis2500

I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
****************************************************************************/

/*Include a library*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

/*define the key buttons*/
#define UP	    'i'
#define DOWN	'k'
#define LEFT	'j'
#define RIGHT	'l'
#define SELECT  'x'

/*prototype*/
void drawBorder(int column, int row);
void userControl(int column, int row);
void aiControl(int column, int row, int yRandNum, int xRandNum, int player, int validSpot[50][50]);

int main()
{
	/*declare a variable*/
	int column = 10;
	int row = 10;
	
	printf("\n \n WELCOME TO ABSTRUCTIONS \n");
	/*printf("HOW MANY ROUNDS WOULD YOU LIKE \n");
	scanf("%d \n", round);*/
	printf("HOW MANY COLUMNS WOULD YOU LIKE? \n");
	scanf("%d", &column);
	printf("HOW MANY ROWS WOULD YOU LIKE? \n");
	scanf("%d", &row);
	
	/*use the game function*/
	userControl(column, row);
	
	refresh();/*refresh the screen*/
	getchar();/*stop the program to end until key is entered*/
	endwin();/*end window*/
	return(0);
}/*end main*/

void userControl(int column, int row)
{
	int xPos, yPos;/*a variables for user positions*/
	int y, x, z = 100;/*variable for counter loops to check taken spots*/
	int spot = 0;
	int validSpot[50][50];
	int scoreA = 0, scoreB = 0;
	int player = 1;
	int yRandNum, xRandNum;
	int ai;
	char buttonIsClick;
	char nameA[10];
	
	/*ask if user wants AI*/
	printf("PLAYER 1 NAME? \n");
	scanf("%s", nameA);
	printf("PLAY WITH AI? (1=yes 2=no) \n");
	scanf("%d", &ai);
	printf("GAME IS STARTING \n");
	
	/*ncurses initialization */
	initscr();/*starts the screen*/
	cbreak();
	noecho();
	start_color();
	/*Set a colour pair*/
	init_pair(1, COLOR_BLACK, COLOR_RED);
	init_pair(3, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_BLACK, COLOR_CYAN);
	init_pair(4, COLOR_BLACK, COLOR_YELLOW);
	init_pair(4, COLOR_BLACK, COLOR_YELLOW);
	init_pair(6, COLOR_BLACK, COLOR_BLACK);
	
	/*set everything to zero*/
	for (y = 0; y < 49; y++)
        {
		for (x = 0; x < 49; x++)
        {
			validSpot[y][x] = 0;
		}/*end loop for row array*/
	}/*end for loop for column array*/
	
	/*loop the program while setting the game*/
	drawBorder(column, row);
	move(1,1);   
	while (z == 100)
        {
		
		/*create random random number*/
		srand(time(NULL));
		yRandNum = (rand() % column)+1;
		xRandNum = (rand() % row)+1;
	
		/*refresh the screen*/
		refresh();
		getyx(stdscr, yPos,xPos);
		
		/*if user choose ai*/
		if (ai == 1)
                {
			/*set color where user clicked*/
			attron(COLOR_PAIR(2));
			/*change players*/
			if (player == 2)
                        {										
					
				while (validSpot[yRandNum][xRandNum] == 1)
                                {						
					/*change spot if the ranNum is taken*/
					if (validSpot[yRandNum][xRandNum] == 1)
                                        {
						yRandNum = (rand() % column)+1;
						xRandNum = (rand() % row)+1;		
					}/*end if*/					
				}/*end while*/
				
				/*pick a spot*/
				move(yRandNum, xRandNum);
				validSpot[yRandNum][xRandNum] = 1;
				printw("2");
				/*assign the color on the taken spots*/
				attron(COLOR_PAIR(3));
				/*put spots on top, down, right, left*/
				move(yRandNum+1, xRandNum);
				validSpot[yRandNum+1][xRandNum] = 1;
				printw("O");
				move(yRandNum-1, xRandNum);
				validSpot[yRandNum-1][xRandNum] = 1;
				printw("O");
				move(yRandNum, xRandNum+1);
				validSpot[yRandNum][xRandNum+1] = 1;
				printw("O");
				move(yRandNum, xRandNum-1);
				validSpot[yRandNum][xRandNum-1] = 1;
				printw("O");
				/*put spots on the corners*/
				move(yRandNum+1, xRandNum+1);
				validSpot[yRandNum+1][xRandNum+1] = 1;
				printw("O");
				move(yRandNum+1, xRandNum-1);
				validSpot[yRandNum+1][xRandNum-1] = 1;
				printw("O");
				move(yRandNum-1, xRandNum+1);
				validSpot[yRandNum-1][xRandNum+1] = 1;
				printw("O");
				move(yRandNum-1, xRandNum-1);
				validSpot[yRandNum-1][xRandNum-1] = 1;
				printw("O");		
				
				spot = 0;
				/*set everything to zero and display the winner*/
				for (y = 1; y < column+1; y++)
                                {
					for (x = 1; x < row+1; x++)
                                        {
						if (validSpot[y][x] == 1)
                                                {
							/*takes the spot*/
							spot = spot + 1;
							if (spot >= (column*row))
                                                        {
								clear();
								if (player == 1)
                                                                {
									scoreA = scoreA + 1;
									player = 1;							
									/*set everything to zero*/
									for (y = 0; y < 49; y++)
                                                                        {
										for (x = 0; x < 49; x++)
                                                                                {
											validSpot[y][x] = 0;
										}/*end loop for row array*/
									}/*end for loop for column array*/											
								}
                                                                else if (player == 2)
                                                                {
									scoreB = scoreB + 1;
									player = 1;																												
									/*set everything to zero*/
									for (y = 0; y < 49; y++)
                                                                        {
										for (x = 0; x < 49; x++)
                                                                                {
											validSpot[y][x] = 0;
										}/*end loop for row array*/									
									}/*end for loop for column array*/											
								}/*end if*/
							}/*end if*/		
						}/*end if*/
					}/*end loop for row array*/
				}/*end for loop for column array*/
				
				/*next player*/
				player = 1;
				
			}/*end if*/	
		}/*end if*/
		
		/*determine which button is clicked and move the cursor*/
		if ((UP == buttonIsClick) && (yPos > 1))
                {
			yPos = yPos - 1;
		}
                else if ((DOWN == buttonIsClick) && (yPos < column))
                {
			yPos = yPos + 1;
		}
                else if ((RIGHT == buttonIsClick) && (xPos < row))
                {
			xPos = xPos + 1;
		}
                else if ((LEFT == buttonIsClick) && (xPos > 1))
                {
			xPos = xPos - 1;
		}
                else if ((SELECT == buttonIsClick) && (validSpot[yPos][xPos] == 0))
                {		
			attron(COLOR_PAIR(4));
			/*if user choose ai*/
			refresh();
			if (ai == 1)
                        {
				/*set color where user clicked*/
				attron(COLOR_PAIR(2));
				/*change players*/
				if (player == 1)
                                {
					/*pick a spot*/
					player = 2;
					move(yPos, xPos);
					validSpot[yPos][xPos] = 1;
					printw("1");
					/*assign the color on the taken spots*/
					attron(COLOR_PAIR(3));
					/*put spots on top, down, right, left*/
					move(yPos+1, xPos);
					validSpot[yPos+1][xPos] = 1;
					printw("O");
					move(yPos-1, xPos);
					validSpot[yPos-1][xPos] = 1;
					printw("O");
					move(yPos, xPos+1);
					validSpot[yPos][xPos+1] = 1;
					printw("O");
					move(yPos, xPos-1);
					validSpot[yPos][xPos-1] = 1;
					printw("O");
					/*put spots on the corners*/
					move(yPos+1, xPos+1);
					validSpot[yPos+1][xPos+1] = 1;
					printw("O");
					move(yPos+1, xPos-1);
					validSpot[yPos+1][xPos-1] = 1;
					printw("O");
					move(yPos-1, xPos+1);
					validSpot[yPos-1][xPos+1] = 1;
					printw("O");
					move(yPos-1, xPos-1);
					validSpot[yPos-1][xPos-1] = 1;
					printw("O");	
				}/*end if*/			
			}
                        else if (ai == 2)
                        {				
				/*set color where user clicked*/
				attron(COLOR_PAIR(2));
		                /*change players*/
				if (player == 1)
                                {
					player = 2;
					move(yPos, xPos);
					validSpot[yPos][xPos] = 1;
					printw("1");
				}
                                else if (player == 2)
                                {
					player = 1;
					move(yPos, xPos);
					validSpot[yPos][xPos] = 1;
					printw("2");
				}/*end if*/
				
				/*assign the color on the taken spots*/
				attron(COLOR_PAIR(3));
				/*put spots on top, down, right, left*/
				move(yPos+1, xPos);
				validSpot[yPos+1][xPos] = 1;
				printw("O");
				move(yPos-1, xPos);
				validSpot[yPos-1][xPos] = 1;
				printw("O");
				move(yPos, xPos+1);
				validSpot[yPos][xPos+1] = 1;
				printw("O");
				move(yPos, xPos-1);
				validSpot[yPos][xPos-1] = 1;
				printw("O");
				/*put spots on the corners*/
				move(yPos+1, xPos+1);
				validSpot[yPos+1][xPos+1] = 1;
				printw("O");
				move(yPos+1, xPos-1);
				validSpot[yPos+1][xPos-1] = 1;
				printw("O");
				move(yPos-1, xPos+1);
				validSpot[yPos-1][xPos+1] = 1;
				printw("O");
				move(yPos-1, xPos-1);
				validSpot[yPos-1][xPos-1] = 1;
				printw("O");	
			}/*end if*/
				
			spot = 0;
			/*set everything to zero and display the winner*/
			for (y = 1; y < column+1; y++)
                        {
				for (x = 1; x < row+1; x++)
                                {
					if (validSpot[y][x] == 1)
                                        {
						spot = spot +1;
						if (spot >= (column*row))
                                                {	
							clear();
							if (player == 1)
                                                        {
								scoreB = scoreB + 1;
								player = 1;				
								/*set everything to zero*/
								for (y = 0; y < 49; y++)
                                                                {
									for (x = 0; x < 49; x++)
                                                                        {
										validSpot[y][x] = 0;
									}/*end loop for row array*/
								}/*end for loop for column array*/									
							}
                                                        else if (player == 2)
                                                        {
								scoreA = scoreA + 1;
								player = 1;
								/*set everything to zero*/
								for (y = 0; y < 49; y++)
                                                                {
									for (x = 0; x < 49; x++)
                                                                        {
										validSpot[y][x] = 0;
									}/*end loop for row array*/
								}/*end for loop for column array*/
							}/*end if*/
						}/*end if*/	
					}/*end if*/
				}/*end loop for row array*/
			}/*end for loop for column array*/	
		}/*end if*/	
		
	        /*display title*/
		attron(COLOR_PAIR(1));
		move(1,column+3);
		printw("                                          ");
		move(1,column+3);
		printw(" ABSTRUCTION!");	
		/*display help*/
		attron(COLOR_PAIR(4));
		move(2,column+3);
		printw("                                          ");
		move(2,column+3);
		printw(" Controls: ijkl      Enter: x");		
		/*display the coordinate of the cursor*/
		attron(COLOR_PAIR(4));
		move(3,column+3);
		printw("                                          ");
		move(3,column+3);
		printw(" Coordinate: %d, %d", yPos, xPos);		
		/*display how many spots are taken*/
		move(4,column+3);
		printw("                                          ");
		move(4,column+3);
		printw(" There are %d spots taken", spot);	
		/*display how manny spots left*/
		move(5,column+3);
		printw("                                          ");
		move(5,column+3);
		printw(" There are %d spots left", (column*row)-spot);		
		/*tell user to change turns*/
		attron(COLOR_PAIR(4));
		move(6,column+3);
		printw("                                          ");
		move(6,column+3);
		printw(" It's Player %d turn", player);	
		/*display the score*/
		attron(COLOR_PAIR(1));
		move(7,column+3);
		printw("                                          ");
		move(7,column+3);		
		printw(" %s has %d WINS", nameA, scoreA);
		/*display the score*/
		move(8,column+3);
		printw("                                          ");
		move(8,column+3);	
		printw(" Second player has %d WINS", scoreB);
		
		/*overlap with a new border*/
		refresh();
		drawBorder(column, row);
		move(yPos, xPos);
		/*next pahse*/
		buttonIsClick = getch();
	}/*end loop*/
}/*end user control function*/

void drawBorder(int column, int row)
{
    /*variable for counter*/
    int y, x;
    /*set color*/
    attron(COLOR_PAIR(1));
    /*draw the border with x*/
    for (y = 0; y < column+2; y++)
    {
	move(y, 0);
        printw("X");
    }/*end for*/
    for (x = 0; x < row; x++)
    {
	move(0, x+1);
	printw("X");
    }/*end for*/
    for (y = 0; y < column+2; y++)
    {
	move(y, row+1);
	printw("X");	
    }/*end for*/
    for (x = 0; x < row; x++)
    {
	move(column+1, x+1);
	printw("X");
    }/*end for*/	
}/*end Border*/
