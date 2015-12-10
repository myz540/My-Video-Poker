/*
Mike Zhong
91.201-Rumshisky
Project2, Due: 12/8/15
*/

#include "DeckOfCards_Class.h"

/*******************************************************

Card class, contains overloaded comparison operators
to assist in sorting a poker hand. Includes toString() 
function to allow printing of Cards in a familiar format

*******************************************************/

// initialize static data members

const string Card::faces[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "JACK", "QUEEN", "KING", "ACE"};
const string Card::suits[4] = {"CLUB", "DIAMOND", "HEART", "SPADE"};

// define overloaded operators

bool Card::operator!=(const Card& rhs)
{
	if(this->face != rhs.face){
		return false;
	}
	else{
		return true;
	}
}

bool Card::operator==(const Card& rhs)
{
	if(this->face == rhs.face){
		return true;
	}
	else{
		return false;
	}
}

bool Card::operator<(const Card& rhs) {return this->face < rhs.face;}
bool Card::operator>(const Card& rhs) {return this->face > rhs.face;}

/**********************************************************

DeckOfCards class, contains a constructor which will create
a deck of cards. The class contains member functions to 
shuffle the deck, deal the top card, and also check to see 
if the deck is empty.

*********************************************************/

// Constructor: generates a 52 card deck where each card is unique

DeckOfCards::DeckOfCards()
{
	for(int i = 2; i <= 14; ++i){
		for(int j = 0; j <= 3; ++j){
			Card card(i, j);
			this->deck.push_back(card);
		}
	}
	
	this->currentCard = 51; // index of the top card on the deck
}

// shuffles the deck by iterating through the deck and swapping each card with a random card in the deck

void DeckOfCards::shuffle()
{
	cout << "\nShuffling deck..." << endl;
	
	srand(time(0));
	for(auto iter = this->deck.begin(); iter != this->deck.end(); ++iter){
		swap(*iter, this->deck.at(rand() % 52));

	}
	cout << "Deck is shuffled" << endl;
}

// returns the Card at the top of the deck and performs pop_back on the deck
// if the function is called with 'true' argument, the cards dealt will be hidden from the user

Card DeckOfCards::dealCard(bool _is_dealer)
{
	Card temp_card = this->deck.at(currentCard);

	if(!_is_dealer){
		cout << "Dealt a: " << this->deck.at(currentCard).toString() << endl;
	}
	else{
		cout << "Dealer dealt themselves a card" << endl;
	}
	
	this->deck.pop_back();
	
	if(this->deck.empty()){
		cout << "The last card has been dealt, the deck is now empty" << endl;
	}
	else{
		--this->currentCard;
	}
	
	return temp_card;
}

// boolean function to determine if the deck is empty

bool DeckOfCards::moreCards()
{
	return !this->deck.empty();
}
