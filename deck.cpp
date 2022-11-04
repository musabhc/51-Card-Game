#include "deck.h"


void Deck::addCardToBack(Card card) //gelen kartý en sona ekleme
{
    this->cards.push_back(card);
}

void Deck::addCardToFront(Card card) // baþa kart ekleme
{
    this->cards.insert(this->cards.begin(), card);
}

void Deck::removeCard(Card card) //kart silimi
{
    vector<Card>::iterator it;
    it = find(this->cards.begin(), this->cards.end(), card); //ilgili kartýn destede bulunmasý ve yerinin belirlenmesi
    this->cards.erase(it); //yeri belirlenen kartýn silinmesi
}

void Deck::sortDeck() //destenin sýralanmasý
{
    int i, j;
    int n = this->cards.size(); //kartlarýn adedi n deðiþkenine atandý
    for (i = 0; i < n - 1; i++) //toplam kart miktarýnýn 1 eksiðince taranýyor
    {
        for (j = 0; j < n - i - 1; j++) //eksik miktarýnýn 1 fazlasý miktarýnca taranýyor
        {
            if (this->cards[j].getId() > this->cards[j + 1].getId()) //örneði 1 numaralý kartýn idsi 10 2 numaralý kartýn idsi 11 ise 1 ve 2 numaralý kartýn++
            {
                //++yeri deðiþtiriliyor.
                this->swap(&this->cards[j], &this->cards[j + 1]);

            }
        }
    }
}



void Deck::mixDeck() //destelerin karýþtýrýlmasý
{
    srand(time(NULL)); //random olmasý saðlanýyor
    for (int i = 0; i < this->cards.size(); ++i)  //kartlarýn tamamý taranýyor
    {
        int random1 = rand() % cards.size() + 1; //random 1 sayý belirleniyor
        int random2 = rand() % cards.size() + 1; //random 1 sayý daha belirleniyor
        random1 = random1 - 1; //bu random sayýdan 1 çýkarýlýyor
        random2 = random2 - 1; //bundan da 1 çýkarýlýyor
        Card temp = cards.at(random1); //geçici bir deðiþkence belirlenen sayýnýn olduðu konumdaki kart depolanýyor
        cards.at(random1) = cards.at(random2); //o kart ile diðer random kart yer deðiþtiriliyor
        cards.at(random2) = temp; // yer deðiþtiren kart temp´e aktarýlýyor.
        /*
        Sonuç olarak 15 ile 17 numaralý kartlar yer deðiþtirmiþ oldu. 1 eksiðinin alýnma sebebi ise en baþta fazladan 1 fazla almamýzdý.
        yani int random1 ve random2 de +1 eklediðimizden ötürü 1 eksiðini alýyoruz bu sayede 0 ile 100 arasýndaki tüm sayýlara hatasýz ulaþma
        imkanýna sahip oluyoruz.
        */

    }
}

Card Deck::getRandomCard() //rastgele bir kartýn çekilmesi
{
    srand(time(NULL)); //ayný sayýnýn gelmesi engellendi
    int random = rand() % cards.size() + 1; // random sayý oluþturuldu
    random = random - 1; //1 eksiltildi
    Card card = this->cards.at(random); // random sayýnýn olduðu yerdeki kart objeye atandý
    return card; //kart sisteme gönderildi
}

void Deck::moveToEnd(Card card) //kartý destenin sonuna aktarma
{
    vector<Card>::iterator it; //bir vektör tasarladýk
    it = find(this->cards.begin(), this->cards.end(), card); // bu vektöre sona gönderilecek kartý bulmasýný söyledik
    this->cards.erase(it); //kartý mevcut konumundan sildik
    this->cards.push_back(card); //þimdi de onu en sona aktardýk.

}

void Deck::printDeck() //destenin tamamýnýn yazdýrýlmasý
{
    for (int i = 0; i < this->cards.size(); ++i) //destenin tamamýnýn taranmasý saðlanýyor
    {
        Card card = this->cards.at(i); //belirtilen konumdaki kart objeye atanýyor
        card.printCard(); //obje yazýdýrýlma iþlemine yollanýyor.
    }
}

void Deck::swap(Card* xp, Card* yp) //kartlarýn birbiriyle olan yerlerinin deðiþtirilmesi
{
    Card temp = *xp; //bir geçici deðiþkene 1. kart atanýyor
    *xp = *yp; //1. kart ile 2. kart deðiþtiriliyor
    *yp = temp; // 2. kart 1. kart oluyor
}

void Deck::clear() //kartlarý temizleme
{
    this->cards.clear(); //temizledik.

}

vector<Card> Deck::getCards() const //kartý gönderme iþlemi
{
    return cards;
}
