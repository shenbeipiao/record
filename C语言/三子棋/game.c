
#define _CRT_SECURE_NO_WARNINGS
//ʵ����Ϸ
#include "game.h"

void inboard(char board[ROW][COL], int row,int col)
{
	int i = 0;
	int j = 0;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			board[i][j] = ' ';  //��ʼ�����̣���ӡ�ո�
		}
	}
}

void play_board(char board[ROW][COL], int row, int col)  //��ӡ����
{
	int i = 0;
	int j = 0;

	for (i = 0; i < row; i++)   //��
	{
		for (j = 0; j < col; j++)  //��
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

void playermove(char board[ROW][COL], int row, int col) // �������
{
	int x = 0;
	int y = 0;

	printf("�����:>\n");

	while (1)
	{
		printf("��������������:>");
		scanf("%d%d", &x, &y);
		//�ж�����Ϸ���
		if (x >= 1 && x <= col && y <= col && y >= 1)
		{
			//�жϸ������Ƿ�ռ��
			if (board[x - 1][y - 1] == ' ')
			{
				board[x - 1][y - 1] = '*';
				break;
		    }
			else
			{
				printf("�������ѱ�ռ��,���������룡\n");
			}
		}
		else
		{
			printf("���������������������룡\n");
		}
	}
}

void computermove(char board[ROW][COL], int row, int col)
{
	printf("������:>\n");

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
//�ж���Ӯ  
char Iswin(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	//�ж���
	for (i = 0; i < col; i++)
	{
		if (board[i][0] == board[i][1] &&board[i][1]==board[i][2] && board[i][2] != ' ')
			return board[0][i];
	}
	//�ж���
	for (i = 0; i < row; i++)
	{
		if (board[0][i] == board[1][i]&& board[1][i]==board[2][i] && board[1][i] != ' ')
			return board[0][i];
	}
	//�ж϶Խ���
	if (board[0][0]== board[1][1] && board[1][1] == board[2][2] && board[1][1]!=' ')
		return board[1][1];
	if (board[0][2]== board[1][1] && board[1][1] == board[2][0] && board[1][1]!=' ')
		return board[1][1];
    //�ж�ƽ��   ���������򷵻�1�����򷵻�0
	int ret = Isfull(board, row, col);
	if (ret == 1)
	{
		ret = 'Q';
		return ret;
	}
	//��Ϸ����
	return 'C';
}