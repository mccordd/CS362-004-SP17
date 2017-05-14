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



int advenCardTester(struct gameState *t) {

  /*Return value for advenCard, card count and coin count before function*/
  int acR, cardC, coinC;

  cardC = t->handCount[t->whoseTurn];
  updateCoins(t->whoseTurn, t, 0);
  coinC = t->coins;

  acR = advenCard (t);

  /*Oracle tests:
    Return -1 for a fail, for the wrong card count after adventurer, 
        or for a coin count that is not increased by 2 or more (2 coppers min)
    */
  updateCoins(t->whoseTurn, t, 0);

  if(acR != 0 || t->handCount[t->whoseTurn] != cardC + 1 ||  t->coins >= coinC + 2) return -1;

  return 0;
}


int main () {

  /*i for iterator, n for number of tests, p for players, x y z for random variables*/
  int i, n, p, x, y, z;
  int testsPassed = TESTS;

  struct gameState TestState;

  printf ("*************RANDOM TEST ADVENTURER CARD*************\n");
  printf ("Testing adventurer Card:\n");

  /*SelectStream is a function in rngs.c to change between up to 256 streams of 
  random numbers, with PutSeed to set the seed*/
  SelectStream(2);
  PutSeed(3);

  /*Create general randomized chaos in the hand: */
  for (n = 0; n < TESTS; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&TestState)[i] = floor(Random()*256);
    }

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
    for (i=0; i<x; i++)
    {
        z= floor(Random() *27);
        TestState.hand[TestState.whoseTurn][i] = z;
    }

    /*Now add an adventurer card in a random, but possible spot*/
    //printf("Test #%d: handCount is: %d\n", n+1, TestState.handCount[TestState.whoseTurn]);
    y = floor(Random() * x);
    TestState.hand[TestState.whoseTurn][y] = 7;

    /*Make sure the counts contain values -- SEE NOTES -- due to added bugs*/
    TestState.deckCount[TestState.whoseTurn] = (floor(Random() * MAX_HAND));
    //printf("Test #%d: deckCount is: %d\n", n+1, TestState.deckCount[TestState.whoseTurn]); 
    for (i=0; i<TestState.deckCount[TestState.whoseTurn]; i++)
    {
        z= floor(Random() *27);
        TestState.deck[TestState.whoseTurn][i] = z;
    }
    TestState.discardCount[TestState.whoseTurn] = (floor(Random() * MAX_HAND));
    //printf("Test #%d: discardCount is: %d\n", n+1, TestState.discardCount[TestState.whoseTurn]); 
    for (i=0; i<TestState.discardCount[TestState.whoseTurn]; i++)
    {
        z= floor(Random() *27);
        TestState.discard[TestState.whoseTurn][i] = z;
    }
    /*Make sure minimum treasure cards are contained in one of 2 random hands -- SEE NOTES*/
    /*y will hold the type of treasure, z will hold the spot of this in hand*/
    p = floor(Random() * 2);
    /*Add to deck*/
    if(p==0)
    {
        /*Coin*/
        y = (floor(Random() * 3)+4);
        /*Position*/
        z = TestState.deckCount[TestState.whoseTurn];
        x = floor(Random() * z);
        TestState.deck[TestState.whoseTurn][x] =  y;
    }
    /*Otherwise the discard*/
    else
    {
        /*Coin*/
        y = (floor(Random() * 3)+4);
        /*Position*/
        z = TestState.discardCount[TestState.whoseTurn];
        x = floor(Random() * z);
        TestState.discard[TestState.whoseTurn][x] =  y;

    }



    /*HARD-CODED VALUES TEST: safe-ranged, not 'interesting'*/
    /*
    
    TestState.numPlayers = 3;
    TestState.supplyCount[treasure_map+1];
    TestState.outpostPlayed = 0;
    TestState.whoseTurn = 0;
    TestState.phase = 0;
    TestState.numActions = 1;
    TestState.coins = 0;
    TestState.numBuys = 1;
    
    TestState.handCount[0] = 5;
    TestState.handCount[1] = 5;
    TestState.handCount[2] = 5;

    TestState.hand[0][0] = 1;
    TestState.hand[0][1] = 4;
    TestState.hand[0][2] = 4;
    TestState.hand[0][3] = 3;
    TestState.hand[0][4] = 7;

    TestState.hand[1][0] = 1;
    TestState.hand[1][1] = 4;
    TestState.hand[1][2] = 1;
    TestState.hand[1][3] = 2;
    TestState.hand[1][4] = 0;

    TestState.hand[2][0] = 3;
    TestState.hand[2][1] = 3;
    TestState.hand[2][2] = 3;
    TestState.hand[2][3] = 3;
    TestState.hand[2][4] = 3;

    TestState.deckCount[0] = 4;
    TestState.deckCount[1] = 4;  
    TestState.deckCount[2] = 4;

    TestState.deck[0][0] = 0;
    TestState.deck[0][1] = 4;
    TestState.deck[0][2] = 2;
    TestState.deck[0][3] = 5;

    TestState.deck[1][0] = 4;
    TestState.deck[1][1] = 5;
    TestState.deck[1][2] = 6;
    TestState.deck[1][3] = 7;

    TestState.deck[2][0] = 8;
    TestState.deck[2][1] = 9;
    TestState.deck[2][2] = 0;
    TestState.deck[2][3] = 1;

    TestState.discardCount[0] = 3;
    TestState.discardCount[1] = 3;  
    TestState.discardCount[2] = 3;

    TestState.discard[0][0] = 1;
    TestState.discard[0][1] = 2;
    TestState.discard[0][2] = 3;

    TestState.discard[1][0] = 3;
    TestState.discard[1][1] = 4;
    TestState.discard[1][2] = 5;

    TestState.discard[2][0] = 1;
    TestState.discard[2][1] = 0;
    TestState.discard[2][2] = 0;
   
    TestState.playedCardCount = 0; 
    */

    /*Run the advenCardTester with randomized state:*/
    testsPassed += advenCardTester(&TestState);
  }

  printf ("Passed %d of %d random card tests\n", testsPassed, TESTS); 

  return 0;
}
