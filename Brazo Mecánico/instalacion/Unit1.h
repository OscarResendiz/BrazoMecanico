//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
#include <MPlayer.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImage *Image2;
        TImage *Image1;
        TBitBtn *BitBtn1;
        TMediaPlayer *MediaPlayer1;
        TLabel *BRAZO_MECANICO;
        TTimer *Timer1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        void __fastcall Image1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall MediaPlayer1Notify(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:
        __fastcall TForm1(TComponent* Owner);
        void marquesina(TLabel *l);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
