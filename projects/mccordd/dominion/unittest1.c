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
        	For printing the value of an enum in C:
        	http://stackoverflow.com/questions/2161790/can-i-display-the-value-of-an-enum-with-printf


***************************************************************************************/



#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#include <stdio.h>


int main() {

	//Iterators:
    int i;
    //For our full deck count returns:
    int fdc = 0;
    //For our score returns (test 2):
    int p0s = 0;
    int p1s = 0;
    //Test pass count
    int passCount = 0;
    int testTotal = 0;

    /****Needed to call initialize game****/
    //Game return state
    int g;

    //Starting with 3 players in test
    int pNum = 3; 
    //Our selection of Kingdom Cards, kept from provided test of updateCoins
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

    //A default value
    int testSeed = 1000; 

    //Our gameState
    struct gameState testGameA;

    /*************************************/
    g = initializeGame (pNum, k, testSeed, &testGameA);
    /*************************************/


    printf("****FUNCTION UNIT TEST 1: fullDeckCount****\n");

    //Our control values for a new game:
    //	Player 0 should have a hand of 5 cards, a draw of 5 cards, and a discard of 0
    //	Player 1 should have a hand of 0 cards, a draw of 10 cards, discard of 0
    //	Player 2 as 2. 

    /*
    int p0de = testGameA.deckCount[0];
    int p0h = testGameA.handCount[0];
    int p0di = testGameA.discardCount[0];

    int p0C = p0de + p0h + p0di;
    //printf("TEMP: p0Control by counts should be 5, 5, 0 and is: %d, %d, %d\n", p0de, p0h, p0di);
	*/


	printf("TEST 1: intialized game decks: \n");
	for (i = 0; i < pNum; i++)
	{
		fdc = fullDeckCount(i, 0, &testGameA);
		printf("	player %d full deck count is: %d; expected: %d\n", i, fdc, 10); 
		printf("	  player %d deck: %d\n", i, testGameA.deckCount[i]);
		printf("	  player %d hand: %d\n", i, testGameA.handCount[i]);
		printf("	  player %d discard: %d\n", i, testGameA.discardCount[i]);

		testTotal++;
		if(fdc == 10) 
		{
			printf("PASSED\n");
			passCount ++;
		}
		else printf("TEST FAILED\n");
	}



	printf("\nTEST 2: Garden card score implementation: \n");
	//Not strictly a unit test, this is needed to verify current implementation of 
	//	fullDeckCount is broken and not just miserably documented

	//First give player 0 a Garden card:
	testGameA.deck[0][5] = gardens;
	testGameA.deckCount[0] = testGameA.deckCount[0] + 1;


	//Now check the score for player 0:
	//	As player 0 has an initialized game, she has 3 estates and a garden, her 
	//		total score should be 3 (1 per estate) + 11/10 or 4. 
	//	As player 1 has an initialzed game, she has 3 estates, and her total score
	//		should be 3 (1 per estate)
	p0s = scoreFor (0, &testGameA);
	p1s = scoreFor (1, &testGameA);

	printf("	player 0 final score: %d, expected: %d\n", p0s, 4);
	testTotal++;
	if(p0s == 4)
	{
			printf("PASSED\n");
			passCount++;
	}
	else printf("TEST FAILED\n");

	printf("	player 1 final score: %d, expected: %d\n", p1s, 3);
	testTotal++;
	if(p0s == 3)
	{
			printf("PASSED\n");
			passCount++;
	}
	else printf("TEST FAILED\n");

	//TEST SUMMARY:
	printf("\n****FUNCTION UNIT TEST 1: PASSED %d of %d tests****\n", passCount, testTotal);



	/*
	//TEMP: Due to multiple bugs, this code was added to verify that fulLDeckCount 
	//	functions in a method other than how it is being implemented. 
	g = fullDeckCount(0, 1,&testGameA);
	printf("TEMP: player 0 estates: %d\n", g);
	g = fullDeckCount(0, 10,&testGameA);
	printf("TEMP: player 0 gardens: %d\n", g);

    for (i = 0; i < pNum; i++)
    {
    	printf("FOR PLAYER: %d\n", i);

    	for (j = 0; j < testGameA.deckCount[i]; j++)
    	{
    		printf("	Value of deck at pos: %d, is: %d\n", j, testGameA.deck[i][j]);

    	}
    }

	g = fullDeckCount(0, 0, &testGameA);
    printf("fullDeckCount for p0, passed card 0 returns: %d\n", g);

    g = fullDeckCount(0, 1, &testGameA);
    printf("fullDeckCount for p1, passed card 1 returns: %d\n", g);
    */



	return 0;
}
