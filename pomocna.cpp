//---------------------------------------------------------------------------

#pragma hdrstop

#include "pomocna.h"
#include <cmath>
//---------------------------------------------------------------------------

void Tacka::Crtaj(TImage *Slika, TColor boja) const {
  Slika->Canvas->Brush->Color = boja;
  int X = round(x), Y = round(y);
  Slika->Canvas->Ellipse(Rect(X-3,Y-3,X+3,Y+3));
  Slika->Canvas->Brush->Color = clWhite;
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

void Duz::Crtaj(TImage *Slika, TColor boja) const {
  Slika->Canvas->Pen->Color = boja;
  Slika->Canvas->MoveTo(A.x,A.y);
  Slika->Canvas->LineTo(B.x,B.y);
  Slika->Canvas->Pen->Color = clBlack;
}



//---------------------------------------------------------------------------

bool daLiSeSijeku(Duz prva, Duz druga) {
   return Orijentacija(prva.A, prva.B, druga.A) != Orijentacija(prva.A, prva.B, druga.B)
	   && Orijentacija(druga.A, druga.B, prva.A) != Orijentacija(druga.A, druga.B, prva.B);
}


//---------------------------------------------------------------------------

int Orijentacija(Tacka A, Tacka B, Tacka C) {
	double P = 0.5 * (A.x*(B.y-C.y) + B.x*(C.y-A.y) + C.x*(A.y-B.y));
	if(P > 0)
	  return -1;
	else return 1;
}

//---------------------------------------------------------------------------

void Trougao::Crtaj(TImage *image) const {
	image->Canvas->MoveTo(A.x,A.y);
	image->Canvas->LineTo(B.x,B.y);
	image->Canvas->LineTo(C.x,C.y);
	image->Canvas->LineTo(A.x,A.y);
}

//---------------------------------------------------------------------------

bool daLiJeTackaUnutarTrougla(Tacka P, Trougao t) {
	if(Orijentacija(t.A,t.B,P) == Orijentacija(t.B,t.C,P) &&
	   Orijentacija(t.B,t.C,P) == Orijentacija(t.C,t.A,P))
		 return true;
	return false;
}
#pragma package(smart_init)
