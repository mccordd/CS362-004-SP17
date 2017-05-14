/**************************************************************************************
    Name: Doug McCord
    Date: 5/9/17
    Project: CS 362 Assignment 4
    Description: 
    "1- Write an automated random test generator for three Dominion cards “the 
        refactored code you created for assignment-2”, one of them being the adventurer 
        card, and at least one being a card you wrote unit tests for in assignment-3. 
        Check these testers in as randomtestcard1.c, randomtestcard2.c, and 
        randomtestadventurer.c.

     2- Submit a pdf file, called Assignment-4.pdf, to the Canvas contains the following 
        sections:
        • Random Testing: write up the development of your random testers, including 
        improvements in coverage and efforts to check the correctness of your 
        specification in a section called.
        • Code Coverage: discuss how much of adventurer and the other cards’ code you 
        managed to cover. Was there code you failed to cover? Why?. For at least one 
        card, make your tester achieve 100% statement and branch coverage, and document 
        this (and how long the test has to run to achieve this level of coverage). It 
        should not take more than five minutes to achieve the coverage goal (on a 
        reasonable machine, e.g. flip).
        • Unit vs Random: compare your coverage to that for your unit tests that you 
        created in assignment-3, and discuss how the tests differ in ability to detect 
        faults. Which tests had higher coverage – unit or random? Which tests had better 
        fault detection capability? ( Be detailed and thorough!).

     3- Add rules to the Makefile to produce randomtestcard1.out, randomtestcard2.out, 
        and randomtestadventurer.out, including coverage results.

    SOURCES: 
        *CS 362 course lecture material, Piazza help boards and provided sample code
            including bst.zip, testUpdateCoins.c and cardtest4.c
        *Other sources:
        	

***************************************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define TESTS 2000



int remodelCardTester(int c1, int c2, struct gameState *t, int hp) {

  /*Return value for smithyCard, card count for comparison*/
  int rcR, cardC;

  cardC = t->handCount[t->whoseTurn];
    
  rcR = remodelCard (c1, c2, t, hp);

 /*Oracle tests:
    Return -1 for a fail, for the wrong card count after remodel, which 
        should be the same (1 added, 1 discarded), and, if c2 (acquire)
        cost +2 is not <= c1 (discard) cost, it should return -1, else (valid 
        exchange) it should return 0.
    */

  if (cardC != t->handCount[t->whoseTurn]) return -1;
  if (rcR != 0 && getCost(c2) +2 > getCost(c1)) return -1;

  return 0;
}


int main () {

  /*i for iterator, n for number of tests; p, q, x, y and z are values we need to preserve
  	temporarily*/
  int i, n, p, q, x, y, z;
  int testsPassed = TESTS;

  struct gameState TestState;

  printf ("*************RANDOM TEST CARD 2*************\n");
  printf ("Testing Remodel Card:\n");

  /*SelectStream is a function in rngs.c to change between up to 256 streams of 
  random numbers, with PutSeed to set the seed*/
  SelectStream(2);
  PutSeed(3);

  /*Create general randomized chaos in the hand: */
  for (n = 0; n < TESTS; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&TestState)[i] = floor(Random()*256);
    }

    /*Values needed specifically for Remodel -- SEE NOTES*/
    TestState.playedCardCount = 0;
    for (i=0; i<27; i++) TestState.supplyCount[i] = 1000;

    /*Pick number of players, and within this pick whose turn*/
    p = floor(Random() * MAX_PLAYERS);
    p = p+1;
    TestState.numPlayers = p;
    //TestState.whoseTurn = floor(Random()*p);
    TestState.whoseTurn = 0;
    //printf("Test #%d: there are %d players\n", n+1, TestState.numPlayers);

    /*Hard to add limits to card values -- SEE NOTES*/
    x = floor(Random() * MAX_HAND);

    /*Had to add this specifically due to my remodel bug -- SEE NOTES*/
    if (x < 3) x = 3;

    TestState.handCount[TestState.whoseTurn] = x;   

    /*Now add a remodel card in a random, but possible spot*/
    //printf("Test #%d: handCount is: %d\n", n+1, TestState.handCount[TestState.whoseTurn]);
    y = floor(Random() * x);
    TestState.hand[TestState.whoseTurn][y] = 12;
    //printf("Value %d is at position %d\n", 12, y);

    /*Make sure the counts contain values -- SEE NOTES -- due to added bugs*/
    TestState.deckCount[TestState.whoseTurn] = (floor(Random() * MAX_DECK));
    //printf("Test #%d: deckCount is: %d\n", n+1, TestState.deckCount[TestState.whoseTurn]); 

    TestState.discardCount[TestState.whoseTurn] = (floor(Random() * MAX_DECK));
    //printf("Test #%d: discardCount is: %d\n", n+1, TestState.discardCount[TestState.whoseTurn]); 

    /*Getting choice to trash (x) and choice to buy (z) -- we'll validate in the tester for value*/
    x = floor(Random() * 27);
    z = floor(Random() * 27);

    p = floor(Random() * TestState.handCount[TestState.whoseTurn]);
    if(p!=y){TestState.hand[TestState.whoseTurn][p] = x;}
    else{
    	while(p==y) p = floor(Random() * TestState.handCount[TestState.whoseTurn]);
    	TestState.hand[TestState.whoseTurn][p] = x;
    }
    //printf("Value %d is at position %d\n", x, p);

    /*SEE NOTES -- due to a bug, both cards are forced to be a player's hand, even 
    	though this is an unrealistic condition*/
   
    q = floor(Random() * TestState.handCount[TestState.whoseTurn]);
    if(q!=y && q!=x){TestState.hand[TestState.whoseTurn][q] = z;}
    else{
    	while(q==y || q==x) q = floor(Random() * TestState.handCount[TestState.whoseTurn]);
    	TestState.hand[TestState.whoseTurn][q] = z;
    }
    //printf("Value %d is at position %d\n", z, q);
  

    /*Run the remodelCardTester with randomized state:*/
    testsPassed += remodelCardTester(p, q, &TestState, y);
	}	

  printf ("Passed %d of %d random card tests\n", testsPassed, TESTS); 

  return 0;
}
