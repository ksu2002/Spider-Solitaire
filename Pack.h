//---------------------------------------------------------------------------

#ifndef PackH
#define PackH
#include"Card.h"
//---------------------------------------------------------------------------
class Pack
{
	private:
		Card Cards[PACK_TOTAL];//массив карт
	public:
		Pack();
		void Shuffle();//перемещать
		void AddCard(Card card);//добавить карту
		Card GetCard();//получить карту
		bool isCard();//наличие карт};
#endif
