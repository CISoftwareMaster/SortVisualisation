/*
 * Sorting Algorithm visualisation
 * 
 * cisoftwaremaster@gmail.com
 * 
 * A fun little experiment that visualises various
 * sorting algorithms
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SIZE 20

//visualisation function
void draw( int array[], int size, int highlight );

//this will be the collection of "blocks" to be sorted
int items[ SIZE ];

//how many steps did the algorithm take to sort the array?
int steps = 0;

//an implementation of the merge sort algorithm
void merge_sort( int array[], int size );

//randomise the content of the items array
void randomise( );

int animation_speed = 85000;
int max_size = 30;

int main( void )
{
    int option;
    
    //loop until the user exits
    while ( 1 )
    {
        //greet the user
        printf( "Which sorting algorithm would you like to visualise?\n1: Bubble sort\n2: Selection sort\n3: Insertion sort\n4: Merge sort\n5: Settings\n6: Exit\n" );
        
        //ask the user for his/her selected option
        do
        {
            printf( "\nOption: " );
            scanf( "%i", &option );
        }
        while ( option <= 0 || option >= 7 );
        
        //access settings
        if ( option == 5 )
        {
            while ( 1 )
            {
                system( "clear" );
                printf( "1: Animation speed\n2: Maximum value of items\n3: Exit" );
         
                printf( "\nOption: " );
                scanf( "%i", &option );
                
                if ( option == 1 )
                {
                    system( "clear" );
                    printf( "Animation speed:\n1: Very slow\n2: Slow\n3: Normal\n4: Fast (default)\n5: Very Fast\n6: Insanely fast\n" );
                    
                    do
                    {
                        printf( "\nSpeed: " );
                        scanf( "%i", &option );
                    }
                    while ( option <= 0 && option >= 6 );
                    
                    //set the animation speed
                    switch (option)
                    {
                        case 1:
                            animation_speed = 1500000;
                            break;
                            
                        case 2:
                            animation_speed = 1000000;
                            break;
                            
                        case 3:
                            animation_speed = 500000;
                            break;
                            
                        case 4:
                            animation_speed = 85000;
                            break;
                            
                        case 5:
                            animation_speed = 35000;
                            break;
                            
                        case 6:
                            animation_speed = 12000;
                            break;
                            
                        default:
                            printf( "Invalid selection! no changes shall be applied.\n" );
                            usleep( 1000000 );
                            break;
                    }
                    
                    option = 0;
                }
                
                else if ( option == 2 )
                {
                    do
                    {
                        printf( "Maximum value for items ( 5 - 80 ): " );
                        scanf( "%i", &option );
                    }
                    while ( option < 5 || option > 80 );
                    
                    //update the maximum size
                    max_size = option;
                    
                    option = 0;
                }
                
                else if ( option == 3 )
                {
                    option = 0;
                    break;
                }
            }
        }
        
        //if the user picks 'exit', break from the infinite loop
        if ( option == 6 )
            break;
        
        //randomise array
        randomise( );
        
        //bubble sort
        if ( option == 1 )
        {
            for ( int i = 0; i < SIZE; ++i )
            {
                int swaps = 0;
                
                for ( int j = 0; j < SIZE - 1; ++j )
                {
                    int x = items[ j ];
                    int y = items[ j + 1 ];
                    
                    //if x is smaller than y, swap
                    if ( x < y )
                    {
                        items[ j ] = y;
                        items[ j + 1 ] = x;
                        swaps ++;
                    }
                
                    //update the number of steps
                    steps ++;
                    
                    //pause then update the visualisation
                    usleep( animation_speed );
                    draw( items, SIZE, j );
                }
                
                if ( swaps == 0 )
                {
                    break;
                }
            }
        }
        
        //selection sort
        else if ( option == 2 )
        {
            int k = 0;
            
            for ( int i = 0; i < SIZE; ++i )
            {
                k = i;

                //find the largest number
                for ( int j = i; j < SIZE; ++j )
                {
                    if ( items[ j ] > items[ k ] )
                    {
                        k = j;
                        steps ++;
                    }
                }
                
                usleep( animation_speed );
                steps ++;
                
                //compare i to the largest number
                if ( items[ i ] < items[ k ] )
                {
                    int x = items[ k ];
                    int y = items[ i ];
                    
                    //swap
                    items[ i ] = x;
                    items[ k ] = y;
                
                    draw( items, SIZE, k );
                }
                else
                {
                    draw( items, SIZE, i );
                }
            }
        }
        
        //insertion sort
        else if ( option == 3 )
        {
            for ( int i = 1; i < SIZE; ++i )
            {
                for ( int j = ( i - 1 ); j >= 0; --j )
                {
                    int x = items[ j ];
                    int y = items[ j + 1 ];
                    
                    //as long as x is smaller than y keep shifting the items
                    if ( x < y )
                    {
                        items[ j ] = y;
                        items[ j + 1 ] = x;
                    }
                    
                    //otherwise, break out of the loop
                    if ( x > y )
                    {
                        break;
                    }
                    
                    steps ++;
                    
                    usleep( animation_speed );
                    draw( items, SIZE, j );
                }
            }
        }
        
        //merge sort
        else if ( option == 4 )
        {
            //show the unsorted array
            draw( items, SIZE, 10000 );
            usleep( animation_speed * 3 );
            
            //sort the array using mergesort
            merge_sort( items, SIZE );
        }
        
        //draw the visualisation one last time (without the highlight)
        draw( items, SIZE, 10000 );
        
        //reset the steps counter
        steps = 0;
    }
    
    //exit successfuly
    return 0;
}

void merge_sort( int array[], int size )
{
    //base-case for recursion
    if ( size < 2 )
    {
        //we've reached the smallest size possible
        return;
    }
    else
    {
        //split the array into two
        int left_size = (size / 2);
        int right_size = (size - left_size);
                
        //the output of merge sort
        int merged[ size ];
        
        //the left half of the array
        int left[ left_size ];
        
        //the right half of the array
        int right[ right_size ];
        
        //distribute items between the arrays
        for ( int i = 0; i < size; ++i )
        {   
            if ( i < left_size )
                left[ i ] = array[ i ];
            else if ( i >= left_size )
                right[ i - left_size ] = array[ i ];
            
            //initialize merged
            merged[ i ] = 0;
            
            steps ++;
        }

        //sort the halves
        merge_sort( left, left_size );
        merge_sort( right, right_size );
        
        //merge counters
        int x = 0; //for the left half
        int y = 0; //for the right half
        
        //merge the arrays
        for ( int m = 0; m < size; ++m )
        {
            //use this when both counters are still within their boundaries
            if ( x < left_size && y < right_size )
            {
                //insert the smaller values first
                if ( left[ x ] > right[ y ] )
                {
                    merged[ m ] = left[ x ];
                    
                    //increment the left counter
                    ++ x;
                }
                else
                {
                    merged[ m ] = right[ y ];
                    
                    //increment the right counter
                    ++ y;
                }
            }
            
            //if not, insert the remaining values into the output array
            else if ( x < left_size )
            {
                merged[ m ] = left[ x ];
                ++ x;
            }
            
            else if ( y < right_size )
            {
                merged[ m ] = right[ y ];
                ++ y;
            }
            
            steps ++;
        }
        
        //increment the number of steps
        ++steps;
        
        //overwrite the original array with the merged array
        for ( int i = 0; i < size; ++i )
        {
            array[ i ] = merged[ i ];
        }
       
       //visualise the current state of the array
        usleep( animation_speed );
        draw( array, size, 90000 );
    }
}

void randomise( )
{
    
    //seed the random number generator
    srand( time( NULL ) );
    
    for ( int i = 0; i < SIZE; ++i )
    {
        items[ i ] = 1 + ( rand() % max_size );
    }
}

void draw( int array[], int size, int highlight )
{
    //clear the screen
    system( "clear" );
    
    //iterate through the array
    for ( int i = 0; i < size; ++i )
    {
        //how "long" is the block?
        for ( int j = 0; j < array[ i ]; ++j )
        {
            printf( "X" );
        }
        
        //should we highlight it?
        if ( i == highlight )
        {
            printf( "\t <--" );
        }
        
        //move to the next block
        printf( "\n" );
    }
    
    //how many steps did the algorithm take?
    printf( "\nSteps: %i\n", steps );
}
