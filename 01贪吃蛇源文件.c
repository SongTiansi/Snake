#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include "Snake.h"


/*
	1.�����ߵĽṹ��
	2.��ʼ���ߵ�λ�ú�ʳ���λ��
	3.��ʼ��Ϸ
		������Ŀ���
		������ǽ�����
		�������������
		����������
		ʳ����ٴγ�ʼ��Init
		score����
		�����ٶ�



*/

void InitFood()
{
	Food[0] = rand() % WIDE;
	Food[1] = rand() % HIGH;

}

void InitSnake()
{
	//���ж��ٽ�
	snake.SIZE = 3;
	//��ͷλ�ó�ʼ��
	snake.body[0].X = WIDE / 2;
	snake.body[0].Y = HIGH / 2;
	//����λ�ó�ʼ��
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
	//���ߵ�ĩβ����Ϊ��' '
	coord.X = lx;
	coord.Y = ly;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar(' ');

	//��ʾ�ߵ�λ��
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

	//��ʾ�÷�
	coord.X = WIDE + 15;
	coord.Y = HIGH - 15;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("�÷֣�%d", score);
	


}

void PlayGame()
{
	//������Ŀ���
	char key = 'w';

	while (snake.body[0].X>=0&&snake.body[0].X<WIDE
		&&snake.body[0].Y>=0&&snake.body[0].Y<HIGH)
	{
		ShowUI();
		//�������
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
		//����Ƿ���������ײ
			if (snake.body[0].X==snake.body[i].X&&snake.body[0].Y==snake.body[i].Y)
			{
				return;
			}

		}
		//�߳Ե�ʳ��
		if (snake.body[0].X==Food[0]&&snake.body[0].Y==Food[1])
		{
			//���ʳ��
			InitFood();
			//����������
			snake.SIZE++;
			//�÷�+10
			score += 20;
		}

		//���������
		lx = snake.body[snake.SIZE - 1].X;
		ly = snake.body[snake.SIZE - 1].Y;

		//������
		for ( int i = snake.SIZE-1; i >0; i--)
		{
			snake.body[i].X = snake.body[i - 1].X;
			snake.body[i].Y = snake.body[i - 1].Y;
		}
		//������ͷ
		snake.body[0].X += dx;
		snake.body[0].Y += dy;
		Sleep(300);
		//sestem("cls");


	}
	return;

}



int main() {

	//�������������
	srand((size_t)time(NULL));

	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = sizeof(cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

	InitWall();
	InitFood();
	InitSnake();
	PlayGame();

	printf("\t��Ϸ����\n");
	getchar();

	

	return 0;

}