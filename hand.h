#ifndef HAND_H
#define HAND_H

#include "card.h"
#include "deck.h"

class Hand : public Deck {

public:
    bool isPcOpened = false;

    bool isUserOpened = false;

    void alignSerial();

    void alignDual();

    const vector<Deck>& getSerialAlignedHand() const;

    const vector<Deck>& getDualAlignedHand() const;

    const Deck& getOtherCardHand() const;

    bool isSerial() const {
        return isSerialHand;
    }

    bool isCardHandleFunc() const;

    void setIsCardHandle(bool isCardHandle);

    void setIsSerialHand(bool serialHand);

    void printHand();

    bool getIsDrawCard() const;

    void setIsDrawCard(bool isDraw);

    void clearSerialHand();

    void clearDualHand();


    string line = "--------------------------------------------------------";


private:
    vector<Deck> serialAlignedHand;
    vector<Deck> dualAlignedHand;
    Deck otherCardHand;
    bool isSerialHand;
    bool isDrawCard;
    bool isCardHandle;

    bool hasOtherSerialDeckList(Card card);

    bool hasOtherDualDeckList(Card card);

    void printSerialHand();

    void printDualHand();

};

#endif // HAND_H
