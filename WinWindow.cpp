//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WinWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
	WebBrowser1->Navigate("https://i.gifer.com/VHFn.gif");
}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormShow(TObject *Sender)
{
 	WebBrowser1->Width = Form3->Width;
	WebBrowser1->Show();
}
//---------------------------------------------------------------------------
