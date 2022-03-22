#ifndef DECK_H
#define DECK_H

#include "card.h"


class Deck {
public:
    void addCardToBack(Card card);

    void addCardToFront(Card card);

    void removeCard(Card card);

    void sortDeck();

    vector<Card> getCards() const;

    void mixDeck();

    Card getRandomCard();

    void moveToEnd(Card card);

    void printDeck();

    void clear();

private :
    vector<Card> cards;

    void swap(Card *xp, Card *yp);
};

#endif // DECK_H
