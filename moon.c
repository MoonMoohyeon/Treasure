#include "moon.h"

// 난이도 별 맵
int Map1[LOWR][LOWC];
int Map2[MIDR][MIDC];
int Map3[HIGHR][HIGHC];

// 방향키 이동을 반환받는 변수
int ch;

// 커서 위치
int cursorX = 0;
int cursorY = 0;

// 플레이어의 현재 위치
int playerX = 1;
int playerY = 1;

// 아이템(깃발 등) 위치 구조체
typedef struct itempos
{
    int x;
    int y;
} item_S;
item_S item[200];

// 아이템의 개수
int max;
int flag;

// 게임오버 조건
int starttime;
int timelimit;
int movecount;

// 리더보드 파일 포인터
FILE* fp1;
FILE* fp2;
FILE* fp3;

// 리더보드 배열
int LB1[10][2] = { 0 };
int LB2[10][2] = { 0 };
int LB3[10][2] = { 0 };

void setColor(int forground, int background) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int code = forground + background * 16;
    SetConsoleTextAttribute(consoleHandle, code);
}


void alert(char words[]) {
    setColor(white, white);
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■\n■");
    setColor(white, black);
    printf("%50s", "");
    setColor(white, white);
    printf("■\n■");
    setColor(white, black);
    printf("%-50s", words);
    setColor(white, white);
    printf("■\n■");
    setColor(white, black);
    printf("%50s", "");
    setColor(white, white);
    printf("■\n■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    setColor(white, black);
}

void CursorView()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}


void SetConsoleView()
{
    system("mode con:cols=120 lines=32");
    system("title Chess");
}

void gotoxy(int x, int y)
{
    COORD Pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void LeaderBoard(int dif)
{
    int tmp1, tmp2;
    char ch;

    system("cls");
    printf("LeaderBoard\n\n");

    switch (dif)
    {
    case 0:
        fp1 = fopen("LB1.txt", "r");
        printf(" ┌──────┬──────────────┬───────────────────┐\n");
        printf(" │ 등수 │ 남은 시간(초)│ 남은 이동횟수(번) │ \n ");
        for (int i = 0; i < 10; i++)
        {
            fscanf(fp1, "%d %d\n", &tmp1, &tmp2);
            //         printf("[%3d 위]  남은시간 : %3d,   남은이동횟수 : %3d\n", i + 1, tmp1, tmp2);
            printf("│──────│──────────────│───────────────────┤\n");
            printf(" │ %4d │  %10d  │  %16d │ \n ", i + 1, tmp1, tmp2);
        }
        printf("└──────┴──────────────┴───────────────────┘\n");
        fclose(fp1);
        printf("\n\n 나가려면 ENTER를 누르세요.");
        while (1)
        {
            ch = _getch();
            if (ch == ENTER)
            {
                break;
            }
        }
        showMenu();
        break;
    case 1:
        fp2 = fopen("LB2.txt", "r");
        printf(" ┌──────┬──────────────┬───────────────────┐\n");
        printf(" │ 등수 │ 남은 시간(초)│ 남은 이동횟수(번) │ \n ");
        for (int i = 0; i < 10; i++)
        {
            fscanf(fp2, "%d %d\n", &tmp1, &tmp2);
            //         printf("[%3d 위]  남은시간 : %3d,   남은이동횟수 : %3d\n", i + 1, tmp1, tmp2);
            printf("│──────│──────────────│───────────────────┤\n");
            printf(" │ %4d │  %10d  │  %16d │ \n ", i + 1, tmp1, tmp2);
        }
        printf("└──────┴──────────────┴───────────────────┘\n");
        fclose(fp2);
        printf("\n\n 나가려면 ENTER를 누르세요.");
        while (1)
        {
            ch = _getch();
            if (ch == ENTER)
            {
                break;
            }
        }
        showMenu();
        break;
    case 2:
        fp3 = fopen("LB3.txt", "r");
        printf(" ┌──────┬──────────────┬───────────────────┐\n");
        printf(" │ 등수 │ 남은 시간(초)│ 남은 이동횟수(번) │ \n ");
        for (int i = 0; i < 10; i++)
        {
            fscanf(fp3, "%d %d\n", &tmp1, &tmp2);
            //         printf("[%3d 위]  남은시간 : %3d,   남은이동횟수 : %3d\n", i + 1, tmp1, tmp2);
            printf("│──────│──────────────│───────────────────┤\n");
            printf(" │ %4d │  %10d  │  %16d │ \n ", i + 1, tmp1, tmp2);
        }
        printf("└──────┴──────────────┴───────────────────┘\n");
        fclose(fp3);
        printf("\n\n 나가려면 ENTER를 누르세요.");
        while (1)
        {
            ch = _getch();
            if (ch == ENTER)
            {
                break;
            }
        }
        showMenu();
        break;
    }
}

void Insert(int array[][2], int loc, int val1, int val2)
{
    for (int i = 8; i >= loc; i--)
    {
        array[i + 1][0] = array[i][0];
        array[i + 1][1] = array[i][1];
    }
    array[loc][0] = val1;
    array[loc][1] = val2;
}

void SetLBFiles()
{
    if ((fp1 = fopen("LB1.txt", "r")) == NULL)
    {
        fp1 = fopen("LB1.txt", "w+");
        for (int i = 0; i < 10; i++)
        {
            fprintf(fp1, "%d %d\n", 0, 0);
        }
        fclose(fp1);
    }
    fp1 = fopen("LB1.txt", "r");
    for (int i = 0; i < 10; i++)
    {
        fscanf(fp1, "%d %d\n", &LB1[i][0], &LB1[i][1]);
    }
    fclose(fp1);

    if ((fp2 = fopen("LB2.txt", "r")) == NULL)
    {
        fp2 = fopen("LB2.txt", "w+");
        for (int i = 0; i < 10; i++)
        {
            fprintf(fp2, "%d %d\n", 0, 0);
        }
        fclose(fp2);
    }
    fp2 = fopen("LB2.txt", "r");
    for (int i = 0; i < 10; i++)
    {
        fscanf(fp2, "%d %d\n", &LB2[i][0], &LB2[i][1]);
    }
    fclose(fp2);

    if ((fp3 = fopen("LB3.txt", "r")) == NULL)
    {
        fp3 = fopen("LB3.txt", "w+");
        for (int i = 0; i < 10; i++)
        {
            fprintf(fp3, "%d %d\n", 0, 0);
        }
        fclose(fp3);
    }
    fp3 = fopen("LB3.txt", "r");
    for (int i = 0; i < 10; i++)
    {
        fscanf(fp3, "%d %d\n", &LB3[i][0], &LB3[i][1]);
    }
    fclose(fp3);
}

// 게임 실행
void PLAY()
{
    CursorView();
    SetLBFiles();
    SetConsoleView();
    story();
    createMap();
    showMenu();
}

void LBMenu()
{
    system("cls");
    gotoxy(31, 8);
    printf("    ■■■   ■      ■    ■■■■    ■■■■    ■■■■    \n");
    gotoxy(31, 9);
    printf(" ■          ■      ■    ■        ■          ■           \n");
    gotoxy(31, 10);
    printf("■           ■■■■■    ■■■■    ■ ■ ■    ■ ■ ■    \n");
    gotoxy(31, 11);
    printf(" ■          ■      ■    ■                 ■          ■   \n");
    gotoxy(31, 12);
    printf("    ■■■   ■      ■    ■■■■    ■■■■    ■■■■    \n\n");
    gotoxy(50, 20);
    printf("Quarter Final LeaderBoard\n");
    gotoxy(50, 21);
    printf("Semi Final LeaderBoard\n");
    gotoxy(50, 22);
    printf("The Final LeaderBoard\n");
    gotoxy(50, 23);
    printf("M E N U\n");
    cursorX = 48;
    cursorY = 20;
    while (1)
    {
        gotoxy(cursorX, cursorY);
        printf("*");
        ch = _getch();
        if (ch == ENTER)
        {
            int sel = cursorY - 20;
            if (sel == 0)
            {
                LeaderBoard(0);
            }
            if (sel == 1)
            {
                LeaderBoard(1);
            }
            if (sel == 2)
            {
                LeaderBoard(2);
            }
            if (sel == 3)
            {
                showMenu();
            }
            break;
        }
        if (ch == 224)
        {
            ch = _getch();
            switch (ch)
            {
            case UP:
                if (cursorY > 20)
                {
                    cursorY--;
                }
                break;
            case DOWN:
                if (cursorY < 23)
                {
                    cursorY++;
                }
                break;
            }
        }
        printf("\b ");
    }
}

void showMenu()
{
    system("cls");
    gotoxy(31, 8);
    printf("    ■■■   ■      ■    ■■■■    ■■■■    ■■■■    \n");
    gotoxy(31, 9);
    printf(" ■          ■      ■    ■        ■          ■           \n");
    gotoxy(31, 10);
    printf("■           ■■■■■    ■■■■    ■ ■ ■    ■ ■ ■    \n");
    gotoxy(31, 11);
    printf(" ■          ■      ■    ■                 ■          ■   \n");
    gotoxy(31, 12);
    printf("    ■■■   ■      ■    ■■■■    ■■■■    ■■■■    \n\n");
    gotoxy(52, 20);
    printf("게 임 시 작\n");
    gotoxy(52, 21);
    printf("게 임 방 법\n");
    gotoxy(52, 22);
    printf("리 더 보 드\n");
    gotoxy(52, 23);
    printf("게 임 종 료\n");
    const int CURSOR_X = 50;
    const int CURSOR_Y_MIN = 20;
    const int CURSOR_Y_MAX = 23;
    cursorX = CURSOR_X;
    cursorY = CURSOR_Y_MIN;

    while (1)
    {
        gotoxy(cursorX, cursorY);
        printf("*");
        ch = _getch();
        if (ch == ENTER)
        {
            int sel = cursorY - CURSOR_Y_MIN;
            switch (sel)
            {
            case 0:
                playerX = playerY = 1;
                int dif = selectDifficulty();
                makeFlag(dif);
                inGameCursor(dif);
                break;
            case 1:
                howToPlay();
                break;
            case 2:
                LBMenu();
                break;
            case 3:
                exit(0);

            default:
                break;
            }
            break;
        }
        if (ch == 0xE0)
        {
            printf("\b ");
            ch = _getch();
            switch (ch)
            {
            case UP:
                if (cursorY > CURSOR_Y_MIN)
                {
                    cursorY--;
                }
                break;
            case DOWN:
                if (cursorY < CURSOR_Y_MAX)
                {
                    cursorY++;
                }
                break;
            }
        }
    }
}

int selectDifficulty()
{
    system("cls");
    gotoxy(31, 8);
    printf("    ■■■   ■      ■    ■■■■    ■■■■    ■■■■    \n");
    gotoxy(31, 9);
    printf(" ■          ■      ■    ■        ■          ■           \n");
    gotoxy(31, 10);
    printf("■           ■■■■■    ■■■■    ■ ■ ■    ■ ■ ■    \n");
    gotoxy(31, 11);
    printf(" ■          ■      ■    ■                 ■          ■   \n");
    gotoxy(31, 12);
    printf("    ■■■   ■      ■    ■■■■    ■■■■    ■■■■    \n\n");
    gotoxy(52, 20);
    printf("Quarter Final\n");
    gotoxy(52, 21);
    printf("Semi Final\n");
    gotoxy(52, 22);
    printf("The Final\n");
    gotoxy(52, 23);
    printf("M E N U\n");
    const int CURSOR_X = 50;
    const int CURSOR_Y_MIN = 20;
    const int CURSOR_Y_MAX = 23;
    cursorX = CURSOR_X;
    cursorY = CURSOR_Y_MIN;
    while (1)
    {
        gotoxy(cursorX, cursorY);
        printf("*");
        ch = _getch();
        if (ch == ENTER)
        {
            if (cursorY - CURSOR_Y_MIN == 3)
                showMenu();
            else
                return cursorY - CURSOR_Y_MIN;
            break;
        }
        if (ch == 0xE0)
        {
            ch = _getch();
            switch (ch)
            {
            case UP:
                if (cursorY > CURSOR_Y_MIN)
                {
                    cursorY--;
                }
                break;
            case DOWN:
                if (cursorY < CURSOR_Y_MAX)
                {
                    cursorY++;
                }
                break;
            }
        }
        printf("\b ");
    }
}

void story()
{
    char ch;

    printf("\n\n\n\n\n          ");
    char* script = "체스 토너먼트에 진출한 당신은 강적을 만나 수세에 몰렸습니다.\n          전세는 점점 불리해지고 평가치는 점점 떨어져 가고 있습니다. \n          \
당신은 정신을 집중하여 수를 읽기 시작하고, 생각의 미로 속으로 빠져듭니다... \n          상황을 극복하려면 평범한 수로는 부족합니다. \n          상대를 제압하는 결정적인 묘수를 찾아낼 수 있을까요?\n\t\t";
    int length = strlen(script);
    for (int i = 0; i < length; i++)
    {
        if (_kbhit()) {
            ch = _getch();
            if (ch == 224) {
                ch = _getch();
            }

            return;
        }
        printf("%c", script[i]);
        Sleep(5);
    }
    system("pause");
}

void howToPlay()
{
    system("cls");
    printf("\n\n\n\n\n                                   ===== 게 임 방 법 =====\n\n");
    char* script = "          더 불리해지기 전에 상황을 타개할 한 수를 찾아야 합니다.\n          머릿속에 떠오르는 수들 중 역전의 묘수가 숨겨져 있을 것입니다. \n          \
당신의 생각은 ◆으로 표시되며, 가능성이 높은 수들은 ▶으로 표시됩니다.\n          하지만 당신이 최선이라고 생각한 수가 패배를 부르는 블런더가 될 수도 있습니다. \n          \
서두르십시오. 당신이 생각하는 동안 시간이 흐르고 있습니다! \n\n                              PRESS ANY KEY TO GO TO THE MENU";
    printf("%s", script);
    ch = _getch();
    if (ch)
    {
        showMenu();
    }
}

void winLevel(int dif)
{
    int t, score;
    t = timelimit + starttime - time(0);
    score = t + movecount;

    createMap();
    if (dif == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            if (score > LB1[i][0] + LB1[i][1])
            {
                Insert(LB1, i, t, movecount);
                break;
            }
        }
        fp1 = fopen("LB1.txt", "w");
        for (int i = 0; i < 10; i++)
        {
            fprintf(fp1, "%d %d\n", LB1[i][0], LB1[i][1]);
        }
        fclose(fp1);

        system("cls");
        printf("\n\n\n\n\n          Great move!!!\n          You will advance to the Semi Final round.", dif + 1);
        printf("\n\n          PRESS ANY KEY TO MOVE ON TO THE NEXT ROUND");
        ch = _getch();
        if (ch)
        {
            makeFlag(dif + 1);
            inGameCursor(dif + 1);
        }
    }
    else if (dif == 1)
    {
        for (int i = 0; i < 10; i++)
        {
            if (score > LB2[i][0] + LB2[i][1])
            {
                Insert(LB2, i, t, movecount);
                break;
            }
        }
        fp2 = fopen("LB2.txt", "w");
        for (int i = 0; i < 10; i++)
        {
            fprintf(fp2, "%d %d\n", LB2[i][0], LB2[i][1]);
        }
        fclose(fp2);

        system("cls");
        printf("\n\n\n\n\n          Brilliant move!!!\n          You will advance to the Final round.", dif + 1);
        printf("\n\n          PRESS ANY KEY TO MOVE ON TO THE NEXT ROUND");
        ch = _getch();
        if (ch)
        {
            makeFlag(dif + 1);
            inGameCursor(dif + 1);
        }
    }
    else if (dif == 2)
    {
        for (int i = 0; i < 10; i++)
        {
            if (score > LB3[i][0] + LB3[i][1])
            {
                Insert(LB3, i, t, movecount);
                break;
            }
        }
        fp3 = fopen("LB3.txt", "w");
        for (int i = 0; i < 10; i++)
        {
            fprintf(fp3, "%d %d\n", LB3[i][0], LB3[i][1]);
        }
        fclose(fp3);

        system("cls");
        printf("\n\n\n\n\n                                             !!\n");
        printf("          당신은 놀라운 수를 거듭하여 불리한 상황을 역전하고 우승을 차지했습니다.\n");
        printf("          성공의 경험을 기억하며, 끊임 없이 정진하여 또다른 성공을 거두길 바랍니다!\n");
        printf("\n\n                              PRESS ANY KEY TO GO TO THE MENU");
        ch = _getch();
        if (ch)
        {
            showMenu();
        }
    }
}

void loseLevel()
{
    createMap();
    system("cls");
    printf("\n\n\n\n\n          아쉽지만 묘수를 찾아내지 못하고 상대방에게 패배했습니다.\n");
    printf("          이번 토너먼트는 여기까지지만, 다시 우승에 도전할 기회가 있을 것입니다.\n");
    printf("          기회가 찾아올 때까지 노력을 멈추지 마십시오.\n");
    printf("          한 칸씩 전진한 폰이 퀸이 되듯이 왕관을 쓰게 될 것입니다.\n");
    printf("\n\n                    PRESS ANY KEY TO GO TO THE MENU");
    ch = _getch();
    if (ch)
    {
        showMenu();
    }
}

void showMap(int dif)
{
    system("cls");
    switch (dif)
    {
    case 0:
    {
        for (int i = 0; i < LOWR; i++)
        {
            for (int j = 0; j < LOWC; j++)
            {
                if (Map1[i][j] == WALL) {
                    //setColor(purple, purple);
                    printf("▦");
                    //setColor(darkgray, black);
                }
                else if (Map1[i][j] == EMPTY) {
                    printf("  ");
                }
                else if (Map1[i][j] == FLAG)
                {
                    printf("▶");
                }
                else if (Map1[i][j] == FAKE1 || Map1[i][j] == FAKE2 || Map1[i][j] == FAKE3)
                {
                    printf("▶");
                }
                /*else if (playerX == j && playerY == i)
                   printf("◆");*/
                else {
                    //setColor(darkgray, darkgray);
                    printf("  ");
                    //setColor(white, black);
                }
            }
            printf("\n");
        }
    }
    break;

    case 1:
    {
        for (int i = 0; i < MIDR; i++)
        {
            for (int j = 0; j < MIDC; j++)
            {
                if (Map2[i][j] == WALL) {
                    //setColor(purple, purple);
                    printf("▦");
                    //setColor(darkgray, black);
                }
                else if (Map2[i][j] == EMPTY)
                    printf("  ");
                else if (Map2[i][j] == FLAG)
                    printf("▶");
                else if (Map2[i][j] == FAKE1 || Map2[i][j] == FAKE2 || Map2[i][j] == FAKE3)
                    printf("▶");
                /*else if (playerX == j && playerY == i)
                   printf("◆");*/
                else
                    printf("  ");
            }
            printf("\n");
        }
    }
    break;

    case 2:
    {
        for (int i = 0; i < HIGHR; i++)
        {
            for (int j = 0; j < HIGHC; j++)
            {
                if (Map3[i][j] == WALL) {
                    //setColor(purple, purple);
                    printf("▦");
                    //setColor(darkgray, black);
                }
                else if (Map3[i][j] == EMPTY)
                    printf("  ");
                else if (Map3[i][j] == FLAG)
                    printf("▶");
                else if (Map3[i][j] == FAKE1 || Map3[i][j] == FAKE2 || Map3[i][j] == FAKE3)
                    printf("▶");
                /*else if (playerX == j && playerY == i)
                   printf("◆");*/
                else
                    printf("  ");
            }
            printf("\n");
        }
    }
    break;
    }
}

void inGameCursor(int dif)
{
    int mapX, mapY, tmpY;
    char* blunder = "블런더! 상황이 악화됩니다.";
    char* good = "괜찮은 수를 두었습니다. 생각할 기회가 늘었습니다.";
    char* bad = "나쁜 수를 두었습니다. 생각할 기회가 줄었습니다.";

    if (dif == 0)
    {
        movecount = 70;
        timelimit = 20;
        starttime = time(0);

        playerX = 2;
        playerY = 1;
        mapX = mapY = 1;
        //Map1[playerY][playerX] = CUR;
        system("cls");
        showMap(dif);
        while (1)
        {

            gotoxy(60, 26);
            printf("남은시간: %d   ", (timelimit + starttime - time(0)));
            gotoxy(60, 28);
            printf("남은 이동횟수: %d   ", movecount);

            gotoxy(playerX, playerY);
            printf("◆");

            if (_kbhit()) {
                ch = _getch();
                if (ch == 224)
                {
                    ch = _getch();
                    switch (ch)
                    {
                    case UP:
                        mapY--;
                        tmpY = playerY - 1;
                        if (Map1[mapY][mapX] == WALL) {
                            mapY++;
                        }
                        else {
                            playerY--;
                        }
                        break;
                    case DOWN:
                        mapY++;
                        tmpY = playerY + 1;
                        if (Map1[mapY][mapX] == WALL) {
                            mapY--;
                        }
                        else {
                            playerY++;
                        }
                        break;
                    case LEFT:
                        mapX--;
                        tmpY = playerY;
                        if (Map1[mapY][mapX] == WALL) {
                            mapX++;
                        }
                        else {
                            playerX -= 2;
                        }
                        break;
                    case RIGHT:
                        mapX++;
                        tmpY = playerY;
                        if (Map1[mapY][mapX] == WALL) {
                            mapX--;
                        }
                        else {
                            playerX += 2;
                        }
                        break;
                    }
                    printf("\b\b  ");
                    if (Map1[mapY][mapX] == FLAG) {
                        winLevel(dif);
                    }
                    if (Map1[mapY][mapX] == FAKE1) {
                        Map1[mapY][mapX] = EMPTY;
                        gotoxy(playerX, tmpY);
                        printf("  ");
                        playerX = 2;
                        playerY = 1;
                        mapX = mapY = 1;
                        gotoxy(0, 25);
                        alert(blunder);
                    }
                    if (Map1[mapY][mapX] == FAKE2)
                    {
                        Map1[mapY][mapX] = EMPTY;
                        movecount += 10;
                        timelimit += 5;
                        gotoxy(0, 25);
                        alert(good);
                    }
                    if (Map1[mapY][mapX] == FAKE3)
                    {
                        Map1[mapY][mapX] = EMPTY;
                        movecount -= 5;
                        gotoxy(0, 25);
                        alert(bad);
                    }
                }

                if (movecount <= 0)
                {
                    loseLevel();
                    break;
                }
                movecount--;
            }
            if (timelimit + starttime - time(0) <= 0)
            {
                loseLevel();
                break;
            }
        }
    }
    else if (dif == 1)
    {
        movecount = 110;
        timelimit = 30;
        starttime = time(0);

        playerX = 2;
        playerY = 1;
        mapX = mapY = 1;
        //Map1[playerY][playerX] = CUR;
        system("cls");
        showMap(dif);
        while (1)
        {

            gotoxy(60, 26);
            printf("남은시간: %d    ", (timelimit + starttime - time(0)));
            gotoxy(60, 28);
            printf("남은 이동횟수: %d   ", movecount);

            gotoxy(playerX, playerY);
            printf("◆");

            if (_kbhit()) {
                ch = _getch();
                if (ch == 224)
                {
                    ch = _getch();
                    switch (ch)
                    {
                    case UP:
                        mapY--;
                        tmpY = playerY - 1;
                        if (Map2[mapY][mapX] == WALL) {
                            mapY++;
                        }
                        else {
                            playerY--;
                        }
                        break;
                    case DOWN:
                        mapY++;
                        tmpY = playerY + 1;
                        if (Map2[mapY][mapX] == WALL) {
                            mapY--;
                        }
                        else {
                            playerY++;
                        }
                        break;
                    case LEFT:
                        mapX--;
                        tmpY = playerY;
                        if (Map2[mapY][mapX] == WALL) {
                            mapX++;
                        }
                        else {
                            playerX -= 2;
                        }
                        break;
                    case RIGHT:
                        mapX++;
                        tmpY = playerY;
                        if (Map2[mapY][mapX] == WALL) {
                            mapX--;
                        }
                        else {
                            playerX += 2;
                        }
                        break;
                    }
                    printf("\b\b  ");
                    if (Map2[mapY][mapX] == FLAG) {
                        winLevel(dif);
                    }
                    if (Map2[mapY][mapX] == FAKE1) {
                        Map2[mapY][mapX] = EMPTY;
                        gotoxy(playerX, tmpY);
                        printf("  ");
                        playerX = 2;
                        playerY = 1;
                        mapX = mapY = 1;
                        gotoxy(0, 25);
                        alert(blunder);
                    }
                    if (Map2[mapY][mapX] == FAKE2)
                    {
                        Map1[mapY][mapX] = EMPTY;
                        movecount += 10;
                        timelimit += 5;
                        gotoxy(0, 25);
                        alert(good);
                    }
                    if (Map2[mapY][mapX] == FAKE3)
                    {
                        Map2[mapY][mapX] = EMPTY;
                        movecount -= 5;
                        gotoxy(0, 25);
                        alert(bad);
                    }
                }
                gotoxy(60, 26);
                printf("남은시간: %d    ", (timelimit + starttime - time(0)));
                gotoxy(60, 28);
                printf("남은 이동횟수: %d    ", movecount);

                if (movecount <= 0)
                {
                    loseLevel();
                    break;
                }
                movecount--;
            }
            if (timelimit + starttime - time(0) <= 0)
            {
                loseLevel();
                break;
            }
        }
    }
    else if (dif == 2)
    {
        movecount = 200;
        timelimit = 45;
        starttime = time(0);

        playerX = 2;
        playerY = 1;
        mapX = mapY = 1;
        //Map1[playerY][playerX] = CUR;
        system("cls");
        showMap(dif);
        while (1)
        {

            gotoxy(60, 26);
            printf("남은시간: %d    ", (timelimit + starttime - time(0)));
            gotoxy(60, 28);
            printf("남은 이동횟수: %d    ", movecount);

            gotoxy(playerX, playerY);
            printf("◆");

            if (_kbhit()) {
                ch = _getch();
                if (ch == 224)
                {
                    ch = _getch();
                    switch (ch)
                    {
                    case UP:
                        mapY--;
                        tmpY = playerY - 1;
                        if (Map3[mapY][mapX] == WALL) {
                            mapY++;
                        }
                        else {
                            playerY--;
                        }
                        break;
                    case DOWN:
                        mapY++;
                        tmpY = playerY + 1;
                        if (Map3[mapY][mapX] == WALL) {
                            mapY--;
                        }
                        else {
                            playerY++;
                        }
                        break;
                    case LEFT:
                        mapX--;
                        tmpY = playerY;
                        if (Map3[mapY][mapX] == WALL) {
                            mapX++;
                        }
                        else {
                            playerX -= 2;
                        }
                        break;
                    case RIGHT:
                        mapX++;
                        tmpY = playerY;
                        if (Map3[mapY][mapX] == WALL) {
                            mapX--;
                        }
                        else {
                            playerX += 2;
                        }
                        break;
                    }
                    printf("\b\b  ");
                    if (Map3[mapY][mapX] == FLAG) {
                        winLevel(dif);
                    }
                    if (Map3[mapY][mapX] == FAKE1) {
                        Map3[mapY][mapX] = EMPTY;
                        gotoxy(playerX, tmpY);
                        printf("  ");
                        playerX = 2;
                        playerY = 1;
                        mapX = mapY = 1;
                        gotoxy(0, 25);
                        alert(blunder);
                    }
                    if (Map3[mapY][mapX] == FAKE2)
                    {
                        Map3[mapY][mapX] = EMPTY;
                        movecount += 10;
                        timelimit += 5;
                        gotoxy(0, 25);
                        alert(good);
                    }
                    if (Map3[mapY][mapX] == FAKE3)
                    {
                        Map3[mapY][mapX] = EMPTY;
                        movecount -= 5;
                        gotoxy(0, 25);
                        alert(bad);
                    }
                }
                gotoxy(60, 26);
                printf("남은시간: %d    ", (timelimit + starttime - time(0)));
                gotoxy(60, 28);
                printf("남은 이동횟수: %d    ", movecount);

                if (movecount <= 0)
                {
                    loseLevel();
                    break;
                }
                if (timelimit + starttime - time(0) <= 0)
                {
                    loseLevel();
                    break;
                }
                movecount--;
            }
            if (timelimit + starttime - time(0) <= 0)
            {
                loseLevel();
                break;
            }
        }
    }
}

void createMap()
{
    for (int i = 0; i < LOWR; i++)
    {
        for (int j = 0; j < LOWC; j++)
        {
            Map1[i][j] = EMPTY;
        }
    }

    for (int i = 0; i < LOWC; i++)
    {
        Map1[0][i] = WALL;
        Map1[LOWR - 1][i] = WALL;
        Map1[i][0] = WALL;
        Map1[i][LOWC - 1] = WALL;
    }

    for (int i = 0; i < MIDR; i++)
    {
        for (int j = 0; j < MIDC; j++)
        {
            Map2[i][j] = EMPTY;
        }
    }

    for (int i = 0; i < MIDC; i++)
    {
        Map2[0][i] = WALL;
        Map2[MIDR - 1][i] = WALL;
        Map2[i][0] = WALL;
        Map2[i][MIDC - 1] = WALL;
    }

    for (int i = 0; i < HIGHR; i++)
    {
        for (int j = 0; j < HIGHC; j++)
        {
            Map3[i][j] = EMPTY;
        }
    }

    for (int i = 0; i < HIGHC; i++)
    {
        Map3[0][i] = WALL;
        Map3[HIGHR - 1][i] = WALL;
        Map3[i][0] = WALL;
        Map3[i][HIGHC - 1] = WALL;
    }
}

void makeFlag(int dif)
{
    srand(time(NULL));
    int arrX[200], arrY[200];
    int temp;
    if (dif == 0)
    {
        max = 30;
        flag = 10;
        for (int i = 0; i < max; i++)
        {
            arrX[i] = rand() % (LOWR - 2) + 1;
            arrY[i] = rand() % (LOWC - 2) + 1;
            for (temp = 0; temp < i; temp++)
            {
                if (arrX[i] == arrX[temp] && arrY[i] == arrY[temp])
                {
                    i--;
                    break;
                }
                else if (arrX[i] == 1 && arrY[i] == 1)
                {
                    i--;
                    break;
                }
            }
        }
        for (int i = 0; i < max; i++)
        {
            item[i].x = arrX[i];
            item[i].y = arrY[i];
        }

        Map1[item[0].x][item[0].y] = FLAG; // 클리어 깃발

        for (int i = 1; i <= flag; i++)
        {
            Map1[item[i].x][item[i].y] = (rand() % 3 + 1);
        }
        for (int i = flag + 1; i <= max; i++)
        {
            Map1[item[i].x][item[i].y] = WALL;
        }
    }
    else if (dif == 1)
    {
        max = 60;
        flag = 20;
        for (int i = 0; i < max; i++)
        {
            arrX[i] = rand() % (MIDR - 2) + 1;
            arrY[i] = rand() % (MIDC - 2) + 1;
            for (temp = 0; temp < i; temp++)
            {
                if (arrX[i] == arrX[temp] && arrY[i] == arrY[temp])
                {
                    i--;
                    break;
                }
                else if (arrX[i] == 1 && arrY[i] == 1)
                {
                    i--;
                    break;
                }
            }
        }
        for (int i = 0; i < max; i++)
        {
            item[i].x = arrX[i];
            item[i].y = arrY[i];
        }

        Map2[item[0].x][item[0].y] = FLAG; // 클리어 깃발

        for (int i = 1; i <= flag; i++)
        {
            Map2[item[i].x][item[i].y] = (rand() % 3 + 1);
        }
        for (int i = flag + 1; i <= max; i++)
        {
            Map2[item[i].x][item[i].y] = WALL;
        }
    }
    else if (dif == 2)
    {
        max = 100;
        flag = 30;
        for (int i = 0; i < max; i++)
        {
            arrX[i] = rand() % (HIGHR - 2) + 1;
            arrY[i] = rand() % (HIGHC - 2) + 1;
            for (temp = 0; temp < i; temp++)
            {
                if (arrX[i] == arrX[temp] && arrY[i] == arrY[temp])
                {
                    i—;
                    break;
                }
                else if (arrX[i] == 1 && arrY[i] == 1)
                {
                    i—;
                    break;
                }
            }
        }
        for (int i = 0; i < max; i++)
        {
            item[i].x = arrX[i];
            item[i].y = arrY[i];
        }

        Map3[item[0].x][item[0].y] = FLAG; // 클리어 깃발

        for (int i = 1; i <= flag; i++)
        {
            Map3[item[i].x][item[i].y] = (rand() % 3 + 1);
        }
        for (int i = flag + 1; i <= max; i++)
        {
            Map3[item[i].x][item[i].y] = WALL;
        }
    }
}