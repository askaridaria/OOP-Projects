#include <iostream>
#include <string>
#include <vector>
#include <exception>
using namespace std;

class plata
{
protected:
    string data;
    float suma;
public:
    plata();
    plata(string,float);
    plata(plata&);
    virtual ~plata();
    void set_suma(float);
    void set_data(string);
    string get_data();
    float get_suma();
    friend istream& operator >>(istream&, plata&);
    plata& operator =(plata&);
    virtual void afisare()=0;
};

plata::plata()
{  suma=0;
}

plata::plata(string s,float f)
{
    data=s;
    suma=f;
}

plata::plata(plata& p)
{
    data=p.data;
    suma=p.suma;
}

plata::~plata()
{
    data.erase();
    suma=0;
}

void plata::set_data(string s)
{
    data=s;
}

string plata::get_data()
{
    return data;
}

void plata::set_suma(float f)
{
    suma=f;
}

float plata::get_suma()
{
    return suma;
}
plata& plata::operator=(plata& p)
{
    if(this == &p)
        return *this;

    data=p.data;
    suma=p.suma;
    return *this;
}

istream& operator >>(istream& in, plata& p)
{
    cout << "data platii: " << endl;
    in >> p.data;
    cout<< "suma platita:" << endl;
    in >> p.suma;
    return in;
}
class numerar : public plata
{

public:
    numerar();
    numerar(string, float);
    numerar(numerar&);
    virtual ~numerar();

    friend istream& operator >>(istream&, numerar&);
    numerar& operator =(numerar&);

    void afisare();
};

numerar::numerar() : plata() {}
numerar::numerar(string s, float f) : plata(s,f) {}
numerar::numerar(numerar& n) : plata(n.data,n.suma) {}
numerar::~numerar() {}

istream& operator >>(istream& in, numerar& n)
{
    in >> (plata&)n;

    return in;
}

numerar& numerar::operator=(numerar& n)
{
    if(this == &n)
        return *this;

}

void numerar::afisare()
{
    cout << "plata a fost efectuata in numerar.\n";
    cout << "data la care a fost efectuata plata : " << data << endl;
    cout << "suma platita : " << suma << endl;
}

class card_de_credit : public plata
{
    string nr_card;
    string nume;
    string prenume;

public:

    card_de_credit();
    card_de_credit(string, float,string,string,string,string);
    card_de_credit(card_de_credit&);
    virtual ~card_de_credit();

    friend istream& operator >> (istream&, card_de_credit&);
    card_de_credit& operator = (card_de_credit&);

    void afisare();

};

card_de_credit::card_de_credit() : plata() {}

card_de_credit::card_de_credit(string s1, float f, string s2,string s3,string s4 ,string s5 ) : plata(s1,f)
{
    nr_card=s2;
    nume=s4;
    prenume=s5;
}

card_de_credit::card_de_credit(card_de_credit& c) : plata(c.data,c.suma)
{
    nr_card=c.nr_card;
    nume=c.nume;
    prenume=c.prenume;
}

card_de_credit::~card_de_credit()
{
    nr_card.erase();
    nume.erase();
    prenume.erase();
}

istream& operator >>(istream& in, card_de_credit& c)
{
    in >> (plata&)c;
   cout<<"numele de familie:\n";
    in >> c.nume;
    cout<<"prenumele:\n";
    in >> c.prenume;
    cout << "numarul cardului:\n";
    in >> c.nr_card;
}

card_de_credit& card_de_credit::operator=(card_de_credit& c)
{
    if(this == &c)
        return *this;

    nr_card=c.nr_card;
    nume=c.nume;
    prenume=c.prenume;
    return *this;
}

void card_de_credit::afisare()
{
    cout << "plata a fost efectuata cu cardul de credit.\n";
    cout << "data la care a fost efectuata plata : " << data << endl;
    cout << "suma platita :" << suma << endl;
    cout << "numele clientului : " << nume << endl;
    cout << "prenumele clientului : " << prenume << endl;
    cout << "numarul cardului : " << nr_card << endl;
}

class cec : public plata
{
    string nume;
    string prenume;

public:

    cec();
    cec(string, float,string,string,string);
    cec(cec&);
    virtual ~cec();

    friend istream& operator >>(istream&, cec&);
    cec& operator =(cec&);

    void afisare();

};

cec::cec() : plata() {}

cec::cec(string s1, float f ,string s3,string s4 ,string s5 ) : plata(s1,f)
{
    nume=s4;
    prenume=s5;
}

cec::cec(cec& c) : plata(c.data,c.suma)
{   nume=c.nume;
    prenume=c.prenume;
}

cec::~cec()
{  nume.erase();
    prenume.erase();
}

istream& operator >>(istream& in, cec& c)
{
    in >> (plata&)c;
    cout<<"numele de familie:\n";
    in >> c.nume;
    cout<<"prenumele:\n";
    in >> c.prenume;
    return in;
}

cec& cec::operator=(cec& c)
{  if(this == &c)
        return *this;
    nume=c.nume;
    prenume=c.prenume;
    return *this;
}

void cec::afisare()
{   cout << "plata a fost efectuata cu un cec.\n";
    cout << "data la care a fost efectuata plata : " << data << endl;
    cout << "suma platita : " << suma << endl;
    cout << "numele clientului : " << nume << endl;
    cout << "prenumele clientului : " << prenume << endl;
}

template <class unordered_map >
class gestiune
 {
protected:
    static int nr_plati;
    vector<unordered_map*> plati;
public:
     gestiune() {}
    ~gestiune()
    {
        int i;
        for(i = 0; i < plati.size(); i++)
            delete plati[i];
        nr_plati= 0;
    }
    gestiune(gestiune<unordered_map> &p)
    {
        plati=p.plati;
    }
    gestiune<unordered_map>& operator +=(unordered_map &p)
    {
        plati.push_back(&p);
        nr_plati++;
        return *this;
    }
    static int get_nr_plati ()
    {
        return nr_plati;
    }
    void afisare_plati()
    {
        int i;
         for(i = 0; i < plati.size(); i++){
          {

            if ( numerar *P=dynamic_cast<numerar*>(plati[i]))
               P->afisare();
            else if ( card_de_credit *P=dynamic_cast<card_de_credit*>(plati[i]))
               P->afisare();
            else if ( cec *P=dynamic_cast<cec*>(plati[i]))
               P->afisare();}
    }
 }
};

template <class unordered_map>
int gestiune<unordered_map>::nr_plati=0;

template <>
class gestiune<char*>
{
    int clienti;
    vector<string>nume_clienti;
    vector<string>prenume_clienti;


public:
    gestiune()
    {
        clienti = 0;
    }
    ~gestiune() {}
    gestiune(gestiune<char*> &p)
    {
        nume_clienti=p.nume_clienti;
        prenume_clienti=p.prenume_clienti;
        clienti=p.clienti;
    }
    gestiune <char*>& operator +=(string s)
    {
        nume_clienti.push_back(s);
        prenume_clienti.push_back(s);
        clienti++;
        return *this;
    }
    void afisare_clienti()
    {
        int i;
        try
        {
         if(nume_clienti.size() == 0)
            throw 0;
         cout << "numarul curent de clienti este : " << clienti << endl;
         for(i = 0; i < nume_clienti.size(); i++)
             cout << nume_clienti[i] << endl;
              cout << prenume_clienti[i] << endl;

        }
        catch(int x)
        { cout << "nu a fost inregistrat niciun client.\n";
        }
    }

};

int main()
{
    int n,out=1;
    gestiune<plata> P;
	gestiune<char*> C;

	 numerar N;
	 card_de_credit Cd;
	 cec K;

    while(out==1)
    {
        cout << "Meniu : \n";
        cout << " 1 -plata numerar.\n";
        cout << " 2- plata card de credit. \n";
        cout << " 3- plata in cec. \n";
        cout << " 4- inregistrare date . \n";
        cout << " 5- exit.\n";

        cin >> n;
        switch(n)
        {
            case 1 :{
                     cin >> N;
                     P += N;
                     break;
                    }
            case 2 :{
                     cin >> Cd;
                     P += Cd;
                     break;
                    }
            case 3 :{
                     cin >> K;
                     P += K;
                     break;
                    }
         case 4 :{
                     string s;
                     cin >> s;
                     C += s;
                     break;
                    }

            case 5 :{
                     out=0;
                     break;
                    }


        }
    }

    cout << "\nnumarul total de plati efectuate : ";
	cout << P.get_nr_plati() << endl;

	P.afisare_plati();
	C.afisare_clienti();
    return 0;

}
