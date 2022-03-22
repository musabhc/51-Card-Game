#include "card.h"
#include <iostream>

Card::Card(int id, int number, CardType cardType) {
    this->id = id; //id tanımı
    this->cardNumber = number; //kart numarası tanımı
    this->cardType = cardType; //kart tipi tanımı

}

int Card::getCardNumber() const {
    return cardNumber; //kart numarasını geri döndürüyor
}

int Card::getId() const {
    return id; //karta atanan id´yi geri döndürüyor
}

CardType Card::getCardType() const {
    return cardType; //kartın tipini geri döndürüyor
}

void Card::printCard() {

    if (kindOfCardByNumber(this->getCardNumber()).empty()) //vale kız gibi kart mı yoksa değil mi kontrolü
    {
        cout << this->id << "->" << getCardTypeName(this->getCardType()) << "-" << this->getCardNumber() << " "; //değilse bunu
    }
    else
    {
        cout << this->id << "->" << getCardTypeName(this->getCardType()) << "-" << kindOfCardByNumber(this->getCardNumber()) << " "; //öyle ise bunu yazdırıyor
    }
}

string Card::getCardTypeName(CardType cardType) //kart tipleri tanımlaması
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

string Card::kindOfCardByNumber(int cardNumber) //ekstra kartların tanımı vale kız vs
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
