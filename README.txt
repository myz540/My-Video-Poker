****************************
******** MIKE ZHONG ********
***** 91.201-RUMSHISKY *****
** PROJECT2, DUE: 12/8/15 **
****************************

The following README file provides technical documentation for the 
video poker game, designed and created by Mike Zhong for Umass Lowell
Computing 3 course, taught by Professor Rumshisky. The goal of the
project was to create a fully functioning game of 5-card draw.
The dealer will shuffle a deck of cards, deal two 5-card hands, allow
the user to trade in up to 3 cards, and then smartly decide which cards
they want to trade in. Once all trade ins are made, the program will
evaluate both hands and determine a winner.

****************************
DeckOfCards Class:
****************************
The DeckOfCards header and implementation file provide the backbone for
the project. They define a Card as an object with two int fields, one for 
the face and one for the suit. Additionally, the header file clearly defines
integer values for JACK, QUEEN, KING, ACE, as well as SPADE, HEART, CLUB, DIAMOND.
Additionally, overloaded comparison operators are defined to allow comparison of
Cards by their face value. A predicate is also defined which will be used in the
generic sort() function to sort a collection of Cards (a poker hand for instance).
Lastly, the class contains const static strings to map and print the Cards'
face and suits into plain english for easier user interaction and readability.

The deck itself is defined as a vector of Cards, and the default constructor is
defined to generate a deck of cards. Additionally, the deck object has member
functions allowing it to shuffle the deck, deal the top card, recognize when 
the deck is empty, and contains an integer data member which is the index of 
the current top card. The dealCard() function has an optional boolean parameter
which will hide the card dealt if true. This allows the program to simulate a 
dealer dealing his cards face down.

*****************************
PokerHand Class:
*****************************
The PokerHand header and implementation file provide the details specific to
the game of 5-card draw poker. The poker hand is defined as a vector of Cards 
and an enumerated type called Rank, which corresponds to the various poker hands
one can assemble. The class contains member functions which can print the hand 
to standard output, as well as evaluate the hand. The evaluate function will
assign the Rank data member as well as order the hand in such a way that any
valid poker hands created will be first, followed by the remaining cards in
descending order.

The class contains a member function to deal a 5-card hand given a deck of cards,
and an optional boolean variable to signify whether the hand should be dealt
face up or face down. There are functions that allow the user to trade in up to 3
cards, and another function which invokes the dealer's AI to smartly trade cards.

The class contains several boolean functions which will return true if the
5-card hand contains the given poker hand.

Lastly, the class contains a friend function which takes two references to poker 
hands and determines the winner.

By default, the user is always Player1 and the dealer is always Player2.

******************************
Testing:
******************************
During development, the testing.cc source code was used as a driver to test the various 
functions of the classes. The various demos roughly correspond to the numbered
requirements on the project specifications sheet. The demos are meant to demonstrate
functionality and correctness of the code, and also allow others to tinker and
alter the code without altering the final product.

To compile and run the test code, simply type 'make testing', followed by './testing'

******************************
Project2:
******************************
The final project can be compiled and run by typing 'make project2', followed
by './project2'. The user will then be guided throughout the remainder of the program.

******************************
Notes and details on the AI:
******************************
During the course of the game, the user will have a chance to trade in up to 3 cards
from their hand for 3 new cards from the deck. Once the user has finished this step,
the dealer will invoke their AI which will evaluate and trade in cards based on
what valid poker hands are currently present, as well as what hands they can potentially
create. I decided to take a conservative approach with the AI, meaning that if the AI
detects a two pair, or a pair, they will ALMOST NEVER break up an existing hand in the
hopes of attaining a higher ranking hand. Additionally, if the dealer has a flush or straight,
no cards will be traded in. 

If the dealer has a four of a kind, they will trade in their kicker, or tie-breaker
card if it is less than 10.

If the dealer has a three of a kind, they will always trade in the smaller of the two
remaining cards, and trade in the larger card only if it is less than 10.

If the dealer has a two pair, they will trade in their kicker only if it is less than 10.

If the dealer has one pair, they will always trade in the smallest remaining card,
and evaluate the other two, trading them in if they are less than 10.

If the dealer has no valid poker hands (just a high card), the dealer will most likely
trade in up to 3 cards (if they are all less than ten) for new cards. The one scenario
where the dealer will opt for a different strategy will be if there are four consecutive
cards and there is an open-ended straight draw, then the dealer will trade in the one
non-consecutive card in the hopes of hitting a straight. Other than that, the dealer will 
trade in up to 3 of the smallest cards in the hand in the hopes of hitting a pair, two pair,
or maybe even a three of a kind. The reasoning for not going for the flush, even if the
dealer has four of the same suit, is that the probability of hitting a flush is very small,
and so a more conservative approach would be to try for higher probability hands.

******************************
Results of 20 game simulations
******************************
Me: 9
Dealer: 11

Friends (Emily Clark/Brian Paciulan): 8
Dealer: 12

Hope you enjoy the game!
