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


    //For saving initial 'other' player game state values:
    int p1hc, p1dec, p1dis;
    int p2hc, p2dec, p2dis;

    //And for current values:
    int chc = 0;
    int cdec = 0;
    int cdis = 0;

    //Return value for council_room card return
    int crcr = 0;

    //For checking the number of buys player has:
    int nb = 0;

    //For card cost value:
    int cc = 0;

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
    if (g != 0)
    {
        printf("TEST CRITICAL FAIL; game does not intiialize\n");
        exit(-1);
    }    
    //Capture p1 and p2's counts as of initialization:
    p1hc = testGameA.handCount[1];
    p2hc = testGameA.handCount[2];
    p1dec = testGameA.deckCount[1]; 
    p2dec = testGameA.deckCount[2]; 
    p1dis = testGameA.discardCount[1];
    p2dis = testGameA.discardCount[2];


    /*************************************/


    printf("****CARD UNIT TEST 4: Council Room****\n");

    printf("TEST 1: set deck and ensure top four cards from player's deck drawn into hand : \n");
    //Stage player 0's deck to have a baron, village, feast and gardens on the top:
    testGameA.deck[0][testGameA.deckCount[0]] = baron;
    testGameA.deckCount[0]++;
    testGameA.deck[0][testGameA.deckCount[0]] = village;
    testGameA.deckCount[0]++;
    testGameA.deck[0][testGameA.deckCount[0]] = feast;
    testGameA.deckCount[0]++;
    testGameA.deck[0][testGameA.deckCount[0]] = gardens;
    testGameA.deckCount[0]++;    

    //Stage council_rooom into player 0;s hand:
    testGameA.hand[0][4] = council_room;

    //Play council room card for player 0:
    crcr = councilCard(&testGameA, 4);
    if (crcr != 0)
    {
        printf("TEST CRITICAL FAIL; councilCard refactor fails\n");
        exit(-1);
    }    

    //Check player 0's hand count -- it should equal 8 (5 + 4 -1, with council room discarded)
    chc = testGameA.handCount[0];
    printf("	card played, player 0 hand count is: %d; expected: %d\n", chc, 8);
	testTotal++;
	if(chc == 7)
	{
		printf("PASSED\n");
		passCount++;	
	}
	else printf("TEST FAILED\n");

	//Check the cards above fifth in player's hand -- they should be gardens, feast, village, baron:
	if(testGameA.hand[0][5] == gardens) 
	{
		printf("	player 0 card 5 is gardens\nPASSED\n");
		passCount++;
	}
	else printf("	player 0 card 5 is gardens\nTEST FAILED\n");
	testTotal++;

	if(testGameA.hand[0][6] == feast) 
	{
		printf("	player 0 card 6 is feast\nPASSED\n");
		passCount++;
	}
	else printf("	player 0 card 6 is feast\nTEST FAILED\n");
	testTotal++;	

	if(testGameA.hand[0][7] == village) 
	{
		printf("	player 0 card 7 is village\nPASSED\n");
		passCount++;
	}
	else printf("	player 0 card 7 is village\nTEST FAILED\n");
	testTotal++;

	if(testGameA.hand[0][8] == baron) 
	{
		printf("	player 0 card 8 is baron\nPASSED\n");
		passCount++;
	}
	else printf("	player 0 card 8 is baron\nTEST FAILED\n");
	testTotal++;	




    printf("\nTEST 2: ensure player's buy amount has increased by 1: \n");
    //Player 0 should have 2 buys, instead of one:
    nb = testGameA.numBuys;
    printf("	player 0 buys count is: %d; expected: %d\n", nb, 2);
	testTotal++;
	if (nb == 2) 
	{
		printf("PASSED\n");
		passCount++;
	}




    printf("\nTEST 3: other players' hands increased by 1 each, deck and discard unchanged: \n");
    //Get current counts for player 1:
    chc = testGameA.handCount[1];
    cdec = testGameA.deckCount[1];
    cdis = testGameA.handCount[1];

    //Compare current card counts for players 1 original:
    printf("	player 1 hand count is: %d; expected: %d\n", chc, p1hc+1);
	testTotal++;
	if (chc == p1hc+1) 
	{
		printf("PASSED\n");
		passCount++;
	}
	else printf("TEST FAILED\n");

    printf("	player 1 deck count is: %d; expected: %d\n", cdec, p1dec);
	testTotal++;
	if (cdec == p1dec) passCount++;
    printf("	player 1 discard count is: %d; expected: %d\n", cdis, p1dis);
	testTotal++;
	if (cdis == p1dis) passCount++;

    //Get current counts for player 2:
    chc = testGameA.handCount[2];
    cdec = testGameA.deckCount[2];
    cdis = testGameA.handCount[2];
    //Compare current card counts for players 2 and original:
    printf("	player 2 hand count is: %d; expected: %d\n", chc, p2hc+1);
	testTotal++;
	if (chc == p2hc+1) 
	{
		printf("PASSED\n");
		passCount++;
	}
	else printf("TEST FAILED\n");
    printf("	player 2 deck count is: %d; expected: %d\n", cdec, p2dec);
	testTotal++;
	if (cdec == p2dec) passCount++;
    printf("	player 2 discard count is: %d; expected: %d\n", cdis, p2dis);
	testTotal++;
	if (cdis == p2dis) passCount++;

    /**********General Card Checks******************************/

    printf("\nTEST 4: card cost check: \n");
	//Per the enum, council_room is card #8
	cc = getCost(8);
	printf("	Council Room card cost returns as: %d, expected: %d\n", cc, 5);
	testTotal++;
	if(cc == 5) 
	{
		printf("PASSED\n");
		passCount++;
	}
	else printf("TEST FAILED\n");



	//TEST SUMMARY:
	printf("\n****CARD UNIT TEST 4: PASSED %d of %d tests****\n", passCount, testTotal);



	return 0;
}