/*
Mike Zhong
91.201-Rumshisky
Project2, Due: 12/8/15
*/

#ifndef DECKOFCARDS_CLASS_H
#define DECKOFCARDS_CLASS_H

#include <string>
#include <iostream>
#include <cstdlib>
#include <algorithm>	
#include <utility>
#include <ctime>
#include <vector>

#define JACK 11
#define QUEEN 12
#define KING 13
#define ACE 14

#define CLUB 0
#define DIAMOND 1
#define HEART 2
#define SPADE 3

using namespace std;

/*******************************************************

Card class, contains overloaded comparison operators
to assist in sorting a poker hand. Includes toString() 
function to allow printing of Cards in a familiar format

*******************************************************/

class Card
{
	public:
		// Constructors and Destructor
		Card(int _face = 0, int _suit = 0) : face(_face), suit(_suit) {}
		~Card() {}
		Card(const Card& rhs) {face = rhs.face; suit = rhs.suit;}
		
		// Overloaded operators
		bool operator!=(const Card& rhs);
		bool operator==(const Card& rhs);
		bool operator<(const Card& rhs);
		bool operator>(const Card& rhs);

		// friend function which is used as the predicate for the sort() function
		friend bool sort_by_face(const Card& lhs, const Card& rhs);
		
		// static data members to represent faces and suits
		const static string faces[13]; 
		const static string suits[4]; 
		
		// getters and utility
		inline int getFace() {return this->face;}
		inline int getSuit() {return this->suit;}
		inline string toString() {return faces[this->face - 2] + " " + suits[this->suit];}
	
	private:
		int face;
		int suit;
};

/**********************************************************

DeckOfCards class, contains a constructor which will create
a deck of cards. The class contains member functions to 
shuffle the deck, deal the top card, and also check to see 
if the deck is empty.

*********************************************************/

class DeckOfCards
{
	public:
		// Constructor and Destructor
		DeckOfCards();
		~DeckOfCards() {}
		
		// Functions to shuffle, deal the top card, and determine if there are cards remaining
		void shuffle();
		Card dealCard(bool _is_dealer = false);
		bool moreCards();
		
	private:
		vector<Card> deck;
		int currentCard;
};

#endif

