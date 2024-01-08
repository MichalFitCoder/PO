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
    int mocSilnika, int maxMomentObrotowySilnika, int rozmiarKol, string* tabDodatkoweWyposazenie){
        this->marka = marka;
        this->model = model;
        this->pojemnoscSilnika = pojemnoscSilnika;
        this-> liczbaCylindrowSilnika = liczbaCylindrowSilnika;
        this->mocSilnika = mocSilnika;
        this->maxMomentObrotowySilnika = maxMomentObrotowySilnika;
        this->rozmiarKol = rozmiarKol;
        for(int i = 0 ; i < 4 ; i++){
            this->tabDodatkoweWyposazenie[i] = tabDodatkoweWyposazenie[i];  
        }        
    };
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
        delete silnik;
        for(int i = 0 ; i < 4 ; i++){
            delete kola[i];
        }

    };
};

class FabrykaSamochodow {
    string nazwa;
    public:
    FabrykaSamochodow(string nazwa) {
        this->nazwa = nazwa;
    }
    Samochod* wyprodukujSamochod(Zamowienie* zamowienie) {
        Samochod* samochod = new Samochod(zamowienie->getMarka(), zamowienie->getModel(), zamowienie->getPojemnoscSilnika(),
            zamowienie->getLiczbaCylindrowSylnika(), zamowienie->getMocSilnika(), zamowienie->getMaxMomentObrotowy(),
            zamowienie->getRozmiarKol());
        doposazWyprodukowaneAuto(samochod,zamowienie);
        return samochod;
    }
        
    void doposazWyprodukowaneAuto(Samochod* samochod, Zamowienie* zamowienie){
        for(int i = 0 ; i < 4 ; i++){
            DodatkoweWyposazenie* d = new DodatkoweWyposazenie(zamowienie->tabDodatkoweWyposazenie[i]);
            samochod->dodajWyposazenie(d);
        }
    }
};

void Samochod::wyswietlSpecifikacje() {
    cout << "Specyfikacje samochodu:\n";
    cout << "Marka: " << marka << "\n";
    cout << "Model: " << model << "\n";
    cout << "Pojemnosc silnika: " << silnik->getPojemnosc() << " litra\n";
    cout << "Liczba cylindrow: " << silnik->getLiczbaCylindrow() << "\n";
    cout << "Moc silnika: " << silnik->getMoc() << " KM\n";
    cout << "Max moment obrotowy: " << silnik->getMaxMomentObrotowy() << " Nm\n";
    cout << "Rozmiar kol: " << kola[0]->getRozmiar() << " cali\n";

    cout << "Dodatkowe wyposazenie:\n";
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
            cout << "Dodano wyposazenie: " << wyposazenie->getNazwa() << "\n";
            return;
        }
    }
    cout << "Nie mozna dodac wiecej wyposazenia, limit: 4\n";
}

int main() {

    string dodatkoweWyposazenieTab[4] = { "Radio", "Klimatyzacja", "Nawigacja", "Podgrzewane fotele" };
    Zamowienie zamowienie("Toyota", "Camry", 2.5, 4, 200, 300, 17, dodatkoweWyposazenieTab);


    FabrykaSamochodow fabryka("Fabryka Toyota");


    Samochod* samochod = fabryka.wyprodukujSamochod(&zamowienie);


    samochod->wyswietlSpecifikacje();

    DodatkoweWyposazenie* dodatkoweWyposazenie = new DodatkoweWyposazenie("System audio premium");
    samochod->dodajWyposazenie(dodatkoweWyposazenie);

    samochod->wyswietlSpecifikacje();

    delete samochod;
    delete dodatkoweWyposazenie;

    return 0;
}