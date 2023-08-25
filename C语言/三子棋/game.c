
#define _CRT_SECURE_NO_WARNINGS
//实现游戏
#include "game.h"

void inboard(char board[ROW][COL], int row,int col)
{
	int i = 0;
	int j = 0;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			board[i][j] = ' ';  //初始化棋盘，打印空格
		}
	}
}

void play_board(char board[ROW][COL], int row, int col)  //打印棋盘
{
	int i = 0;
	int j = 0;

	for (i = 0; i < row; i++)   //行
	{
		for (j = 0; j < col; j++)  //列
		{
			printf(" %c ", board[i][j]);
			if (j < col - 1)
				printf("|");
		 }
		printf("\n");
		if (i < row - 1)
		{
			for (j = 0; j < col; j++)
			{
				printf("---");
				if (j < col - 1)
				{
					printf("|");
				}
			}
		}
		printf("\n");
	}

}

void playermove(char board[ROW][COL], int row, int col) // 玩家下棋
{
	int x = 0;
	int y = 0;

	printf("玩家走:>\n");

	while (1)
	{
		printf("请输入落子坐标:>");
		scanf("%d%d", &x, &y);
		//判断坐标合法性
		if (x >= 1 && x <= col && y <= col && y >= 1)
		{
			//判断该坐标是否被占用
			if (board[x - 1][y - 1] == ' ')
			{
				board[x - 1][y - 1] = '*';
				break;
		    }
			else
			{
				printf("该坐标已被占用,请重新输入！\n");
			}
		}
		else
		{
			printf("输入坐标有误，请重新输入！\n");
		}
	}
}

void computermove(char board[ROW][COL], int row, int col)
{
	printf("电脑走:>\n");

	while (1)
	{
		int x = rand() % row;
		int y = rand() % col;
		if (board[x][y] == ' ')
		{
			board[x][y] = '#';
			break;
		}
	}
}

int Isfull(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
				return 0;
		}
	}
	return 1;
}
//判断输赢  
char Iswin(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	//判断行
	for (i = 0; i < col; i++)
	{
		if (board[i][0] == board[i][1] &&board[i][1]==board[i][2] && board[i][2] != ' ')
			return board[0][i];
	}
	//判断列
	for (i = 0; i < row; i++)
	{
		if (board[0][i] == board[1][i]&& board[1][i]==board[2][i] && board[1][i] != ' ')
			return board[0][i];
	}
	//判断对角线
	if (board[0][0]== board[1][1] && board[1][1] == board[2][2] && board[1][1]!=' ')
		return board[1][1];
	if (board[0][2]== board[1][1] && board[1][1] == board[2][0] && board[1][1]!=' ')
		return board[1][1];
    //判断平局   棋盘满了则返回1，否则返回0
	int ret = Isfull(board, row, col);
	if (ret == 1)
	{
		ret = 'Q';
		return ret;
	}
	//游戏继续
	return 'C';
}