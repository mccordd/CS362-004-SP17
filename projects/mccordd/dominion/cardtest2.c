/**************************************************************************************
    Name: Doug McCord
    Date: 5/25/17 originally -- 4/28/17
    Project: CS 362 Assignment 5 (modified from Assignment 3 version)

    A3 Description: 
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

    int i;

    //For saving initial 'other' player game state values:
    int p1hc, p1dec, p1dis;
    int p2hc, p2dec, p2dis;
    //And for p0s original coin count (before card played)
    int p0cc = 0;

    //And for current values:
    int chc = 0;
    int cdec = 0;
    int cdis = 0;

    //Return value for advenCard
    int acr = 0;

    //Return value for updateCoins
    int ucr = 0;

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


    printf("****CARD UNIT TEST 2: Adventurer****\n");

    printf("TEST 1: set deck, run and verify right Treasures added: \n");
    //Stage player 0's deck to have a Treasure (gold) lowest, then on top:
    //	gardens, feast, mine, Treasure(silver), duchy
    testGameA.deck[0][testGameA.deckCount[0]] = gold;
    testGameA.deckCount[0]++;
    testGameA.deck[0][testGameA.deckCount[0]] = gardens;
    testGameA.deckCount[0]++;
    testGameA.deck[0][testGameA.deckCount[0]] = feast;
    testGameA.deckCount[0]++;
    testGameA.deck[0][testGameA.deckCount[0]] = mine;
    testGameA.deckCount[0]++;
    testGameA.deck[0][testGameA.deckCount[0]] = silver;
    testGameA.deckCount[0]++;
    testGameA.deck[0][testGameA.deckCount[0]] = duchy;
    testGameA.deckCount[0]++;


    //Stage adventurer into player 0;s hand:
    testGameA.hand[0][4] = adventurer;

    //Update coins and grab the coin total before adventurer is played:
    ucr = updateCoins(0, &testGameA, 0); 
    if (ucr != 0)
    {
        printf("TEST CRITICAL FAIL; updateCoins fails\n");
        exit(-1);
    }
    //Get initial coin count:
    p0cc = testGameA.coins; 
    printf("    Player 0 initial coin value is: %d\n", p0cc);
    //Initial Hand:
    for(i=0;i<testGameA.handCount[0]; i++){printf(" Player 0's card at pos %d is %d\n", i, testGameA.hand[0][i]);}



    //Play adventurer card for player 0:
    acr = advenCard(&testGameA);
    if (acr != 0)
    {
        printf("TEST CRITICAL FAIL; advenCard refactor fails\n");
        exit(-1);
    }

    //Check player 0's hand count -- it should equal 6 (5 + 2 -1, with Adventurer discarded)
    chc = testGameA.handCount[0];
    printf("	card played, player 0 hand count is: %d; expected: %d\n", chc, 6);
	testTotal++;
	if(chc == 6)
	{
		printf("PASSED\n");
		passCount++;	
	}
	else printf("TEST FAILED\n");

	//Check the cards in player's hand -- they should be gold and silver, reversed --
    //  due to the card 4 being dropped as discard!:
	if(testGameA.hand[0][4] == gold) 
	{
		printf("	player 0 card 4 is gold\nPASSED\n");
		passCount++;
	}
	else printf("	player 0 card 4 is not gold\nTEST FAILED\n");
	testTotal++;

    //Check the cards in player's hand -- they should be gold and silver, reversed --
    //  due to the card 4 being dropped as discard!:
	if(testGameA.hand[0][5] == silver) 
	{
		printf("	player 0 card 5 is silver\nPASSED\n");
		passCount++;
	}
	else printf("	player 0 card 5 is not silver\nTEST FAILED\n");
	testTotal++;

    //Final Hand:
    for(i=0;i<testGameA.handCount[0]; i++){printf(" player 0's card at pos %d is %d\n", i, testGameA.hand[0][i]);}


    printf("\nTEST 2: coins return the right new Treasure total: \n");

    //Run the update coins so we can measure coin total -- it should be the 
    //	original coin total +5 for a silver and gold. 
    ucr = updateCoins(0, &testGameA, 0); 
    if (ucr != 0)
    {
        printf("TEST CRITICAL FAIL; updateCoins fails\n");
        exit(-1);
    }   
    printf("	player 0 original coin count: %d\n", p0cc);
    printf("	player 0 new coin count: %d, expected (above + 5): %d\n", testGameA.coins, p0cc+5);
	testTotal++;
	if (testGameA.coins == p0cc+5) 
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
	//Per the enum, Adventurer is card #7
	cc = getCost(7);
	printf("	Adventurer card cost returns as: %d, expected: %d\n", cc, 6);
	testTotal++;
	if(cc == 6) 
	{
		printf("PASSED\n");
		passCount++;
	}
	else printf("TEST FAILED\n");



	//TEST SUMMARY:
	printf("\n****CARD UNIT TEST 2: PASSED %d of %d tests****\n", passCount, testTotal);



	return 0;
}
