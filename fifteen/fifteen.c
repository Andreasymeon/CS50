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
            printf("Congrats! You've won the game!\n");
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
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
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
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    //calculate highest number -1 for the emty tile  
    int tile = d * d - 1;
    
    //for each row
    for (int row = 0; row < d; row++)
    {
        //for each column
        for(int col = 0; col < d; col++)
        {
            //intitialize board from d*d-1 to 1
            board[row][col] = tile--;
        }
        //if number of tiles is even, "1" comes before and "2" is the last tile
        if (d % 2 == 0)
        {
            board[d - 1][d - 2] = 2;
            board[d - 1][d - 3] = 1;
        }
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    //print new line
    printf("\n");
    
    // for each row
    for (int row = 0; row < d; row++)
    {
        //for each column
        for (int col = 0; col < d; col++)
        {
            //print underscore for blank tile
            if (board[row][col] == 0)
            {
                printf("  _ |");
            }
            
            //print tile in current state
            else
            {
                printf(" %2i |",board[row][col]);
            }
        }
       
        //print new line
        printf("\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    //check tile is valid or not
    if (tile < 1 || tile > d * d - 1)
    {
        return false;
    }
    
    //linear search to find tile location
    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            if (board[row][col] == tile)
            {
                //check if legal move, swap tile and blank tile
                if (board[row + 1][col] == 0 && row + 1 < d)
                {
                    board[row + 1][col] = board[row][col];
                    board[row][col] = 0;
                    return true;
                }
                else if (board[row - 1][col] == 0 && row - 1 >= 0)
                {
                    board[row - 1][col] = board[row][col];
                    board[row][col] = 0;
                    return true;
                }
                else if (board[row][col + 1] == 0 && col + 1 < d)
                {
                    board[row][col + 1] = board[row][col];
                    board[row][col] = 0;
                    return true;
                }
                else if (board[row][col - 1] == 0 && col - 1 >= 0)
                {
                    board[row][col - 1] = board[row][col];
                    board[row][col] = 0;
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    //check if every tile is in its increasing order
    int check = 1;
    
    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            if (board[row][col] != check && check != d * d)
            {
                return false;
            }
            else 
            {
                check++;
            }
        }
    }
    return true;
}
