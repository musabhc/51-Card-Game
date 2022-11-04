#include "hand.h"


void Hand::alignSerial() //seri dizim
{
    vector<Card> cardList = this->getCards(); //kartlar� �ekerek bunu bir vekt�re at�yoruz
    this->serialAlignedHand.clear(); //�nceki k�s�mdan kald�ysa seri dizim elimizi temizliyoruz
    this->dualAlignedHand.clear(); //�nceden kald�ysa diye �ifte gidimi temizliyoruz
    this->otherCardHand.clear(); // �nceden kald�ysa diye depo edilen vekt�r�m�z� temizliyoruz

    for (int i = 0; i < cardList.size(); ++i) //elimizdeki kartlar� aramaya ba�l�yoruz
    {
        Card card = cardList.at(i); //her bir kart� card objesine at�yoruz
        Deck deck; //deck objesi olu�turduk
        deck.addCardToBack(card); //deck�e i. kart� ekliyoruz
        for (int j = 0; j < cardList.size(); ++j) //bir kez daha tarama d�ng�s�ne giriyoruz
        {
            if (j != i) //i ve j�nin e�it olmad��� anlar� tar�yoruz
            {
                Card secondCard = cardList.at(j); //ikinci bir obje olu�turup buna da di�er kartlar� ekleyece�iz
                bool isAddThisCard = true; // bu kart eklenecek mi�yi evet yap�yoruz
                for (int k = 0; k < deck.getCards().size(); ++k)  //bu sefer deck miktar�nca bir tarama yap�yoruz
                {
                    if (deck.getCards().at(k).getCardNumber() != secondCard.getCardNumber() ||
                        deck.getCards().at(k).getCardType() == secondCard.getCardType()) {
                        /*E�er 2. for d�ng�s�nden �nce ekledi�imiz kartlar�n i�erisindeki "k." kart�n numaras� ile ikinci objeye eklenen kartlar ayn� de�il ise veya
                        bu kartlar�n tipleri ayn� de�il ise kart�n eklenmeyece�ini sisteme bildirmek i�in isAddThisCard��  false yap�yoruz*/
                        isAddThisCard = false;
                    }
                }
                if (isAddThisCard && !hasOtherSerialDeckList(
                    secondCard)) // e�er kart eklenecekse ve belirtilen kart daha �nce eklenmemi� ise++
                {
                    deck.addCardToBack(secondCard); //kart� ekliyoruz
                }
            }
        }
        if (deck.getCards().size() >= 3)  //e�er deck objesindeki kartlar�n boyutu 3 veya daha fazla ise
        {
            serialAlignedHand.push_back(deck); //vekt�r�m�ze bunu aktar�yoruz.
        }
    }

    for (int i = 0; i < cardList.size(); ++i)  //tekrardan kartlar� arat�yoruz
    {
        Card card = cardList.at(i); //i. kart� objeye atad�k
        if (this->hasOtherSerialDeckList(card))  //e�er hasOtherSerialDeckList�te ilgili kart var ise
        {
            continue; //devam ediyoruz
        }
        Deck deck; //yeni bir obje olu�turuyoruz
        deck.addCardToBack(card); //bu objeye az �nceki kart�m�z� at�yoruz
        for (int j = 0; j < cardList.size(); ++j) //kartlar� taramaya ba�l�yoruz
        {
            if (j != i) //i ve j�nin ayn� olmad��� bir anda
            {
                Card secondCard = cardList.at(j); // ikinci bir kart� al�p onu 2.kart olarak at�yoruz
                if (hasOtherSerialDeckList(secondCard))  //e�er bu kart zaten var ise
                {
                    continue; //devam et
                }
                Card firstCard = deck.getCards().at(0); //ilk kart� bir objeye at�yoruz
                Card lastCard = deck.getCards().at(deck.getCards().size() - 1); //son kart� da bir objeye at�yoruz
                if (secondCard.getCardType() == firstCard.getCardType() &&
                    firstCard.getCardNumber() - secondCard.getCardNumber() == 1) {
                    /*E�er ikinci kart�n tipi ile birinci kart�n ti�i ayn� ve yine ikisinin numaralar�n�n fark� 1 ise (ard���k iseler) bu kart� deckin ba��na aktar */
                    deck.addCardToFront(secondCard);
                }
                else if (secondCard.getCardType() == lastCard.getCardType() &&
                    secondCard.getCardNumber() - lastCard.getCardNumber() == 1) {
                    /*E�er ikinci kart�n tipi ile sonuncu kart�n ti�i ayn� ve yine ikisinin numaralar�n�n fark� 1 ise (ard���k iseler) bu kart� deckin sonuna aktar */
                    deck.addCardToBack(secondCard);
                }
            }
        }

        if (deck.getCards().size() >= 3) //yine 3leme veya fazlas� olduysa bunu seri dizi olarak yolla
        {
            serialAlignedHand.push_back(deck);
        }
    }

    for (int i = 0; i < cardList.size(); ++i) //taratma ba�l�yoruz
    {
        Card card = cardList.at(i); //i. kart� aktar�yoruz
        bool thisCardUsed = false; //kart kullan�lm�� m� ifadesi olu�turuyoruz
        for (int j = 0; j < serialAlignedHand.size(); ++j)  //taratmay� bu sefer seri dizim yap�lm�� elde yap�yoruz
        {
            Deck alignedDeck = serialAlignedHand.at(
                j); //kontrol� yapabilmek i�in j. eleman� farkl� bir objeye aktar�yoruz
            for (int k = 0;
                k < alignedDeck.getCards().size(); ++k) //deckimizdeki kartlar�n boyutunca aratma ba�lat�yoruz
            {
                Card alignedCard = alignedDeck.getCards().at(k); //deckimizdeki k. kart� farkl� bir objeye aktar�yoruz
                if (alignedCard.getId() == card.getId())  //e�er bu 2 objenin idleri birbirini tutuyor ise
                {
                    thisCardUsed = true; //kart kullan�lm�� demektir
                    break; //d�ng�y� k�r�yoruz
                }
            }
            if (thisCardUsed) //e�er kart kullan�lm��sa
            {
                break; //d�ng�y� k�r�yoruz
            }

        }
        if (!thisCardUsed) //e�er kart kullan�lmam�� ise
        {
            this->otherCardHand.addCardToBack(card); //kart� otherCardHand�de en arkaya ekliyoruz
        }

    }
}

void Hand::alignDual() //�ifte gidim
{
    vector<Card> cardList = this->getCards(); //kartlar�m�z� al�p bunu cardList ad�ndaki bir vekt�re at�yoruz
    this->serialAlignedHand.clear(); //temizlik
    this->dualAlignedHand.clear(); //temizlik
    this->otherCardHand.clear(); //temizlik

    for (int i = 0; i < cardList.size(); ++i)  //listeyi taramaya ba�l�yoruz
    {
        Card card = cardList.at(i); //ge�ici objeye kart� atama
        Deck deck; //ge�ici deck
        deck.addCardToBack(card); //kart� bu decke at�yoruz
        for (int j = 0; j < cardList.size(); ++j)  //tekrardan tarama
        {
            if (j != i) //ayn� olmad�klar� an� bul
            {
                Card secondCard = cardList.at(j); //di�er kart� 2. ge�ici de�i�kene ata
                bool isAddThisCard = false; //kart eklenmeyecek default olarak
                for (int k = 0; k < deck.getCards().size(); ++k) //kart eklenmi� deck miktar�nca tarama
                {
                    if (deck.getCards().at(k).getCardNumber() == secondCard.getCardNumber() &&
                        deck.getCards().at(k).getCardType() == secondCard.getCardType()) {
                        /*E�er ge�ici deckteki k. kart�n numaras� ile 2. kart�n numaras� ve bunlar�n tipleri uyu�uyor ise*/
                        isAddThisCard = true; //kart�n eklenece�ini sisteme bildir
                    }
                }
                if (isAddThisCard && !hasOtherDualDeckList(secondCard)) //e�er bu kart daha �nce eklenmemi� ise
                {
                    deck.addCardToBack(secondCard); //sona ekle
                }
            }
        }
        if (deck.getCards().size() == 2) //e�er kart miktar� 2 olduysa
        {
            dualAlignedHand.push_back(deck); //�ifte gidim eline ekle
        }
    }

    for (int i = 0; i < cardList.size(); ++i) //tekrar bir tarama yap
    {
        Card card = cardList.at(i);  //ge�ici obje
        bool thisCardUsed = false; //kart kullan�lm�� m�
        for (int j = 0; j < dualAlignedHand.size(); ++j) //tekrar tara
        {
            Deck alignedDeck = dualAlignedHand.at(j); //2. ge�ici objeye ata
            for (int k = 0; k < alignedDeck.getCards().size(); ++k) //tarama
            {
                Card alignedCard = alignedDeck.getCards().at(k); //3. ge�ici objeye atama
                if (alignedCard.getId() == card.getId())  // e�er kart uyu�uyor ise
                {
                    thisCardUsed = true; //kart kullan�lm�� demektir
                    break; //d�ng�y� k�r
                }
            }
            if (thisCardUsed) //kart kullan�lm�� m�
            {
                break; //o zaman k�r gitsin
            }

        }
        if (!thisCardUsed) //e�er kullan�lmad�ysa
        {
            this->otherCardHand.addCardToBack(card); //kart� sona ekle
        }

    }

}

const vector<Deck>& Hand::getSerialAlignedHand() const {
    return serialAlignedHand; //seri dizim yap�lm�� decki g�nder
}

const vector<Deck>& Hand::getDualAlignedHand() const {
    return dualAlignedHand;
}

bool Hand::hasOtherSerialDeckList(Card card)
{
    for (int i = 0; i < this->serialAlignedHand.size(); ++i) // tarama
    {
        Deck deck = this->serialAlignedHand.at(i); //ge�ici objeye kart atama
        for (int j = 0; j < deck.getCards().size(); ++j)  //yine tarama
        {
            Card c = deck.getCards().at(j); //ge�ici farkl� objeye kart atama
            if (c.getId() == card.getId())return true; //e�er birbirlerine e�it ise true de�erini d�nd�r
        }
    }
    return false; //de�ilse false de�erini d�nd�r.
}

bool Hand::hasOtherDualDeckList(Card card)
{
    for (int i = 0; i < this->dualAlignedHand.size(); ++i) //tara
    {
        Deck deck = this->dualAlignedHand.at(i); //ge�ici objeye ata
        for (int j = 0; j < deck.getCards().size(); ++j) //tara
        {
            Card c = deck.getCards().at(j); //ge�ici objeye ata
            if (c.getId() == card.getId())return true; //birbirlerine e�it iseler true d�nd�r
        }
    }
    return false; //de�illerse false d�nd�r.
}

void Hand::setIsSerialHand(bool serialHand) //elin seri olup olmad���n� belirleme
{
    Hand::isSerialHand = serialHand; //�a�r�l�rsa elin seri oldu�unu sisteme bildir
}

void Hand::printSerialHand() //seri dizim decki yazd�rma
{
    cout << line << endl; // "--"ler
    for (int i = 0; i < this->serialAlignedHand.size(); ++i) //tara
    {
        Deck deck = this->serialAlignedHand.at(i); //ge�ici de�i�kene seri dizim decki ver
        deck.printDeck(); // decki yazd�rma fonksiyonuna yolla
        cout << "     "; // araya bo�luk b�rakt�r
    }
    this->otherCardHand.printDeck(); //di�er eli bast�rt
    cout << endl; //alt sat�ra ge�

}

void Hand::printDualHand() //�ifte gidim yazd�r�lmas�
{
    cout << line << endl; //"--"ler
    for (int i = 0; i < this->dualAlignedHand.size(); ++i) //taramay� ba�lat
    {
        Deck deck = this->dualAlignedHand.at(i); //atamay� yap
        deck.printDeck(); //yazd�rmaya yolla
        cout << "     "; //bo�luk b�rak
    }
    this->otherCardHand.printDeck(); //di�er eli yazd�r
    cout << endl; //alt sat�ra ge�

}

void Hand::printHand() //eli yazd�rma
{
    if (this->isSerial()) //seri mi de�il mi bak
    {
        this->printSerialHand(); //seri ise seri yazd�rt
    }
    else {
        this->printDualHand(); //de�ilse �ifte yazd�rt
    }

}

const Deck& Hand::getOtherCardHand() const //di�er kart elini d�nd�r�r
{
    return otherCardHand;
}

bool Hand::getIsDrawCard() const //kart �ekip �ekmedi�ini d�nd�r�r
{
    return isDrawCard;
}

void Hand::setIsDrawCard(bool isDraw)  //�ektiyse �ekmi� olarak sisteme bildirme
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

