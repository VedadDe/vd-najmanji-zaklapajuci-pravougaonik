//---------------------------------------------------------------------------

#ifndef pomocnaH
#define pomocnaH

struct Tacka {
	double x,y;
    Tacka(double X, double Y):x(X),y(Y) {}
	void Crtaj(TImage *Slika, TColor boja  = clWhite) const;

};

//---------------------------------------------------------------------------
struct Sirina {
	double sirina;
	Tacka A;
	Sirina(double X, Tacka T):sirina(X),A(T) {}


};


//---------------------------------------------------------------------------
struct Duz {
	Tacka A,B;
	Duz(Tacka A, Tacka B):A(A),B(B) {}
	void Crtaj(TImage *Slika, TColor boja = clBlack) const;
};

//---------------------------------------------------------------------------

struct Trougao {
	Tacka A;
	Tacka B;
	Tacka C;
	Trougao(Tacka A, Tacka B, Tacka C):A(A),B(B),C(C) {}
	void Crtaj(TImage*) const;
};


bool daLiSeSijeku(Duz prva, Duz druga);
int Orijentacija(Tacka A, Tacka B, Tacka C);
bool operator<(Tacka A, Tacka B) { return A.x < B.x; }
bool operator==(Tacka A, Tacka B) { return A.x == B.x && A.y == B.y; }
bool daLiJeTackaUnutarTrougla(Tacka, Trougao);

//---------------------------------------------------------------------------
#endif
