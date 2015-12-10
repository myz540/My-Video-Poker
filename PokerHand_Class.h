/*
Mike Zhong
91.201-Rumshisky
Project2, Due: 12/8/15
*/

#ifndef POKERHAND_CLASS_H
#define POKERHAND_CLASS_H

#include "DeckOfCards_Class.h"

using namespace std;

// define an enumerated type, Rank, to store the relative values of the poker hands

typedef enum rank {HIGH_CARD, 
				   ONE_PAIR, 
				   TWO_PAIR, 
				   THREE_OF_A_KIND,
				   STRAIGHT,
				   FLUSH,
				   FOUR_OF_A_KIND
				   } Rank;

// overloaded << operator to easily print Rank

ostream& operator<<(ostream& os, Rank _rank);

/**********************************************

PokerHand class contains a vector<Card> and 
an enum variable called Rank to store the
highest ranking poker hand in any given hand.
Functions to deal a hand given a deck, evaluate 
a hand, allow user to trade in cards, allow 
dealer to smartly trade in cards, display hand, 
and a friend function to determine the winner 
given two PokerHands objects

**********************************************/

class PokerHand
{
	public:
		vector<Card> hand;
		Rank base_rank;

		// functions to deal a hand, either for the user or for the dealer,
		// trade in cards for user and dealer, print this->hand to standard output,
		// sort the hand in descending order by face, and evaluate a given hand,
		// re-arranging the hand while also assigning it a Rank
		void deal_hand(DeckOfCards& _deck, bool _is_dealer = false); 	
		void trade_in(int _num_of_cards, DeckOfCards& _deck);   		
		void auto_trade_in(DeckOfCards& _deck);							
		void display_hand(); 											
		void evaluate_hand(bool _is_dealer = false);																						

		// boolean functions to determine whether this->hand contains a certain poker hand
		bool has_four_of_a_kind();
		bool has_flush();
		bool has_straight();
		bool has_three_of_a_kind();
		bool has_two_pair();
		bool has_pair();
		
		// friend function that accepts two references to PokerHands
		// and determines which of the two hands is better
		friend void determine_winner(PokerHand& _player1, PokerHand& _player2);
};

#endif
