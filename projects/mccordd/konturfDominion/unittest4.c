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
    int i, j;

    //For update coin return value:
    int ucr = 0;

    //For coins returned:
    int cr = 0;

    //For coins expected:
    int ce = 0;

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


    printf("****FUNCTION UNIT TEST 4: updateCoins****\n");

    printf("TEST 1: initialized hands, no bonus: \n");

    //First we get the number of copper in the player's hand for expected -- 
    //	as copper's are worth 1 coin each, we can use total
  	for (i = 0; i < pNum; i++)
    {
    	ce = 0;
    	ucr = updateCoins(i, &testGameA, 0);
    	if (ucr != 0)
    	{
    		printf("TEST CRITICAL FAIL; updateCoins function fail\n");
        	exit(-1);
    	}
    	cr = testGameA.coins;

    	for (j = 0; j < testGameA.handCount[i]; j++)
    	{
    		if (testGameA.hand[i][j] == copper) ce++;
    	}
    	printf("	player %d returned coins: %d; expected: %d\n", i, cr, ce); 
    	testTotal++;
    	if(cr == ce){passCount++;}
    	
    }

    /*
    //TEMP TEST verified player 1's coppers in deck:
    ce = 0;
	for (j = 0; j < testGameA.deckCount[0]; j++)
    {
    	if (testGameA.deck[0][j] == copper) ce++;
    }
    printf("TEMP: player 0 copper in deck %d\n",ce);
    */

    printf("TEST 2: coin values -- p0 has 5 silvers, p1 has 5 gold, no bonus: \n");

    //set player 0 to have 10 silver Treasure cards in deck:
    for (i = 0; i < 5; i++)
    {
 	   testGameA.hand[0][i] = silver;    	
    }
    //set player 1 to have 10 gold Treasure cards in deck:
    for (i = 0; i < 5; i++)
    {
 	   testGameA.hand[1][i] = gold; 
 	   testGameA.handCount[1]++;   	
    }
    //check the points are updated correctly. Silver are worth 2 per, so p0 should
    //	have 10 coins on check, and gold are worth 3 per, so p1 should have 15 
    for (i = 0; i < pNum; i++)
    {
    	if (i == 0) ce = 10;
    	else ce = 15;

    	ucr = updateCoins(i, &testGameA, 0);
    	if (ucr != 0)
    	{
    		printf("TEST CRITICAL FAIL; updateCoins function fail\n");
        	exit(-1);
    	}
    	cr = testGameA.coins;

    	printf("	player %d returned coins: %d; expected: %d\n", i, cr, ce); 
    	testTotal++;
    	if(cr == ce){passCount++;}
    	
    }


    printf("TEST 4: test 3 + bonus: \n");

    //Add a bonus of +2 to player 0:
    ucr = updateCoins(0, &testGameA, 2);
	if (ucr != 0)
	{
		printf("TEST CRITICAL FAIL; updateCoins function fail\n");
    	exit(-1);
	}
	cr = testGameA.coins;
	//Expected is 5 silvers +2, or 12 coins:
	ce = 12;
	printf("	bonus +2 added, returned coins: %d; expected: %d\n", cr, ce); 
	testTotal++;
	if(cr == ce){passCount++;}

	//Add a bonus of +2 to player 1:
    ucr = updateCoins(1, &testGameA, 2);
	if (ucr != 0)
	{
		printf("TEST CRITICAL FAIL; updateCoins function fail\n");
    	exit(-1);
	}
	cr = testGameA.coins;
	//Expected is 5 golds +2, or 17 coins:
	ce = 17;
	printf("	bonus +2 added, returned coins: %d; expected: %d\n", cr, ce); 
	testTotal++;
	if(cr == ce){passCount++;}



    printf("TEST 5: boundary -- no Treasure, no bonus: \n");

    //set both players to have all Curse cards in hand:
    for (i = 0; i< pNum; i++)
    {
    	for (j = 0; j < 5; j++)
    	{
 	   		testGameA.hand[i][j] = curse;    	
    	}    	
    }
   	//Expected pn a handful without Treasures is 0:
    ce = 0;
    //Check player 0's hand:
    ucr = updateCoins(0, &testGameA, 0);
	if (ucr != 0)
	{
		printf("TEST CRITICAL FAIL; updateCoins function fail\n");
    	exit(-1);
	}
	cr = testGameA.coins;
	printf("	player 0 returned coins: %d; expected: %d\n", cr, ce); 
	testTotal++;
	if(cr == ce){passCount++;}

	//Check player 1's hand:
    ucr = updateCoins(1, &testGameA, 0);
	if (ucr != 0)
	{
		printf("TEST CRITICAL FAIL; updateCoins function fail\n");
    	exit(-1);
	}
	cr = testGameA.coins;
	printf("	player 1 returned coins: %d; expected: %d\n", cr, ce); 
	testTotal++;
	if(cr == ce){passCount++;}





	//TEST SUMMARY:
	printf("\n****FUNCTION UNIT TEST 4: PASSED %d of %d tests****\n", passCount, testTotal);


	return 0;
}