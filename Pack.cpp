//---------------------------------------------------------------------------


#pragma hdrstop

#include "Pack.h"
#include "Card.h"
#include <stdlib.h>


//---------------------------------------------------------------------------



Pack::Pack()
{
	int card_num, pack_num, suit, value;
	card_num = 0;
	for(pack_num = 0; pack_num < PACK_NUM; pack_num ++)
		for( value = 0; value < VALUE_NUM; value ++ ){
		 // инициализация карты
		Cards[card_num].Init(value) ;
		// переход к следующей карте
		card_num ++ ;
	}
}

void Pack::Shuffle()
{
	int n, rnd;
	Card card;
	// каждой карте присваиваем признак "находится в колоде"
	for( n = 0; n < PACK_TOTAL; n ++ )
		Cards[n].Is = true;
		// PACK_TOTAL раз выполняем перестановку карт
		for( n = 1; n <= PACK_TOTAL; n ++)
			for( n = 0; n < PACK_TOTAL; n ++)
			{
			// выбираем случайный номер карты в диапазоне от 0
			// до PACK_TOTAL-1
			rnd = random(PACK_TOTAL);
			// запоминаем последнюю карту
			card = Cards[PACK_TOTAL-1];
			// на ее место записываем карту с номером rnd
			Cards[PACK_TOTAL-1] = Cards[rnd];
			// на место карты с номером rnd записываем карту,
			// которая ранее была последней
			Cards[rnd] = card;
			}
}

void Pack::AddCard(Card card)
{
	int i ;
	for( i = 0; i < PACK_TOTAL; i ++ )
		if( !Cards[i].Is && Cards[i].GetValue() == card.GetValue())
		{
			Cards[i].Is = true;
			return;
		}
}

Card Pack::GetCard()
{
	int i;
	for( i = 0; i < PACK_TOTAL; i ++ )
		if( Cards[i].Is )
		{
			Cards[i].Is = false;
			return Cards[i] ;
		}
	return Cards[0] ;
}bool Pack::isCard(){
	int i;
	for( i = 0; i < PACK_TOTAL; i ++ )
		if( Cards[i].Is ) return true;
	return false;
}#pragma package(smart_init)
