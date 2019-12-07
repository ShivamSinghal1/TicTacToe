#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <graphics.h>
#include <time.h>

using namespace std;

int cP_lies_in_quadrant(int x,int y,int mw,int mh,int ttt[10]);
void draw_X(int quad,int mw,int mh);
void draw_O(int quad,int mw,int mh);
bool check_win(int a[],int player);
int CPU_TURN(int turn,int a[]);
int check_preWin(int a[],int player);

int main()
{
    srand(time(NULL));
    int ttt[10] = {-1};
    DWORD sW = GetSystemMetrics(SM_CXSCREEN);
    DWORD sH = GetSystemMetrics(SM_CYSCREEN);
    initwindow(sW,sH,"",-3,-3);
    int mw = sW/2;
    int mh = sH/2;
    int page=0,turn=0;
    POINT cP;
    while(!GetAsyncKeyState(VK_ESCAPE)){
        int quad,cpu;
        line(mw-50,mh-150,mw-50,mh+150);
        line(mw+50,mh-150,mw+50,mh+150);
        line(mw-150,mh-50,mw+150,mh-50);
        line(mw-150,mh+50,mw+150,mh+50);
        if(GetAsyncKeyState(VK_LBUTTON))
        {
            GetCursorPos(&cP);
            char a[10];
            quad = cP_lies_in_quadrant(cP.x,cP.y,mw,mh,ttt);
            if(quad>0 && quad<10){draw_O(quad,mw,mh);
            ttt[quad] = 1;
            turn++;
            cpu = CPU_TURN(turn,ttt);
            if(cpu>0 &&cpu<10) {draw_X(cpu,mw,mh);
            ttt[cpu] = 2;
            turn++;
            }
            else if(cpu==786)
            {
                outtextxy(10,10,"You Won");
                break;
            }
            else if(cpu==123)
            {
                outtextxy(10,10,"Game Draw");
                break;
            }
            if(check_win(ttt,2)==true)
            {
                outtextxy(10,10,"CPU WON");
                break;
            }
            }
        }
    }
    getch();
    closegraph();
    return 0;
}

int cP_lies_in_quadrant(int x,int y,int mw,int mh,int ttt[10]){

    if(y<mh-150||y>mh+150||x<mw-150||x>mw+150)
        return -1;
    else if(y>=mh-150&&y<=mh-50)
    {
        if(x>=mw-150&&x<=mw-50&&ttt[1]!=1&&ttt[1]!=2)
            return 1;
        else if(x>=mw-50&&x<=mw+50&&ttt[2]!=1&&ttt[2]!=2)
            return 2;
        else if(x>=mw+50&&x<=mw+150&&ttt[3]!=1&&ttt[3]!=2)
            return 3;
        else return -1;
    }
    else if(y>=mh-50&&y<=mh+50)
    {
        if(x>=mw-150&&x<=mw-50&&ttt[4]!=1&&ttt[4]!=2)
            return 4;
        else if(x>=mw-50&&x<=mw+50&&ttt[5]!=1&&ttt[5]!=2)
            return 5;
        else if(x>=mw+50&&x<=mw+150&&ttt[6]!=1&&ttt[6]!=2)
            return 6;
        else return -1;
    }
    else
    {
        if(x>=mw-150&&x<=mw-50&&ttt[7]!=1&&ttt[7]!=2)
            return 7;
        else if(x>=mw-50&&x<=mw+50&&ttt[8]!=1&&ttt[8]!=2)
            return 8;
        else if(x>=mw+50&&x<=mw+150&&ttt[9]!=1&&ttt[9]!=2)
            return 9;
        else return -1;
    }
}

void draw_X(int quad,int mw,int mh){
        settextstyle(4,0,7);
        int w = textwidth("X");
        int h = textheight("X");
        w = w/2;
        h = h/2;
        switch(quad)
        {
        case 1:
            outtextxy(mw-100-w,mh-100-h,"X");
            break;
        case 2:
            outtextxy(mw-w,mh-100-h,"X");
            break;
        case 3:
            outtextxy(mw+100-w,mh-100-h,"X");
            break;
        case 4:
            outtextxy(mw-100-w,mh-h,"X");
            break;
        case 5:
            outtextxy(mw-w,mh-h,"X");
            break;
        case 6:
            outtextxy(mw+100-w,mh-h,"X");
            break;
        case 7:
            outtextxy(mw-100-w,mh+100-h,"X");
            break;
        case 8:
            outtextxy(mw-w,mh+100-h,"X");
            break;
        case 9:
            outtextxy(mw+100-w,mh+100-h,"X");
            break;
        }
}

void draw_O(int quad,int mw,int mh){
        settextstyle(4,0,7);
        int w = textwidth("O");
        int h = textheight("O");
        w = w/2;
        h = h/2;
        switch(quad)
        {
        case 1:
            outtextxy(mw-100-w,mh-100-h,"O");
            break;
        case 2:
            outtextxy(mw-w,mh-100-h,"O");
            break;
        case 3:
            outtextxy(mw+100-w,mh-100-h,"O");
            break;
        case 4:
            outtextxy(mw-100-w,mh-h,"O");
            break;
        case 5:
            outtextxy(mw-w,mh-h,"O");
            break;
        case 6:
            outtextxy(mw+100-w,mh-h,"O");
            break;
        case 7:
            outtextxy(mw-100-w,mh+100-h,"O");
            break;
        case 8:
            outtextxy(mw-w,mh+100-h,"O");
            break;
        case 9:
            outtextxy(mw+100-w,mh+100-h,"O");
            break;
        }
}

int CPU_TURN(int turn,int a[]){

    if(check_win(a,1)==true)
        return 786;
    if(turn==9)
        return 123;
    int isWinC = check_preWin(a,2);
    int isWinP = check_preWin(a,1);
    if(isWinC!=-1)
        return isWinC;
    if(isWinP!=-1)
        return isWinP;
    int t=0;
    while(a[t]!=0){
        t = (rand()%9 + 1);
    }
    return t;
}

bool check_win(int a[],int player){
    for(int i=0;i<7;i+=3)
    {
        if(a[i+1]==a[i+2]&&a[i+2]==a[i+3]&&a[i+1]==player)
        {
            return true;
        }
    }
    for(int i=1;i<4;i++)
    {
        if(a[i]==a[i+3]&&a[i+3]==a[i+6]&&a[i]==player)
        {
            return true;
        }
    }
    if(a[1]==a[5]&&a[5]==a[9]&&a[1]==player)
        return true;
    if(a[3]==a[5]&&a[5]==a[7]&&a[3]==player)
        return true;
    return false;
}

int check_preWin(int a[],int player){
    if(a[5]==player){
        for(int i=1;i<=9;i++){
                if(a[i]==player && i!=5 && a[10-i]!=1 && a[10-i]!=2)
                    return 10-i;
        }
    }
    if(a[1]==player && a[2]==player && a[3]!=1 && a[3]!=2)
            return 3;
    if(a[3]==player && a[2]==player && a[1]!=1 && a[1]!=2)
            return 1;
    if(a[7]==player && a[8]==player && a[9]!=1 && a[9]!=2)
            return 9;
    if(a[9]==player && a[8]==player && a[7]!=1 && a[7]!=2)
            return 7;
    if(a[1]==player && a[4]==player && a[7]!=1 && a[7]!=2)
            return 7;
    if(a[7]==player && a[4]==player && a[1]!=1 && a[1]!=2)
            return 1;
    if(a[3]==player && a[6]==player && a[9]!=1 && a[9]!=2)
            return 9;
    if(a[9]==player && a[6]==player && a[3]!=1 && a[3]!=2)
            return 3;
    if(a[1]==player && a[3]==player && a[2]!=1 && a[2]!=2)
            return 2;
    if(a[1]==player && a[7]==player && a[4]!=1 && a[4]!=2)
            return 4;
    if(a[9]==player && a[3]==player && a[6]!=1 && a[6]!=2)
            return 6;
    if(a[9]==player && a[7]==player && a[8]!=1 && a[8]!=2)
            return 8;
    if(a[1]==player && a[9]==player && a[5]!=1 && a[5]!=2)
            return 5;
    if(a[2]==player && a[8]==player && a[5]!=1 && a[5]!=2)
            return 5;
    if(a[3]==player && a[7]==player && a[5]!=1 && a[5]!=2)
            return 5;
    if(a[4]==player && a[6]==player && a[5]!=1 && a[5]!=2)
            return 5;
    return -1;
}
