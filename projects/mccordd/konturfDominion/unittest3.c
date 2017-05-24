/**************************************************************************************
    Name: Doug McCord
    Date: 4/28/17
    Project: CS 362 Assignment 3
    Description: 
    "1- Write unit tests for four functions (not card implementations, and not 
        cardEffect) in dominion.c. Check these tests in as unittest1.c,unittest2.c, 
        unittest3.c, and unittest4.c. At least two of these functions should be more 
        than 5 lines of code. (20 points)
     2- Write unit tests for four Dominion cards implemented in dominion.c. These tests 
        should be checked in as cardtest1.c, cardtest2.c, cardtest3.c, and cardtest4.c. 
        It is mandatory to test smithy and adventurer card. (20 points)"

    Add a written report as specified, and also the makefile must do the following:

    "Add a rule in Makefile that will generate and execute all of these tests, and 
     append complete testing results (including % coverage) into a file called 
     unittestresults.out. The rule should be named unittestresults.out and should 
     depend on all your test code as well as the dominion code. The .out files contain 
     the output of your running tests and coverage information. Basically .out file 
     should act as a proof that your tests run correctly and you collected coverage 
     information correctly. (10 points)"

    SOURCES: 
        *CS 362 course lecture material, Piazza help boards and provided sample code
            including bst.zip, testUpdateCoins.c and cardtest4.c
        *Other sources:
        	For creating an array of strings in C (refresher):
        	http://stackoverflow.com/questions/1088622/how-do-i-create-an-array-of-strings-in-c

***************************************************************************************/



#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#include <stdio.h>
#include <stdlib.h>



int main() {

	//Iterators:
    int i;

    //For our whoseTurn return
    int wtr = 0;
    //For expected turn
    int wte = 0;

    //For advance game return:
    int ag;


    //Test pass count
    int passCount = 0;
    int testTotal = 0;

    /****Needed to call initialize game****/
    //Game return state
    int g;

    //Starting with 2 players in test
    int pNum = 2; 
    //Our selection of Kingdom Cards, kept from provided test of updateCoins
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

    //A default value
    int testSeed = 1000; 

    //Our gameState
    struct gameState testGameA;

    /*************************************/
    g = initializeGame (pNum, k, testSeed, &testGameA);
    if (g != 0)
    {
        printf("TEST CRITICAL FAIL; game does not intiialize\n");
        exit(-1);
    }    
    /*************************************/


    printf("****FUNCTION UNIT TEST 3: whoseTurn****\n");

    printf("TEST: intialized game with 2 players, go through both turns twice: \n");

    for (i = 0; i < 5; i++)
    {
    	//Check returned turn and score the test:
    	wtr = whoseTurn(&testGameA);
    	wte = i % 2;
   		printf("	turn %d, player's turn: %d; expected: %d\n", i, wtr, wte);
   		testTotal++;

   		if (wtr == wte) 
   		{
   			printf ("PASSED\n");
   			passCount++;
   		}
   		else printf("TEST FAILED\n");

   		//Advance the turn:
   		ag = endTurn(&testGameA);
   		if (ag != 0)
    	{
        	printf("TEST CRITICAL FAIL; game turn not advance\n");
        	exit(-1);
    	}  
    }



	//TEST SUMMARY:
	printf("\n****FUNCTION UNIT TEST 3: PASSED %d of %d tests****\n", passCount, testTotal);


	return 0;
}