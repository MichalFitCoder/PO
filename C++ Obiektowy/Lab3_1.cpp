#include <iostream>

using namespace std;

class Kierowca{
    private: 
    string identyfikator;
    bool czyMaWyznaczonyKurs;
    public:
    Kierowca(string identyfikator,bool czyMaWyznaczonyKurs){
        this->identyfikator = identyfikator;
    };

};

class TIR{
    private:
    string marka;
    string nrRejestracyjny;
    Kierowca* kierowca;
    public:
    TIR(string mar,string nrRej,Kierowca* kier){
        this->marka = mar;
        this->nrRejestracyjny = nrRej;
        this->kierowca = kier;
    };
};

class Naczepa{
    private:
    string nrRejestracyjny;
    TIR* podczepionyTIR;
    public:
    Naczepa(string nrRej,TIR* podczepionyTIR){
        this->nrRejestracyjny = nrRej;
        this->podczepionyTIR = podczepionyTIR;
    };

};

int main(){



}