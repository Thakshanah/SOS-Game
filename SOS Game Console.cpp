#include <iostream>
#include<windows.h>

void init_board (void);//To fill the spaces with s or o
void draw_board (void);//constructing board
int numb_players (void);// selecting number of players
int play_again (void);//Selecting y or n to play again
int square_valid (int);//Function related squares of board
int game_done (void);//Check the availabilty of spaces in the board
int find_sos (int, int, char);//find and Count number of sos 
void two_player (void);//Move of two players 
int find_square (void);// To find the square
void player_move(int);//Input os square number and no.of players
void comp_play(void);//Move of Computer until game finishes
void comp_move(void);//Edit completed, Move of computer
void winner (void);//Declare the winner
void how_big(void);//Selection of board size
int comp_find_os (void);//Recognization of os symbol by computer
int comp_find_ss (void);//Recognization of ss symbol by computer


char board[20][20];// array for board size
int Player1, Player2, Computer, players, n;//variables

int main ()
{
	HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE);

	
	
SetConsoleTextAttribute(color, 14);
printf("-----------------------------------------------------------------------------------\n");
printf("---------------------------------SOS-----------------------------------------------\n");
printf("-----------------------------------------------------------------------------------\n");

	while(1)//to check true value
	{
		how_big();//Selection of board size
		init_board();//To fill spaces with s or o
		if(numb_players()==1)
		{
			players=1;
			comp_play();
		}
		else
		{
			players=2;
			two_player();
		}
                if(game_done())
                {
                        printf("Game done!\n");
			winner();
			
			if (!play_again())
                	{
                        	break;
                	}

                }
	} 	
	return 0;
}

void init_board()//edit completed

{
	
	for (int row = 0; row < n; row++)//To fill the spaces with s or o 
	{
		for (int col=0; col<n; col++)
		{
			board[row][col]=' ';
		}
	}
	Player1 = 0;
	Player2 = 0;
	Computer = 0;
	
	return;
}

void draw_board()//edit complete

{
	
	int row, col;//rows, coloumns
	printf("\n");
	if (row != n)//n-size of the board, for 1st horizontal line
		{
			printf(" ");
			for(int ii=0; ii<((n*4)+1); ii++)
			{ 
				printf("-");
			}
			printf(" \n");
		}
	for (int row=0; row<n; row++)//to print overall board
	{
			
		printf(" |"); 
		for (col=0; col<n; col++)//to print | this line as column
		{
			printf(" %c |",board[row][col]);//to allocate space between | this line
		}
		printf(" \n");
		if (row != n)//n-size of the board
		{
			printf(" ");
			for(int ii=0; ii<((n*4)+1); ii++)// print ---- this line as row
			{ 
				printf("-");
			}
			printf(" \n");
		}
	}
	printf("\n");		
	if(players == 1)
	{
		printf("Player has %d points, while I have %d points.\n", Player1, Computer);
	}
	else if (players == 2)
	{
		printf("Player 1 has %d points, while Player 2 has %d points.\n", Player1, Player2);
	}
	return;
}

int numb_players()//Edit completed
{
	char answer;
	
	printf("How many players are playing? (1 or 2)\n");
	do 
	{
		answer = getchar();// Selecting number of players
	} while((answer !='1') && (answer !='2'));
	
	if(answer == '1')
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

void how_big()//edit completed
{

        printf("The board is nxn, how big do you want n to be (4-20)\n");
        do
        {
                scanf("%d", &n);
                if(n>20 || n<4){//nxn board number
                	printf("Invalid board number!!!!! \n");
                	how_big();
				}
        } while((n==0) && (n>20));
        
	
	return;
}

int play_again()//Edit completed
{
  char response;

  printf("Do you want to play again? (y/n) \n");
  do
  {
    response = getchar();//Get the response y or n

  }while ((response != 'y') && (response != 'Y') &&
       (response != 'n') && (response != 'N'));

  if ((response == 'y') || (response == 'Y'))//If yes then play from the begining
  {
     return 1;
  }
  else
  {
    return 0;
  }
}

int game_done()//Edit completed
{
	int row, col;
	
	for (row=0; row<n; row++)//Check the availability of space if space available 
	{
		for(col=0; col<n; col++)
		{
			if (board[row][col] == ' ')
			{
				return 0;
			}
		}
	}
	
	return 1;
}

int square_valid (int square)//Edit completed
{
   int row, col;
   
   if(square>0 && square<((n*n)+1))
   {	
	row = (square-1)/n;// Select array value for square in a row
	col = (square-1)%n;// Select array value for square in a coloumn

	if (board[row][col]==' ')//Allocating space for each square
	{
		return 1;//get value only for space if not return 0
	}
	else 
	{
		return 0;
	} 
  }
  else
  {
	return 0;	
  }
}

void two_player()//Edit completed
{
	do
	{
		player_move(1);//Move of player 1
		if(game_done())
		{ 
			return;
		}
		player_move(2);//Move of player 2
	}while (!game_done());

	return;	
}

void player_move(int player)//edit completed
{
  int square;
  int row, col;
  char symbol;

  do
  {
	draw_board();
        printf("\nPlayer %d enter a square: \n",player);

	do
	{
		scanf("%d", &square);//Select box number in the board
	}while (!square_valid(square));

	row = (square-1)/n;
	col = (square-1)%n;
	
	printf("What symbol do you want to enter in square %d? (S or O) \n", square);
	do
	{
		symbol = getchar();
	}while ((symbol != 'S') && (symbol != 's') && (symbol != 'O') && (symbol != 'o') && (symbol != '0'));//To get all possible inputs in  upper and lower case

	if((symbol == 'S') || (symbol == 's'))
	{
		symbol = 'S';
	}
	else 
	{
		symbol = 'O';	
	}

	board[row][col] = symbol;
   }while(find_sos (square, player, symbol)); 
   
   return;
}


int find_sos (int square, int player, char symbol)//Edit completed
{
	int row,col,sos;
	
	row = (square-1)/n;
	col = (square-1)%n;
	sos = 0;//Count the number of sos 
	
  if(symbol == 'S')//count number of sos when first input is s
  {
	if ((board[row][col-2] == 'S') && (board[row][col-1] == 'O'))
	{
		sos++;
	}
	if ((board[row][col+1]== 'O') && (board[row][col+2] == 'S'))
	{
		sos++;
	}	
	if((board[row+1][col] == 'O') && (board[row+2][col] == 'S'))
	{
		sos++;
	}
	if((board[row-1][col] == 'O') && (board[row-2][col] == 'S'))
	{
		sos++;
	}
	if((board[row+1][col+1] == 'O') && (board[row+2][col+2] == 'S'))
	{
		sos++;
	}
	if((board[row-1][col-1] == 'O') && (board[row-2][col-2] == 'S'))
	{
		sos++;
	}
	if((board[row+1][col-1] == 'O') && (board[row+2][col-2] == 'S'))
	{
		sos++;
	}
	if((board[row-1][col+1] == 'O') && (board[row-2][col+2] == 'S'))
	{
		sos++;
	}
  }
  else if(symbol == 'O')//Count number of sos if first input is o
  {
	if((board[row+1][col] == 'S') && (board[row-1][col] == 'S'))
	{
		sos++;
	}
	if((board[row][col+1] == 'S') && (board[row][col-1] == 'S'))
	{
		sos++;
	}
	if((board[row+1][col+1] == 'S') && (board[row-1][col-1] == 'S'))
	{
		sos++;
	}
	if((board[row+1][col-1] == 'S') && (board[row-1][col+1] == 'S'))
	{
		sos++;
	}
  }



        if (player == 1)
        {
                Player1= Player1+sos;//count of points for player 1
        }
        else if (player == 2)
        {
                 Player2= Player2+sos;//count of points for player 2
        }
        else if (player == 3)
        {
                 Computer= Computer+sos;// count of point for computer
        }
	


	if (sos>0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void winner()//Edit completed
{
	if ((Player1 > Player2) || (Player1 > Computer))
	{
		printf("Player 1 won!\n");//Declare player 1 is won
	}
	else if ((Player2> Player1) || (Player2 > Computer))
	{
		printf("Player 2 won!\n");//Declare player 2 is won
	}
	else if ((Computer > Player1)|| (Computer>Player2))
	{ 
		printf("I won!\n");//Declare computer won
	}
	else
	{
		printf("Game is a draw\n");//If points are equal game is draw
	}
}

void comp_play()//Edit completed
{
	do
	{
		player_move(1);//Move of player
		if (!game_done())
		{
			comp_move();//Move of computer until game finishes
		}
	}while(!game_done());

	return;
}

int find_square()// Edit completed
{
	int row, col, square;
	
	for (square=1; square<((n*n)+1); square++)// Finding the Square
	{
		row = (square-1)/n;
		col = (square-1)%n;
		if (board[row][col] == ' ')// Allocate space for square
		{
			return square;
		}
	}
	return 0;
}

void comp_move()//Edit completed
{
	
  int square;
  int row, col;
  char symbol;

  do
  {
        draw_board();// Constructing board
	if(comp_find_os())
	{
		square = comp_find_os();//If os is found input s
		symbol = 'S';
	}
	else if(comp_find_ss())//If ss is found input o
	{
		square = comp_find_ss();
		symbol = 'O';
	}
	else
	{
		square = find_square();// if nothing is found input s
		symbol = 'S';
	}
	row = (square-1)/n;//Find row
	col = (square-1)%n;//Find coloumn
        
   	board[row][col] = symbol;
	printf("I am putting a %c in %d square\n", symbol, square);
   }while(find_sos (square, 3, symbol));// 3: computer

   return;
}

int comp_find_os ()//Recognization of os symbol by computer
{
	int square;//Select the position of square

	for (int ii=0; ii<n; ii++)
	{
		for(int jj=0; jj<n; jj++)
		{
		   square = ((ii*n) +jj)+1;
		   if(square_valid(square))
		   {
			if((board[ii][jj+1]=='O') && (board[ii][jj+2] == 'S'))
			{
				return square;
			}
                       if((board[ii][jj-1]=='O') && (board[ii][jj-2] == 'S'))
                        {
                                return square;
                        }
			if ((board[ii+1][jj] == 'O') && (board[ii+2][jj] =='S'))
			{
				return square;
			}
                        if ((board[ii-1][jj] == 'O') && (board[ii-2][jj] =='S'))
                        {
                                return square;
                        }
			if((board[ii+1][jj+1] == 'O') && (board[ii+2][jj+2] == 'S'))
                        {
                                return square;
                        }
                        if((board[ii-1][jj-1] == 'O') && (board[ii-2][jj-2] == 'S'))
                        {
                                return square;
                        }
                        if((board[ii+1][jj-1] == 'O') && (board[ii+2][jj-2] == 'S'))
                        {
                                return square;
                        }
                        if((board[ii-1][jj+1] == 'O') && (board[ii-2][jj+2] == 'S'))
                        {
                                return square;
                        }
		  }
		}
	}
	return 0;
}

int comp_find_ss()//Regonization of ss symbol by computer
{
	int square;

        for (int ii=0; ii<n; ii++)
        {
                for(int jj=0; jj<n; jj++)
                {  
                   square = ((ii*n) +jj)+1;

                   if(square_valid(square))
                   {

		        if((board[ii][jj+1]=='S') && (board[ii][jj-1] == 'S'))
                        {
                                return square;
                        }
                        if ((board[ii+1][jj] == 'S') && (board[ii-1][jj] =='S'))
                        {
                                return square;
                        }
                        if((board[ii+1][jj+1] == 'S') && (board[ii-1][jj-1] == 'S'))
                        {
                                return square;
                        }
                        if((board[ii+1][jj-1] == 'S') && (board[ii-1][jj+1] == 'S'))
                        {
                                return square;
                        }
                  }
		}
        }
	return 0;
}
