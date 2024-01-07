#include <iostream>

using namespace std;

class ProduktPapierniczy{
    protected:
    string rodzaj;
    string nazwa;
    double cena;
    public:
    
    string getRodzaj(){return rodzaj;}
    string getNazwa(){return nazwa;}
    double getCena(){return cena;}
};

class SklepPapierniczy{
    friend class Zaopatrzeniowiec;
    ProduktPapierniczy* produktyNaStanie[1600];
    int aktualnaLiczbaProduktow;
    public:
    void dodajNaStan(ProduktPapierniczy* produkt){
        produktyNaStanie[aktualnaLiczbaProduktow++] = produkt;
    };
    void zdejmijZeStanu(ProduktPapierniczy* produkt){
        for(int i = 0 ; i < aktualnaLiczbaProduktow ; i ++){
            if(produktyNaStanie[i] == produkt){
                produktyNaStanie[i] = nullptr;
                aktualnaLiczbaProduktow--;
            }
        }
    };
    ProduktPapierniczy* znajdzProdukt(string rodzaj, string nazwa){
        for(int i = 0 ; i < this->aktualnaLiczbaProduktow ; i++ ){
            if(this->produktyNaStanie[i]->getRodzaj() == rodzaj && this->produktyNaStanie[i]->getNazwa() == nazwa){
                return this->produktyNaStanie[i];
            }
        }
    };
    void wyswietlProdukty(){
        if(this->aktualnaLiczbaProduktow == 0){
            cout << "Brak produktow do wyswietlenia\n ";
            return;
        }
        for(int i = 0 ; i < this->aktualnaLiczbaProduktow; i++){
            cout << i << ": Nazwa: " <<  produktyNaStanie[i]->getNazwa() << " Rodzaj: " << this->produktyNaStanie[i]->getRodzaj() << 
            " Cena: " << this->produktyNaStanie[i]->getCena() << endl;
        }
    };
    SklepPapierniczy(){
        aktualnaLiczbaProduktow = 0;
        for(int i = 0 ; i < 1600 ; i++){
            produktyNaStanie[i] = nullptr;
        }
    };
};

class Pracownik{
    string imie;
    string nazwisko; 
    SklepPapierniczy* sklep;
    public:
    string getImie(){return imie;};
    string getNazwisko(){return nazwisko;}
    SklepPapierniczy* getSklep(){return sklep;}
    void setSklep(SklepPapierniczy* sklep){
        this->sklep = sklep;
    };
    Pracownik(string imie, string nazwisko, SklepPapierniczy* sklep = NULL){
        this->imie = imie;
        this->nazwisko = nazwisko;
        this->sklep = sklep;
    }
};

class Koperta : public ProduktPapierniczy{
    string format;
    public:
    string getRodzaj(){return rodzaj;}
    string getNazwa(){return nazwa;}
    double getCena(){return cena;}
    string getFormat(){return format;}
    Koperta(string rodzaj,string nazwa, double cena, string format){
        this->rodzaj = rodzaj;
        this->nazwa = nazwa;
        this->cena = cena;
        this->format = format;
    }
};

class Zeszyt : public ProduktPapierniczy{
    int liczbaStron;
    public:
    string getRodzaj(){return rodzaj;}
    string getNazwa(){return nazwa;}
    double getCena(){return cena;}
    int getLiczbaStron(){return liczbaStron;}
    Zeszyt(string rodzaj, string nazwa, double cena, int liczbaStron){
        this->rodzaj = rodzaj;
        this->nazwa = nazwa;
        this->cena = cena;
        this->liczbaStron = liczbaStron;
    }
};

class Kredki : public ProduktPapierniczy{
    int liczbaSztuk;
    bool czyDrewniane;
    public:
    string getRodzaj(){return rodzaj;}
    string getNazwa(){return nazwa;}
    double getCena(){return cena;}
    int getLiczbaStron(){return liczbaSztuk;}
    bool getCzyDrewniane(){return czyDrewniane;}
    Kredki(string rodzaj, string nazwa, double cena, int liczbaSztuk, bool czyDrewniane){
        this->rodzaj = rodzaj;
        this->nazwa = nazwa;
        this->cena = cena;
        this->liczbaSztuk = liczbaSztuk;
        this->czyDrewniane = czyDrewniane;
    }
};

class Sprzedawca : public Pracownik{
    public:
    void sprzedajProdukt(string rodzaj, string nazwa);
    Sprzedawca(string imie, string nazwisko, SklepPapierniczy* sklep = NULL) : Pracownik(imie, nazwisko, sklep){}
};

class Zaopatrzeniowiec : public Pracownik{
    ProduktPapierniczy* produktyNaPace[200];
    int aktualnaLiczbaProduktow;
    public:
    void zaladujProduktNaPake(ProduktPapierniczy* produkt){
        produktyNaPace[aktualnaLiczbaProduktow] = produkt;
        aktualnaLiczbaProduktow++;
    };
    void dostarczWszystkieProduktyNaSklep(){
        SklepPapierniczy* sklep = this->getSklep();
        for( ; aktualnaLiczbaProduktow > 0 ; aktualnaLiczbaProduktow--){
            sklep->produktyNaStanie[sklep->aktualnaLiczbaProduktow] = produktyNaPace[aktualnaLiczbaProduktow];
            sklep->aktualnaLiczbaProduktow--;
            
        }
    };
    Zaopatrzeniowiec(string imie, string nazwisko, SklepPapierniczy* sklep) : Pracownik(imie, nazwisko, sklep){
        aktualnaLiczbaProduktow = 0;
        for(int i = 0 ; i < 200 ; i++){
            produktyNaPace[i] = nullptr;
        }
    };
};

int main(){
    SklepPapierniczy* sklep1 = new SklepPapierniczy;
    //Zeszyt* zeszyt1 = new Zeszyt;
    //sklep1->dodajNaStan(zeszyt1);
    sklep1->wyswietlProdukty();



    return 0;
}