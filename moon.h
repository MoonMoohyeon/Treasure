#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define LOWC 22
#define LOWR 12
#define MIDC 32
#define MIDR 17
#define HIGHC 42
#define HIGHR 22

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 13

#define WALL -1
#define EMPTY 0
#define FAKE1 1
#define FAKE2 2
#define FAKE3 3
#define FLAG 8
#define CUR 9

#ifndef __COLOR_LIST_
#define __COLOR_LIST_

enum
{
    black,
    blue,
    green,
    cyan,
    red,
    purple,
    brown,
    lightgray,
    darkgray,
    lightblue,
    lightgreen,
    lightcyan,
    lightred,
    lightpurple,
    yellow,
    white
};

#endif

void setColor(INT, INT);
void SetConsoleView();
void gotoxy(int x, int y);

// - 과제 주요 기능 작성
// - 주요 기능 구현을 위한 기술적 상세 명세 (주요 코드 중심 방법론 설명)

// 이윤희
// 메인 메뉴, 난이도 선택 메뉴, 리더보드 메뉴, 배경 스토리
void showMenu();
int selectDifficulty();
void LBMenu();
void story();

// 박준성
// 게임 클리어시 다음 난이도 자동 이동, 리더보드 출력, 알림창 출력
void alert(char words[]);
void winLevel(int dif);
void LeaderBoard(int dif);

// 문무현
// 맵 생성 및 출력, 깃발 초기화
void createMap();
void makeFlag(int dif);
void showMap(int dif);

// 문신혁
// 리더보드 파일 입출력, 커서 이동
void SetLBFiles();
void Insert(int array[][2], int loc, int val1, int val2);
void inGameCursor(int dif);

// 각자 토의 사항 의견 작성할 것

void PLAY();
void loseLevel();
void howToPlay();