#include <iostream>

using namespace std;

class DodatkoweWyposazenie;
class Kolo;
class Silnik;
class Zamowienie;
class Samochod; 

class Kolo {
    int rozmiar;
public:
    Kolo(int rozmiar) {
        this->rozmiar = rozmiar;
    }
    int getRozmiar() { return rozmiar; }
    ~Kolo() {
        cout << "Zniszczono kolo\n";
    };
};


class Silnik {
    double pojemnosc;
    int liczbaCylindrow;
    int moc;
    int maxMomentObrotowy;
public:
    Silnik(double pojemnosc, int liczbaCylindrow, int moc, int maxMoment) {
        this->pojemnosc = pojemnosc;
        this->liczbaCylindrow = liczbaCylindrow;
        this->moc = moc;
        this->maxMomentObrotowy = maxMoment;
    }
    double getPojemnosc() { return pojemnosc; }
    int getLiczbaCylindrow() { return liczbaCylindrow; }
    int getMoc() { return moc; }
    int getMaxMomentObrotowy() { return maxMomentObrotowy; }
};

class Zamowienie {
    string marka;
    string model;
    double pojemnoscSilnika;
    int liczbaCylindrowSilnika;
    int mocSilnika;
    int maxMomentObrotowySilnika;
    int rozmiarKol;
public:
    string tabDodatkoweWyposazenie[4];
    Zamowienie(string marka, string model, double pojemnoscSilnika, int liczbaCylindrowSilnika,
                int mocSilnika, int maxMomentObrotowySilnika, int rozmiarKol, string* tabDodatkoweWyposazenie);
    string getMarka() { return marka; }
    string getModel() { return model; }
    double getPojemnoscSilnika() { return pojemnoscSilnika; }
    int getLiczbaCylindrowSylnika() { return liczbaCylindrowSilnika; }
    int getMocSilnika() { return mocSilnika; }
    int getMaxMomentObrotowy() { return maxMomentObrotowySilnika; }
    int getRozmiarKol() { return rozmiarKol; }
};

class DodatkoweWyposazenie {
    string nazwa;
public:
    DodatkoweWyposazenie(string nazwa) {
        this->nazwa = nazwa;
    }
    string getNazwa() { return nazwa; }
};

class Samochod {
    friend class FabrykaSamochodow;
    string marka;
    string model;
    Silnik* silnik;
    Kolo* kola[4];
    DodatkoweWyposazenie* dodatkoweWyposazenie[4];
    
    Samochod(string marka, string model, double pojemnoscSilnika, int liczbaCylindrowSilnika, int mocSilnika,
        int maxMomentObrotowySilnika, int rozmiarKol) 
        : marka(marka), model(model), silnik(new Silnik(pojemnoscSilnika, liczbaCylindrowSilnika, mocSilnika, maxMomentObrotowySilnika)) {
        
        for (int i = 0; i < 4; ++i) {
            kola[i] = new Kolo(rozmiarKol);
            dodatkoweWyposazenie[i] = nullptr;
        }
    }
public:
    void wyswietlSpecifikacje();
    static Samochod* wyprodukujSamochod(Zamowienie* zamowienie);
    void dodajWyposazenie(DodatkoweWyposazenie* wyposazenie);
    ~Samochod() {
        cout << "Zniszczono samochod\n";
    };
};

class FabrykaSamochodow {
    string nazwa;
    public:
    FabrykaSamochodow(string nazwa) {
        this->nazwa = nazwa;
    }
    Samochod* wyprodukujSamochod(Zamowienie* zamowienie) {
        return new Samochod(zamowienie->getMarka(), zamowienie->getModel(), zamowienie->getPojemnoscSilnika(),
            zamowienie->getLiczbaCylindrowSylnika(), zamowienie->getMocSilnika(), zamowienie->getMaxMomentObrotowy(),
            zamowienie->getRozmiarKol());
    }
};

void Samochod::wyswietlSpecifikacje() {
    cout << "Specyfikacje samochodu:\n";
    cout << "Marka: " << marka << "\n";
    cout << "Model: " << model << "\n";
    cout << "Pojemność silnika: " << silnik->getPojemnosc() << " litra\n";
    cout << "Liczba cylindrów: " << silnik->getLiczbaCylindrow() << "\n";
    cout << "Moc silnika: " << silnik->getMoc() << " KM\n";
    cout << "Max moment obrotowy: " << silnik->getMaxMomentObrotowy() << " Nm\n";
    cout << "Rozmiar kół: " << kola[0]->getRozmiar() << " cali\n";

    cout << "Dodatkowe wyposażenie:\n";
    for (int i = 0; i < 4; ++i) {
        if (dodatkoweWyposazenie[i] != nullptr) {
            cout << " - " << dodatkoweWyposazenie[i]->getNazwa() << "\n";
        }
    }
}

void Samochod::dodajWyposazenie(DodatkoweWyposazenie* wyposazenie) {
    for (int i = 0; i < 4; ++i) {
        if (dodatkoweWyposazenie[i] == nullptr) {
            dodatkoweWyposazenie[i] = wyposazenie;
            cout << "Dodano wyposażenie: " << wyposazenie->getNazwa() << "\n";
            return;
        }
    }
    cout << "Nie można dodać więcej wyposażenia, limit: 4\n";
}

int main(){


    return 0;
}
