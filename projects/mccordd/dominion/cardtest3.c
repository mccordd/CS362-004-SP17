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

    //Return value for remodelCard
    int rcr = 0;


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


    printf("****CARD UNIT TEST 3: Remodel****\n");

    printf("TEST 1: set hand, verify desired trash is trashed, desired replacement done : \n");

    //Stage remodel and a village into player 0;s hand -- village will be trashed:
    testGameA.hand[0][3] = village;
    testGameA.hand[0][4] = remodel;

    //Play remodel card for player 0, trashing village (3) and buying a council_room (5) - enum is 8
    rcr = remodelCard(3, 8, &testGameA, 4);
    if (rcr != 0)
    {
        printf("TEST CRITICAL FAIL; remodelCard refactor fails\n");
        exit(-1);
    }

    //Verify hand count is 4 (5 - 1 trashed -1 remodel discard +1 replacement)
    chc = testGameA.handCount[0];
    printf("	card played, player 0 hand count is: %d; expected: %d\n", chc, 4);
	testTotal++;
	if(chc == 4)
	{
		printf("PASSED\n");
		passCount++;	
	}
	else printf("TEST FAILED\n");

	//Verify the added card (should be in position 3) is the council_room:
	if(testGameA.hand[0][3] == council_room) 
	{
		printf("	player 0 card 4 is council room\nPASSED\n");
		passCount++;
	}
	else printf("	player 0 card 4 is council room\nTEST FAILED\n");
	testTotal++;		

	/*
	//TEMP TEST: returning as village -- so it is not being trashed as directed
	int t = 0;
	t = testGameA.hand[0][3];
	printf("TEMP: fourth card in hand is: %d\n", t);
	*/


    printf("\nTEST 2: try to replace with a card that's too expensive: \n");

    //Run remodelCard as above but pass in province as the desired buy (cost 8 is too great)
    //	First, re-stage remodel and a village into player 0;s hand -- village will be trashed:
    testGameA.hand[0][3] = village;
    testGameA.hand[0][4] = remodel;

    //Play remodel card for player 0, trashing village (3) and buying a province (8) - enum is 3
    rcr = remodelCard(3, 3, &testGameA, 4);

    printf("	P0 buys too much, function returned: %d, expected: %d\n", rcr, -1);
	testTotal++;
	if (rcr == -1) 
	{
		printf("PASSED\n");
		passCount++;
	}
	else printf("TEST FAILED\n");




    /**********General Card Checks******************************/

    printf("\nTEST 3: No change in other players' card counts: \n");
    //Get current counts for player 1:
    chc = testGameA.handCount[1];
    cdec = testGameA.deckCount[1];
    cdis = testGameA.handCount[1];

    //Compare current card counts for players 1 original:
    printf("	player 1 hand count is: %d; expected: %d\n", chc, p1hc);
	testTotal++;
	if (chc == p1hc) passCount++;
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
    printf("	player 2 hand count is: %d; expected: %d\n", chc, p2hc);
	testTotal++;
	if (chc == p2hc) passCount++;
    printf("	player 2 deck count is: %d; expected: %d\n", cdec, p2dec);
	testTotal++;
	if (cdec == p2dec) passCount++;
    printf("	player 2 discard count is: %d; expected: %d\n", cdis, p2dis);
	testTotal++;
	if (cdis == p2dis) passCount++;


    printf("\nTEST 4: card cost check: \n");
	//Per the enum, remodel is card #12
	cc = getCost(12);
	printf("	Remodel card cost returns as: %d, expected: %d\n", cc, 4);
	testTotal++;
	if(cc == 4) 
	{
		printf("PASSED\n");
		passCount++;
	}
	else printf("TEST FAILED\n");



	//TEST SUMMARY:
	printf("\n****CARD UNIT TEST 3: PASSED %d of %d tests****\n", passCount, testTotal);



	return 0;
}