#include "hand.h"


void Hand::alignSerial() //seri dizim
{
    vector<Card> cardList = this->getCards(); //kartlarý çekerek bunu bir vektöre atýyoruz
    this->serialAlignedHand.clear(); //önceki kýsýmdan kaldýysa seri dizim elimizi temizliyoruz
    this->dualAlignedHand.clear(); //önceden kaldýysa diye çifte gidimi temizliyoruz
    this->otherCardHand.clear(); // önceden kaldýysa diye depo edilen vektörümüzü temizliyoruz

    for (int i = 0; i < cardList.size(); ++i) //elimizdeki kartlarý aramaya baþlýyoruz
    {
        Card card = cardList.at(i); //her bir kartý card objesine atýyoruz
        Deck deck; //deck objesi oluþturduk
        deck.addCardToBack(card); //deck´e i. kartý ekliyoruz
        for (int j = 0; j < cardList.size(); ++j) //bir kez daha tarama döngüsüne giriyoruz
        {
            if (j != i) //i ve j´nin eþit olmadýðý anlarý tarýyoruz
            {
                Card secondCard = cardList.at(j); //ikinci bir obje oluþturup buna da diðer kartlarý ekleyeceðiz
                bool isAddThisCard = true; // bu kart eklenecek mi´yi evet yapýyoruz
                for (int k = 0; k < deck.getCards().size(); ++k)  //bu sefer deck miktarýnca bir tarama yapýyoruz
                {
                    if (deck.getCards().at(k).getCardNumber() != secondCard.getCardNumber() ||
                        deck.getCards().at(k).getCardType() == secondCard.getCardType()) {
                        /*Eðer 2. for döngüsünden önce eklediðimiz kartlarýn içerisindeki "k." kartýn numarasý ile ikinci objeye eklenen kartlar ayný deðil ise veya
                        bu kartlarýn tipleri ayný deðil ise kartýn eklenmeyeceðini sisteme bildirmek için isAddThisCard´ý  false yapýyoruz*/
                        isAddThisCard = false;
                    }
                }
                if (isAddThisCard && !hasOtherSerialDeckList(
                    secondCard)) // eðer kart eklenecekse ve belirtilen kart daha önce eklenmemiþ ise++
                {
                    deck.addCardToBack(secondCard); //kartý ekliyoruz
                }
            }
        }
        if (deck.getCards().size() >= 3)  //eðer deck objesindeki kartlarýn boyutu 3 veya daha fazla ise
        {
            serialAlignedHand.push_back(deck); //vektörümüze bunu aktarýyoruz.
        }
    }

    for (int i = 0; i < cardList.size(); ++i)  //tekrardan kartlarý aratýyoruz
    {
        Card card = cardList.at(i); //i. kartý objeye atadýk
        if (this->hasOtherSerialDeckList(card))  //eðer hasOtherSerialDeckList´te ilgili kart var ise
        {
            continue; //devam ediyoruz
        }
        Deck deck; //yeni bir obje oluþturuyoruz
        deck.addCardToBack(card); //bu objeye az önceki kartýmýzý atýyoruz
        for (int j = 0; j < cardList.size(); ++j) //kartlarý taramaya baþlýyoruz
        {
            if (j != i) //i ve j´nin ayný olmadýðý bir anda
            {
                Card secondCard = cardList.at(j); // ikinci bir kartý alýp onu 2.kart olarak atýyoruz
                if (hasOtherSerialDeckList(secondCard))  //eðer bu kart zaten var ise
                {
                    continue; //devam et
                }
                Card firstCard = deck.getCards().at(0); //ilk kartý bir objeye atýyoruz
                Card lastCard = deck.getCards().at(deck.getCards().size() - 1); //son kartý da bir objeye atýyoruz
                if (secondCard.getCardType() == firstCard.getCardType() &&
                    firstCard.getCardNumber() - secondCard.getCardNumber() == 1) {
                    /*Eðer ikinci kartýn tipi ile birinci kartýn tiði ayný ve yine ikisinin numaralarýnýn farký 1 ise (ardýþýk iseler) bu kartý deckin baþýna aktar */
                    deck.addCardToFront(secondCard);
                }
                else if (secondCard.getCardType() == lastCard.getCardType() &&
                    secondCard.getCardNumber() - lastCard.getCardNumber() == 1) {
                    /*Eðer ikinci kartýn tipi ile sonuncu kartýn tiði ayný ve yine ikisinin numaralarýnýn farký 1 ise (ardýþýk iseler) bu kartý deckin sonuna aktar */
                    deck.addCardToBack(secondCard);
                }
            }
        }

        if (deck.getCards().size() >= 3) //yine 3leme veya fazlasý olduysa bunu seri dizi olarak yolla
        {
            serialAlignedHand.push_back(deck);
        }
    }

    for (int i = 0; i < cardList.size(); ++i) //taratma baþlýyoruz
    {
        Card card = cardList.at(i); //i. kartý aktarýyoruz
        bool thisCardUsed = false; //kart kullanýlmýþ mý ifadesi oluþturuyoruz
        for (int j = 0; j < serialAlignedHand.size(); ++j)  //taratmayý bu sefer seri dizim yapýlmýþ elde yapýyoruz
        {
            Deck alignedDeck = serialAlignedHand.at(
                j); //kontrolü yapabilmek için j. elemaný farklý bir objeye aktarýyoruz
            for (int k = 0;
                k < alignedDeck.getCards().size(); ++k) //deckimizdeki kartlarýn boyutunca aratma baþlatýyoruz
            {
                Card alignedCard = alignedDeck.getCards().at(k); //deckimizdeki k. kartý farklý bir objeye aktarýyoruz
                if (alignedCard.getId() == card.getId())  //eðer bu 2 objenin idleri birbirini tutuyor ise
                {
                    thisCardUsed = true; //kart kullanýlmýþ demektir
                    break; //döngüyü kýrýyoruz
                }
            }
            if (thisCardUsed) //eðer kart kullanýlmýþsa
            {
                break; //döngüyü kýrýyoruz
            }

        }
        if (!thisCardUsed) //eðer kart kullanýlmamýþ ise
        {
            this->otherCardHand.addCardToBack(card); //kartý otherCardHand´de en arkaya ekliyoruz
        }

    }
}

void Hand::alignDual() //çifte gidim
{
    vector<Card> cardList = this->getCards(); //kartlarýmýzý alýp bunu cardList adýndaki bir vektöre atýyoruz
    this->serialAlignedHand.clear(); //temizlik
    this->dualAlignedHand.clear(); //temizlik
    this->otherCardHand.clear(); //temizlik

    for (int i = 0; i < cardList.size(); ++i)  //listeyi taramaya baþlýyoruz
    {
        Card card = cardList.at(i); //geçici objeye kartý atama
        Deck deck; //geçici deck
        deck.addCardToBack(card); //kartý bu decke atýyoruz
        for (int j = 0; j < cardList.size(); ++j)  //tekrardan tarama
        {
            if (j != i) //ayný olmadýklarý aný bul
            {
                Card secondCard = cardList.at(j); //diðer kartý 2. geçici deðiþkene ata
                bool isAddThisCard = false; //kart eklenmeyecek default olarak
                for (int k = 0; k < deck.getCards().size(); ++k) //kart eklenmiþ deck miktarýnca tarama
                {
                    if (deck.getCards().at(k).getCardNumber() == secondCard.getCardNumber() &&
                        deck.getCards().at(k).getCardType() == secondCard.getCardType()) {
                        /*Eðer geçici deckteki k. kartýn numarasý ile 2. kartýn numarasý ve bunlarýn tipleri uyuþuyor ise*/
                        isAddThisCard = true; //kartýn ekleneceðini sisteme bildir
                    }
                }
                if (isAddThisCard && !hasOtherDualDeckList(secondCard)) //eðer bu kart daha önce eklenmemiþ ise
                {
                    deck.addCardToBack(secondCard); //sona ekle
                }
            }
        }
        if (deck.getCards().size() == 2) //eðer kart miktarý 2 olduysa
        {
            dualAlignedHand.push_back(deck); //çifte gidim eline ekle
        }
    }

    for (int i = 0; i < cardList.size(); ++i) //tekrar bir tarama yap
    {
        Card card = cardList.at(i);  //geçici obje
        bool thisCardUsed = false; //kart kullanýlmýþ mý
        for (int j = 0; j < dualAlignedHand.size(); ++j) //tekrar tara
        {
            Deck alignedDeck = dualAlignedHand.at(j); //2. geçici objeye ata
            for (int k = 0; k < alignedDeck.getCards().size(); ++k) //tarama
            {
                Card alignedCard = alignedDeck.getCards().at(k); //3. geçici objeye atama
                if (alignedCard.getId() == card.getId())  // eðer kart uyuþuyor ise
                {
                    thisCardUsed = true; //kart kullanýlmýþ demektir
                    break; //döngüyü kýr
                }
            }
            if (thisCardUsed) //kart kullanýlmýþ mý
            {
                break; //o zaman kýr gitsin
            }

        }
        if (!thisCardUsed) //eðer kullanýlmadýysa
        {
            this->otherCardHand.addCardToBack(card); //kartý sona ekle
        }

    }

}

const vector<Deck>& Hand::getSerialAlignedHand() const {
    return serialAlignedHand; //seri dizim yapýlmýþ decki gönder
}

const vector<Deck>& Hand::getDualAlignedHand() const {
    return dualAlignedHand;
}

bool Hand::hasOtherSerialDeckList(Card card)
{
    for (int i = 0; i < this->serialAlignedHand.size(); ++i) // tarama
    {
        Deck deck = this->serialAlignedHand.at(i); //geçici objeye kart atama
        for (int j = 0; j < deck.getCards().size(); ++j)  //yine tarama
        {
            Card c = deck.getCards().at(j); //geçici farklý objeye kart atama
            if (c.getId() == card.getId())return true; //eðer birbirlerine eþit ise true deðerini döndür
        }
    }
    return false; //deðilse false deðerini döndür.
}

bool Hand::hasOtherDualDeckList(Card card)
{
    for (int i = 0; i < this->dualAlignedHand.size(); ++i) //tara
    {
        Deck deck = this->dualAlignedHand.at(i); //geçici objeye ata
        for (int j = 0; j < deck.getCards().size(); ++j) //tara
        {
            Card c = deck.getCards().at(j); //geçici objeye ata
            if (c.getId() == card.getId())return true; //birbirlerine eþit iseler true döndür
        }
    }
    return false; //deðillerse false döndür.
}

void Hand::setIsSerialHand(bool serialHand) //elin seri olup olmadýðýný belirleme
{
    Hand::isSerialHand = serialHand; //çaðrýlýrsa elin seri olduðunu sisteme bildir
}

void Hand::printSerialHand() //seri dizim decki yazdýrma
{
    cout << line << endl; // "--"ler
    for (int i = 0; i < this->serialAlignedHand.size(); ++i) //tara
    {
        Deck deck = this->serialAlignedHand.at(i); //geçici deðiþkene seri dizim decki ver
        deck.printDeck(); // decki yazdýrma fonksiyonuna yolla
        cout << "     "; // araya boþluk býraktýr
    }
    this->otherCardHand.printDeck(); //diðer eli bastýrt
    cout << endl; //alt satýra geç

}

void Hand::printDualHand() //çifte gidim yazdýrýlmasý
{
    cout << line << endl; //"--"ler
    for (int i = 0; i < this->dualAlignedHand.size(); ++i) //taramayý baþlat
    {
        Deck deck = this->dualAlignedHand.at(i); //atamayý yap
        deck.printDeck(); //yazdýrmaya yolla
        cout << "     "; //boþluk býrak
    }
    this->otherCardHand.printDeck(); //diðer eli yazdýr
    cout << endl; //alt satýra geç

}

void Hand::printHand() //eli yazdýrma
{
    if (this->isSerial()) //seri mi deðil mi bak
    {
        this->printSerialHand(); //seri ise seri yazdýrt
    }
    else {
        this->printDualHand(); //deðilse çifte yazdýrt
    }

}

const Deck& Hand::getOtherCardHand() const //diðer kart elini döndürür
{
    return otherCardHand;
}

bool Hand::getIsDrawCard() const //kart çekip çekmediðini döndürür
{
    return isDrawCard;
}

void Hand::setIsDrawCard(bool isDraw)  //çektiyse çekmiþ olarak sisteme bildirme
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

