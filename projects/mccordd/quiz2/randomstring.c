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

***************************************************************************************/

/*
PLEASE NOTE: PER INSTRUCTIONS, THIS IS ACTUALLY A TEXT FILE, NOT C CODE

SOURCES USED:
	-For the ASCII table:
	http://www.asciitable.com/
	-For the average length of English words:
	https://www.quora.com/Whats-the-average-length-of-English-words
	-For the probability of a random word coming up:
	https://math.stackexchange.com/questions/201648/probability-of-character-series-in-random-word
		and
	https://math.stackexchange.com/questions/815741/probability-of-a-four-letter-word-from-a-sequence-of-n-random-letters


HOW I DEVELOPED RANDOM TESTER SOLUTION:
  The first step in solving this quiz is to understand what exactly is being asked. 
My initial thought is that the test must already be partially integrated inside the 
source code -- so that the functions 'inputChar()' and 'inputString()' are part of 
the test to simulate random user input. But what is the testme() function even trying 
to accomplish? 
  Walking through this code: testme checks the provided characters from 'inputChar()'
and when they equal certain values, it increments the 'state' integer. These characters
are (in order): '[({ ax})]'. 
  Once the 'state' is set to the value 9, it checks the string provided from 
'inputString()' -- if this equals 'reset' (with a null terminating character), it prints
'error' and exits 200. 
  Immediately I have numerous questions: how long will random generation have to go until
the desired values are called? How is this testing at all, vs exploration of random char
generation? Am I supposed to edit anything aside from the two random character generating
functions?
  Looking at Piazza (question 53, https://piazza.com/class/j0xblek9xau521?cid=53, has an
answer endorsed by the professor), I see we are to only change those two functions. 
  So my first step is just to implement 'random' character and 'random' string and run it to see how long it will take on its own. While this isn't efficient in any sense of the 
word, it is, strictly speaking, the best interpretation of the provided assignment. 
  The first concession is that we're using ASCII characters, and within a certain range --
If we want all of them, but not the extended, we would generate 'random' from 0 to 127. 
  Rather than repeat code, we can just call the 'inputChar()' function within 
'inputString()' and write these to an array of a random size. Again, we have to make a 
choice here about the size of the string. This process goes on and on -- so I've made
an outline of the decisions I made going forward below:

Decisions made for random char and random string (pointer to string literal):
1. Use ASCII table without null (0), as this would terminate at once
2. Limit to characters 0-127 (decimal) starting. I know before beginning we're going to 
	want to limit these far more to ensure it completes. But we start here. 
3. String size: there are no specifications and no intended use for this program we're 
	testing, so I do some research. The average length of an English word is just over
	5. So we triple this, to start with, which is 15. This doesn't count the null
	terminating char. 
4. This gets us to state 9 rapidly, but iterates endlessly without getting 'reset.' 
	As this throws more data at the character but still manages to process, I decide
	to leave this, and instead modify only the inputString() function. We will limit the
	values written into this string -- as minimally as possible -- so starting with '!'
	or ASCII value 33, and going up to '~', or ASCII 126. 
5. This still doesn't find the word 'reset' in any reasonable amount of time. I do more 
	research here and the time for this is staggering. So we do more limiting. Once 
	solution is to simply feed the word 'reset' after n random attempts are made, but 
	I don't believe that's intended in the assignment -- as we're only editing the 
	'inputString()' and 'inputChar()' functions. So instead of this, I tighten the 
	string to the lower case alphabet, or 'a' - 'z'.
6. Set the word length to be 5 characters always. Even with this, it could run indefinitely.
7. Put in the string "reset" just to see how long it will run even with this handed 
	to it. Also with a limited overall range of 'e' to 't' for these characters. 
8. Gave a more limited range to each character -- starting with 4 possible characters for 	each. Test runs with this iterate between 850 and 6000 times. 

Not knowing any more about the rationale (ie, is this sufficient to test this objective), 
I conclude here. 


HOW SOLUTION WORKS AND FINDS ERROR MESSAGE:
	The solution works to find the error message by feeding any random character from
the non-extended list of characters. Once each desired character is fed into the 'testme()'
function, state is increased until it reaches 9. At this point, the string is checked each 
time until it equals 'reset.' As there are limited options for each character, this will 
occur within a certain range of iterations, as described above. 
	With this setup, it would be easy to adjust the ranges here, and build a superior
solution (for example from the lectures, avoiding '1287' in these ranges) -- but more 
information would be needed on intended use!



*/
