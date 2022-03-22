#include "hand.h"


void Hand::alignSerial() //seri dizim
{
    vector<Card> cardList = this->getCards(); //kartları çekerek bunu bir vektöre atıyoruz
    this->serialAlignedHand.clear(); //önceki kısımdan kaldıysa seri dizim elimizi temizliyoruz
    this->dualAlignedHand.clear(); //önceden kaldıysa diye çifte gidimi temizliyoruz
    this->otherCardHand.clear(); // önceden kaldıysa diye depo edilen vektörümüzü temizliyoruz

    for (int i = 0; i < cardList.size(); ++i) //elimizdeki kartları aramaya başlıyoruz
    {
        Card card = cardList.at(i); //her bir kartı card objesine atıyoruz
        Deck deck; //deck objesi oluşturduk
        deck.addCardToBack(card); //deck´e i. kartı ekliyoruz
        for (int j = 0; j < cardList.size(); ++j) //bir kez daha tarama döngüsüne giriyoruz
        {
            if (j != i) //i ve j´nin eşit olmadığı anları tarıyoruz
            {
                Card secondCard = cardList.at(j); //ikinci bir obje oluşturup buna da diğer kartları ekleyeceğiz
                bool isAddThisCard = true; // bu kart eklenecek mi´yi evet yapıyoruz
                for (int k = 0; k < deck.getCards().size(); ++k)  //bu sefer deck miktarınca bir tarama yapıyoruz
                {
                    if (deck.getCards().at(k).getCardNumber() != secondCard.getCardNumber() ||
                        deck.getCards().at(k).getCardType() == secondCard.getCardType()) {
/*Eğer 2. for döngüsünden önce eklediğimiz kartların içerisindeki "k." kartın numarası ile ikinci objeye eklenen kartlar aynı değil ise veya
bu kartların tipleri aynı değil ise kartın eklenmeyeceğini sisteme bildirmek için isAddThisCard´ı  false yapıyoruz*/
                        isAddThisCard = false;
                    }
                }
                if (isAddThisCard && !hasOtherSerialDeckList(
                        secondCard)) // eğer kart eklenecekse ve belirtilen kart daha önce eklenmemiş ise++
                {
                    deck.addCardToBack(secondCard); //kartı ekliyoruz
                }
            }
        }
        if (deck.getCards().size() >= 3)  //eğer deck objesindeki kartların boyutu 3 veya daha fazla ise
        {
            serialAlignedHand.push_back(deck); //vektörümüze bunu aktarıyoruz.
        }
    }

    for (int i = 0; i < cardList.size(); ++i)  //tekrardan kartları aratıyoruz
    {
        Card card = cardList.at(i); //i. kartı objeye atadık
        if (this->hasOtherSerialDeckList(card))  //eğer hasOtherSerialDeckList´te ilgili kart var ise
        {
            continue; //devam ediyoruz
        }
        Deck deck; //yeni bir obje oluşturuyoruz
        deck.addCardToBack(card); //bu objeye az önceki kartımızı atıyoruz
        for (int j = 0; j < cardList.size(); ++j) //kartları taramaya başlıyoruz
        {
            if (j != i) //i ve j´nin aynı olmadığı bir anda
            {
                Card secondCard = cardList.at(j); // ikinci bir kartı alıp onu 2.kart olarak atıyoruz
                if (hasOtherSerialDeckList(secondCard))  //eğer bu kart zaten var ise
                {
                    continue; //devam et
                }
                Card firstCard = deck.getCards().at(0); //ilk kartı bir objeye atıyoruz
                Card lastCard = deck.getCards().at(deck.getCards().size() - 1); //son kartı da bir objeye atıyoruz
                if (secondCard.getCardType() == firstCard.getCardType() &&
                    firstCard.getCardNumber() - secondCard.getCardNumber() == 1) {
/*Eğer ikinci kartın tipi ile birinci kartın tiği aynı ve yine ikisinin numaralarının farkı 1 ise (ardışık iseler) bu kartı deckin başına aktar */
                    deck.addCardToFront(secondCard);
                } else if (secondCard.getCardType() == lastCard.getCardType() &&
                           secondCard.getCardNumber() - lastCard.getCardNumber() == 1) {
/*Eğer ikinci kartın tipi ile sonuncu kartın tiği aynı ve yine ikisinin numaralarının farkı 1 ise (ardışık iseler) bu kartı deckin sonuna aktar */
                    deck.addCardToBack(secondCard);
                }
            }
        }

        if (deck.getCards().size() >= 3) //yine 3leme veya fazlası olduysa bunu seri dizi olarak yolla
        {
            serialAlignedHand.push_back(deck);
        }
    }

    for (int i = 0; i < cardList.size(); ++i) //taratma başlıyoruz
    {
        Card card = cardList.at(i); //i. kartı aktarıyoruz
        bool thisCardUsed = false; //kart kullanılmış mı ifadesi oluşturuyoruz
        for (int j = 0; j < serialAlignedHand.size(); ++j)  //taratmayı bu sefer seri dizim yapılmış elde yapıyoruz
        {
            Deck alignedDeck = serialAlignedHand.at(
                    j); //kontrolü yapabilmek için j. elemanı farklı bir objeye aktarıyoruz
            for (int k = 0;
                 k < alignedDeck.getCards().size(); ++k) //deckimizdeki kartların boyutunca aratma başlatıyoruz
            {
                Card alignedCard = alignedDeck.getCards().at(k); //deckimizdeki k. kartı farklı bir objeye aktarıyoruz
                if (alignedCard.getId() == card.getId())  //eğer bu 2 objenin idleri birbirini tutuyor ise
                {
                    thisCardUsed = true; //kart kullanılmış demektir
                    break; //döngüyü kırıyoruz
                }
            }
            if (thisCardUsed) //eğer kart kullanılmışsa
            {
                break; //döngüyü kırıyoruz
            }

        }
        if (!thisCardUsed) //eğer kart kullanılmamış ise
        {
            this->otherCardHand.addCardToBack(card); //kartı otherCardHand´de en arkaya ekliyoruz
        }

    }
}

void Hand::alignDual() //çifte gidim
{
    vector<Card> cardList = this->getCards(); //kartlarımızı alıp bunu cardList adındaki bir vektöre atıyoruz
    this->serialAlignedHand.clear(); //temizlik
    this->dualAlignedHand.clear(); //temizlik
    this->otherCardHand.clear(); //temizlik

    for (int i = 0; i < cardList.size(); ++i)  //listeyi taramaya başlıyoruz
    {
        Card card = cardList.at(i); //geçici objeye kartı atama
        Deck deck; //geçici deck
        deck.addCardToBack(card); //kartı bu decke atıyoruz
        for (int j = 0; j < cardList.size(); ++j)  //tekrardan tarama
        {
            if (j != i) //aynı olmadıkları anı bul
            {
                Card secondCard = cardList.at(j); //diğer kartı 2. geçici değişkene ata
                bool isAddThisCard = false; //kart eklenmeyecek default olarak
                for (int k = 0; k < deck.getCards().size(); ++k) //kart eklenmiş deck miktarınca tarama
                {
                    if (deck.getCards().at(k).getCardNumber() == secondCard.getCardNumber() &&
                        deck.getCards().at(k).getCardType() == secondCard.getCardType()) {
/*Eğer geçici deckteki k. kartın numarası ile 2. kartın numarası ve bunların tipleri uyuşuyor ise*/
                        isAddThisCard = true; //kartın ekleneceğini sisteme bildir
                    }
                }
                if (isAddThisCard && !hasOtherDualDeckList(secondCard)) //eğer bu kart daha önce eklenmemiş ise
                {
                    deck.addCardToBack(secondCard); //sona ekle
                }
            }
        }
        if (deck.getCards().size() == 2) //eğer kart miktarı 2 olduysa
        {
            dualAlignedHand.push_back(deck); //çifte gidim eline ekle
        }
    }

    for (int i = 0; i < cardList.size(); ++i) //tekrar bir tarama yap
    {
        Card card = cardList.at(i);  //geçici obje
        bool thisCardUsed = false; //kart kullanılmış mı
        for (int j = 0; j < dualAlignedHand.size(); ++j) //tekrar tara
        {
            Deck alignedDeck = dualAlignedHand.at(j); //2. geçici objeye ata
            for (int k = 0; k < alignedDeck.getCards().size(); ++k) //tarama
            {
                Card alignedCard = alignedDeck.getCards().at(k); //3. geçici objeye atama
                if (alignedCard.getId() == card.getId())  // eğer kart uyuşuyor ise
                {
                    thisCardUsed = true; //kart kullanılmış demektir
                    break; //döngüyü kır
                }
            }
            if (thisCardUsed) //kart kullanılmış mı
            {
                break; //o zaman kır gitsin
            }

        }
        if (!thisCardUsed) //eğer kullanılmadıysa
        {
            this->otherCardHand.addCardToBack(card); //kartı sona ekle
        }

    }

}

const vector<Deck> &Hand::getSerialAlignedHand() const {
    return serialAlignedHand; //seri dizim yapılmış decki gönder
}

const vector<Deck> &Hand::getDualAlignedHand() const {
    return dualAlignedHand;
}

bool Hand::hasOtherSerialDeckList(Card card)
{
    for (int i = 0; i < this->serialAlignedHand.size(); ++i) // tarama
    {
        Deck deck = this->serialAlignedHand.at(i); //geçici objeye kart atama
        for (int j = 0; j < deck.getCards().size(); ++j)  //yine tarama
        {
            Card c = deck.getCards().at(j); //geçici farklı objeye kart atama
            if (c.getId() == card.getId())return true; //eğer birbirlerine eşit ise true değerini döndür
        }
    }
    return false; //değilse false değerini döndür.
}

bool Hand::hasOtherDualDeckList(Card card)
{
    for (int i = 0; i < this->dualAlignedHand.size(); ++i) //tara
    {
        Deck deck = this->dualAlignedHand.at(i); //geçici objeye ata
        for (int j = 0; j < deck.getCards().size(); ++j) //tara
        {
            Card c = deck.getCards().at(j); //geçici objeye ata
            if (c.getId() == card.getId())return true; //birbirlerine eşit iseler true döndür
        }
    }
    return false; //değillerse false döndür.
}

void Hand::setIsSerialHand(bool serialHand) //elin seri olup olmadığını belirleme
{
    Hand::isSerialHand = serialHand; //çağrılırsa elin seri olduğunu sisteme bildir
}

void Hand::printSerialHand() //seri dizim decki yazdırma
{
    cout << line << endl; // "--"ler
    for (int i = 0; i < this->serialAlignedHand.size(); ++i) //tara
    {
        Deck deck = this->serialAlignedHand.at(i); //geçici değişkene seri dizim decki ver
        deck.printDeck(); // decki yazdırma fonksiyonuna yolla
        cout << "     "; // araya boşluk bıraktır
    }
    this->otherCardHand.printDeck(); //diğer eli bastırt
    cout << endl; //alt satıra geç

}

void Hand::printDualHand() //çifte gidim yazdırılması
{
    cout << line << endl; //"--"ler
    for (int i = 0; i < this->dualAlignedHand.size(); ++i) //taramayı başlat
    {
        Deck deck = this->dualAlignedHand.at(i); //atamayı yap
        deck.printDeck(); //yazdırmaya yolla
        cout << "     "; //boşluk bırak
    }
    this->otherCardHand.printDeck(); //diğer eli yazdır
    cout << endl; //alt satıra geç

}

void Hand::printHand() //eli yazdırma
{
    if (this->isSerial()) //seri mi değil mi bak
    {
        this->printSerialHand(); //seri ise seri yazdırt
    } else {
        this->printDualHand(); //değilse çifte yazdırt
    }

}

const Deck &Hand::getOtherCardHand() const //diğer kart elini döndürür
{
    return otherCardHand;
}

bool Hand::getIsDrawCard() const //kart çekip çekmediğini döndürür
{
    return isDrawCard;
}

void Hand::setIsDrawCard(bool isDraw)  //çektiyse çekmiş olarak sisteme bildirme
{
    this->isDrawCard = isDraw;
}

void Hand::clearSerialHand() {
    this->serialAlignedHand.clear();

}

void Hand::clearDualHand() {
    this->dualAlignedHand.clear();

}

bool Hand::isCardHandleFunc() const {
    return isCardHandle;
}

void Hand::setIsCardHandle(bool isCardHandle) {
    Hand::isCardHandle = isCardHandle;
}

