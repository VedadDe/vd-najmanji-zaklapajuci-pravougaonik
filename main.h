//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <vector>
#include "pomocna.h"
using namespace std;
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
	TImage *Slika;
	TEdit *Koordinate;
	TLabel *LabelaBrojTacaka;
	TEdit *EditBrojTacaka;
	TButton *GenerisanjeTacaka;
	TLabel *Akcija;
	TRadioButton *CrtanjeMnogougla;
	TRadioButton *TackaUnutar;
	TRadioButton *DodavanjeTacaka;
	TRadioButton *UnutarKonveksnog;
	TButton *ZavrsiMnogougao;
	TButton *ProstiMnogougao;
	TButton *UvijanjePoklonaDugme;
	TButton *GrahamScanDugme;
	TRadioButton *TangenteDugme;
	TButton *KonveksniInduktivno;
	TButton *Triangulacija;
	TButton *Button1;
	TButton *Button2;
	void __fastcall SlikaMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall SlikaMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall ZavrsiMnogougaoClick(TObject *Sender);
	void __fastcall ProstiMnogougaoClick(TObject *Sender);
	void __fastcall UvijanjePoklonaDugmeClick(TObject *Sender);
	void __fastcall GrahamScanDugmeClick(TObject *Sender);
	void __fastcall GenerisanjeTacakaClick(TObject *Sender);
	void __fastcall KonveksniInduktivnoClick(TObject *Sender);
	void __fastcall TriangulacijaClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);

private:
	vector<Tacka> tacke;
	vector<Tacka> konveksni_omotac;
    vector<Duz> dijagonale;
	void dodajTacku(Tacka T);
	void iscrtajPoligon(vector<Tacka> &tacke);
	bool jeLiUnutarKonveksnog(Tacka A, vector<Tacka> &konveksni);
	void povuciTangente(Tacka A, int &lijevi, int &desni, vector<Tacka> &konveksni);
public:		// User declarations
	__fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
