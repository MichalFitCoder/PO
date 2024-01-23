#include<iostream>

class Bankomat{
    int aktualnyPoziomGotowki;
    bool zablokowanyBankomat;
    bool uwierzytelnionyUzytkownik;
public:
    Bankomat(int poziomGotowki,bool zablokowany);
    void wlozKarte();
    void wyjmijKarte();
    void zrobWplate(int kwota);
    void zrobWyplate(int kwota);
    void odblokujBankomat();
    void zrobWrzutGotowki(int kwota);
    void stan();
    bool zwrocstan();
};

using namespace std;
int main(){

    Bankomat* b1 = new Bankomat(1000,false);
    Bankomat* b2 = new Bankomat(1000,false);
    b1->zrobWplate(1000);
    b1->wlozKarte();
    b2->wlozKarte();
    b2->zrobWyplate(1000);
    b1->zrobWplate(1000);
    cout << "Stan bankomatu 1:" << endl;
    b1->stan();
    cout << "Stan bankomatu 2:" << endl;
    b2->stan();
    delete b1;
    delete b2;
    return 0;
}

Bankomat::Bankomat(int x,bool y){
    this->aktualnyPoziomGotowki = x;
    this->zablokowanyBankomat = y;
}

void Bankomat::wlozKarte(){
    this->uwierzytelnionyUzytkownik = true;
}

void Bankomat::wyjmijKarte(){
    this->uwierzytelnionyUzytkownik = false;
}

void Bankomat::zrobWplate(int kwota){
    if(this->uwierzytelnionyUzytkownik && !this->zablokowanyBankomat){
       this->aktualnyPoziomGotowki += kwota;
    }
}

void Bankomat::zrobWyplate(int kwota){
    char x;
    if(this->uwierzytelnionyUzytkownik && !this->zablokowanyBankomat)
    {
        if(this->aktualnyPoziomGotowki > kwota) this->aktualnyPoziomGotowki -= kwota; //wystarczające środki na koncie
        else
        {  //Brak środków na koncie
            cout << "Niewystarczajacy poziom gotowki!!! Stan konta wynosi obecnie: " << this->aktualnyPoziomGotowki << endl << "Chcialbys wyplacic wszyskie swoje srodki ? Y/N" << endl;
            cin >> x;
            if(x == 'Y') {
                this->aktualnyPoziomGotowki = 0;
                this->zablokowanyBankomat = true;
            }
            else if(x == 'N') cout << "Pieniadze nie zostaly wyplacone"<< endl;
            else cout << "Podany znak jest niepoprawny, pieniadze nie zostaly wyplacone" << endl;           
        }
       
    }
}

void Bankomat::odblokujBankomat(){
    if(this->aktualnyPoziomGotowki) this->zablokowanyBankomat = false;
}

void Bankomat::zrobWrzutGotowki(int kwota){
    this->aktualnyPoziomGotowki += kwota;
}

void Bankomat::stan(){
    cout << "Aktualny stan gotowki wynosi: " << this->aktualnyPoziomGotowki << endl;
}

bool Bankomat::zwrocstan()
{
    return !this->zablokowanyBankomat;
}
