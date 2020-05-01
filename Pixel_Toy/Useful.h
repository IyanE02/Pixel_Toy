#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <mmsystem.h>
#include <Digitalv.h>
#include <process.h>

#pragma comment(lib, "winmm.lib")

/*
 *	Useful.c
 */
typedef enum
{
    NOCURSOR,
    SOLIDCURSOR,
    NORMALCURSOR
} CURSOR_TYPE;

void RemoveScrollbar();
void SetWindow(int Width, int Height);
void Gotoxy(int x, int y);
void Gotoxy_(int x, int y);
void TextColor(int color_number);
void SetCursorType(CURSOR_TYPE c);
void Click(int* x, int* y);
void Click_(int* x, int* y);
void Click__(int* x, int* y);
int BeInput();
int GetInput(WORD* vkey, COORD* pos);

const int kBlack = 0;
const int kBlue = 1;
const int kGreen = 2;
const int kAqua = 3;
const int kRed = 4;
const int kPurple = 5;
const int kYellow = 6;
const int kWhite = 7;
const int kGray = 8;
const int kLBlue = 9;
const int kLGreen = 10;
const int kLAqua = 11;
const int kLRed = 12;
const int kLPurple = 13;
const int kLYellow = 14;
const int kLWhite = 15;

/*textcolor(0x�������ڻ�)
0 = ������       8 = ȸ��
1 = �Ķ���       9 = ���� �Ķ���
2 = �ʷϻ�       A = ���� �ʷϻ�
3 = ����         B = ���� ����
4 = ������       C = ���� ������
5 = ���ֻ�       D = ���� ���ֻ�
6 = �����       E = ���� �����
7 = ���         F = ���� ���*/