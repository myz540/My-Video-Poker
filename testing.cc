/*
Mike Zhong
91.201-Rumshisky
Project2, Due: 12/8/15
*/

#include "PokerHand_Class.h"
#include "DeckOfCards_Class.h"

void demo0()
{
	cout << "Demo 0: generate deck, shuffle deck, deal cards until deck is empty" << endl;

	DeckOfCards my_deck;
	my_deck.shuffle();
	
	while(my_deck.moreCards()){
		my_deck.dealCard();
	}
}

void demo1()
{
	cout << "Demo 1: generate deck, shuffle deck, deal poker hand, evaluate the hand" << endl;

	DeckOfCards my_deck;
	my_deck.shuffle();

	PokerHand my_poker_hand;
	my_poker_hand.deal_hand(my_deck);
	my_poker_hand.evaluate_hand();

	// can change the face and suit of the five custom cards below
	// to test that the program will recognize all valid poker hands
	Card a(12,0), b(12,1), c(12,2), d(12,3), e(11,1);

	PokerHand custom_hand;
	custom_hand.hand.push_back(a);
	custom_hand.hand.push_back(b);
	custom_hand.hand.push_back(c);
	custom_hand.hand.push_back(d);
	custom_hand.hand.push_back(e);

	custom_hand.display_hand();
	custom_hand.evaluate_hand();
}

void demo2()
{
	cout << "Demo 2: generate deck, shuffle deck, deal 2 hands, evaluate both hands, determine better hand" << endl;
	
	DeckOfCards my_deck;
	my_deck.shuffle();

	PokerHand player1, dealer;
	player1.deal_hand(my_deck);
	dealer.deal_hand(my_deck);
	
	determine_winner(player1, dealer);
}

void demo3()
{
	cout << "Demo 3: generate deck, shuffle deck, allow user to trade in cards before evaluating" << endl;
	
	int trade_in = 0;
	DeckOfCards my_deck;
	my_deck.shuffle();

	PokerHand my_hand;
	my_hand.deal_hand(my_deck);
	
	my_hand.evaluate_hand();
	
	do{
		cout << "How many cards would you like to trade in: ";
		cin >> trade_in;
	}
	while(trade_in <= 0 && trade_in >= 3);
	
	my_hand.trade_in(trade_in, my_deck);
	my_hand.evaluate_hand();
}

int main()
{
	//demo0();
	//demo1();
	//demo2();
	//demo3();
	
	return 0;
}
