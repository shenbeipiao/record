#define _CRT_SECURE_NO_WARNINGS

//测试游戏

#include "game.h"

void menu()    //菜单选项 
{
	printf("**********************\n");
	printf("** 1.新游戏  2.退出 **\n");
	printf("**********************\n");
}

void game()  //储存游戏数据
{
	char board[ROW][COL] ; //棋盘的行和列，二维数组
	inboard( board,ROW,COL);  //初始化棋盘
	play_board(board, ROW, COL);   //打印棋盘
	char ret = 0;//接受判断返回值

	while (1)
	{
		//玩家下棋
		playermove(board, ROW, COL);
		play_board(board, ROW, COL);   
		//判断输赢   玩家赢 *  电脑赢#  平局Q  游戏继续 C
		ret = Iswin(board,ROW,COL);
		if (ret != 'C')
			break;
		//电脑下棋
		computermove(board, ROW, COL);
		play_board(board, ROW, COL);   
		ret = Iswin(board, ROW, COL);
		if (ret != 'C')
			break;
	}
	if (ret == 'Q')
	{
		printf("平局！\n");
	}
	if (ret == '*')
	{
		printf("玩家赢！\n");
	}
    if (ret == '#')
	{
		printf("电脑赢！\n");
	}
	play_board(board, ROW, COL);

}
int main(void)
{
	int input;
	srand((unsigned int)time(NULL));

	do
	{
		menu();  //打印菜单，给出选项
		printf("请选择：>");
		scanf("%d", &input);
		switch (input)
		{
		case 1: game();
			break;
		case 2: printf("退出游戏！\n");
			break;
		default:printf("数据有误，请重新输入！\n");
			break;
		}

	} while (input);
	

	return 0;
}