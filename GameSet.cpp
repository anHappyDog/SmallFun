#include "GameSet.h"

GameSet::GameSet()
{
	m_rank = 1;
	m_gameBackGround = new int* [GAME_BACKGROUND_X];
	for (int i = 0; i < GAME_BACKGROUND_X; i++)
	{
		m_gameBackGround[i] = new int[GAME_BACKGROUND_Y];
		memset(m_gameBackGround[i], 0, sizeof(int) * GAME_BACKGROUND_Y);
	}
}
int Block::IfBlockArrival(GameSet& gameSet)
{
	int flag;
	if (Judge(block_X + 1, block_Y, gameSet) == 0)
	{
		ChangeGroundWhenArrive(gameSet);
		if (top > block_X )//?
		{
			ChangeTop(block_X);
		}
		if (top <=0)
		{
			return -1;//游戏结束
		}
		for (int i = block_X; i < block_X+high[currBlock] && i < GAME_BACKGROUND_X; i++)			//消除行
		{
			flag = 1;
			for (int j = 0; j < GAME_BACKGROUND_Y; j++)					//判定某一行是否满， 用flag来标记
				if (gameSet.JudgeIfZero(i,j) == 1)
					flag = 0;
			if (flag == 1)
			{
				for (int k = i; k >= top; k--)
				{
					for (int p = 0; p < GAME_BACKGROUND_Y; p++)
					{
						gameSet.SetGameGround(k,p,gameSet.GetGameGround(k-1,p));
						gameSet.SetPos((p + 1) * 2, k);
						if (gameSet.GetGameGround(k, p) == 1)
							cout << "■";
						else cout << "  ";

					}
				}
				gameSet.SetScores();
				gameSet.ShowScore();
				
			}
		}
		currBlock = nextBlock;
		ChangeBlockX(0);
		ChangeBlockY(5);
		ClearNextBlock(gameSet);
		nextBlock = rand() % 15;
		ShowNextBlock(gameSet);
		return 0;
	}
	return 1;

}
void Block::ChangeGroundWhenArrive(GameSet& gameSet)
{
	int nx, ny;
	for (int i = 0; i < 4; i++)
	{
		nx = block_X + blockVariety[currBlock][2 * i];
		ny = block_Y + blockVariety[currBlock][2 * i + 1];
		gameSet.ChangeGround(nx, ny);
	}
}
void Block::DrawSpace(int x, int y, GameSet& gameSet)
{
	int nx, ny;
	for (int i = 0; i < 4; i++)
	{
		nx = x + blockVariety[currBlock][2 * i];
		ny = y + blockVariety[currBlock][2 * i + 1];
		gameSet.SetPos((ny + 1) * 2, nx);
		if (nx == 0)
			continue;
		cout << "  ";
	}


}
void Block::TurnShape(int num)
{
	switch (num)
	{
	case a1: currBlock = a2; break;					//条形互换
	case a2: currBlock = a1; break;

	case b: currBlock = b; break;					//方块无法旋转

	case c1: currBlock = c2; break;					//各种L形互换
	case c2: currBlock = c3; break;
	case c3: currBlock = c4; break;
	case c4: currBlock = c1; break;

	case d1: currBlock = d2; break;					//各种T形互换
	case d2: currBlock = d3; break;
	case d3: currBlock = d4; break;
	case d4: currBlock = d1; break;

	case e1: currBlock = e2; break;					//两种闪电形互换
	case e2: currBlock = e1; break;

	case f1: currBlock = f2; break;
	case f2: currBlock = f1; break;
	}
}
void Block::DrawBlock(GameSet& gameSet)
{
	int nx, ny;
	for (int i = 0; i < 4; i++)
	{
		nx = block_X + blockVariety[currBlock][2 * i];
		ny = block_Y + blockVariety[currBlock][2 * i + 1];
		gameSet.SetPos((ny + 1) * 2, nx);
		if (nx == 0)
		{
			gameSet.SetColor(3);
		}
		else
		{
			gameSet.SetColor(i);
		}
		cout << "■";
	}
	gameSet.SetColor(3);
}
GameSet::~GameSet()
{
	for (int i = 0; i < GAME_BACKGROUND_X; i++)
	{
		delete[] m_gameBackGround[i];
	}
	delete[] m_gameBackGround;

}
void Block::GetDirection(GameSet& gameSet)
{
	int temp = 0, containers, rightM = 0;
	if (_kbhit())
	{

		temp = _getch();
		if (isalpha(temp) && tolower(temp) == 'a' && block_Y >0&&(Judge(block_X,block_Y-1,gameSet) == 1))
		{
			DrawSpace(block_X, block_Y, gameSet);
			ChangeBlockY(block_Y - 1);
			DrawBlock(gameSet);
		}
		else if (isalpha(temp) && tolower(temp) == 'd')
		{
			for (int i = 0; i < 4; i++)
			{
				if (block_Y + blockVariety[currBlock][2 * i + 1] > rightM)
					rightM = block_Y + blockVariety[currBlock][2 * i + 1];
			}
			if (rightM < GAME_BACKGROUND_Y - 1 && (Judge(block_X, block_Y +  1, gameSet) == 1))
			{
				DrawSpace(block_X, block_Y, gameSet);
				ChangeBlockY(block_Y + 1);
				DrawBlock(gameSet);
			}

		}
		else if (isalpha(temp) && tolower(temp) == 's')
		{
			DrawSpace(block_X, block_Y, gameSet);
			ChangeBlockX(block_X + 1);
			DrawBlock(gameSet);
			if (IfBlockArrival(gameSet) != 1)
			{
				return;
			}
			/*for (int i = 0; i < 4; i++)
			{
				if (block_Y + blockVariety[currBlock][2 * i + 1] > rightM)
					rightM = block_Y + blockVariety[currBlock][2 * i + 1];
			}
			if (rightM < GAME_BACKGROUND_Y - 1)
			{
				DrawSpace(block_X, block_Y, gameSet);
				ChangeBlockY(block_Y + 1);
				DrawBlock(gameSet);*/
		}
		else if (isalpha(temp) && tolower(temp) == 'w' && block_Y < GAME_BACKGROUND_Y)
	{
		containers = currBlock;
		TurnShape(currBlock);
		if (Judge(block_X, block_Y, gameSet) == 0)
		{
			currBlock = containers;
		}
		else
		{
			currBlock = containers;
			DrawSpace(block_X, block_Y, gameSet);
			TurnShape(currBlock);
			DrawBlock(gameSet);

		}
		/*DrawSpace(gameSet);
		ChangeBlockY(block_Y + 1);
		DrawBlock(gameSet);*/
	}
	}
	

}
void GameSet::SetPos(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}
void GameSet::SetColor(int color_num)
{
	int n;
	switch (color_num)
	{
	case 0: n = 0x08; break;
	case 1: n = 0x0C; break;
	case 2: n = 0x0D; break;
	case 3: n = 0x0E; break;
	case 4: n = 0x0A; break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
}
void GameSet::ShowScore()
{
	SetPos(GAME_BACKGROUND_Y * 2 + 49, 4);
	cout << "得分:" << m_scores;
	SetPos(GAME_BACKGROUND_X + 2, GAME_BACKGROUND_Y + 2);
}
void Block::ShowNextBlock(GameSet& gameSet)
{
	int nx, ny, x, y;
	y = GAME_BACKGROUND_Y + 9, x = 7;
	gameSet.SetPos(GAME_BACKGROUND_Y * 2 + 16, 7);
	for (int i = 0; i < 4; i++)
	{
		gameSet.SetColor(i);
		nx = x + blockVariety[nextBlock][2 * i];
		ny = y + blockVariety[nextBlock][2 * i + 1];
		gameSet.SetPos(ny * 2, nx);
		cout << "■";
	}
}
void Block::ClearNextBlock(GameSet& gameSet)
{
	int nx, ny, x, y;
	y = GAME_BACKGROUND_Y + 9, x = 7;
	gameSet.SetPos(GAME_BACKGROUND_Y * 2 + 16, 7);
	for (int i = 0; i < 4; i++)
	{
		nx = x + blockVariety[nextBlock][2 * i];
		ny = y + blockVariety[nextBlock][2 * i + 1];
		gameSet.SetPos(ny * 2, nx);
		cout << "  ";
	}

}
void GameSet::GameRun(GameSet& gameSet, Block& block)
{
	int i = 0;
	block.ShowNextBlock(gameSet);
	while (1)
	{

		block.DrawBlock(gameSet);
		i = 0;
		while (i < 50)
		{
			block.GetDirection(gameSet);
			i++;
			Sleep(1);
		}
		if (block.IfBlockArrival(gameSet) == 1)
		{
			block.DrawSpace(block.GetBlockX(), block.GetBlockY(), gameSet);
			block.ChangeBlockX(block.GetBlockX() + 1);
		}
		else if (block.IfBlockArrival(gameSet) == -1)
		{
			system("cls");
			cout << "失败" << endl;
			break;
		}
		else if (block.IfBlockArrival(gameSet) == 2)
		{
			gameSet.ShowScore();
		}
	}
}
bool Block::Judge(int x, int y, GameSet& gameSet)
{
	int nx, ny;
	for (int i = 0; i < 4; i++)
	{
		nx = x + blockVariety[currBlock][2 * i];
		ny = y + blockVariety[currBlock][2 * i + 1];
		if (nx > GAME_BACKGROUND_X - 1 ||nx < 0 || ny > GAME_BACKGROUND_Y - 1||ny <0 || gameSet.JudgeIfZero(nx, ny) == 0)
		{
			return false;
		}
	}
	return true;
}
void GameSet::PrintGameGround()
{
	SetColor(3);
	SetPos(GAME_BACKGROUND_Y * 2 + 45, 2);
	cout << "■■■■■■■■■■";
	SetPos(GAME_BACKGROUND_Y * 2 + 45, 3);
	cout << "■                ■";
	SetPos(GAME_BACKGROUND_Y * 2 + 45, 4);
	cout << "■                ■";
	SetPos(GAME_BACKGROUND_Y * 2 + 49, 4);//展示分数：GAME_BACKGROUND_Y * 2 + 49,4
	cout << "得分:" << m_scores;
	SetPos(GAME_BACKGROUND_Y * 2 + 45, 5);
	cout << "■                ■";
	SetPos(GAME_BACKGROUND_Y * 2 + 45, 6);
	cout << "■                ■";
	SetPos(GAME_BACKGROUND_Y * 2 + 45, 7);
	cout << "■■■■■■■■■■";
	SetPos(GAME_BACKGROUND_Y * 2 + 13, 2);
	cout << "■■■■■■■■■■■";
	SetPos(GAME_BACKGROUND_Y * 2 + 13, 3);
	cout << "■                  ■";
	SetPos(GAME_BACKGROUND_Y * 2 + 18, 3);
	cout << "下一个方块:";
	SetPos(GAME_BACKGROUND_Y * 2 + 13, 4);
	cout << "■■■■■■■■■■■";
	SetPos(GAME_BACKGROUND_Y * 2 + 13, 5);
	cout << "■                  ■";
	SetPos(GAME_BACKGROUND_Y * 2 + 13, 6);//展示方块的位置（GAME_BACKGROUND_Y * 2 + 16，7）
	cout << "■                  ■";
	SetPos(GAME_BACKGROUND_Y * 2 + 13, 7);
	cout << "■                  ■";
	SetPos(GAME_BACKGROUND_Y * 2 + 13, 8);
	cout << "■                  ■";
	SetPos(GAME_BACKGROUND_Y * 2 + 13, 9);
	cout << "■                  ■";
	SetPos(GAME_BACKGROUND_Y * 2 + 13, 10);
	cout << "■                  ■";
	SetPos(GAME_BACKGROUND_Y * 2 + 13, 11);
	cout << "■                  ■";
	SetPos(GAME_BACKGROUND_Y * 2 + 13, 12);
	cout << "■■■■■■■■■■■";
	SetPos(0, 0);
	for (int i = 0; i < GAME_BACKGROUND_X + 1; i++)
	{
		for (int j = 0; j < GAME_BACKGROUND_Y + 2; j++)
		{
			if (i == 0 || i == GAME_BACKGROUND_X)
			{
				cout << "■";
			}
			else
			{
				if (j == 0 || j == GAME_BACKGROUND_Y + 1)
				{
					cout << "■";
				}
				else
				{
					cout << "  ";
				}
			}
		}
		cout << endl;
	}

}
int Block::SrandBlock()
{
	srand((unsigned int)time(NULL));
	return rand() % 15;
}
Block::Block()
{
	currBlock = SrandBlock();
	nextBlock = SrandBlock();
	block_X = 0;
	block_Y = 5;
	top = GAME_BACKGROUND_X;

}
Block::~Block()
{


}

