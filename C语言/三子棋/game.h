#pragma once
//ͷ�ļ�����
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROW 3
#define COL 3  //  ���ŵĶ��� ���̵��к���

//����������
void inboard(char board[ROW][COL], int row, int col); // ��ʼ������
void play_board(char board[ROW][COL], int row, int col); //��ӡ����
void playermove(char board[ROW][COL], int row, int col); // �������
void computermove(char board[ROW][COL], int row, int col); // ��������
char Iswin(char board[ROW][COL], int row, int col);//�ж���Ӯ   ���Ӯ *  ����Ӯ#  ƽ��Q  ��Ϸ���� C