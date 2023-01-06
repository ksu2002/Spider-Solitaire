//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GameWindow.h"
#include "Card.h"
#include "Pack.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;

//---------------------------------------------------------------------------

int AmountCardsInColumn(int pos){//кол-во карт в столбцах
	int j = 0;
	while(Columns[pos][j].Is ){
		j++;
	}
	return j;
}

Card GetCardByIndex(int pos, int index){//взятие карты по индексу	if( Columns[pos][index].Is ){
		// карта найдена:
		Columns[pos][index].Is = false;
		Columns[pos][index].Avaliable = true;
	}
	return Columns[pos][index];
}

void AddCard( int pos, bool pack, Card card){//если pack = true то из колоды (тогда не важно какую карты передать)
	if( pack && !Pack.isCard()) return; //если нет карт
	int i;
	for( i = 0; i < PACK_TOTAL; i++ )
		if(!Columns[pos][i].Is ){
			if(pack) {
			Columns[pos][i] = Pack.GetCard();//добавляем карты в колоду из колоды pask
			}
			else {
			Columns[pos][i] = card;
			}
		  Columns[pos][i].Is = true;
		 return;
	}
}

 void MoveCard(int pos1,int pos2,int index){//перемещение карты из 1 в 2 позицию
	if(IsCard(pos1)){
		Card card;
		card = GetCardByIndex( pos1, index);//взять карту из pos1
		AddCard( pos2, false, card); //добавить карту в pos2
		Columns[pos1][AmountCardsInColumn(pos1)-1].Avaliable = true;
		Columns[pos1][AmountCardsInColumn(pos1)].Is = false;// удалить из pos1
		Columns[pos2][AmountCardsInColumn(pos2)-1].Avaliable = true;
		Columns[pos2][AmountCardsInColumn(pos2)-1].Is = true;
			if(AmountCardsInColumn(pos1)!=0) {
			Columns[pos1][AmountCardsInColumn(pos1)-1].pic->Invalidate();
		}
	}
	return;
}

void NewGame(){
	int i, j , p;
	win = false;
	Card card;
	AmmountOfDoneColumns =0;
	card.Init(0);
	Pack.Shuffle();
	// инициализировать стопки
	for( j = 0; j < 11; j ++ )
		for( p = 0; p < PACK_TOTAL; p ++ )
			Columns[j][p].Is = false;
	// 4 стопки по 6 карт:
	for( i = 0; i < 4; i ++ )
		for( j = 0; j < 6; j ++ ) {
			AddCard (i, true, card);
	}
	for( i = 0; i < 4; i ++ )
		Columns[i][5].Avaliable = true;
	// 6 стопки по 5 карт:
	for( i = 4; i < 10; i ++ )
		for( j = 0; j < 5; j ++ )
			AddCard (i, true, card);
	for( i = 4; i < 10; i ++ )
		Columns[i][4].Avaliable = true;
	// колода:
	for( i = 0; i < 104-54; i ++ ) {
		AddCard (10, true, card);
		Columns[10][i].Avaliable = false;
	}
}

bool IsCard(int pos){ //наличие карт в столбце
	int i;
	for( i = 0; i < PACK_TOTAL; i ++ )
		if( Columns[pos][i].Is ) return true;
	return false;
}

bool CanMoveTo(int pos, int Pos){// проверка карт на допустимость перемещения
	if(Columns[pos][AmountCardsInColumn(pos)-1].GetValue()-Columns[Pos][indexOfFirstCardToMove].GetValue()!=1
	&& AmountCardsInColumn(pos)!=0 )//если карты не в порядке убывания и не пустая стопка
		return false;
	return true;
}

bool CardsAvaliable(int Pos){//проверка карт на доступность для игры (открытые карты)
	for(int i = indexOfFirstCardToMove; i<indexOfLastCardToMove; i++)
		if(!Columns[Pos][i].Avaliable)  return false;
	int firstIndex = indexOfFirstCardToMove;
	firstIndex++;
	for(firstIndex; firstIndex<indexOfLastCardToMove; firstIndex++)
		if(Columns[Pos][firstIndex-1].GetValue()-Columns[Pos][firstIndex].GetValue()!=1)
			return false;
	return true;
}

// возвращает индекс короля в собранной стопке(король-туз)
int KingIndexInDoneColumn(int pos, int Pos, int first, int last){
	int king = -1;
	for(int i = 0; i<AmountCardsInColumn(pos); i++)
		if(Columns[pos][i].GetValue() == KING
		&& Columns[pos][i].Avaliable)
			king = i;
	int count = KING;
	for(int j = king; j<AmountCardsInColumn(pos); j++)
	   if(Columns[pos][j].GetValue() == count) count =  count -1;
	if(count != -1) king = -1;
	return king;
}

//удалить собраную стопку (король-туз) с игрового поля
void RemoveDoneColumn(int pos, int Pos, int first, int last){
	int firstIndex = KingIndexInDoneColumn(pos, Pos, first, last);//поиск короля
	if(firstIndex!=-1){
		 int k = AmountCardsInColumn(pos);
		 for(int j =firstIndex; j<k; j++){
			Card card;
			card = GetCardByIndex( pos, j) ;
			Columns[pos][j].Is = false;   //удаление карт
			Columns[pos][j].Avaliable = false;
		}
		Columns[pos][AmountCardsInColumn(pos)-1].Avaliable = true;
		AmmountOfDoneColumns++;//увеличение количества собраных стопок
	}
	return;
}

void __fastcall TForm1::N4Click(TObject *Sender)
{
	Form1->Close();
}
//---------------------------------------------------------------------------


void AddFromPack(int i){//добавить карту из колоды
	Card card;
	card = GetCardByIndex( 10, AmountCardsInColumn(10)-1);//взять карту колоды
	AddCard( i, false, card); //добавить карту в стопку i
	Columns[10][AmountCardsInColumn(10)-1].Avaliable = true;
	Columns[10][AmountCardsInColumn(10)].Is = false;
	Columns[i][AmountCardsInColumn(i)-1].Avaliable = true;
	Columns[i][AmountCardsInColumn(i)-1].Is = true;
}



__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}



//---------------------------------------------------------------------------

