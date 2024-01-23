#include <iostream>

using namespace std;

class Silnik;

class Samochod{
    string marka;
    string model;
    bool czyPrzykreconeKola;
    Silnik* silnik;
public:
    friend void fn_zamontuj_silnik_w_samochodzie(Silnik *silnik, Samochod *samochod);
    Samochod(string mar = "Ford", string mod = "Mustang", bool czyPrzykreconeKola = false, Silnik* sil = NULL){
        this->marka = mar;
        this->model = mod;
        this->czyPrzykreconeKola = czyPrzykreconeKola;
        this->silnik = sil;
    }

    friend class Mechanik;
};

class Silnik{
    string nazwa;
    string VIN;
    double maxPojemnoscOleju;
    double aktPojrmnoscOleju;
    Samochod* samochod;
public:
    friend void fn_zamontuj_silnik_w_samochodzie(Silnik *silnik, Samochod *samochod);
    Silnik(string nazwa = "Beznazwy",string VIN = "b.d" , double maxPojOleju = 6.2, double aktPojOleju = 2.5, Samochod* sam = NULL){
        this->nazwa = nazwa;
        this->VIN = VIN;
        this->maxPojemnoscOleju = maxPojOleju;
        this->aktPojrmnoscOleju = aktPojOleju;
        this->samochod = sam;
    }

    friend class Mechanik;
};

class Mechanik{
    string imie;
    string nazwisko;
public:
    void dolejOlejSilnikowy(Silnik* silnik,double pojemnosc);
    void przykrecKola(Samochod* Samochod);
    Mechanik(string imie,string nazwisko){
        this->imie = imie;
        this->nazwisko = nazwisko;
    }
    friend class Silnik;

};


void fn_zamontuj_silnik_w_samochodzie(Silnik* silnik, Samochod* samochod);

int main(){
    Silnik* s1 = new Silnik("Kozacki silnik");
    Samochod* sam1 = new Samochod;
    Mechanik* Mech1 = new Mechanik("Tomasz","Gaworski");
    fn_zamontuj_silnik_w_samochodzie(s1,sam1);
    Mech1->dolejOlejSilnikowy(s1,10);

    return 0;
}

void Mechanik::dolejOlejSilnikowy(Silnik *silnik, double pojemnosc){
    double wolnemiejsce = silnik->maxPojemnoscOleju - silnik->aktPojrmnoscOleju;
    if(wolnemiejsce > pojemnosc){
        silnik->aktPojrmnoscOleju += pojemnosc;
        cout << "Pomyslnie dolano oleju do silnika!\n";
    }else{
        cout << "Niestety nie ma miejsca na tyle oleju! Obecne miejsce wynosi: " << wolnemiejsce << endl;
    }
}

void Mechanik::przykrecKola(Samochod *Samochod)
{
    Samochod->czyPrzykreconeKola = true;
}

void fn_zamontuj_silnik_w_samochodzie(Silnik *silnik, Samochod *samochod)
{
    samochod->silnik = silnik;
    silnik->samochod = samochod;
    cout << "Poprawnie zamontowano silnik " << samochod->silnik->nazwa << " w samochodzie " << samochod->model << endl;
}
