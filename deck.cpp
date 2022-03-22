#include "deck.h"


void Deck::addCardToBack(Card card) //gelen kartı en sona ekleme
{
    this->cards.push_back(card);
}

void Deck::addCardToFront(Card card) // başa kart ekleme
{
    this->cards.insert(this->cards.begin(), card);
}

void Deck::removeCard(Card card) //kart silimi
{
    vector<Card>::iterator it;
    it = find(this->cards.begin(), this->cards.end(), card); //ilgili kartın destede bulunması ve yerinin belirlenmesi
    this->cards.erase(it); //yeri belirlenen kartın silinmesi
}

void Deck::sortDeck() //destenin sıralanması
{
    int i, j;
    int n = this->cards.size(); //kartların adedi n değişkenine atandı
    for (i = 0; i < n - 1; i++) //toplam kart miktarının 1 eksiğince taranıyor
    {
        for (j = 0; j < n - i - 1; j++) //eksik miktarının 1 fazlası miktarınca taranıyor
        {
            if (this->cards[j].getId() > this->cards[j + 1].getId()) //örneği 1 numaralı kartın idsi 10 2 numaralı kartın idsi 11 ise 1 ve 2 numaralı kartın++
            {
                //++yeri değiştiriliyor.
                this->swap(&this->cards[j], &this->cards[j + 1]);

            }
        }
    }
}



void Deck::mixDeck() //destelerin karıştırılması
{
    srand(time(NULL)); //random olması sağlanıyor
    for (int i = 0; i < this->cards.size(); ++i)  //kartların tamamı taranıyor
    {
        int random1 = rand() % cards.size() + 1; //random 1 sayı belirleniyor
        int random2 = rand() % cards.size() + 1; //random 1 sayı daha belirleniyor
        random1 = random1 - 1; //bu random sayıdan 1 çıkarılıyor
        random2 = random2 - 1; //bundan da 1 çıkarılıyor
        Card temp = cards.at(random1); //geçici bir değişkence belirlenen sayının olduğu konumdaki kart depolanıyor
        cards.at(random1) = cards.at(random2); //o kart ile diğer random kart yer değiştiriliyor
        cards.at(random2) = temp; // yer değiştiren kart temp´e aktarılıyor.
/*
Sonuç olarak 15 ile 17 numaralı kartlar yer değiştirmiş oldu. 1 eksiğinin alınma sebebi ise en başta fazladan 1 fazla almamızdı.
yani int random1 ve random2 de +1 eklediğimizden ötürü 1 eksiğini alıyoruz bu sayede 0 ile 100 arasındaki tüm sayılara hatasız ulaşma
imkanına sahip oluyoruz.
*/

    }
}

Card Deck::getRandomCard() //rastgele bir kartın çekilmesi
{
    srand(time(NULL)); //aynı sayının gelmesi engellendi
    int random = rand() % cards.size() + 1; // random sayı oluşturuldu
    random = random - 1; //1 eksiltildi
    Card card = this->cards.at(random); // random sayının olduğu yerdeki kart objeye atandı
    return card; //kart sisteme gönderildi
}

void Deck::moveToEnd(Card card) //kartı destenin sonuna aktarma
{
    vector<Card>::iterator it; //bir vektör tasarladık
    it = find(this->cards.begin(), this->cards.end(), card); // bu vektöre sona gönderilecek kartı bulmasını söyledik
    this->cards.erase(it); //kartı mevcut konumundan sildik
    this->cards.push_back(card); //şimdi de onu en sona aktardık.

}

void Deck::printDeck() //destenin tamamının yazdırılması
{
    for (int i = 0; i < this->cards.size(); ++i) //destenin tamamının taranması sağlanıyor
    {
        Card card = this->cards.at(i); //belirtilen konumdaki kart objeye atanıyor
        card.printCard(); //obje yazıdırılma işlemine yollanıyor.
    }
}

void Deck::swap(Card *xp, Card *yp) //kartların birbiriyle olan yerlerinin değiştirilmesi
{
    Card temp = *xp; //bir geçici değişkene 1. kart atanıyor
    *xp = *yp; //1. kart ile 2. kart değiştiriliyor
    *yp = temp; // 2. kart 1. kart oluyor
}

void Deck::clear() //kartları temizleme
{
    this->cards.clear(); //temizledik.

}

vector<Card> Deck::getCards() const //kartı gönderme işlemi
{
    return cards;
}
