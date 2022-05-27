#include<iostream>
#include"GameSet.h"
using namespace std;

int main()
{
	GameSet gameSet;
	Block block;
	gameSet.PrintGameGround();
	//gameSet.SetColor(1);
	//cout << "¡ö";
	//gameSet.SetColor(2);
	//cout << "¡ö"<<endl;
	//gameSet.SetColor(3);
	//cout << "¡ö";
	//gameSet.SetColor(4);
	//cout << "¡ö";
	//gameSet.ShowScore();
	//gameSet.ShowNextBlock(block);
	//srand((unsigned int)time(NULL));
	gameSet.GameRun(gameSet,block);
	block.ShowNextBlock(gameSet);
	gameSet.SetPos(GAME_BACKGROUND_Y + 2,GAME_BACKGROUND_X+ 2);
	return 0;
}