//---------------------------------------------------------------------------


#pragma hdrstop

#include "Card.h"
#include "Pack.h"
#include "GameWindow.h"
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------

void Card::Init(int value)
{
	Value = value; 
	Is = true;
	Avaliable = false;
}
int Card::GetValue() { return Value; }
#pragma package(smart_init)
