#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define WIDTH   52
#define HEIGHT  25

/*
체크리스트

(1) 인트로X : 게임 배경 설명

(2) 게임판O : x 길이 0-92, y길이 0-25

(3) 게임조작법O : 좌 : ← / 우 : → / 공격 : s

(4) 스코어 표시O : 일반 좀비 * 100 / 특수 좀비 * 1000 / 보스 좀비 * 10000

(5) 라이프 표시O : 주인공이 지키는 커맨드센터의 체력 100
                   - 좀비가 벽(*)을 공격했을 시 좀비 공격력만큼 체력 깎임
                   - 좀비가 주인공을 공격했을 시 좀비 공격력 * 2 배로 체력 깎임 

(6) 플레이어O : 좌우무빙

(7) 플레이어 총알O : 시작 20발 / 최대 100발 
		            일반 좀비 처치 시 총알 + 3
		            특수 좀비 처치 시 총알 + 6

(8) 적(1,2,3)X
                일반 좀비(1) : 체력 2, 공격력 1
                특수 좀비(2) : 좌우무빙, 체력 4, 공격력 5
                보스(3) : 투사체 공격, 좌우무빙, 1,2번 좀비 생성, 체력 30, 공격력 10 

(9) 아이템(1, 2)X
                1 : 라이프 + 10
                2 : 총알 보급 + 20

(10) 아웃트로X : 엔딩

체크리스트 달성률 60% (6 / 10)
*/
int c;
int c1;

char board[HEIGHT][WIDTH];

gotoxy(int x, int y)
{
    COORD pos = { x , y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int target(void)
{
    srand((unsigned int)time(NULL));

    int x = (rand() % 49) + 2;
    int y = 2;
    gotoxy(x, y);
    printf("0");
    c = y;
    return x;
}
int target1(void)
{
    srand((unsigned int)time(NULL)/2);
    int x = (rand() % 49) + 2;
    int y = 8;
    gotoxy(x, y);
    printf("1");
    c1 = y;
    return x;
}


void game(void)
{
    char ch;
    int x = 25, y = 23, loc, loc1; //플레이어 시작 위치
    int score = 0;//점수 int 값
    int wall = 100; // 벽 int 값
    int bullet = 20; //총알 int 값
    gotoxy(0, 0);

    printf("┏");//상단 오른쪽 모서리

    for (int i = 1; i < 52; i++) {//왼쪽 상단줄
        printf("━");
    }

    printf("┳");//중간 표시

    for (int i = 53; i < 92; i++) {
        printf("━");//오른쪽 상단줄
    }

    printf("┓");//오른쪽 상단 모서리
    
    for (int i = 1; i < 25; i++) {
        gotoxy(0, i);
        printf("┃");//왼쪽 세로줄
    }
    
    for (int i = 1; i < 25; i++) {
        gotoxy(52, i);
        printf("┃");//가운데 세로줄
    }

    for (int i = 1; i < 25; i++) {
        gotoxy(92, i);
        printf("┃");//오른쪽 세로줄
    }

    gotoxy(1, 24);

    for (int i = 1; i < 52; i++) {
        printf("*");//벽
    }

    gotoxy(0, 25);

    printf("┗");//왼쪽 모서리

    for (int i = 1; i < 52; i++) {
        printf("━");//왼쪽 하단줄
    }

    printf("┻");//하단 중단 표시

    for (int i = 53; i < 92; i++) {
        printf("━");//오른쪽 하단줄
    }
    printf("┛");//하단 왼쪽 모서리

    gotoxy(60, 3);
    printf("점수 : %d", score); // 화면상 점수 표시
    gotoxy(60, 6);
    printf("총알 : %d / 100", bullet); // 총알의 수 표시
    gotoxy(60, 9);
    printf("HP :% d / 100", wall);// HP 표시
    gotoxy(60, 19);
    printf("<- : 왼쪽으로 이동");//조작법
    gotoxy(60, 21);
    printf("<- : 오른쪽으로 이동");//조작법
    gotoxy(60, 23);
    printf("s : 총알발사");//조작법
    loc = target(); // 최초 목표물 생성 + 목표물 x좌표 반환
  
    int T = 0;
    int a = 100;
    int b = 0;
    int e1 = 0;
    while (1)
    {
        gotoxy(60, 3);
        printf("점수 : %d", score); // 화면상 점수 표시
        gotoxy(60, 6);
        printf("총알 : %d / 100", bullet); // 총알의 수 표시
        gotoxy(60, 9);
        printf("HP :% d / 100", wall);// HP 표시
        gotoxy(60, 12);
        printf("시간 :% d", T);// 시간 표시
      
        
        gotoxy(x, y);
        printf("@"); //플레이어 표시

        T++;//T 설정
        if (T == 300) {
            loc1 = target1();
        }
        Sleep(20);
        if (_kbhit()) {
            ch = _getch();
            if(a > 50){//a가 50 이상일 떄 총알이 안나간다.
            if (ch == 's')
            {
   
                b = x;
                a = 22;
                bullet--;//총알 발사하면 줄어듬
            }
            }
            switch (ch)
            {
            case 75:
                if (x > 2) {
                    x--; // 방향키 ← 
                    gotoxy(x + 1, y);
                    printf("  ");
                    break;
                }

            case 77:
                if (x < 50) {
                    x++; //방향키 →
                    gotoxy(x -1, y);
                    printf("  ");
                    break;
                }
            }
        }

        //총알
        if (a < 23) {
            a--;
            gotoxy(b, a);
            board[a][b] = 'l';
            printf("%c", board[a][b]); //총알이 x좌표에서 위로 날아감 
            Sleep(10);
            gotoxy(b, a);
            printf(" "); //총알이 지나간 위치에는 공백으로 지워줌 
            board[a][b] = ' ';
            if (a < 2) {
                a = 100;
            }

        }

        //적("0")
        if(T % 20 == 1){
        gotoxy(loc, c - 1);
        printf(" ");
        Sleep(5);
        gotoxy(loc, c++);
        printf("0");
        if (c == 24) {
            Sleep(20);
            gotoxy(loc, c - 1);
            printf(" ");
            loc = target();
            wall -= 5;
        }
        }
        if (loc == b && a == c) {
            score += 10;//적에 총알이 닿으면 점수의 표시가 10올라감
            bullet += 3;//적에 총알이 닿으면 총알의 표시가 3올라감
            loc = target();
        }
        //적("1")
        if(T>300){
            if (T % 30 == 1) {
                gotoxy(loc1, c1 - 1);
                printf(" ");
                Sleep(5);
                gotoxy(loc1, c1++);
                printf("1");
                if (c1 == 24) {
                    Sleep(20);
                    gotoxy(loc1, c1 - 1);
                    printf(" ");
                    loc1 = target1();
                    wall -= 10;
                }
            }
            if (loc1 == b && a == c1) {
                e1++;
                if(e1 >= 2){
                    score += 20;//적에 총알이 닿으면 점수의 표시가 20올라감
                    bullet += 3;//적에 총알이 닿으면 총알의 표시가 3올라감
                    loc1 = target1();
                    e1 = 0;
                }
            }
        }

    }
}

void CursorView()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

int main(void)
{
    CursorView();
    game();
    return 0;
}