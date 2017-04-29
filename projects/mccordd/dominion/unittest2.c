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
#include <string.h>



int main() {

	//Iterators:
    int i;

    //For our supply count return
    int spc = 0;
    //For our expected supply pile
    int spe = 0;

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

    //For retrieving our enum titles: 
    const char *cards[27];
    cards[0] = "curse";
    cards[1] = "estate";
    cards[2] = "duchy";
    cards[3] = "province";
    cards[4] = "copper";
    cards[5] = "silver";
    cards[6] = "gold";
    cards[7] = "adventurer";
    cards[8] = "council_room";
    cards[9] = "feast";
    cards[10] = "gardens";
    cards[11] = "mine";
    cards[12] = "remodel";
    cards[13] = "smithy";
    cards[14] = "village";
    cards[15] = "baron";
    cards[16] = "great_hall";
    cards[17] = "minion";
    cards[18] = "steward";
    cards[19] = "tribue";
    cards[20] = "ambassador";
    cards[21] = "cutpurse";
    cards[22] = "embargo";
    cards[23] = "outpost";
    cards[24] = "salvager";
    cards[25] = "sea_hag";
    cards[26] = "teasure_map";

    /*************************************/
    g = initializeGame (pNum, k, testSeed, &testGameA);
    /*************************************/


    printf("****FUNCTION UNIT TEST 2: supplyCount****\n");


	printf("TEST 1: intialized game supply counts for 3 players: \n");

    //NOTE: 27 comes from the enum values of the tested game. There are 27 possible cards, 
    //	but we are initializing kingdom cards only through great_hall, or 16. Hence all 
    //	that are out of the game, and hence should register a -1. 

    //First check for kingdom cards in play, victory, curse and Treasure cards:
	for (i = 0; i < 17; i++)
	{
		spc = supplyCount(i, &testGameA);

		//Curses for 3 players:
		if(i == 0) spe = 20;

		//Victory cards: 
		else if(i < 4) spe = 12;

		//Treasure cards copper, silver, gold:
		else if(i == 4) spe = 39; //60 - 7 per 3 players in this test
		else if(i == 5) spe = 40;
		else if(i == 6) spe = 30;

		//Victory type Kingdom cards:
		else if (i == 10) spe = 12;
		else if (i == 16) spe = 12;

		//Other in-game Kingdom cards
		else spe = 10; 

		printf("	Card %s supply pile is: %d; expected: %d\n", cards[i], spc, spe); 

		testTotal++;

		if(spc == spe) 
		{
			//printf("PASSED\n");
			passCount ++;
		}
		//else printf("TEST FAILED\n");
	}

	//Now check for kingdom cards that are out of play:
	spe = -1;

	for (i = 17; i < 27; i++)
	{
		spc = supplyCount(i, &testGameA);
		printf("	Card %s supply pile is: %d; expected: %d\n", cards[i], spc, spe); 

		testTotal++;

		if(spc == spe) 
		{
			//printf("PASSED\n");
			passCount ++;
		}
		//else printf("TEST FAILED\n");
	}

	printf("\nTEST 2: mod and check depleted game supply count: \n");

	//Assign player 3 all of the remaining province cards to his deck:
	//	First, ensure there are the correct 12 province cards in supply:
	spc = supplyCount(3, &testGameA);

	if (spc == 12)
	{
			for (i = 0; i < spc; i++)
			{
				testGameA.deck[3][i+10] = province;
				testGameA.deckCount[3] = testGameA.deckCount[3] + 1;
				testGameA.supplyCount[3]--;
				printf("	Player 3 adds %s; count is: %d\n", cards[3], testGameA.supplyCount[3]);
			}

		//Now get the count after and check it:
		spc = supplyCount(3, &testGameA); 
		spe = 0;
		printf("	Card %s supply pile is: %d; expected: %d\n", cards[3], spc, spe);
		if(spc == spe) passCount++;
	}
	
	testTotal++;



	//TEST SUMMARY:
	printf("\n****FUNCTION UNIT TEST 2: PASSED %d of %d tests****\n", passCount, testTotal);


	return 0;
}