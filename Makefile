CC = g++
CFLAGS = -g --std=c++11

testing: testing.o PokerHand_Class.o DeckOfCards_Class.o
	$(CC) -o testing testing.o PokerHand_Class.o DeckOfCards_Class.o
testing.o: testing.cc PokerHand_Class.h DeckOfCards_Class.h
	$(CC) $(CFLAGS) -c -o testing.o testing.cc
PokerHand_Class.o: PokerHand_Class.cc PokerHand_Class.h DeckOfCards_Class.h
	$(CC) $(CFLAGS) -c -o PokerHand_Class.o PokerHand_Class.cc
DeckOfCards_Class.o: DeckOfCards_Class.cc DeckOfCards_Class.h
	$(CC) $(CFLAGS) -c -o DeckOfCards_Class.o DeckOfCards_Class.cc


project2: project2.o PokerHand_Class.o DeckOfCards_Class.o
	$(CC) -o project2 project2.o PokerHand_Class.o DeckOfCards_Class.o
project2.o: project2.cc PokerHand_Class.h DeckOfCards_Class.h
	$(CC) $(CFLAGS) -c -o project2.o project2.cc
