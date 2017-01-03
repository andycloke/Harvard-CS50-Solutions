/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

//location of blank square
int blankX, blankY;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(5000);
        }

        // sleep thread for animation's sake
        usleep(2500);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(200000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
  int evenBoard = 1 - (d % 2);   //even board flag
  //fill board numbers
  for (int i = 0, num = d*d - 1; i < d; i++)
  {
      for (int j = 0; j < d; j++)
      {
        // for even boards, reverse order of 1 and 2
        if (evenBoard && num == 2)
        {
          board[i][j] = 1;
          num--;
        }
        else if (evenBoard && num == 1)
        {
          board[i][j] = 2;
          num--;
        }
        //populate other spaces with numbers, making a note of location of blank (0)
        else
        {
          board[i][j] = num;
          if (num == 0)
          {
            blankX = j;
            blankY = i;
           }
          num--;
        }
      }
  }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
  printf("\n\n");
  for (int i = 0; i < d; i++)
  {
      for (int j = 0; j < d; j++)
      {
        //user _ to represent blank square
        if (board[i][j] == 0)
        {
          printf(" _");
        }
        else
        {
          printf("%2i", board[i][j]);
        }
        //print spaces between numbers, but not at the end
        if (j < d - 1)
        {
          printf("   ");
        }
      }

      printf("\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    
   int toSwapX, toSwapY;

    //find coordinates of given number. //TODO: ADD ERROR CHECKING if bum not found?
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
           if (board[i][j] == tile)
            {
                toSwapX = j;
                toSwapY = i;
            }
        } 
    }

    //calculate differences in X and Y positions
    int xDiff = abs(blankX-toSwapX);
    int yDiff = abs(blankY-toSwapY);

    //if possible, swap
    if (xDiff + yDiff == 1)
    {
        board[blankY][blankX] = tile;
        board[toSwapY][toSwapX] = 0;
        blankX = toSwapX;
        blankY = toSwapY;
        return true;
    }
    else 
    {
        return false;
    }
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int counter = 0;
    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
           //if tile does not = counter, and not looking at last spot, then we have not won
          counter++;
          if (board[i][j] != counter && !(i == d-1 && j == d - 1))
           {
                return false;     
           }
          
        }
    }
    return true;
}
