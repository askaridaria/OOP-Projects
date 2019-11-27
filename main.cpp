 #include <iostream>

using namespace std;

class Complex{

 private:
  double re,im;
  public:
  Complex(double r=0,double i=0){
   re=r;
   im=i;
  }
  Complex(const Complex& c){
    re=c.re;
    im=c.im;
  }
  ~Complex(){}
  double get_imaginar(){
    return im;
  }
  double get_real(){
    return re;
  }

  friend istream& operator>>(istream& i,Complex& c);
  friend ostream& operator<<(ostream& o,Complex& c);
  Complex& operator=(Complex& c);
  Complex& operator+(Complex& c);
  Complex& operator*(Complex& c);
  Complex& operator-(Complex& c);
  Complex& operator/(Complex& c);

};

istream& operator>>(istream& i,Complex& c){
  cout<<"Partea reala este : ";
  i>>c.re;
  cout<<"Partea imaginara este : ";
  i>>c.im;

  return i;

}

ostream& operator<<(ostream& o,Complex& c){

 o<<c.re<<"+"<<c.im<<"*i";

  return o;
}

Complex& Complex::operator=(Complex& c){

 re=c.re;
 im=c.im;

 return *this;

}

Complex& Complex::operator+(Complex& c){

 Complex *z=new Complex();
 z->re=re+c.re;
 z->im=im+c.re;

 return *z;
}

Complex& Complex::operator*(Complex& c){

 Complex *z =new Complex();
 z->re=(re*c.re)-(im*c.im);
 z->im=(re*c.im)+(im*c.re);

 return*z;
}

Complex& Complex::operator-(Complex& c){

 Complex *z=new Complex();
 z->re=re-c.re;
 z->im=im-c.im;

 return *z;
}

Complex& Complex::operator/(Complex &c){

 Complex *z=new Complex();
 z->re=((re*c.re)+(im*c.im))/((c.re*c.re)+(c.im*c.im));
 z->im=((c.re*im)-(re*c.im))/((c.re*c.re)+(c.im*c.im));

 return*z;
}


 class Matrice{
 protected:
 Complex**v;
 public:
 Matrice(int d1,int d2){
  v=new Complex*[d1]();
  int i;
  for(i=0;i<d1;i++)
   v[i]=new Complex[d2]();
 }
 Matrice(const Matrice&mat){}
 virtual int verif_diagonala()=0;
 virtual void citire(istream& f)=0;
 virtual void afisare(ostream& o)=0;
 int verif_valoare(int i,int j){
   if ((v[i][j].get_real()==0)&& (v[i][j].get_imaginar()==0))
     return 1;
    return 0;
 }
};

istream& operator>>(istream& f,Matrice& mat){
  mat.citire(f);
  return f;
}

ostream& operator<<(ostream& o,Matrice& mat){
  mat.afisare(o);
  return o;
}

class Matrice_oarecare:public Matrice{
 private:
 int lin,col;
 public:
 Matrice_oarecare(int l,int c) : lin(l),col(c),Matrice(l,c) {}
 void citire(istream& f){
  int i,j;
  for(i=0;i<lin;i++)
   for(j=0;j<col;j++){
    cout<<"Introduceti valoarea de pe linia "<<i<<" coloana "<<j<<" : "<<endl;
    f>>v[i][j];
   }
 }
void afisare(ostream& o){
  int i,j;
  o<<"Matricea este : "<<endl;
  for(i=0;i<lin;i++){
   for(j=0;j<col;j++)
    o<<v[i][j]<<" ";
    o<<endl;
  }
}
Matrice_oarecare(const Matrice_oarecare& mat) : Matrice(mat) {
  lin=mat.lin;
  col=mat.col;
  int i,j;
  v=new Complex*[mat.lin]();
    for(i=0;i<lin;i++)
     v[i]=new Complex[col]();

    for(i=0;i<lin;i++)
     for(j=0;j<col;j++)
       v[i][j]=mat.v[i][j];
}
~Matrice_oarecare(){}
Matrice_oarecare& operator=(Matrice_oarecare& mat);
int verif_diagonala();
};

Matrice_oarecare& Matrice_oarecare::operator=(Matrice_oarecare& mat){
  lin=mat.lin;
  col=mat.col;
  int i,j;
  for(i=0;i<lin;i++)
   for(j=0;j<col;j++)
     v[i][j]=mat.v[i][j];

 return *this;
}

int Matrice_oarecare::verif_diagonala(){
  int i,j;
  int ok=1;
  for(i=0;i<lin;i++)
   for(j=0;j<col;j++)
     if(verif_valoare(i,j)==0)
       if(i!=j)
         ok=0;

    return ok;
}

class Matrice_patratica:public Matrice{
 private:
 int dim;
 public:
 Matrice_patratica(int d) : dim(d),Matrice(d,d){}
 void citire(istream& f){
  int i,j;
  for(i=0;i<dim;i++)
   for(j=0;j<dim;j++){
    cout<<"Introduceti valoarea de pe linia "<<i<<" coloana "<<j<<" : "<<endl;
    f>>v[i][j];
   }
 }
void afisare(ostream& o){
  int i,j;
  o<<"Matricea este : "<<endl;
  for(i=0;i<dim;i++){
   for(j=0;j<dim;j++)
    o<<v[i][j]<<" ";
  o<<endl;
  }
  o<<"Determinantul matricii este : ";
  o<<determinant();
}
Complex& determinant();
Matrice_patratica(const Matrice_patratica& mat): Matrice(mat) {
  dim=mat.dim;
  int i,j;
  v=new Complex*[mat.dim]();
    for(i=0;i<dim;i++)
     v[i]=new Complex[dim]();

    for(i=0;i<dim;i++)
     for(j=0;j<dim;j++)
       v[i][j]=mat.v[i][j];
}
~Matrice_patratica(){}
Matrice_patratica& operator=(Matrice_patratica& mat);
int verif_diagonala();
};

Matrice_patratica& Matrice_patratica::operator=(Matrice_patratica& mat){
  dim=mat.dim;
  int i,j;
  for(i=0;i<dim;i++)
   for(j=0;j<dim;j++)
     v[i][j]=mat.v[i][j];
 return *this;
}

int Matrice_patratica::verif_diagonala(){
  int i,j;
  int ok=1;
  for(i=0;i<dim;i++)
   for(j=0;j<dim;j++)
     if(verif_valoare(i,j)==0)
       if(i!=j)
         ok=0;

    return ok;
}
Complex& Matrice_patratica::determinant(){

  Complex p(1,0);
  if (dim==1)
   return v[0][0];
  int x=0;
  int i,j;
  while(dim-x>2){
    for(i=x+1;i<dim;i++)
      for(j=x+1;j<dim;j++)
        v[i][j]=v[i][j]-((v[x][j]*v[i][x])/v[x][x]);
    p=p*v[x][x];
    x++;

  }

  p=p*((v[x][x]*v[x+1][x+1])-(v[x][x+1]*v[x+1][x]));

 return p;

}
int main()
{
      cout<<"Introduceti numarul de matrici oarecare:"<<endl;
      int i,n,d,d1,d2;
      cin>>n;
      for(i=0;i<n-2;i++){
       cout<<"Introduceti dimensiunile acestora (linie apoi coloana) : ";
        cin>>d1>>d2;
        Matrice_oarecare Mo(d1,d2);
        cin>>Mo;
        cout<<Mo;
        if(Mo.verif_diagonala()==1)
          cout<<"Este matrice diagonala ";
          else cout<<"Nu este matrice diagonala";
        cout<<endl;

      }
       cout<<"Introduceti dimensiunile acestora (linie apoi coloana) : ";
        cin>>d1>>d2;
        Matrice_oarecare Mo(d1,d2);
        cin>>Mo;
        cout<<Mo;
        if(Mo.verif_diagonala()==1)
          cout<<"Este matrice diagonala ";
          else cout<<"Nu este matrice diagonala";
        cout<<endl;
         Matrice_oarecare Mo2(Mo);
         cout<<Mo2;
         cout<<"(cea copiata)"<<endl;

      cout<<"Introduceti numarul de matrici patratice"<<endl;
      cin>>n;
      for(i=0;i<n-2;i++){
       cout<<"Introduceti dimensiunea acestora : ";
        cin>>d;
        Matrice_patratica Mp(d);
        cin>>Mp;
        cout<<Mp;
        cout<<endl;
        if(Mp.verif_diagonala()==1)
          cout<<"Este matrice diagonala ";
          else cout<<"Nu este matrice diagonala";
          cout<<endl;
      }
      cout<<"Introduceti dimensiunea acestora : ";
        cin>>d;
        Matrice_patratica Mp(d);
        cin>>Mp;
        cout<<Mp;
        cout<<endl;
        if(Mp.verif_diagonala()==1)
          cout<<"Este matrice diagonala ";
          else cout<<"Nu este matrice diagonala";
          cout<<endl;
          Matrice_patratica Mp2(Mp);
         cout<<Mp2;
         cout<<"(Matricea copiata)"<<endl;

        return 0;
}
