#include "card.h"
#include <iostream>

Card::Card(int id, int number, CardType cardType) {
    this->id = id; //id tanýmý
    this->cardNumber = number; //kart numarasý tanýmý
    this->cardType = cardType; //kart tipi tanýmý

}

int Card::getCardNumber() const {
    return cardNumber; //kart numarasýný geri döndürüyor
}

int Card::getId() const {
    return id; //karta atanan id´yi geri döndürüyor
}

CardType Card::getCardType() const {
    return cardType; //kartýn tipini geri döndürüyor
}

void Card::printCard() {

    if (kindOfCardByNumber(this->getCardNumber()).empty()) //vale kýz gibi kart mý yoksa deðil mi kontrolü
    {
        cout << this->id << "->" << getCardTypeName(this->getCardType()) << "-" << this->getCardNumber() << " "; //deðilse bunu
    }
    else
    {
        cout << this->id << "->" << getCardTypeName(this->getCardType()) << "-" << kindOfCardByNumber(this->getCardNumber()) << " "; //öyle ise bunu yazdýrýyor
    }
}

string Card::getCardTypeName(CardType cardType) //kart tipleri tanýmlamasý
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

string Card::kindOfCardByNumber(int cardNumber) //ekstra kartlarýn tanýmý vale kýz vs
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
