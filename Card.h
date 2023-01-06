//---------------------------------------------------------------------------

#ifndef CardH
#define CardH
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
const VALUE_NUM = 13; // число значений карт
const PACK_LEN = VALUE_NUM;
const PACK_NUM = 8; // число колод
const PACK_TOTAL = PACK_NUM*PACK_LEN; // общее число карт
const KING = 12; // король
const ACE = 0; // туз

class Card
{
private:
	int Value; // значение 0- туз, ..., 12-король
public:
	void Init(int value); //инициализировать значением
	int GetValue();//получить значение
	bool Avaliable;//доступность
	TImage *pic;//Image
	bool Is; //наличие
};
#endif
