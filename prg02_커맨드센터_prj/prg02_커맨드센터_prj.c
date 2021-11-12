#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define _CRT_SECURE_NO_WARNINGS
#define WIDTH   52
#define HEIGHT  25

char board[HEIGHT][WIDTH]; // 플레이어 게임판
int boss_hp = 30; // 보스 HP
int score = 0;//점수 int 값
int T = 0;    // 시간
int T_b = 0, cb_hit, cb_a, c, c1;
// c : "0"의 y값         c1 : "1"의 y값             T_b : 보스(on/off)
// cb_a : 보스 화살 y값  cb_hit : 보스 히트박스 y값

gotoxy(int x, int y) // 좌표 이동
{
    COORD pos = { x , y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void CursorView() // 커서 숨기기
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

int target(void) // 첫 번째 적("0")
{
    //srand((unsigned int)time(NULL));
    srand((int)time(NULL));

    int x = ((rand() * 37) % 49) + 2;
    int y = 2;
    if (T_b == 0) {
        y = 2;
    }
    else
    {
        y = 8;
    }
    gotoxy(x, y);
    printf("0");
    c = y;
    return x;
}

int target1(void) // 두 번째 적("1")
{
    //srand((unsigned int)time(NULL) / 2);
    srand((int)time(NULL));
    int x = ((rand() * 29) % 49) + 2;
    int y = 8;
    gotoxy(x, y);
    printf("1");
    c1 = y;
    return x;
}

int boss(void) // 보스
{

    gotoxy(20, 2);
    printf("＾── ＾");
    gotoxy(20, 3);
    printf("ⓞωⓞ＂＂＂＂＂");
    gotoxy(20, 4);
    printf("＂               ＂");
    gotoxy(20, 5);
    printf("＂               ＂＂");
    gotoxy(20, 6);
    printf("ㆀㆀ＂＂＂＂＂ㆀㆀ");
    cb_hit = 5; // 히트박스 판정 y값
    return 20;
}

int boss_a(void) // 보스 화살
{
    //srand((unsigned int)time(NULL) / 5);
    srand((int)time(NULL));

    int x = (rand() % 49) + 2;
    int y = 8;
    gotoxy(x, y);
    printf("v");
    cb_a = y;
    return x;
}

void opening() {
    printf("┏");//상단 오른쪽 모서리

    for (int i = 1; i < 108; i++) {//상단줄
        printf("━");
    }

    printf("┓");//상단 오른쪽 모서리

    for (int i = 1; i < 25; i++) {
        gotoxy(0, i);
        printf("┃");//왼쪽 세로줄
    }

    for (int i = 1; i < 25; i++) {
        gotoxy(108, i);
        printf("┃");//오른쪽 세로줄
    }
    gotoxy(0, 25);

    printf("┗");//왼쪽 모서리

    for (int i = 1; i < 108; i++) {
        printf("━");//하단줄
    }

    printf("┛");//하단 오른쪽 모서리

    gotoxy(20, 3);
    printf("적으로부터 벽(*)을 지켜주세요!");
    gotoxy(51, 3);
    printf("시간이 지날수록 강한 적이 등장합니다!");
    Sleep(1200);

    gotoxy(8, 6);
    printf("몬스터 ""0,"" ""v ""는 한 발만 맞춰도 죽일 수 있습니다!");
    gotoxy(56, 6);
    printf("몬스터 ""1 ""은 두 발을 맞춰서 죽일 수 있습니다!");
    Sleep(1200);

    gotoxy(25, 9);
    printf("몬스터 ""0,"" ""1,"" ""v"" 를 죽이면 총알과 체력을 얻을 수 있습니다!");
    Sleep(1200);

    gotoxy(12, 12);
    printf("시간이 지나면 최종 보스가 나타납니다.");
    gotoxy(51, 12);
    printf("최종 보스는 여러 번 공격해야 죽일 수 있습니다!");
    Sleep(1200);

    gotoxy(19, 15);
    printf("총을 연사하면 쏘면 명중률이 떨어져");
    gotoxy(55, 15);
    printf("멀리 있는 적을 맞출 수 없게 됩니다!");
    Sleep(1200);


    gotoxy(28, 19);
    printf("====  게임을 시작하시겠습니까? Enter를 눌러주세요!  =====");
    Sleep(1000);

    while(_getch() != '\r'){
    }

    gotoxy(28, 19);
    printf("========        잠시후 게임이 시작됩니다!        ========");
    Sleep(1000);
    gotoxy(28, 19);
    printf("========                    3                    ========");
    Sleep(1000);
    gotoxy(28, 19);
    printf("========                    2                    ========");
    Sleep(1000);
    gotoxy(28, 19);
    printf("========                    1                    ========");
    Sleep(1000);
    gotoxy(28, 19);
    printf("========            게임을 시작합니다            ========");

    Sleep(1500);
    system("cls");
}

void gamewin() {
    printf("┏");//상단 오른쪽 모서리

    for (int i = 1; i < 108; i++) {//상단줄
        printf("━");
    }

    printf("┓");//오른쪽 상단 모서리

    for (int i = 1; i < 25; i++) {
        gotoxy(0, i);
        printf("┃");//왼쪽 세로줄
    }

    for (int i = 1; i < 25; i++) {
        gotoxy(108, i);
        printf("┃");//오른쪽 세로줄
    }
    gotoxy(0, 25);

    printf("┗");//왼쪽 모서리

    for (int i = 1; i < 108; i++) {
        printf("━");//하단줄
    }

    printf("┛");//하단 왼쪽 모서리
    for (int i = 0; i < 6; i++) {
        for (int j = 8; j < 21; j++) {
            gotoxy(3, j);
            printf("                                                                                                         ");//
        }
        Sleep(300);
        gotoxy(3, 8);
        printf("           ■        ■  ■■■■■■  ■        ■  ■  ■■  ■  ■■■■■■  ■■      ■            ");//
        gotoxy(3, 9);
        printf("           ■        ■  ■        ■  ■        ■  ■  ■■  ■  ■■■■■■  ■■      ■            ");//
        gotoxy(3, 10);
        printf("           ■■    ■■  ■        ■  ■        ■  ■ ■  ■ ■      ■■      ■ ■     ■            ");//
        gotoxy(3, 11);
        printf("             ■    ■    ■        ■  ■        ■  ■ ■  ■ ■      ■■      ■  ■    ■            ");//
        gotoxy(3, 12);
        printf("              ■■■     ■        ■  ■        ■  ■■    ■■      ■■      ■    ■  ■            ");//
        gotoxy(3, 13);
        printf("               ■■      ■        ■  ■        ■  ■■    ■■      ■■      ■     ■ ■            ");//
        gotoxy(3, 14);
        printf("               ■■      ■        ■  ■        ■  ■        ■  ■■■■■■  ■      ■■            ");//
        gotoxy(3, 15);
        printf("               ■■      ■■■■■■  ■■■■■■  ■        ■  ■■■■■■  ■      ■■            ");//
        gotoxy(30, 20);
        printf("최종 점수 : %d점 ", score);
        gotoxy(60, 20);
        printf("플레이 타임 : %d ", T);
        Sleep(700);
    }

    gotoxy(0, 25);
    Sleep(1000);
}

void gameover() {
    printf("┏");//상단 오른쪽 모서리

    for (int i = 1; i < 108; i++) {//상단줄
        printf("━");
    }

    printf("┓");//오른쪽 상단 모서리

    for (int i = 1; i < 25; i++) {
        gotoxy(0, i);
        printf("┃");//왼쪽 세로줄
    }

    for (int i = 1; i < 25; i++) {
        gotoxy(108, i);
        printf("┃");//오른쪽 세로줄
    }
    gotoxy(0, 25);

    printf("┗");//왼쪽 모서리

    for (int i = 1; i < 108; i++) {
        printf("━");//하단줄
    }

    printf("┛");//하단 왼쪽 모서리


    for (int i = 0; i < 6; i++) {
        for (int j = 8; j < 16; j++) {
            gotoxy(3, j);
            printf("                                                                                                         ");//
        }
        Sleep(300);
        gotoxy(3, 8);
        printf("■■■■■■ ■■■■■■ ■        ■ ■■■■■■ ■■■■■■ ■        ■ ■■■■■■ ■■■■■■  ");//
        gotoxy(3, 9);
        printf("■        ■ ■        ■ ■■    ■■ ■           ■        ■ ■        ■ ■           ■        ■  ");//
        gotoxy(3, 10);
        printf("■        ■ ■        ■ ■■    ■■ ■           ■        ■ ■        ■ ■           ■        ■  ");//
        gotoxy(3, 11);
        printf("■           ■        ■ ■ ■  ■ ■ ■           ■        ■ ■        ■ ■           ■■■■■■  ");//
        gotoxy(3, 12);
        printf("■    ■■■ ■■■■■■ ■ ■  ■ ■ ■■■■■■ ■        ■ ■■    ■■ ■■■■■■ ■  ■  ");//
        gotoxy(3, 13);
        printf("■        ■ ■        ■ ■  ■■  ■ ■           ■        ■   ■    ■   ■           ■    ■  ");//
        gotoxy(3, 14);
        printf("■        ■ ■        ■ ■  ■■  ■ ■           ■        ■     ■■     ■           ■      ■    ");//
        gotoxy(3, 15);
        printf("■■■■■■ ■        ■ ■  ■■  ■ ■■■■■■ ■■■■■■     ■■     ■■■■■■ ■        ■  ");//
        Sleep(700);
    }

    gotoxy(0, 25);
    Sleep(1000);
}

void game(void)
{
    char ch;
    int x = 25, y = 23, loc_b = 0, loc_ba = 0, loc, loc1; //플레이어 시작 위치

    int wall = 50; // HP int 값
    int bullet = 20; //총알 int 값
    int a = 100; // 총알 y값
    int b = 0;   // 총알 x값
    int e1 = 0;  // 적("1")의 체력(총알을 맞은 횟수)

    gotoxy(0, 0);

    printf("┏");//상단 오른쪽 모서리

    for (int i = 1; i < 52; i++) {//왼쪽 상단줄
        printf("━");
    }

    printf("┳");//중간 표시

    for (int i = 53; i < 108; i++) {
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
        gotoxy(108, i);
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

    for (int i = 53; i < 108; i++) {
        printf("━");//오른쪽 하단줄
    }
    printf("┛");//하단 왼쪽 모서리

    gotoxy(60, 16);
    printf("<- : 왼쪽으로 이동");//조작법
    gotoxy(60, 18);
    printf("<- : 오른쪽으로 이동");//조작법
    gotoxy(60, 20);
    printf("S  : 공격");//조작법
    loc = target(); // 최초 목표물 생성 + 목표물 x좌표 반환

    while (1)
    {
        CursorView();
        gotoxy(60, 3);
        printf("점수 : %d        ", score); // 점수 표시
        printf("시간 : %d ", T); // 시간 표시
        gotoxy(60, 6);
        printf("총알 : %d / 30 ", bullet); // 총알 수 표시
        gotoxy(60, 9);
        printf("플레이어 HP :% d / 50 ", wall);// HP 표시
        
        gotoxy(71 + boss_hp / 3 * 2, 12); // 보스체력에서 3씩 감소될 때마다 ■ 하나 줄어듦.
        printf("  ");

        gotoxy(x, y);
        printf("@"); //플레이어 표시

        // 게임시간이 150이 되면 적("1") 생성
        if (T == 150) {
            loc1 = target1();
        }

        // 게임시간이 300을 초과하면 보스 화살 생성
        if (T > 300 && T_b == 0) {
            loc_ba = boss_a();
            T_b++; // 보스 ON
        }
        if (T_b == 1) {
            loc_b = boss(); // 보스 생성
            gotoxy(60, 12);
            printf("보스 HP :");// 보스 HP 표시. 보스의 HP는 30이며 3씩 ■를 그려 10개의 ■로 체력을 표현
            for (int i = 0; i < boss_hp / 3; i++) {
                gotoxy(70 + i * 2, 12);
                printf("■");
            }
        }

        T++;//T 설정
        
        Sleep(10);

        // kbhit 조건을 줘서 눌렀을 때만 작동하도록
        if (_kbhit()) {
            ch = _getch();
            if (a > 50 || a < 5) {//a가 50 이상일 때 총알이 못 쏨.(연타 불가능)
                if (ch == 's')
                {

                    b = x;
                    a = 23;
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
                    gotoxy(x - 1, y);
                    printf("  ");
                    break;
                }
            }
        }

        //총알
        if (a < 24) {
            a--;
            gotoxy(b, a);
            board[a][b] = 'l';
            printf("%c", board[a][b]); //좌표를 받아 총알을 위로 발사함
            Sleep(5);
            gotoxy(b, a);
            printf(" "); //총알이 지나간 위치에는 공백으로 지워줌 
            board[a][b] = ' ';
            if (a < 2) {
                a = 100;
            }
        }

        //적("0")
        if (T % 22 == 1) {
            gotoxy(loc, c - 1);
            printf(" ");
            Sleep(8);
            gotoxy(loc, c++);
            printf("0");
            if (c == 24) { // 적이 플레이어와 같은 y축 위치(24)까지 오면 HP를 감소시키고 다시 적("0") 생성
                Sleep(20);
                gotoxy(loc, c - 1);
                printf(" ");
                wall -= 11; // HP 10 감소
                loc = target(); // 적생성

            }
        }
        // b는 플레이어가 총을 쏠 때 x값, loc는 적의 x값, a는 총알의 y값, c는 적의 y값
        if (loc == b && a == c) {
            score += 19;//적을 맞추면 점수 + 19
            wall += 1;
            if (wall > 50) {
                wall = 50;
            }
            bullet += 2;//적을 맞추면 2발 장전
            // 총알은 최대 30발까지 채울 수 있다
            if (bullet > 20) {
                bullet = 20;
            }
            loc = target();
        }


        //적("1")
        if (T > 150) {
            if (T % 31 == 1) {
                gotoxy(loc1, c1 - 1);
                printf(" ");
                Sleep(3);
                gotoxy(loc1, c1++);
                printf("1");
                if (c1 == 24) { // 적이 플레이어와 같은 y축 위치(맨밑)까지 오면 HP를 감소시키고 다시 적("1") 생성
                    Sleep(20);
                    gotoxy(loc1, c1 - 1);
                    printf(" ");
                    wall -= 15; //HP 10 감소
                    e1 = 0; //적이 다시 생성될 때 적의 체력을 초기화
                    loc1 = target1();
                }
            }
            // b는 플레이어가 총을 쏠 때 x값, loc1은 적의 x값, a는 총알의 y값, c1은 적의 y값
            if (loc1 == b && a == c1) {
                e1++; // 총알을 맞은 횟수 + 1
                // 맞은 횟수가 2 이상이면 적을 죽인 것으로 판정
                if (e1 >= 2) {
                    score += 43;//적을 맞추면 점수 + 43
                    wall += 2;
                    if (wall > 50) {
                        wall = 50;
                    }
                    bullet += 3;//적을 맞추면 3발 장전
                    if (bullet > 20) {
                        bullet = 20;
                    }
                    loc1 = target1();
                    e1 = 0;
                }
            }
        }
        //보스 화살
        if (loc_ba > 0) {
            if (T % 13 == 1) {
                gotoxy(loc_ba, cb_a - 1);
                printf(" ");
                Sleep(5);
                gotoxy(loc_ba, cb_a++);
                printf("v");
                if (cb_a == 24) {
                    Sleep(20);
                    gotoxy(loc_ba, cb_a - 1);
                    printf(" ");
                    wall -= 18;        // 보스 화살에 맞으면 HP - 20
                    loc_ba = boss_a(); // 보스 화살의 x값
                }
            }
            if (loc_ba == b && a == cb_a) {
                score += 36;//적을 맞추면 점수 + 36
                wall += 1;
                if (wall > 50) {
                    wall = 50;
                }
                bullet += 1;//적을 맞추면 3발 장전
                if (bullet > 20) {
                    bullet = 20;
                }
                loc_ba = boss_a();
            }
        }
        // 보스가 있을때 
        if (loc_b > 0) {
            // 플레이어 총알의 x값이 20~40이고 y값이 cb(보스 히트박스y값)이면 보스 HP 감소
            if (b > 19 && b < 41 && a == cb_hit) {
                boss_hp--;
                // 보스 HP가 0 이하로 떨어지면 보스 삭제
                if (boss_hp < 1) {

                    score += 5000;
                    gotoxy(60, 3);
                    printf("점수 : %d ", score); // 점수 표시
                    gotoxy(60, 12);
                    printf("보스 HP :");// 보스 HP 표시. 보스의 HP는 30이며 3씩 ■를 그려 10개의 ■로 체력을 표현
                    gotoxy(70, 12);
                    printf("    ");

                    for (int i = 1; i < 10; i++) {
                        gotoxy(20, 2);
                        printf("                           ");
                        gotoxy(20, 3);
                        printf("                           ");
                        gotoxy(20, 4);
                        printf("                           ");
                        gotoxy(20, 5);
                        printf("                           ");
                        gotoxy(20, 6);
                        printf("                           ");

                        Sleep(1000/i);

                        gotoxy(20, 2);
                        printf("＾── ＾");
                        gotoxy(20, 3);
                        printf("ⓞωⓞ＂＂＂＂＂");
                        gotoxy(20, 4);
                        printf("＂               ＂");
                        gotoxy(20, 5);
                        printf("＂               ＂＂");
                        gotoxy(20, 6);
                        printf("ㆀㆀ＂＂＂＂＂ㆀㆀ");

                        Sleep(1000/i);
                    }
                    
                    //T_b++;
                }
            }
        }
        // 총알이 0 미만이 되거나 플레이어 HP가 1 미만이 되거나 보스의 HP가 0 이하가 되었을 때 게임 종료
        if (bullet < 0 || wall < 1 || boss_hp < 1) {
            break;
        }
    }
}

int main(void)
{
    CursorView();
    opening();
    system("cls");
    game();
    system("cls");
    //game()이 break 되었을 때 보스를 잡은 경우 승리 화면을 보여준다.
    if (boss_hp <= 0) {
        gamewin();
    }
    //보스를 잡지 못한 경우 패배 화면을 보여준다.
    else {
        gameover();
    }
    return 0;
}