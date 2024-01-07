#include <iostream>

using namespace std;

class ProduktPapierniczy {
protected:
    string rodzaj;
    string nazwa;
    double cena;

public:
    string getRodzaj() { return rodzaj; }
    string getNazwa() { return nazwa; }
    double getCena() { return cena; }
};

class SklepPapierniczy {
    friend class Zaopatrzeniowiec;
    ProduktPapierniczy* produktyNaStanie[1600];
    int aktualnaLiczbaProduktow;

public:
    void dodajNaStan(ProduktPapierniczy* produkt) {
        produktyNaStanie[aktualnaLiczbaProduktow++] = produkt;
    };

    void zdejmijZeStanu(ProduktPapierniczy* produkt) {
        for (int i = 0; i < aktualnaLiczbaProduktow; i++) {
            if (produktyNaStanie[i] == produkt) {
                // Shift the remaining products to fill the gap
                for (int j = i; j < aktualnaLiczbaProduktow - 1; j++) {
                    produktyNaStanie[j] = produktyNaStanie[j + 1];
                }
                produktyNaStanie[aktualnaLiczbaProduktow - 1] = nullptr;
                aktualnaLiczbaProduktow--;
                break;
            }
        }
    };

    ProduktPapierniczy* znajdzProdukt(string rodzaj, string nazwa) {
        for (int i = 0; i < this->aktualnaLiczbaProduktow; i++) {
            if (this->produktyNaStanie[i]->getRodzaj() == rodzaj && this->produktyNaStanie[i]->getNazwa() == nazwa) {
                return this->produktyNaStanie[i];
            }
        }
        return nullptr;
    };

    void wyswietlProdukty() {
        if (this->aktualnaLiczbaProduktow == 0) {
            cout << "Brak produktow do wyswietlenia\n ";
            return;
        }
        for (int i = 0; i < this->aktualnaLiczbaProduktow; i++) {
            cout << i << ": Nazwa: " << produktyNaStanie[i]->getNazwa() << " Rodzaj: " << this->produktyNaStanie[i]->getRodzaj() <<
                " Cena: " << this->produktyNaStanie[i]->getCena() << endl;
        }
    };

    SklepPapierniczy() {
        aktualnaLiczbaProduktow = 0;
        for (int i = 0; i < 1600; i++) {
            produktyNaStanie[i] = nullptr;
        }
    };
};

class Pracownik {
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

    Pracownik(string imie, string nazwisko, SklepPapierniczy* sklep = NULL) {
        this->imie = imie;
        this->nazwisko = nazwisko;
        this->sklep = sklep;
    }
};

class Koperta : public ProduktPapierniczy {
    string format;

public:
    Koperta(string rodzaj, string nazwa, double cena, string format) {
        this->rodzaj = rodzaj;
        this->nazwa = nazwa;
        this->cena = cena;
        this->format = format;
    }
};

class Zeszyt : public ProduktPapierniczy {
    int liczbaStron;

public:
    Zeszyt(string rodzaj, string nazwa, double cena, int liczbaStron){
        this->rodzaj = rodzaj;
        this->nazwa = nazwa;
        this->cena = cena;
        this->liczbaStron = liczbaStron;
    }
};

class Kredki : public ProduktPapierniczy {
    int liczbaSztuk;
    bool czyDrewniane;

public:
    Kredki(string rodzaj, string nazwa, double cena, int liczbaSztuk, bool czyDrewniane){
        this->rodzaj = rodzaj;
        this->nazwa = nazwa;
        this->cena = cena;
        this->liczbaSztuk = liczbaSztuk;
        this->czyDrewniane = czyDrewniane;
    }
};

class Sprzedawca : public Pracownik {
    public:
    void sprzedajProdukt(string rodzaj, string nazwa);
    Sprzedawca(string imie, string nazwisko, SklepPapierniczy* sklep = NULL) : Pracownik(imie, nazwisko, sklep){}
};

class Zaopatrzeniowiec : public Pracownik {
    ProduktPapierniczy* produktyNaPace[200];
    int aktualnaLiczbaProduktow;

public:
    void zaladujProduktNaPake(ProduktPapierniczy* produkt) {
        produktyNaPace[aktualnaLiczbaProduktow] = produkt;
        aktualnaLiczbaProduktow++;
    };

    void dostarczWszystkieProduktyNaSklep() {
        SklepPapierniczy* sklep = this->getSklep();
        for (; aktualnaLiczbaProduktow > 0; aktualnaLiczbaProduktow--) {
            sklep->produktyNaStanie[sklep->aktualnaLiczbaProduktow] = produktyNaPace[aktualnaLiczbaProduktow - 1];
            sklep->aktualnaLiczbaProduktow++;
        }
    };

    Zaopatrzeniowiec(string imie, string nazwisko, SklepPapierniczy* sklep)
        : Pracownik(imie, nazwisko, sklep) {
        aktualnaLiczbaProduktow = 0;
        for (int i = 0; i < 200; i++) {
            produktyNaPace[i] = nullptr;
        }
    };
};

int main() {

    SklepPapierniczy* sklep1 = new SklepPapierniczy;
    Zeszyt* zeszyt1 = new Zeszyt("A4", "Zeszyt", 5.0, 100);
    for(int i = 1 ; i < 5 ; i++){
        Kredki* kredki1 = new Kredki("Pastelowe","kredki",i,20,0);
        sklep1->dodajNaStan(kredki1);
    }
    sklep1->dodajNaStan(zeszyt1);
    sklep1->wyswietlProdukty();

    return 0;
}
