#pragma once
#include<iostream>
#include<windows.h>
#include<conio.h>
using namespace std;
#define GAME_BACKGROUND_X 22
#define GAME_BACKGROUND_Y 15
#define a1  0			//条形
#define a2  1

#define b 2					// 方块

#define c1 3					//L形
#define c2 4
#define c3 5
#define c4 6

#define d1 7					//T形
#define d2 8 
#define d3 9
#define d4 10

#define e1 11				//闪电1形
#define e2 12

#define f1 13				//闪电2形
#define f2 14
class Block;

class GameSet
{
protected:
	int m_scores;
	int** m_gameBackGround;
	int m_rank;
	int top;

public:
	GameSet();
	~GameSet();
	void SetPos(int x, int y);
	void SetColor(int color_num);
	int GetRank() { return m_rank; }
	int GetScores() { return m_scores; }
	void SetScores() { m_scores += 10 * m_rank; }
	void PrintGameGround();
	int GetGameGround(int x, int y) { return m_gameBackGround[x][y]; }
	void SetGameGround(int x, int y, int num) { m_gameBackGround[x][y] = num; };
	void ChangeGround(int x, int y) { 
		if(0<x&& x < GAME_BACKGROUND_X&&y >=0&&y <GAME_BACKGROUND_Y)
		m_gameBackGround[x][y] = 1; }
	bool JudgeIfZero(int x, int y) { return m_gameBackGround[x][y] == 0 ? 1 : 0; }
	void ShowScore();
	void GameRun(GameSet& gameSet, Block& blocks);
};
class Block
{
private:



protected:
	int block_X;//起始地点
	int block_Y;
	int rightMax;
	int leftMax;
	int currBlock;
	int nextBlock;
	int top;
	const int high[15] = { 4,1,2,2,3,2,3,2,3,2,3,2,3,2,3 };
	int blockVariety[15][8] = {
{0,0,1,0,2,0,3,0},{0,0,0,1,0,2,0,3},
{0,0,1,0,0,1,1,1},
{0,0,1,0,1,1,1,2},{0,1,1,1,2,0,2,1},{0,0,0,1,0,2,1,2},{0,0,0,1,1,0,2,0},
{1,0,1,1,1,2,0,2},{0,0,0,1,1,1,2,1},{0,0,0,1,0,2,1,0},{0,0,1,0,2,0,2,1},
{0,0,0,1,1,1,1,2},{0,1,1,0,1,1,2,0},
{0,1,0,2,1,0,1,1},{0,0,1,0,1,1,2,1}
	};
public:
	Block();
	~Block();
	int SrandBlock();
	int GetBlockX() { return block_X; };
	int GetBlockY() { return block_Y; };
	void DrawBlock(GameSet& gameSet);
	void DrawSpace(int x,int y,GameSet& gameSet);
	void ShowNextBlock(GameSet&);
	void ChangeRightMax(int x) { rightMax = x; }
	void ChangeLeftMax(int y) { leftMax = y; }
	void ChangeBlockX(int x) { block_X = x; }
	void ChangeBlockY(int y) { block_Y = y; }
	void GetDirection(GameSet&);
	void TurnShape(int num);
	bool Judge(int,int,GameSet&);
	int IfBlockArrival(GameSet&);
	void ClearNextBlock(GameSet&);
	void ChangeGroundWhenArrive(GameSet&);
	void ChangeTop(int x) { top = x; };
};

