/**************************************************************************************
	Name: Doug McCord
	Date: 4/27/17
	Project: CS 362 Quiz 2
	Description: Quiz instructions:
	  "Implement a random tester for the function testme() in testme.c that is capable 
	  of printing the error message.  You should implement inputChar() and inputString() 
	  to produce random values. Write up the development of your random tester and how 
	  it finds the error message as randomstring.c. Submit testme.c and randomstring.c 
	  under your onid directory in class github. (under your onid directory and not under 
	  dominion directory). The randomstring.c is a text file that outlines how you 
	  developed your solution and how it works!"

	
	NOTE: Per Piazza, only the inputChar() and inputString() functions are modified
		from the provided code. 
	SOURCES: see randomstring.c for all sources

***************************************************************************************/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char inputChar()
{
    // TODO: rewrite this function
    // DKM: quiz states this should produce random values
    char genChar;
    genChar  = (char)(rand() % 127 + 1);
    return genChar;
}

char *inputString()
{
    // TODO: rewrite this function
    //	DKM: quiz states this should produce random values
    // 		The length of our random strings will be randomly determined, between 1
    //		and 15 characters. See randomstring.c for rationale. 
    int i;
    int wordLen;
    //wordLen = (random() % 15 + 1);
    wordLen = 5;

    char genStr [wordLen];
    memset(genStr, '\0', wordLen);

    //Now loop this and fill with random chars from our inputChar function:
    for (i = 0; i < wordLen; i++)
    {	
    	//See randomstring.c for explanation of these attempted approaches:
    	//genStr[i] = inputChar();
    	//genStr[i] = '!' + (rand() % 94);
    	//genStr[i] = 'e' + (rand() % 16); 

    	if(i == 0) genStr[0] = 'q'+ (rand() % 4); 		// for char 'r'
    	else if(i == 1) genStr[1] = 'c'+ (rand() % 4);	//for char 'e'
    	else if(i == 2) genStr[2] = 'r'+ (rand() % 4);	//for char 's'
    	else if(i == 3) genStr[3] = 'd'+ (rand() % 4);	//for char 'e'
    	else if(i == 4) genStr[4] = 's'+ (rand() % 4);	//for char 't'
    }
    char *returnStr = genStr;
    //char *returnStr = "reset";

    return returnStr;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
