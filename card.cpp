#include "card.h"
#include <iostream>

Card::Card(int id, int number, CardType cardType) {
    this->id = id; //id tan�m�
    this->cardNumber = number; //kart numaras� tan�m�
    this->cardType = cardType; //kart tipi tan�m�

}

int Card::getCardNumber() const {
    return cardNumber; //kart numaras�n� geri d�nd�r�yor
}

int Card::getId() const {
    return id; //karta atanan id�yi geri d�nd�r�yor
}

CardType Card::getCardType() const {
    return cardType; //kart�n tipini geri d�nd�r�yor
}

void Card::printCard() {

    if (kindOfCardByNumber(this->getCardNumber()).empty()) //vale k�z gibi kart m� yoksa de�il mi kontrol�
    {
        cout << this->id << "->" << getCardTypeName(this->getCardType()) << "-" << this->getCardNumber() << " "; //de�ilse bunu
    }
    else
    {
        cout << this->id << "->" << getCardTypeName(this->getCardType()) << "-" << kindOfCardByNumber(this->getCardNumber()) << " "; //�yle ise bunu yazd�r�yor
    }
}

string Card::getCardTypeName(CardType cardType) //kart tipleri tan�mlamas�
{
    switch (cardType)
    {
    case maca:
        return "Maca";
    case sinek:
        return "Sinek";
    case kupa:
        return "Kupa";
    case karo:
        return "Karo";

    }
}

string Card::kindOfCardByNumber(int cardNumber) //ekstra kartlar�n tan�m� vale k�z vs
{
    if (cardNumber > 10)
    {
        switch (cardNumber % 10) {
        case 1:
            return "Vale";
        case 2:
            return "Kiz";
        case 3:
            return "Papaz";
        case 4:
            return "As";
        default:
            return "";
        }
    }
    return "";
}
