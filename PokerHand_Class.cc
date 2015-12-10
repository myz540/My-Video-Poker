/*
Mike Zhong
91.201-Rumshisky
Project2, Due: 12/8/15
*/

#include "PokerHand_Class.h"

// predicate used by sort() algorithm

bool sort_by_face(const Card& lhs, const Card& rhs)
{
	if(lhs.face > rhs.face){
		return true;
	}
	else{
		return false;
	}
}

// overloaded << operator to easily print Rank

ostream& operator<<(ostream& os, Rank _rank)
{
	if(_rank == HIGH_CARD){
		os << "HIGH CARD";
	}
	else if(_rank == ONE_PAIR){
		os << "ONE PAIR";
	}
	else if(_rank == TWO_PAIR){
		os << "TWO PAIR";
	}
	else if(_rank == THREE_OF_A_KIND){
		os << "THREE OF A KIND";
	}
	else if(_rank == STRAIGHT){
		os << "STRAIGHT";
	}
	else if(_rank == FLUSH){
		os << "FLUSH";
	}
	else if(_rank == FOUR_OF_A_KIND){
		os << "FOUR OF A KIND";
	}

	return os;
}

/********************************************

PokerHand class contains a vector<Card> and 
an enum variable called Rank to store the
highest ranking poker hand in any given hand
Functions to deal a hand given a deck,evaluate 
a hand, allow user to trade in cards, allow 
dealer to smartly trade in cards, display hand, 
and a friend functionto determine the winner 
given two PokerHands

********************************************/

// given a deck, will deal top 5 cards into this hand
// if the second argument is true, the cards dealt will be hidden from the user

void PokerHand::deal_hand(DeckOfCards& _deck, bool _is_dealer)
{
	cout << "\nDealing hand..." << endl;

	for(int i = 0; i < 5; ++i){
		if(!_deck.moreCards()){
			cout << "You are trying to deal cards from an empty deck, exiting program" << endl;
			exit(1);
		}
		
		this->hand.push_back(_deck.dealCard(_is_dealer));
	}

	cout << endl;
}

// assigns Rank rearranges hand to relevant ordering
// will hide the results if the hand belongs to the dealer

void PokerHand::evaluate_hand(bool _is_dealer)
{
	cout << "\nEvaluating hand..." << endl;

	// Sort hand in descending order by face value
	sort(this->hand.begin(), this->hand.end(), sort_by_face);
	
	// if else to determine base_rank of the hand
	// check highest rank first, since by definition, a four of a kind will
	// contain a three of a kind, which will also contain a pair
	if(this->has_four_of_a_kind()){
		this->base_rank = FOUR_OF_A_KIND;
	}
	else if(this->has_flush()){
		this->base_rank = FLUSH;
	}
	else if(this->has_straight()){
		this->base_rank = STRAIGHT;
	}
	else if(this->has_three_of_a_kind()){
		this->base_rank = THREE_OF_A_KIND;
	}
	else if(this->has_two_pair()){
		this->base_rank = TWO_PAIR;
	}
	else if(this->has_pair()){
		this->base_rank = ONE_PAIR;
	}
	else{
		this->base_rank = HIGH_CARD;
		sort(this->hand.begin(), this->hand.end(), sort_by_face);
	}
	
	if(!_is_dealer){
		cout << "Your hand has been evaluated: " << this->base_rank << endl;
		this->display_hand();
		cout << endl;
	}
	else{
		cout << "Dealer hand has been evaluated: " << this->base_rank << endl;
		cout << endl;
	}
}

// Prints the cards of the hand and their index for trade in purposes

void PokerHand::display_hand()
{
	cout << "\nDISPLAYING HAND" << endl;
	int i = 0;
	for(auto iter = this->hand.begin(); iter != this->hand.end(); ++iter){
		cout << "Index " << i << ": " << iter->toString() << endl;
		++i;
	}
}

// Displays hand and allows the user to select the indices of the cards they wish to trade in
// The cards you get are from the same DeckOfCards that dealt the hand

void PokerHand::trade_in(int _num_of_cards, DeckOfCards& _deck)
{
	if(_num_of_cards == 0){
		cout << "No cards were traded in" << endl;
		return;
	}

	int i = _num_of_cards,  index = 0;
	
	while(i > 0){
		this->display_hand();
		cout << "Please enter the index of the card you wish to trade in: ";
		cin >> index;

		if(index >= 0 && index < this->hand.size() && _deck.moreCards()){
			auto iter1 = this->hand.begin() + index;
			this->hand.erase(iter1);
			--i;
		}
		else{
			cout << "ERROR: Either an invalid index was entered or the deck has run out of cards" << endl;
		}
	}

	while(i < _num_of_cards && _deck.moreCards()){
		this->hand.push_back(_deck.dealCard());
		++i;
	}

	cout << "Done trading in cards" << endl;
}

// function call will allow dealer to smartly trade in cards
// details and explanation for the implementation are provided in the README.txt

void PokerHand::auto_trade_in(DeckOfCards& _deck)
{
	cout << "\nDealer is trading in cards..." << endl;
	
	// evaluate dealer hand, set an iterator to the final card, create a switch for the Rank
	this->evaluate_hand(true);
	Rank A = this->base_rank;
	auto iter = this->hand.end() - 1;

	switch(A)
	{
	case FOUR_OF_A_KIND:
		if(iter->getFace() < 10){
			this->hand.pop_back();
			this->hand.push_back(_deck.dealCard(true));
		}
		break;

	case FLUSH:

	case STRAIGHT:
		break;

	case THREE_OF_A_KIND:
		this->hand.pop_back();
		iter--;
		if(iter->getFace() < 10){
			this->hand.pop_back();
			this->hand.push_back(_deck.dealCard(true));
		}
		this->hand.push_back(_deck.dealCard(true));
		break;

	case TWO_PAIR:
		if(iter->getFace() < 10){
			this->hand.pop_back();
			this->hand.push_back(_deck.dealCard(true));
		}
		break;		

	case ONE_PAIR:
		this->hand.pop_back();
		iter--;
		if(iter->getFace() < 10){
			this->hand.pop_back();
			iter--;
			if(iter->getFace() < 10){
				this->hand.pop_back();
				this->hand.push_back(_deck.dealCard(true));
			}
			this->hand.push_back(_deck.dealCard(true));
		}
		this->hand.push_back(_deck.dealCard(true));
		break;

	case HIGH_CARD:			
		bool connecting_cards = true;
		
		for(auto iter1 = this->hand.begin(); iter1 != this->hand.begin() + 2; ++iter1){
			for(auto iter2 = iter1 + 1; iter2 != iter1 + 4; ++iter2){
				if(iter1->getFace() != iter2->getFace() + 1){
					connecting_cards = false;
					break;
				}
			}
			if(connecting_cards == false){break;}
		}

		if(connecting_cards){
			auto iter1 = this->hand.begin();
			auto iter2 = iter1 + 1;
			if(iter1->getFace() == iter2->getFace() + 1){
				this->hand.pop_back();
			}
			else{
				swap(*iter1, *iter);
				this->hand.pop_back();
			}
			this->hand.push_back(_deck.dealCard(true));
			break;
		}

		else{
			this->hand.pop_back();
	                iter--;
        	        if(iter->getFace() < 10){
                	        this->hand.pop_back();
                        	iter--;
                        	if(iter->getFace() < 10){
                                	this->hand.pop_back();
                                	this->hand.push_back(_deck.dealCard(true));
                        	}
                        	this->hand.push_back(_deck.dealCard(true));
                	}
                	this->hand.push_back(_deck.dealCard(true));
                	break;
		}
	}
	
	cout << "Dealer has finished trading in cards" << endl;
}

// friend function that accepts two references to PokerHands
// and determines which of the two hands is better

void determine_winner(PokerHand& _player1, PokerHand& _player2)
{
	cout << "\nDETERMINING WINNER...\n" << endl;

	// 1. Evaluate both hands so they are in their proper order
	cout << "Player1's hand: " << endl;
	_player1.evaluate_hand();
	cout << "Dealer's hand: " << endl;
	_player2.evaluate_hand();

	// 2. If both hands are of the same rank...
	// compare the faces of the cards from each hand until one is greater than the other
	if(_player1.base_rank == _player2.base_rank){
		
		int i = 0;		
		for(i = 0; i < 5; ++i){
			if(_player1.hand[i].getFace() > _player2.hand[i].getFace()){
				cout << "***Player1 wins***" << endl;
				break;
			}
			else if(_player1.hand[i].getFace() < _player2.hand[i].getFace()){
				cout << "***Dealer wins***" << endl;
				break;
			}
			else {continue;}
		}
		if(i == 4){
			cout << "Push" << endl;
		}
	}

	// 3. If one hand has a higher rank than the other, that hand is automatically the winner
	else if(_player1.base_rank > _player2.base_rank){
		cout << "***Player1 wins***" << endl;
		cout << _player1.base_rank << " beats " << _player2.base_rank << endl;
	}
	
	else if(_player1.base_rank < _player2.base_rank){
		cout << "***Dealer wins***" << endl;
		cout << _player2.base_rank << " beats " << _player1.base_rank << endl;
	}
}


/*****************************************

boolean functions to check for poker hands
and sort hand accordingly to make for
easier comparisons in determining winner

*****************************************/

// All of the boolean functions share a similar structure
// First, the hand gets sorted in descending order
// Second, a boolean flag is set to true or false depending on the poker hand it is searching for
// Third, through an iterative process, the hand is evaluated and the boolean flag is either flipped or stays the same

// Identifies four a kind and arranges the hand accordingly

bool PokerHand::has_four_of_a_kind()
{
	sort(this->hand.begin(), this->hand.end(), sort_by_face);
	bool four_of_a_kind = true;
	
	// only need iter1 to check the first two cards, iter2 only needs to check three cards after iter1
	for(auto iter1 = this->hand.begin(); iter1 != this->hand.end() - 3; ++iter1){
		for(auto iter2 = iter1 + 1; iter2 != iter1 + 3; ++ iter2){
			
			if(iter1->getFace() != iter2->getFace()){ 			// FLAG
				four_of_a_kind = false;
				break;
			}
		}
		if(!four_of_a_kind) {break;}
	}
	
	if(four_of_a_kind){
		if(this->hand[0] < this->hand[4]){
			swap(this->hand[0], this->hand[4]);
		}
		cout << "Hand contains four of a kind, RANK: 6" << endl;
	}
	
	return four_of_a_kind;
}

// Identifies a flush and swaps the high card to the front for easy comparison

bool PokerHand::has_flush()
{
	sort(this->hand.begin(), this->hand.end(), sort_by_face);
	bool flush = true;	
	
	// Check the suit of each Card against the first
	auto iter1 = this->hand.begin();
	for(auto iter2 = this->hand.begin() + 1; iter2 != this->hand.end(); ++iter2){
		
		if(iter1->getSuit() != iter2->getSuit()){			// FLAG
			flush = false;
			break;
		}
	}
	
	if(flush){
		cout << "Hand contains a flush, RANK: 5" << endl;
	}
	
	return flush;
}

// Identifies a straight and swaps the high card to the front for easy comparison

bool PokerHand::has_straight()
{
	sort(this->hand.begin(), this->hand.end(), sort_by_face);
	bool straight = true;			// assume we have a straight
	
	// If our assumption that this hand contains a straight is correct, 
	// then each subsequent Card, based on the sorting algorithm, 
	// should be one less than the card before it
	auto iter1 = this->hand.begin();
	for(auto iter2 = this->hand.begin() + 1; iter2 != this->hand.end(); ++iter2){
		
		if(iter2->getFace() != iter1->getFace() - 1){			// if it is not one less, FLAG
			straight = false;
			break;
		}

		++iter1;			// advance iter1
	}
	
	if(straight){
		cout << "Hand contains a straight, RANK: 4" << endl;
	}
	
	return straight;
}

// Identifies three of a kind and swaps them to the front, then orders the last two remaining by descending face value
// NOTE: function is called by evaluate_hand(), which will only call this function if all the above bool functions return false.

bool PokerHand::has_three_of_a_kind()
{
	sort(this->hand.begin(), this->hand.end(), sort_by_face);
	bool three_of_a_kind = false;
	
	int count = 0;			// number of instances of a Card face in this->hand
	Card temp_card;			// store the face value of the pair, if found
	
	for(auto iter1 = this->hand.begin(); iter1 != this->hand.end() - 2; ++iter1){
		count = 0;			// must reset this counter each time iter1 moves

		for(auto iter2 = iter1 + 1; iter2 != this->hand.end(); ++iter2){
			
			if(count == 0 && iter1->getFace() == iter2->getFace()){		
				// found our first instance A.K.A a pair
				++count;
				swap(*iter1, this->hand[0]);
				swap(*iter2, this->hand[1]);
				temp_card = this->hand[0];
			}
			
			else if(count == 1 && temp_card.getFace() == iter2->getFace()){		
				// you found one instance before, and now you have found another
				swap(*iter2, this->hand[2]);
				++count;
				break;
			}
		}
		if(count == 2){break;}
	}
	
	// FLAG and possible swap of last two cards
	if(count == 2){
		cout << "Hand contains three of a kind, RANK 3" << endl;
		three_of_a_kind = true;

		if(this->hand[3] < this->hand[4]){
			swap(this->hand[3], this->hand[4]);
		}
	}
	
	return three_of_a_kind;
}

// Identifies a two pair and swaps them to the front by descending face value. The kicker is the last card at index = 4
// NOTE: function is called by evaluate_hand(), which will only call this function if all the above bool functions return false.

bool PokerHand::has_two_pair()
{
	sort(this->hand.begin(), this->hand.end(), sort_by_face);
	bool two_pair = false;
	int count = 0;
	
	// check for pairs with the first two Cards of the hand
	for(auto iter1 = this->hand.begin(); iter1 != this->hand.end() - 3; ++iter1){
		for(auto iter2 = iter1 + 1; iter2 != this->hand.end(); ++iter2){
			
			if(iter1->getFace() == iter2->getFace()){			// if you find a pair

				swap(*iter1, this->hand[0]);
				swap(*iter2, this->hand[1]);
				++count;
				break;
			}
		}
		if(count == 1){					
			break;
		}
	}
	
	// check for pairs starting with the third Card of the hand
	for(auto iter1 = this->hand.begin() + 2; iter1 != this->hand.end() - 1; ++iter1){
		for(auto iter2 = iter1 + 1; iter2 != this->hand.end(); ++iter2){

			if(iter1->getFace() == iter2->getFace()){			// another pair?! what a hand

				swap(*iter1, this->hand[2]);
				swap(*iter2, this->hand[3]);
				++count;
				break;
			}
		}
		if(count == 2){break;}
	}

	// FLAG
	if(count == 2){
		cout << "Hand contains a two pair, RANK 2" << endl;
		two_pair = true;
	}
	
	return two_pair;
}

// Identifies a single pair and swaps them to the front, sorts the remaining cards in descending order of face value
// NOTE: function is called by evaluate_hand(), which will only call this function if all the above bool functions return false.

bool PokerHand::has_pair()
{
	sort(this->hand.begin(), this->hand.end(), sort_by_face);
	bool pair = false;
	int count = 0;
	
	// Iterate through hand looking for a pair
	for(auto iter1 = this->hand.begin(); iter1 != this->hand.end() - 1; ++iter1){
		for(auto iter2 = iter1 + 1; iter2 != this->hand.end(); ++iter2){
			
			if(iter1->getFace() == iter2->getFace()){			// if you find a pair
				
				swap(*iter1, this->hand[0]);
				swap(*iter2, this->hand[1]);
				++count;
				break;
			}
		}
		if(count == 1){break;}
	}

	// FLAG
	if(count == 1){
		cout << "Hand contains a pair, RANK 1" << endl;
		sort(this->hand.begin() + 2, this->hand.end(), sort_by_face);
		pair = true;
	}
	
	return pair;
}
