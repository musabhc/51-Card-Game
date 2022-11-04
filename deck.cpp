#include "deck.h"


void Deck::addCardToBack(Card card) //gelen kart� en sona ekleme
{
    this->cards.push_back(card);
}

void Deck::addCardToFront(Card card) // ba�a kart ekleme
{
    this->cards.insert(this->cards.begin(), card);
}

void Deck::removeCard(Card card) //kart silimi
{
    vector<Card>::iterator it;
    it = find(this->cards.begin(), this->cards.end(), card); //ilgili kart�n destede bulunmas� ve yerinin belirlenmesi
    this->cards.erase(it); //yeri belirlenen kart�n silinmesi
}

void Deck::sortDeck() //destenin s�ralanmas�
{
    int i, j;
    int n = this->cards.size(); //kartlar�n adedi n de�i�kenine atand�
    for (i = 0; i < n - 1; i++) //toplam kart miktar�n�n 1 eksi�ince taran�yor
    {
        for (j = 0; j < n - i - 1; j++) //eksik miktar�n�n 1 fazlas� miktar�nca taran�yor
        {
            if (this->cards[j].getId() > this->cards[j + 1].getId()) //�rne�i 1 numaral� kart�n idsi 10 2 numaral� kart�n idsi 11 ise 1 ve 2 numaral� kart�n++
            {
                //++yeri de�i�tiriliyor.
                this->swap(&this->cards[j], &this->cards[j + 1]);

            }
        }
    }
}



void Deck::mixDeck() //destelerin kar��t�r�lmas�
{
    srand(time(NULL)); //random olmas� sa�lan�yor
    for (int i = 0; i < this->cards.size(); ++i)  //kartlar�n tamam� taran�yor
    {
        int random1 = rand() % cards.size() + 1; //random 1 say� belirleniyor
        int random2 = rand() % cards.size() + 1; //random 1 say� daha belirleniyor
        random1 = random1 - 1; //bu random say�dan 1 ��kar�l�yor
        random2 = random2 - 1; //bundan da 1 ��kar�l�yor
        Card temp = cards.at(random1); //ge�ici bir de�i�kence belirlenen say�n�n oldu�u konumdaki kart depolan�yor
        cards.at(random1) = cards.at(random2); //o kart ile di�er random kart yer de�i�tiriliyor
        cards.at(random2) = temp; // yer de�i�tiren kart temp�e aktar�l�yor.
        /*
        Sonu� olarak 15 ile 17 numaral� kartlar yer de�i�tirmi� oldu. 1 eksi�inin al�nma sebebi ise en ba�ta fazladan 1 fazla almam�zd�.
        yani int random1 ve random2 de +1 ekledi�imizden �t�r� 1 eksi�ini al�yoruz bu sayede 0 ile 100 aras�ndaki t�m say�lara hatas�z ula�ma
        imkan�na sahip oluyoruz.
        */

    }
}

Card Deck::getRandomCard() //rastgele bir kart�n �ekilmesi
{
    srand(time(NULL)); //ayn� say�n�n gelmesi engellendi
    int random = rand() % cards.size() + 1; // random say� olu�turuldu
    random = random - 1; //1 eksiltildi
    Card card = this->cards.at(random); // random say�n�n oldu�u yerdeki kart objeye atand�
    return card; //kart sisteme g�nderildi
}

void Deck::moveToEnd(Card card) //kart� destenin sonuna aktarma
{
    vector<Card>::iterator it; //bir vekt�r tasarlad�k
    it = find(this->cards.begin(), this->cards.end(), card); // bu vekt�re sona g�nderilecek kart� bulmas�n� s�yledik
    this->cards.erase(it); //kart� mevcut konumundan sildik
    this->cards.push_back(card); //�imdi de onu en sona aktard�k.

}

void Deck::printDeck() //destenin tamam�n�n yazd�r�lmas�
{
    for (int i = 0; i < this->cards.size(); ++i) //destenin tamam�n�n taranmas� sa�lan�yor
    {
        Card card = this->cards.at(i); //belirtilen konumdaki kart objeye atan�yor
        card.printCard(); //obje yaz�d�r�lma i�lemine yollan�yor.
    }
}

void Deck::swap(Card* xp, Card* yp) //kartlar�n birbiriyle olan yerlerinin de�i�tirilmesi
{
    Card temp = *xp; //bir ge�ici de�i�kene 1. kart atan�yor
    *xp = *yp; //1. kart ile 2. kart de�i�tiriliyor
    *yp = temp; // 2. kart 1. kart oluyor
}

void Deck::clear() //kartlar� temizleme
{
    this->cards.clear(); //temizledik.

}

vector<Card> Deck::getCards() const //kart� g�nderme i�lemi
{
    return cards;
}
