/*
Mike Zhong
91.201-Rumshisky
Project2, Due: 12/8/15
*/

#include "PokerHand_Class.h"

void play_game();

// allow user to play game until they no longer want to

int main()
{
	cout << endl;
	cout << "***************************************" << endl;
	cout << "* WELCOME TO MIKE ZHONG'S VIDEO POKER *" << endl;
	cout << "***************************************" << endl;

	char cont = 'N';

	do{
		play_game();
		cout << "\nDo you wish to play again (Y/N)? ";
		cin >> cont;
	}
	while(cont == 'Y' || cont == 'y');

	cout << endl;
	cout << "***************************************" << endl;
	cout << "******** THANK YOU FOR PLAYING ********" << endl;
	cout << "***************************************" << endl;

	return 0;
}

// the play_game() function does the heavy lifting

void play_game()
{
	cout << "\nThe name of the game is 5-card draw" << endl;
	cout << "The player and dealer will each be dealt a 5-card hand" << endl;
	cout << "The player will have an opportunity to trade up to 3 of their cards in for new cards" << endl;
	cout << "The dealer will also have the same opportunity" << endl;
	cout << "Once the cards have been exchanged, the player with the better poker hand wins" << endl;

	// create and shuffle deck
	DeckOfCards my_deck;
	my_deck.shuffle();

	// create and deal player and dealer hands
	PokerHand player_hand, dealer_hand;
	player_hand.deal_hand(my_deck);
	dealer_hand.deal_hand(my_deck, true);

	// evaluate player hand and allow them to trade in
	player_hand.evaluate_hand();

	int trade_in = 0;
	do{
		cout << "How many cards would you like to trade in: ";
		cin >> trade_in;
	}
	while(trade_in <= 0 && trade_in >= 3);
	
	player_hand.trade_in(trade_in, my_deck);

	// dealer trades in cards, uncomment the two evaluate_hand() lines below
	// to see the dealer's hand before and after the AI trades in cards

	//dealer_hand.evaluate_hand();
	dealer_hand.auto_trade_in(my_deck);
	//dealer_hand.evaluate_hand();

	// determine winning hand
	determine_winner(player_hand, dealer_hand);	
}
