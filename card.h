#ifndef CARD_H
#define CARD_H


#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

enum CardType {
    maca,
    sinek,
    kupa,
    karo,
};

class Card {
public:
    Card(int id, int number, CardType cardType);

    int getCardNumber() const;

    int getId() const;

    CardType getCardType() const;

    void printCard();

    bool operator==(const Card& i) const { return this->id == i.id; }

    bool operator!=(const Card& i) const { return this->id != i.id; }

    bool operator>(const Card& i) const { return this->id > i.id; }

    bool operator<(const Card& i) const { return this->id < i.id; }


private:
    int id;
    int cardNumber;
    CardType cardType;

    static string getCardTypeName(CardType cardType);

    static string kindOfCardByNumber(int cardNumber);

};

#endif // CARD_H
