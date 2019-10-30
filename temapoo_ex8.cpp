#include<iostream>

using namespace std;

class Nod{
    public:
    char info;
    Nod *next;
};

class Coada_de_caractere{
Nod *primul,*ultimul;

    public:

    Coada_de_caractere(){primul=ultimul=NULL;}
    void isempty();
    void push(char n);
    void pop(char n);
    void concatenare();
    void afisare();
    friend Coada_de_caractere operator +(Coada_de_caractere & Q, Coada_de_caractere & W);
    friend Coada_de_caractere operator -(Coada_de_caractere & Q, Coada_de_caractere & W);
    ~Coada_de_caractere();
    Coada_de_caractere & operator = (const Coada_de_caractere & other);
    friend ostream &operator<<(ostream &output,Coada_de_caractere &p);
    friend istream &operator>>(istream &output,Coada_de_caractere &p);
};
void Coada_de_caractere::push(char n){
    Nod *temp=new Nod;
    temp->info=n;
    temp->next=NULL;

    if(primul==NULL){
        primul=ultimul=temp;
    }
    else{
        ultimul->next=temp;
        ultimul=temp;
    }
    //cout<<n<<" a fost inserat"<<endl;
}
void Coada_de_caractere::isempty(){
if (primul == NULL && ultimul==NULL) cout<<"Este goala"<<endl;
      return;}
void Coada_de_caractere::afisare(){

    if(primul==NULL){

        return;
    }
    Nod *temp=primul;

    while(temp){
        cout<<temp->info<<" ";
        temp=temp->next;
    }
    cout<<endl;
}

Coada_de_caractere operator+(Coada_de_caractere &Q, Coada_de_caractere &W){
    Coada_de_caractere rezultat;
    Nod *tmp = Q.primul;
    while(tmp != NULL){
        rezultat.push(tmp->info);
        tmp = tmp->next;
    }
    tmp = W.primul;
    while(tmp != NULL){
        rezultat.push(tmp->info);
        tmp = tmp->next;
    }
    return rezultat;
}

Coada_de_caractere operator-(Coada_de_caractere &Q, Coada_de_caractere &W){
    Coada_de_caractere rezultat;
    Nod *tmpQ, *tmpW;
    tmpQ = Q.primul;
    tmpW = W.primul;
    while(tmpQ != NULL && tmpW != NULL){
        if(tmpQ->info < tmpW->info){
            rezultat.push(tmpW->info);
        }else{
            rezultat.push(tmpQ->info);
        }
        tmpQ = tmpQ->next;
        tmpW = tmpW->next;
    }
    return rezultat;
}

Coada_de_caractere & Coada_de_caractere::operator=(const Coada_de_caractere & other){
    if(this != &other){
        this->~Coada_de_caractere();
        Nod *tmp = other.primul;
        while(tmp != nullptr){
            push(tmp->info);
            tmp = tmp->next;
        }
    }
    return *this;
}

void Coada_de_caractere :: pop(char n)
    {
    if (primul==NULL){
        return;
    }

    cout<<primul->info<<" este sters "<<endl;
    if(primul==ultimul)
        primul=ultimul=NULL;
    else
        primul=primul->next;
}

//void Coada_de_caractere::concatenare( )

//{   Coada_de_caractere Q,W,Z;


        //if(Q.primul > W.primul )Z.push('Q.primul');
                            //else Z.push('W.primul');



Coada_de_caractere ::~Coada_de_caractere()
{
    while(primul!=NULL)
    {
        Nod *temp=primul;
        primul=primul->next;
        delete temp;
    }
    ultimul=NULL;
}

ostream &operator<<(ostream &output,Coada_de_caractere &p)
{
    Nod *tmp = p.primul;
    while(tmp != NULL)
    {
        output<<tmp->info<< " ";
        tmp = tmp->next;
    }
    return output;
}
istream &operator>>(istream &input,Coada_de_caractere &p)
{
    int n;
    char f;
    input >> n;
    for(int i=1; i<=n; i++)
    {
        input>>f;
        p.push(f);
    }
    return input;
}

int main(){
    Coada_de_caractere Q,W,Z,Y;
    cin >> Q;
    cin >> W;
    Z = Q + W;
    cout << Z;
    Y = Q - W;
     //Z.concatenare();
     //Z.afisare();
    cout << endl;
    cout << Y;
    return 0;
}
