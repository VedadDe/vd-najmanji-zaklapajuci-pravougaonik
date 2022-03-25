//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include <algorithm>
#include <math.h>
//#include <bits/stdc++.h>
using namespace std;

//---------------------------------------------------------------------------
#pragma package(smart_init)

#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
  Slika->Canvas->FillRect(Rect(0,0,Slika->Width, Slika->Height));
}
//---------------------------------------------------------------------------
void __fastcall TForm4::SlikaMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
  Koordinate->Text = "( " + IntToStr(X) + " , " + IntToStr(Y) + " )";
}

//---------------------------------------------------------------------------
void TForm4::dodajTacku(Tacka T) {
	tacke.push_back(T);
	T.Crtaj(Slika);
}
//---------------------------------------------------------------------------
void TForm4::iscrtajPoligon(vector<Tacka> &tacke) {
	int n = tacke.size();
	for(int i=0;i<n;i++) {
		tacke[i].Crtaj(Slika);
		Duz trenutna(tacke[i],tacke[(i+1)%n]);
		trenutna.Crtaj(Slika);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm4::SlikaMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
  if(CrtanjeMnogougla->Checked) {
	  if(tacke.empty())
		Slika->Canvas->MoveTo(X,Y);

	  else Slika->Canvas->LineTo(X,Y);

	  dodajTacku(Tacka(X,Y));
  }
  else if(TackaUnutar->Checked) {
	  Duz poluprava(Tacka(X,Y), Tacka(Slika->Width,Slika->Height));
	  int n = tacke.size();
	  int brojac = 0;
	  for(int i=0;i<n;i++) {
		  Duz trenutna(tacke[i], tacke[(i+1)%n]);
		  if(daLiSeSijeku(poluprava,trenutna))
			brojac++;
	  }
	  if(brojac % 2 == 0)
		ShowMessage("Tacka je van mnogougla");
	  else ShowMessage("Tacka je unutar mnogougla");
  }
  else if(DodavanjeTacaka->Checked) {
	 dodajTacku(Tacka(X, Y));
  }
  else if(UnutarKonveksnog->Checked) {
	  if(jeLiUnutarKonveksnog(Tacka(X,Y),konveksni_omotac))
		ShowMessage("Tacka je unutar konveksnog mnogougla");
	  else ShowMessage("Tacka nije unutar konveksnog mnogougla");
  }
  else if(TangenteDugme->Checked) {
	  int lijevi,desni;
	  povuciTangente(Tacka(X,Y),lijevi,desni,konveksni_omotac);
	  Slika->Canvas->MoveTo(konveksni_omotac[desni].x,konveksni_omotac[desni].y);
	  Slika->Canvas->LineTo(X,Y);
	  Slika->Canvas->LineTo(konveksni_omotac[lijevi].x,konveksni_omotac[lijevi].y);
  }
}
//---------------------------------------------------------------------------

bool TForm4::jeLiUnutarKonveksnog(Tacka A, vector<Tacka> &konveksni) {
  int pocetak = 0, kraj = konveksni.size() - 1;
  while(kraj - pocetak > 1) {
	  int sredina = (pocetak + kraj) / 2;
	  if(daLiJeTackaUnutarTrougla(A, Trougao(konveksni[pocetak],konveksni[sredina],konveksni[kraj])))
		return true;
	  if(Orijentacija(konveksni[pocetak],A,konveksni[sredina]) < 0)
		kraj = sredina;
	  else pocetak = sredina;
  }
  return false;
}
//---------------------------------------------------------------------------

void __fastcall TForm4::ZavrsiMnogougaoClick(TObject *Sender)
{
  Slika->Canvas->LineTo(tacke[0].x,tacke[0].y);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::ProstiMnogougaoClick(TObject *Sender)
{
  int n = tacke.size();
  for(int i=1;i<n;i++)
	if(tacke[i] < tacke[0])
	  swap(tacke[i],tacke[0]);

  Tacka lijeva = tacke[0];
  sort(tacke.begin()+1, tacke.end(), [lijeva](Tacka A, Tacka B) -> bool {
									   return Orijentacija(lijeva,A,B) < 0;
									});

  iscrtajPoligon(tacke);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::UvijanjePoklonaDugmeClick(TObject *Sender)
{
  int indeks = 0;
  for(int i=1;i<tacke.size();i++)
	if(tacke[i] < tacke[indeks])
	  indeks = i;

  konveksni_omotac.push_back(tacke[indeks]);

  //indeks je indeks zadnje tacke koju smo dodali u konveksni omotac
  //novi_indeks je indeks tacke koju trazimo u koraku petlje da dodamo u konveksni
  while(true) {
	int novi_indeks = 0;
	if(indeks == 0)
	  novi_indeks = 1;
	for(int i = 1;i<tacke.size();i++)
	  if(i != indeks && i != novi_indeks && Orijentacija(tacke[indeks], tacke[novi_indeks], tacke[i]) > 0)
		novi_indeks = i;

	if(tacke[novi_indeks] == konveksni_omotac[0])
	  break;
	else konveksni_omotac.push_back(tacke[novi_indeks]);
	indeks = novi_indeks;

  }

  iscrtajPoligon(konveksni_omotac);
}
//---------------------------------------------------------------------------

Double udaljenost(Tacka A, Tacka B, Tacka E){

				 //y=ax+

	double a = A.y - B.y;
	double b = B.x - A.x;
	double f = a * (B.x) + b * (B.y);
	double c = -f;


	 float d = abs((a * E.x + b * E.y + c)) /
			 (sqrt(a * a + b * b));
	 return d;





	//return (sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)));

}

Tacka binarySearchNajudaljenija(vector <Tacka> t, Tacka zadana, Tacka naredna, int low, int high, int i){


	  //	ShowMessage("Usao za ");
		//ShowMessage(i);
		//ShowMessage(low);
		//ShowMessage(high);
		int m = t.size();

		if (low == high){
			return t[(low+i)%m];}
		/**
		if ((high == low + 1) && (udaljenost (zadana, naredna, t[low]) >= udaljenost(zadana, naredna, t[high]))){
			return t[low];}
		if ((high == low + 1) && (udaljenost( zadana, naredna, t[low]) < udaljenost(zadana, naredna, t[high]))){
			return t[high];}
		   */
		int mid = (low + high)/2;

		if ( ( udaljenost( zadana, naredna, t[(mid+i)%m]) >= udaljenost(zadana,naredna, t[(mid + 1+i)%m])) && ( udaljenost( zadana,naredna, t[(mid+i)%m]) >= udaljenost(zadana, naredna, t[(mid - 1+i)%m]))){
			return t[(mid+i)%m];}

		if ( ( udaljenost( zadana, naredna, t[(mid+i)%m]) >= udaljenost( zadana, naredna, t[(mid + 1+i)%m])) && (udaljenost(zadana, naredna, t[(mid+i)%m]) <= udaljenost(zadana, naredna, t[(mid - 1+i)%m]))){
			return binarySearchNajudaljenija(t, zadana, naredna, low, mid-1, i);}
		else{
			return binarySearchNajudaljenija(t, zadana, naredna, mid + 1, high, i);}

}







void __fastcall TForm4::GrahamScanDugmeClick(TObject *Sender)
{
  int n = tacke.size();
  for(int i=1;i<n;i++)
	if(tacke[i] < tacke[0])
	  swap(tacke[i],tacke[0]);


  Tacka lijeva = tacke[0];
  sort(tacke.begin()+1, tacke.end(), [lijeva](Tacka A, Tacka B) -> bool {
									   return Orijentacija(lijeva,A,B) < 0;
									});

  konveksni_omotac.push_back(tacke[0]);
  konveksni_omotac.push_back(tacke[1]);
  konveksni_omotac.push_back(tacke[2]);

  for(int i = 3; i < n; i++) {
	  while(Orijentacija(konveksni_omotac[konveksni_omotac.size()-2],
						 konveksni_omotac[konveksni_omotac.size()-1],
						 tacke[i]) > 0)
			konveksni_omotac.pop_back();

	  konveksni_omotac.push_back(tacke[i]);
  }

		double minX = DBL_MAX;
		double minY = DBL_MAX;
		double maxX = DBL_MIN;
		double maxY = DBL_MIN;


	for(int i=0;i<konveksni_omotac.size();i++)
		{
			Tacka p = konveksni_omotac[i];
			if(minX > p.x)
				minX = p.x;
			if(maxX < p.x)
				maxX = p.x;
			if(minY > p.y)
				minY = p.y;
			if(maxY < p.y)
				maxY = p.y;
		}

		Tacka A (minX, minY);
		Tacka B (minX + maxX - minX, minY);
		Tacka C (minX + maxX - minX, minY + maxY - minY);
		Tacka D =  Tacka(minX , minY+maxY - minY);

		 vector<Tacka> pravougao;

		 pravougao.push_back(A);
		 pravougao.push_back(B);
		 pravougao.push_back(C);
		 pravougao.push_back(D);

		 //iscrtajPoligon(pravougao);



	  double razdaljina_najmanja = DBL_MAX;//ok formaula
	  //udaljenost
	  //uslovi
	  //dvije iste
	  //
	  Tacka max = Tacka(0.0,0.0);
	  Tacka poectak_pravi = Tacka(0.0,0.0);
	  Tacka kraj_pravi = Tacka(0.0,0.0);
	  int m= konveksni_omotac.size();

	  iscrtajPoligon(konveksni_omotac);

	  for(int i=0;i<m;i++)

		{
	  ShowMessage(i);
	  //int v=
		 // ShowMessage("usao");
		  Tacka pocetak = konveksni_omotac[((i+m-1)%m)];
		  Tacka kraj = konveksni_omotac[i];
		  Tacka najdalja = binarySearchNajudaljenija(konveksni_omotac, konveksni_omotac[((i+m-1)%m)], konveksni_omotac[i], 1, m-2, i);
		  double razdaljina = udaljenost(pocetak, kraj, najdalja);
		  //ShowMessage(razdaljina);
		  if (razdaljina_najmanja>razdaljina ) {
			  razdaljina_najmanja = razdaljina;
			  poectak_pravi = pocetak;
			  kraj_pravi = kraj;
			  max = najdalja;

		  }

		  }



		  vector <Tacka> tr;

		  tr.push_back(poectak_pravi);
		  tr.push_back(kraj_pravi);
		  tr.push_back(max);

		  iscrtajPoligon(tr);
		  /*///proba obrisi kasnije
		  Tacka M (minX, maxY-razdaljina_najmanja);
		  Tacka N (poectak_pravi.x, poectak_pravi.y-razdaljina_najmanja);

		  Tacka P (minX, kraj_pravi.y+razdaljina_najmanja);

		  Duz nova(M,N);
		  Duz nn(P, M);

		  nova.Crtaj(Slika);
		  nn.Crtaj(Slika);

		  */


		  ////--------------------------------





		  //iscrtajPoligon(tr);
		  iscrtajPoligon(konveksni_omotac);

		  /*if(udaljenost (binarySearchNajudaljenija(konveksni_omotac, konveksni_omotac[i-1], konveksni_omotac[i], 0, konveksni_omotac.size()-1),konveksni_omotac[i])<razdaljina){

		   razdaljina=udaljenost (binarySearchNajudaljenija(konveksni_omotac, konveksni_omotac[i-1], konveksni_omotac[i], 0,
		   konveksni_omotac.size()-1),konveksni_omotac[i]);

		   poectak=konveksni_omotac[i-1];
		   kraj=konveksni_omotac[i];

		   max=binarySearchNajudaljenija(konveksni_omotac, konveksni_omotac[i], 0,
		   konveksni_omotac.size()-1);
		   }
		   }

		   int a,b;
		   a=3;
		   b=4;

		  Tacka pocetak = konveksni_omotac[a];
		  Tacka kraj = konveksni_omotac[b];
		  Tacka najdalja = binarySearchNajudaljenija(konveksni_omotac, pocetak, kraj, 0, konveksni_omotac.size()-1);
		  double d = udaljenost(pocetak, kraj, kraj);
		  ShowMessage(d);
		  poectak_pravi = pocetak;
		  kraj_pravi = kraj;
		  max = najdalja;
		  double razdaljina = udaljenost(pocetak, kraj, najdalja);
		  //ShowMessage(razdaljina);


		   */
	   /*	for (int i = 0; i < konveksni_omotac.size()-1; i++) {
			if(konveksni_omotac[i].x==max.x && konveksni_omotac[i].y==max.y)
					ShowMessage(i);
		}*/
		//ShowMessage(max.x);
		//ShowMessage(razdaljina_najmanja);

		 /*
		vector<Tacka>proba;
		proba.push_back(max);
		proba.push_back(poectak_pravi);
		proba.push_back(kraj_pravi);

		//ShowMessage("tacka" + );

		iscrtajPoligon(proba);
		iscrtajPoligon(konveksni_omotac);



		/*Tacka A = binarySearchNajudaljenija(konveksni_omotac, konveksni_omotac[0], 0, konveksni_omotac.size()-1);

		vector<Tacka>proba;
		proba.push_back(A);
		proba.push_back(konveksni_omotac[0]);
		iscrtajPoligon(proba);
		  */






















	   /*
		 for(int i=0;i<konveksni_omotac.size();i++)
		{
			Tacka edge = konveksni_omotac.getEdge(i);
			//Rotate the polygon so that the current edge is parallel to a major axis
			//The y-Axis in this use case
			double theta = Math.acos(edge.normalize().y);
			polygon.rotate(theta);
			//Calculate a bounding box
			rects[i] = boundingBox(polygon);
			polygon.rotate(-theta);
			rects[i].rotate(-theta, polygon.getCenter());
		}*/




























  //iscrtajPoligon(konveksni_omotac);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::GenerisanjeTacakaClick(TObject *Sender)
{
  int broj_tacaka = EditBrojTacaka->Text.ToInt();
  for(int i=0;i<broj_tacaka;i++) {
	  Tacka nova(rand()%Slika->Width, rand()%Slika->Height);
	  dodajTacku(nova);
  }
}
//---------------------------------------------------------------------------
void TForm4::povuciTangente(Tacka A, int &lijevi, int &desni, vector<Tacka> &konveksni) {

	int n = konveksni.size();
	int pocetak = 0, kraj = n - 1;
	lijevi = -1;
	while (pocetak < kraj) {
	  int sredina = (pocetak+kraj)/2;
	  //prvo provjerimo da li je sredina trazeni indeks
	  if(Orijentacija(A,konveksni[sredina],konveksni[(sredina+n-1)%n]) < 0 &&
		 Orijentacija(A,konveksni[sredina],konveksni[(sredina+1)%n]) < 0) {
			 lijevi = sredina;
			 break;
		 }
	  //ako je sredina na blizem luku
	  if(Orijentacija(A,konveksni[sredina],konveksni[(sredina+1)%n]) > 0) {
		  if(Orijentacija(A,konveksni[kraj],konveksni[(kraj+1)%n]) < 0 ||
			 Orijentacija(A,konveksni[(kraj+n-1)%n],konveksni[kraj]) < 0 ||
			 Orijentacija(A,konveksni[sredina],konveksni[kraj]) < 0)
			   pocetak = sredina + 1;
		  else kraj = sredina - 1;
	  }
	  //ako je sredina na daljem luku
	  else {
		  if(Orijentacija(A,konveksni[pocetak],konveksni[(pocetak+1)%n]) > 0 ||
			 Orijentacija(A,konveksni[(pocetak+n-1)%n],konveksni[pocetak]) > 0 ||
			 Orijentacija(A,konveksni[pocetak],konveksni[sredina]) > 0)
			   kraj = sredina - 1;
		  else pocetak = sredina + 1 ;
	  }
	}
	if(lijevi == -1)
	  lijevi = pocetak;
	////////////////////////////////////////////////////////////////////////////
	pocetak = 0;
	kraj = n - 1;
	desni = -1;
	while (pocetak < kraj) {
	  int sredina = (pocetak+kraj)/2;
	  //prvo provjerimo da li je sredina trazeni indeks
	  if(Orijentacija(A,konveksni[sredina],konveksni[(sredina+n-1)%n]) > 0 &&
		 Orijentacija(A,konveksni[sredina],konveksni[(sredina+1)%n]) > 0) {
			 desni = sredina;
			 break;
		 }
	  //ako je sredina na blizem luku
	  if(Orijentacija(A,konveksni[sredina],konveksni[(sredina+1)%n]) > 0) {
		  if(Orijentacija(A,konveksni[pocetak],konveksni[(pocetak+1)%n]) < 0 ||
			 Orijentacija(A,konveksni[(pocetak+n-1)%n],konveksni[pocetak]) < 0 ||
			 Orijentacija(A,konveksni[sredina],konveksni[pocetak]) > 0)
			   kraj = sredina - 1;
		  else pocetak = sredina + 1;
	  }
	  //ako je sredina na daljem luku
	  else {
		  if(Orijentacija(A,konveksni[kraj],konveksni[(kraj+1)%n]) > 0 ||
			 Orijentacija(A,konveksni[(kraj+n-1)%n],konveksni[kraj]) > 0 ||
			 Orijentacija(A,konveksni[kraj],konveksni[sredina]) < 0)
			   pocetak = sredina + 1;
		  else kraj = sredina - 1 ;
	  }
	}
	if(desni == -1)
	  desni = pocetak;
}

void __fastcall TForm4::KonveksniInduktivnoClick(TObject *Sender)
{
  konveksni_omotac.push_back(tacke[0]);
  konveksni_omotac.push_back(tacke[1]);
  konveksni_omotac.push_back(tacke[2]);
  if(Orijentacija(konveksni_omotac[0],konveksni_omotac[1],konveksni_omotac[2])>0)
	swap(konveksni_omotac[1],konveksni_omotac[2]);

  for(int i=3;i<tacke.size();i++)
	if(!jeLiUnutarKonveksnog(tacke[i],konveksni_omotac)) {
		int lijevi,desni;
		povuciTangente(tacke[i],lijevi,desni,konveksni_omotac);
		if(desni < lijevi) {
			konveksni_omotac.erase(konveksni_omotac.begin()+ desni + 1,konveksni_omotac.begin() + lijevi);
			konveksni_omotac.insert(konveksni_omotac.begin() + desni + 1,tacke[i]);
		}
		else {
			konveksni_omotac.erase(konveksni_omotac.begin()+ desni + 1,konveksni_omotac.end());
			konveksni_omotac.erase(konveksni_omotac.begin(),konveksni_omotac.begin() + lijevi);
			konveksni_omotac.push_back(tacke[i]);
		}
	}
	iscrtajPoligon(konveksni_omotac);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::TriangulacijaClick(TObject *Sender)
{
  vector<Tacka> pomocni = tacke;
  int trenutni = 0;
  while(pomocni.size() > 3) {
	 int n = pomocni.size();
	 //ShowMessage(n);
	 //ShowMessage(trenutni);
	 int naredni = (trenutni + 1) % n;
	 int prethodni = (trenutni + n - 1) % n;
	 if(Orijentacija(pomocni[prethodni],pomocni[trenutni],pomocni[naredni]) < 0) {
		 bool uho = true;
		 Trougao T(pomocni[prethodni],pomocni[trenutni],pomocni[naredni]);
		 auto it = pomocni.begin() + naredni;
		 it++;
		 if(it==pomocni.end())
		   it = pomocni.begin();
		 while(it != pomocni.begin() + prethodni) {
		   if(daLiJeTackaUnutarTrougla(*it,T)) {
			   uho = false;
			   break;
		   }
		   it++;
		   if(it==pomocni.end())
			 it = pomocni.begin();
		 }
		 if(uho) {
			 dijagonale.push_back(Duz(pomocni[prethodni],pomocni[naredni]));
			 //dijagonale[dijagonale.size()-1].Crtaj(Slika);
			 pomocni.erase(pomocni.begin()+trenutni);
			 if(trenutni != 0)
			   trenutni--;
			 else trenutni = pomocni.size()-1;
			 if(trenutni != 0)
			   trenutni--;
			 else trenutni = pomocni.size()-1;
		 }

	 }
	 trenutni++;
	 if(trenutni == pomocni.size())
	   trenutni = 0;
  }
  for(int i=0;i<dijagonale.size();i++)
	dijagonale[i].Crtaj(Slika);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button1Click(TObject *Sender)
{
	int n = tacke.size();
   //	sort(tacke.begin()+1, tacke.end());
	vector <Tacka> plave(tacke.begin(), tacke.begin()+n/2);
	vector <Tacka> crvene(tacke.begin()+n/2, tacke.end());
	int i;
	vector <Tacka> trenutne;
	 //	sort(plave.begin()+1, plave.end());
	   //		sort(crvene.begin()+1, crvene.end());
	for (i = 0; i < plave.size(); i++) {
		 plave[i].Crtaj(Slika,clBlue);
	}

	for (i = 0; i < crvene.size(); i++) {
		 crvene[i].Crtaj(Slika,clRed);
	}


	  int indeks = 0;
  for(int i=1;i<tacke.size();i++)
	if(tacke[i] < tacke[indeks])
	  indeks = i;

  konveksni_omotac.push_back(tacke[indeks]);

  //indeks je indeks zadnje tacke koju smo dodali u konveksni omotac
  //novi_indeks je indeks tacke koju trazimo u koraku petlje da dodamo u konveksni
  while(true) {
	int novi_indeks = 0;
	if(indeks == 0)
	  novi_indeks = 1;
	for(int i = 1;i<tacke.size();i++)
	  if(i != indeks && i != novi_indeks && Orijentacija(tacke[indeks], tacke[novi_indeks], tacke[i]) > 0)
		novi_indeks = i;

	if(tacke[novi_indeks] == konveksni_omotac[0])
	  break;
	else konveksni_omotac.push_back(tacke[novi_indeks]);
	indeks = novi_indeks;

  }

  int m=konveksni_omotac.size();
  bool sviIsti;
  int brojac=0;
  for(int i=0; i<m; i++){
	for(int j=0; j<plave.size(); j++)
		{
		if(konveksni_omotac[i]==plave[j]){
			brojac ++;
		}
		}

  }
   int broojac=0;
  for(int i=0; i<m; i++){
	for(int j=0; j<crvene.size(); j++)
		{
		if(konveksni_omotac[i]==crvene[j]){
			broojac ++;
		}
		}

  }


  if(m==brojac)
  ShowMessage("sve plave");
  if(m==broojac)
  ShowMessage("sve crvene");
	if(m!=brojac && m!=broojac)
	  ShowMessage("sve razlicite");
  //sort(plave.begin()+1,plave.end());
  //sort(crvene.begin()+1, crvene.end());
  sort(tacke.begin()+1,tacke.end());
  if(m!=brojac && m!=broojac){
	  /***
	  Dio pod a
	  **/

	  bool nasao=false;
	for(int i=0; i<m; i++){
	int br = 0;
	for(int j=0; j<plave.size(); j++)
		{
		if(konveksni_omotac[i]==plave[j]){
			br ++;
		}
		if(br==0 ){

			Slika->Canvas->MoveTo(konveksni_omotac[i].x, konveksni_omotac[i].y);
			Slika->Canvas->LineTo(konveksni_omotac[i+2].x,konveksni_omotac[i+1].y);}

			nasao=true;
		}
		if (nasao) {
				 break;
		}
		}

  }
	  //Slika->Canvas->MoveTo(crvene[1].x-5, crvene[1].y-5);
		//	Slika->Canvas->LineTo(plave[1].x,plave[1].y);}
		  //Dio b
  else{
	for (i = 0; i < tacke.size(); i++) {
			Slika->Canvas->MoveTo(tacke[i].x,0);
			Slika->Canvas->LineTo(tacke[i].x,tacke[i].y);}
			}
}











//---------------------------------------------------------------------------

void __fastcall TForm4::Button2Click(TObject *Sender)
{

	   konveksni_omotac.push_back(tacke[0]);
  konveksni_omotac.push_back(tacke[1]);
  konveksni_omotac.push_back(tacke[2]);
  if(Orijentacija(konveksni_omotac[0],konveksni_omotac[1],konveksni_omotac[2])>0)
	swap(konveksni_omotac[1],konveksni_omotac[2]);

  for(int i=3;i<tacke.size();i++)
	if(!jeLiUnutarKonveksnog(tacke[i],konveksni_omotac)) {
		int lijevi,desni;
		povuciTangente(tacke[i],lijevi,desni,konveksni_omotac);
		if(desni < lijevi) {
			konveksni_omotac.erase(konveksni_omotac.begin()+ desni + 1,konveksni_omotac.begin() + lijevi);
			konveksni_omotac.insert(konveksni_omotac.begin() + desni + 1,tacke[i]);
		}
		else {
			konveksni_omotac.erase(konveksni_omotac.begin()+ desni + 1,konveksni_omotac.end());
			konveksni_omotac.erase(konveksni_omotac.begin(),konveksni_omotac.begin() + lijevi);
			konveksni_omotac.push_back(tacke[i]);
		}
	}
	iscrtajPoligon(konveksni_omotac);
	int prva=2;
	int druga=6;
	int treca=9;
	//triangulacija konveksnog obicnog
	/*
	for (int i=1; i < konveksni_omotac.size(); i++) {
	Slika->Canvas->MoveTo(konveksni_omotac[0].x,konveksni_omotac[0].y);
		Slika->Canvas->LineTo(konveksni_omotac[i].x,konveksni_omotac[i].y);}
	*/


	for(int i=prva; i<druga; i++)
		 {
				Slika->Canvas->MoveTo(konveksni_omotac[prva].x,konveksni_omotac[prva].y);
				Slika->Canvas->LineTo(konveksni_omotac[i+1].x,konveksni_omotac[i+1].y);

		 }

		 for(int i=druga; i<treca; i++)
		 {
				Slika->Canvas->MoveTo(konveksni_omotac[druga].x,konveksni_omotac[druga].y);
				Slika->Canvas->LineTo(konveksni_omotac[i+1].x,konveksni_omotac[i+1].y);

		 }



		  for(int i=0; i<prva; i++)
		 {
				Slika->Canvas->MoveTo(konveksni_omotac[treca].x,konveksni_omotac[treca].y);
				Slika->Canvas->LineTo(konveksni_omotac[i].x,konveksni_omotac[i].y);

		 }



		Slika->Canvas->MoveTo(konveksni_omotac[prva].x,konveksni_omotac[prva].y);
		Slika->Canvas->LineTo(konveksni_omotac[druga].x,konveksni_omotac[druga].y);
		Slika->Canvas->MoveTo(konveksni_omotac[druga].x,konveksni_omotac[druga].y);
		Slika->Canvas->LineTo(konveksni_omotac[treca].x,konveksni_omotac[treca].y);
		Slika->Canvas->MoveTo(konveksni_omotac[treca].x,konveksni_omotac[treca].y);
		Slika->Canvas->LineTo(konveksni_omotac[prva].x,konveksni_omotac[prva].y);


	}







//---------------------------------------------------------------------------

