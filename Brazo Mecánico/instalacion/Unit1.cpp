//---------------------------------------------------------------------------
//        WinExec("\\INSTALL.exe",SW_SHOW);


#include <vcl.h>
#include <string.h>
#include <stdio.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1Click(TObject *Sender)
{
        char txt[500];
        AnsiString s;
        int i;
        GetSystemDirectory(txt,500);
        for(i=0;txt[i]!='\0';i++)
                if(txt[i+1]=='\\')
                        break;
                else
                        s=s+txt[i];
        s=s+":\\Archivos de programa\\Internet Explorer\\IEXPLORE.EXE \\Brazo Mec?nico\\P?G WEB\\CAR?TULA\\Index12.htm";
//         WinExec("C:\\Archivos de programa\\Internet Explorer\\IEXPLORE.EXE \\Brazo Mec?nico\\P?G WEB\\CAR?TULA\\Index12.htm",SW_MAXIMIZE);
         WinExec(s.c_str(),SW_MAXIMIZE);
  //       Close();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
        MediaPlayer1->FileName="PSYCH EXIT.WAV";
        try
        {
                MediaPlayer1->Open();
                MediaPlayer1->Play();
        }
        catch(...)
        {
                return;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MediaPlayer1Notify(TObject *Sender)
{
        try
        {
                MediaPlayer1->Play();
        }
        catch(...)
        {
                return;
        }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        marquesina(BRAZO_MECANICO);
   //     marquesina(CAMACHO);

}
//---------------------------------------------------------------------------


void TForm1::marquesina(TLabel * l)
{
        //TODO: Add your source code here
        char txt[100];
        int i;
        strcpy(txt,l->Caption.c_str());
        for(i=0;i<strlen(txt);i++)
                if(txt[i]=='_')
                        txt[i]=' ';
        l->Caption=&txt[1];
        if(l->Caption=="")
                l->Caption="                                                                                  BRAZO MECANICO";

}


