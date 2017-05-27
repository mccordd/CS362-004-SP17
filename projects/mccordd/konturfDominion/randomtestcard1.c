/**************************************************************************************
    Name: Doug McCord
    Date: 5/25/17 originally -- 5/9/17
    Project: CS 362 Assignment 5 (modified from Assignment 4 version)

    A4 Description:  
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



int smithyCardTester(struct gameState *t, int hp) {

  /*Return value for smithyCard and card count for comparison:*/
  int scR, cardC;

  cardC = t->handCount[t->whoseTurn];
    
  scR = smithyEffect (t, hp);

 /*Oracle tests:
    Return -1 for a fail, for the wrong card count after smith, which 
        should be the original +2 (3 added, one discarded)
    */
  if(scR != 0 || t->handCount[t->whoseTurn] != cardC + 2) return -1;

  return 0;
}


int main () {

  /*i for iterator, n for number of tests, p for players, x y z for random variables*/
  int i, n, p, x, y;
  int testsPassed = TESTS;

  struct gameState TestState;

  printf ("*************RANDOM TEST CARD 1*************\n");
  printf ("Testing Smithy Card:\n");

  /*SelectStream is a function in rngs.c to change between up to 256 streams of 
  random numbers, with PutSeed to set the seed*/
  SelectStream(2);
  PutSeed(3);

  /*Create general randomized chaos in the hand: */
  for (n = 0; n < TESTS; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&TestState)[i] = floor(Random()*256);
    }

    /*Values needed specifically for Smithy -- SEE NOTES*/
    TestState.playedCardCount = 0;

    /*Pick number of players, and within this pick whose turn*/
    p = floor(Random() * MAX_PLAYERS);
    p = p+1;
    TestState.numPlayers = p;
    //TestState.whoseTurn = floor(Random()*p);
    TestState.whoseTurn = 0;
    //printf("Test #%d: there are %d players\n", n+1, TestState.numPlayers);

    /*Hard to add limits to card values -- SEE NOTES*/
    x = floor(Random() * MAX_HAND);
    TestState.handCount[TestState.whoseTurn] = x;   

    /*Now add a smithy card in a random, but possible spot*/
    //printf("Test #%d: handCount is: %d\n", n+1, TestState.handCount[TestState.whoseTurn]);
    y = floor(Random() * x);
    TestState.hand[TestState.whoseTurn][y] = 13;

    /*Make sure the counts contain values -- SEE NOTES -- due to added bugs*/
    TestState.deckCount[TestState.whoseTurn] = (floor(Random() * MAX_DECK));
    //printf("Test #%d: deckCount is: %d\n", n+1, TestState.deckCount[TestState.whoseTurn]); 

    TestState.discardCount[TestState.whoseTurn] = (floor(Random() * MAX_DECK));
    //printf("Test #%d: discardCount is: %d\n", n+1, TestState.discardCount[TestState.whoseTurn]); 

    /*Run the smithyCardTester with randomized state:*/
    testsPassed += smithyCardTester(&TestState, y);
  }

  printf ("Passed %d of %d random card tests\n", testsPassed, TESTS); 

  return 0;
}
