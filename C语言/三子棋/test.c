#define _CRT_SECURE_NO_WARNINGS

//������Ϸ

#include "game.h"

void menu()    //�˵�ѡ�� 
{
	printf("**********************\n");
	printf("** 1.����Ϸ  2.�˳� **\n");
	printf("**********************\n");
}

void game()  //������Ϸ����
{
	char board[ROW][COL] ; //���̵��к��У���ά����
	inboard( board,ROW,COL);  //��ʼ������
	play_board(board, ROW, COL);   //��ӡ����
	char ret = 0;//�����жϷ���ֵ

	while (1)
	{
		//�������
		playermove(board, ROW, COL);
		play_board(board, ROW, COL);   
		//�ж���Ӯ   ���Ӯ *  ����Ӯ#  ƽ��Q  ��Ϸ���� C
		ret = Iswin(board,ROW,COL);
		if (ret != 'C')
			break;
		//��������
		computermove(board, ROW, COL);
		play_board(board, ROW, COL);   
		ret = Iswin(board, ROW, COL);
		if (ret != 'C')
			break;
	}
	if (ret == 'Q')
	{
		printf("ƽ�֣�\n");
	}
	if (ret == '*')
	{
		printf("���Ӯ��\n");
	}
    if (ret == '#')
	{
		printf("����Ӯ��\n");
	}
	play_board(board, ROW, COL);

}
int main(void)
{
	int input;
	srand((unsigned int)time(NULL));

	do
	{
		menu();  //��ӡ�˵�������ѡ��
		printf("��ѡ��>");
		scanf("%d", &input);
		switch (input)
		{
		case 1: game();
			break;
		case 2: printf("�˳���Ϸ��\n");
			break;
		default:printf("�����������������룡\n");
			break;
		}

	} while (input);
	

	return 0;
}