#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include "Snake.h"


/*
	1.建立蛇的结构体
	2.初始化蛇的位置和食物的位置
	3.开始游戏
		方向键的控制
		蛇碰到墙会结束
		蛇碰到身体结束
		蛇身体增长
		食物的再次初始化Init
		score增加
		设置速度



*/

void InitFood()
{
	Food[0] = rand() % WIDE;
	Food[1] = rand() % HIGH;

}

void InitSnake()
{
	//蛇有多少节
	snake.SIZE = 3;
	//蛇头位置初始化
	snake.body[0].X = WIDE / 2;
	snake.body[0].Y = HIGH / 2;
	//蛇身位置初始化
	snake.body[1].X = WIDE / 2;
	snake.body[1].Y = HIGH / 2 + 1;
	snake.body[2].X = WIDE / 2;
	snake.body[2].Y = HIGH / 2 + 2;


}

void InitWall()
{
	for (int i = 0; i <= HIGH; i++)
	{
		for (int j = 0; j <= WIDE; j++) {
			if (i==HIGH)
			{
				putchar('=');
			}
			else if (j == WIDE) {
				putchar('=');
			}
			else
			{
				putchar(' ');
			}
		}putchar('\n');
	}
	return;
}



void ShowUI()
{
	
	COORD coord;
	//将蛇的末尾设置为空' '
	coord.X = lx;
	coord.Y = ly;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar(' ');

	//显示蛇的位置
	for (int i = 0; i < snake.SIZE-1; i++)
	{
		coord.X = snake.body[i].X;
		coord.Y = snake.body[i].Y;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		if (i==0)
		{
			putchar('@');
		}
		else {
			putchar('*');
		}
	}
	
	coord.X = Food[0];
	coord.Y = Food[1];
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar('#');

	//显示得分
	coord.X = WIDE + 15;
	coord.Y = HIGH - 15;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("得分：%d", score);
	


}

void PlayGame()
{
	//方向键的控制
	char key = 'w';

	while (snake.body[0].X>=0&&snake.body[0].X<WIDE
		&&snake.body[0].Y>=0&&snake.body[0].Y<HIGH)
	{
		ShowUI();
		//方向控制
		while (_kbhit())
		{
			key = _getch();
		}
		switch (key)
		{
		case 'A': case 'a':dx = -1; dy = 0; break;
		case 'D': case 'd':dx = 1; dy = 0; break;
		case 'W': case 'w':dx = 0; dy = -1; break;
		case 'S': case 's':dx = 0; dy = 1; break;
		}
		for (int i = 1; i < snake.SIZE; i++)
		{
		//检测是否与自身碰撞
			if (snake.body[0].X==snake.body[i].X&&snake.body[0].Y==snake.body[i].Y)
			{
				return;
			}

		}
		//蛇吃到食物
		if (snake.body[0].X==Food[0]&&snake.body[0].Y==Food[1])
		{
			//随机食物
			InitFood();
			//蛇身体增长
			snake.SIZE++;
			//得分+10
			score += 20;
		}

		//蛇坐标更新
		lx = snake.body[snake.SIZE - 1].X;
		ly = snake.body[snake.SIZE - 1].Y;

		//蛇增长
		for ( int i = snake.SIZE-1; i >0; i--)
		{
			snake.body[i].X = snake.body[i - 1].X;
			snake.body[i].Y = snake.body[i - 1].Y;
		}
		//更新蛇头
		snake.body[0].X += dx;
		snake.body[0].Y += dy;
		Sleep(300);
		//sestem("cls");


	}
	return;

}



int main() {

	//设置随机数种子
	srand((size_t)time(NULL));

	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = sizeof(cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

	InitWall();
	InitFood();
	InitSnake();
	PlayGame();

	printf("\t游戏结束\n");
	getchar();

	

	return 0;

}