#pragma once
//头文件包含
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROW 3
#define COL 3  //  符号的定义 棋盘的行和列

//函数的声明
void inboard(char board[ROW][COL], int row, int col); // 初始化棋盘
void play_board(char board[ROW][COL], int row, int col); //打印棋盘
void playermove(char board[ROW][COL], int row, int col); // 玩家下棋
void computermove(char board[ROW][COL], int row, int col); // 电脑下棋
char Iswin(char board[ROW][COL], int row, int col);//判断输赢   玩家赢 *  电脑赢#  平局Q  游戏继续 C