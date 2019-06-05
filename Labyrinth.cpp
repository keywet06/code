#include <bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#define ef else if

using namespace std;

#define Rint register int
#define Lint long long int
#define Uint unsigned long long

enum CFC
{
    FRed      =FOREGROUND_INTENSITY	|FOREGROUND_RED,
    FGreen    =FOREGROUND_INTENSITY	|FOREGROUND_GREEN,
    FBlue     =FOREGROUND_INTENSITY	|FOREGROUND_BLUE,
    FYellow   =FOREGROUND_INTENSITY	|FOREGROUND_RED		|FOREGROUND_GREEN,
    FPurple   =FOREGROUND_INTENSITY	|FOREGROUND_RED		|FOREGROUND_BLUE,
    FCyan     =FOREGROUND_INTENSITY	|FOREGROUND_GREEN	|FOREGROUND_BLUE,
    FGray     =FOREGROUND_INTENSITY,
    FWhite    =						 FOREGROUND_RED		|FOREGROUND_GREEN	|FOREGROUND_BLUE,
    FHighWhite=FOREGROUND_INTENSITY	|FOREGROUND_RED		|FOREGROUND_GREEN	|FOREGROUND_BLUE,
    FBlack    =0,
};
enum CBC
{
    BRed      =BACKGROUND_INTENSITY	|BACKGROUND_RED,
    BGreen    =BACKGROUND_INTENSITY	|BACKGROUND_GREEN,
    BBlue     =BACKGROUND_INTENSITY	|BACKGROUND_BLUE,
    BYellow   =BACKGROUND_INTENSITY	|BACKGROUND_RED		|BACKGROUND_GREEN,
    BPurple   =BACKGROUND_INTENSITY	|BACKGROUND_RED		|BACKGROUND_BLUE,
    BCyan     =BACKGROUND_INTENSITY	|BACKGROUND_GREEN	|BACKGROUND_BLUE,
    BWhite    =						 BACKGROUND_RED		|BACKGROUND_GREEN	|BACKGROUND_BLUE,
    BHighWhite=BACKGROUND_INTENSITY	|BACKGROUND_RED		|BACKGROUND_GREEN	|BACKGROUND_BLUE,
    BBlack    =0,
};
void SC(CFC foreColor=FWhite, CBC backColor=BBlack)
{
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, foreColor | backColor);
}
string _map[100];
void cursor(int x,int y)
{
	HANDLE hout;
	COORD coord;
	coord.X=y;
	coord.Y=x;
	hout=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout,coord);
}

char intoch(int x)
{
	return x^48;
}
string LV1[100];
int money,key,atk,def,HP,gx;
double score;
bool Course=1,quit = 0;
int Exprint;
string intosnum(int x,int p)
{
	string s="";
	if (!x) s="0"+s;
	for (; x; s=intoch(x%10)+s,x/=10);
	for (; s.length()<p;)
	{
		s+=' ';
		if (s.length()<p)
			s=' '+s;
	}
	return s;
}
string intosloat(float x,int p)
{
	string s=".";
	float y = (int)(x*10)/10.0-((int)x);
	int z=x;
	if (!z)s = "0.";
	for (; z!=0; s=intoch(z%10)+s,z/=10);
	s += intoch(y*10);
	for (; s.length()<p;)
	{
		s=s+" ";
		if (s.length()<p)
			s=" "+s;
	}
	return s;
}

void Change(int x,int y,char ch)
{
	cursor(x,y);
	if (x == 6 && y == 54 && ch == 'K')
			SC(FBlue,BBlack),	putchar('K'),SC(FWhite,BBlack);
	if (y > 35 && y<47 && x>4 && x<12)
	{
		if (ch == '%')
			SC(FCyan,BBlack),	putchar('%'),SC(FWhite,BBlack);
		ef (ch == '#')
			SC(FRed,BBlack),	putchar('#'),SC(FWhite,BBlack);
		ef (ch == '=')
			SC(FRed,BBlack),	putchar('='),SC(FWhite,BBlack);
		ef (ch == '!')
			SC(FRed,BBlack),	putchar('!'),SC(FWhite,BBlack);
		ef (ch == 'T')
			SC(FGray,BBlack),	putchar('T'),SC(FWhite,BBlack);
		ef (ch == 'H')
			SC(FGreen,BBlack),	putchar('H'),SC(FWhite,BBlack);
		ef (ch == 'K')
			SC(FBlue,BBlack),	putchar('K'),SC(FWhite,BBlack);
		ef (ch == 'M')
			SC(FBlue,BBlack),	putchar('M'),SC(FWhite,BBlack);
		ef (ch == '$')
			SC(FYellow,BBlack),	putchar('$'),SC(FWhite,BBlack);
		else
			putchar(ch);
	}
	else
		putchar(ch);
}
void ChangeRow(int x,char ch,int rowllen,int rowlen)
{
	for (Rint i=rowllen; i<rowlen; i++)
		Change(i,x,ch);
}
void ChangeMap(int kk,int k,int ll,int l)
{
	_map[12]="|                                  |Time:"+intosnum(clock()/1000,6)+"|     |     |   ";
	ChangeRow(ll,'|',kk,k),
	Sleep(5),
	ChangeRow(ll,'|',kk,k),
	ChangeRow(ll+1,'*',kk,k),
	Sleep(5),
	ChangeRow(ll,'|',kk,k),
	ChangeRow(ll+1,'*',kk,k),
	ChangeRow(ll+2,'|',kk,k),
	Sleep(5);
	for (Rint i=ll; i<=l+3; i++)
	{
		while (_kbhit())
			char ch = getch();
		if (i+2<l) ChangeRow(i+1,'|',kk,k);
		if (i+3<l) ChangeRow(i+2,'*',kk,k);
		if (i+4<l) ChangeRow(i+3,'|',kk,k);
		for (Rint j=kk; j<k; j++)
		{
			Change(j,i,_map[j][i]);
			if (i-3>=0)
				Change(j,i-3,_map[j][i-3]);
		}
		if (i<=l)
			for (int j=kk; j<k; j++)
				if (!(rand()%3))
					Change(j,i,'*');
		Sleep(5);
	}
}

void pmp()
{
	if (Exprint>0)
	{
		for (Rint i=3,j; i<13; i++)
			for (cursor(i,j=2); j<47; j++)
				if (j > 35 && j<47 && i>4 && i<12)
				{
					if (_map[i][j] == '%')
						SC(FCyan,BBlack),	putchar('%'),SC(FWhite,BBlack);
					ef (_map[i][j] == 'T')
						SC(FGray,BBlack),	putchar('T'),SC(FWhite,BBlack);
					ef (_map[i][j] == '#')
						SC(FRed,BBlack),	putchar('#'),SC(FWhite,BBlack);
					ef (_map[i][j] == '=')
						SC(FRed,BBlack),	putchar('='),SC(FWhite,BBlack);
					ef (_map[i][j] == '!')
						SC(FRed,BBlack),	putchar('!'),SC(FWhite,BBlack);
					ef (_map[i][j] == 'H')
						SC(FGreen,BBlack),	putchar('H'),SC(FWhite,BBlack);
					ef (_map[i][j] == 'K')
						SC(FBlue,BBlack),	putchar('K'),SC(FWhite,BBlack);
					ef (_map[i][j] == 'M')
						SC(FBlue,BBlack),	putchar('M'),SC(FWhite,BBlack);
					ef (_map[i][j] == '$')
						SC(FYellow,BBlack),	putchar('$'),SC(FWhite,BBlack);
					else
						putchar(_map[i][j]);
				}
				else
					putchar(_map[i][j]);
		_map[3] ="|                                  |HP:"+intosnum(HP,5)+"   | ATK |Money|   ",
		_map[4] ="| +-----+-----+-----+-----+        +-----------+ "+intosnum(atk,3)+" |"+intosnum(money,5)+"|   ",
		_map[5] ="| |Q:   |W:   |E:   |R:   |        |           |     +-----+   ",
		_map[6] ="| | Quit|  Up | Shop|Agree|        |           |     |K:"+intosnum(key,3)+"|   ",
		_map[7] ="| +-----+-----+-----+-----+        |           | DEF |K: 1 |   ",
		_map[8] ="|   +-----+-----+-----+-----+      |           | "+intosnum(def,3)+" |K: 1 |   ",
		_map[9] ="|   |A:   |S:   |D:   |F:   |      |           |     +-----+   ",
		_map[10]="|   | Left| Down|Right| Help|      |           |     |Score|   ",
		_map[11]="|   +-----+-----+-----+-----+      +-----------+     |"+intosloat(score,5)+"|   ";
		_map[12]="|                                  |Time:"+intosnum(clock()/1000,6)+"|     |     |   ";
	}
	else
		for (Rint i=3,j; i<12; i++)
			for (cursor(i,j=36); j<47; j++)
				if (j > 35 && j<47 && i>4 && i<12)
				{
					if (_map[i][j] == '%')
						SC(FCyan,BBlack),	putchar('%'),SC(FWhite,BBlack);
					ef (_map[i][j] == 'T')
						SC(FGray,BBlack),	putchar('T'),SC(FWhite,BBlack);
					ef (_map[i][j] == '#')
						SC(FRed,BBlack),	putchar('#'),SC(FWhite,BBlack);
					ef (_map[i][j] == '=')
						SC(FRed,BBlack),	putchar('='),SC(FWhite,BBlack);
					ef (_map[i][j] == '!')
						SC(FRed,BBlack),	putchar('!'),SC(FWhite,BBlack);
					ef (_map[i][j] == 'H')
						SC(FGreen,BBlack),	putchar('H'),SC(FWhite,BBlack);
					ef (_map[i][j] == 'K')
						SC(FBlue,BBlack),	putchar('K'),SC(FWhite,BBlack);
					ef (_map[i][j] == 'M')
						SC(FBlue,BBlack),	putchar('M'),SC(FWhite,BBlack);
					ef (_map[i][j] == '$')
						SC(FYellow,BBlack),	putchar('$'),SC(FWhite,BBlack);
					else
						putchar(_map[i][j]);
				}
				else
					putchar(_map[i][j]);
	cursor(12,41);
	cout<<intosnum(clock()/1000,6);
}

void stopp()
{
	while (!_kbhit());
	getch();
}
int lv=1;
string LV[100][100];
int LVX[100],LVY[100];
int LVN[100],LVM[100];
string Infor(int lv,int x,int y,int l)
{
	if (lv == 0)
	{
		if (x == 0 && y == 0)
			if (l == 2) return "         Are You Sure?        ";
			ef (l == 3) return "        If You Do this,       ";
			ef (l == 4) return "      Your Game Progress      ";
			ef (l == 5) return "   Will  NOT  Be  SAVED !!!   ";
	}
	if (lv == 1)
	{
		if (x == 6 && y == 2)
			if (l == 2) return "            Hello             ";
			ef (l == 3) return "   Welcom to \" Labyrinth \"    ";
	}
	if (lv == 2)
	{
		if (x == 3 && y == 5)
			if (l == 2) return "        Pick Up Money         ";
			ef (l == 3)	return "And You Can Use Money To Shop ";
	}
	if (lv == 3)
	{
		if (x == 7 && y == 6)
			if (l == 2) return "         Use The Key          ";
			ef (l == 3) return "       To Open The Door       ";
		if (x == 5 && y == 12) 
			if (l == 2) return "       This Is The Door.      ";
			ef (l == 4) return "  Now,Use The Key To Open It  ";
	}
	if (lv == 4) 
	{
		if (x == 5 && y == 3)
			if (l == 2) return "       Bypassing Traps        ";
			ef (l == 3) return "    It Will Reduce Your HP    ";
			ef (l == 4) return "  If Your HP Is Lower Than 0  ";
			ef (l == 5) return "         Then You Die         ";
		if (x == 5 && y == 7)
			if (l == 3) return "  Pick Up \"H\" To Increase HP  ";
	}
	if (lv == 5)
	{
		if (x == 2 && y == 5)
			if (l == 2) return "     Press E To Open Shop     ";
			ef (l == 4) return "            In It,            ";
			ef (l == 5) return "    You Can Buy Keys Or HP    ";
	}
	return "                              ";
}
void gotoshop()
{
	_map[3] ="|  +---------------------------+   |HP:"+intosnum(HP,5)+"   | ATK |Money|   ";
	_map[4] ="|  |     Welcome To MyShop     |   +-----------+ "+intosnum(atk,3)+" |"+intosnum(money,5)+"|   ";
	_map[5] ="|  +---------------------------+   |           |     +-----+   ";
	_map[6] ="|  |K:$|  1:2  | 10:18 | 20:34 |   |           |     |K:"+intosnum(key,3)+"|   ";
	_map[7] ="|  |---+=======+-------+-------|   |           | DEF |K: 1 |   ";
	_map[8] ="|  |K:$|  1:2  | 10:18 | 20:34 |   |           | "+intosnum(def,3)+" |K: 1 |   ";
	_map[9] ="|  |---+=======+-------+-------|   |           |     +-----+   ";
	_map[10]="|  |K:$|  1:2  | 10:18 | 20:34 |   |           |     |Score|   ";
	_map[11]="|  +---------------------------+   +-----------+     |"+intosloat(score,5)+"|   ";
	_map[12]="|                                  |Time:"+intosnum(clock()/1000,6)+"|     |     |   ";
	int nowx=1,nowy=1;
	bool flag=0;
	for (Rint i=3,j; i<13; i++)
		for (cursor(i,j=1); j<34; j++)
			putchar(_map[i][j]);
	for (;;){
		while (!_kbhit())
			cursor(12,41),cout<<intosnum(clock()/1000,6);
		char ch=getch();
		for (Rint i=1; i<=7; ++i)
			LV[0][nowx*2+5][i+nowy*8-1] = '-',
			LV[0][nowx*2+3][i+nowy*8-1] = '-';
		bool move = 1;
		Rint need=-1,ek=0,eh=0;
		switch (ch){
			case 'w':
				nowx--;
				break;
			case 's':
				nowx++;
				break;
			case 'a':
				nowy--;
				break;
			case 'd':
				nowy++;
				break;
			case 'r':
				if (nowx<3)
					if (nowy==1)
						need=2,ek=1;
					else if (nowy==2)
						need=18,ek=10;
					else need=34,ek=20;
				if (need != -1 && need <= money)
					score+=(need/5.0+(nowy-1)*0.5),money -= need,cursor(4,54),
					cout<<intosnum(money,5)<<endl,
					_map[4] ="| +-----+-----+-----+-----+        +-----------+ "+intosnum(atk,3)+" |"+intosnum(money,5)+"|   ",
					_map[11]="|  +---------------------------+   +-----------+     |"+intosloat(score,5)+"|   ",
					key += ek,cursor(6,56),cout<<intosnum(key,3)<<endl,
					_map[6] ="| | Quit|  Up | Shop|Agree|        |           |     |K:"+intosnum(key,3)+"|   ";
				break;
			case 'q':
				_map[3] ="|                                  |HP:"+intosnum(HP,5)+"   | ATK |Money|   ",
				_map[4] ="| +-----+-----+-----+-----+        +-----------+ "+intosnum(atk,3)+" |  0  |   ",
				_map[5] ="| |Q:   |W:   |E:   |R:   |        |           |     +-----+   ",
				_map[6] ="| | Quit|  Up | Shop|Agree|        |           |     |K:"+intosnum(key,3)+"|   ",
				_map[7] ="| +-----+-----+-----+-----+        |           | DEF |K: 1 |   ",
				_map[8] ="|   +-----+-----+-----+-----+      |           | "+intosnum(def,3)+" |K: 1 |   ",
				_map[9] ="|   |A:   |S:   |D:   |F:   |      |           |     +-----+   ",
				_map[10]="|   | Left| Down|Right| Help|      |           |     |Score|   ",
				_map[11]="|   +-----+-----+-----+-----+      +-----------+     |"+intosloat(score,5)+"|   ",
				_map[12]="|                                  |Time:"+intosnum(clock()/1000,6)+"|     |     |   ";
				for (Rint i=3,j; i<13; ++i)
					for (cursor(i,j=2); j<34; ++j)
						putchar(_map[i][j]);
				return;
		}
		if (nowx<0) nowx=move=0;
		if (nowy<1) nowy=1,move=0;
		if (nowy>3) nowy=3,move=0;
		if (nowx>3) nowx=3,move=0;
		if (move){
			for (Rint i=1; i<=7; ++i)
				LV[0][nowx*2+5][i+nowy*8-1] = '=',
				LV[0][nowx*2+3][i+nowy*8-1] = '=';
			for (Rint i=6,j; i<=10; ++i)
				for (cursor(i,j=4); j<=30; ++j)
					putchar(LV[0][i+nowx*2-4][j]);
		}
	}
}
void Labyrinth(){
    char cmd[32]={0};
    sprintf(cmd, "MODE CON: COLS=%d LINES=%d",63 ,18),
    system(cmd),
	money=0,HP=100,key=1,atk=5,def=5,
	_map[0] ="+----------------------------------------------------------+   ",
	_map[1] ="|                         Level   1                        |   ",
	_map[2] ="+----------------------------------+-----------+-----+-----+   ",
	_map[3] ="|                                  |HP: 100    | ATK |Money|   ",
	_map[4] ="| +-----+-----+-----+-----+        +-----------+  5  |  0  |   ",
	_map[5] ="| |Q:   |W:   |E:   |R:   |        |           |     +-----+   ",
	_map[6] ="| | Quit|  Up | Shop|Agree|        |           |     |K: 1 |   ",
	_map[7] ="| +-----+-----+-----+-----+        |    @      | DEF |K: 1 |   ",
	_map[8] ="|   +-----+-----+-----+-----+      |           |  5  |K: 1 |   ",
	_map[9] ="|   |A:   |S:   |D:   |F:   |      |           |     +-----+   ",
	_map[10]="|   | Left| Down|Right| Help|      |           |     |Score|   ",
	_map[11]="|   +-----+-----+-----+-----+      +-----------+     |  0  |   ",
	_map[12]="|                                  |Time:      |     |     |   ",
	_map[13]="+----------------------------------------------+-----+-----+   ",
	_map[14]="|               This game is provided by HTJ.              |   ",
	_map[15]="+----------------------------------------------------------+   ",
	LV[0][1] ="   +---------------------------+",
	LV[0][2] ="   |      Press R To Sure      |",
	LV[0][3] ="   +---+-------+-------+-------+",
	LV[0][4] ="   |K:$|  1:2  | 10:18 | 20:34 |",
	LV[0][5] ="   |---+-------+-------+-------+",
	LV[0][6] ="   |K:$|  1:2  | 10:18 | 20:34 |",
	LV[0][7] ="   |---+-------+-------+-------+",
	LV[0][8] ="   |K:$|  1:2  | 10:18 | 20:34 |",
	LV[0][9] ="   |---+-------+-------+-------+",
	LV[0][10]="   |H:$|  1:5  | 10:28 | 20:55 |",
	LV[0][11]="   |---+-------+-------+-------+",
	LV[0][12]="   |   |       |       |       |",
	LV[0][13]="   |---+-------+-------+-------+",
	LV[1][1]="###########==##",
	LV[1][2]="#  ##   ##    #",
	LV[1][3]="!$##  # ## == !",
	LV[1][4]="! ## ## ## ## #",
	LV[1][5]="! !# ## ## ## #",
	LV[1][6]="# %# !# ## ## #",
	LV[1][7]="#    !#    !#>#",
	LV[1][8]="##==###===#####",
	LVN[1]=8,LVM[1]=14,LVX[1]=LVY[1]=2,
	LV[2][1]="#####==#######.",
	LV[2][2]="#< #   #   # ##",
	LV[2][3]="##   % $ #    !",
	LV[2][4]="###==##==##== !",
	LV[2][5]=".#$    $##    !",
	LV[2][6]=".##$  #### #= #",
	LV[2][7]="..###      ##>#",
	LV[2][8]="....###########",
	LVN[2]=8,LVM[2]=14,LVY[LVX[2]=2]=1,
	LV[3][1]="###############",
	LV[3][2]="#<###        ##",
	LV[3][3]="# ##  #==# #$ #",
	LV[3][4]="# $! ##K## ## #",
	LV[3][5]="# ## ## $# #% #",
	LV[3][6]="# ## ### # ## #",
	LV[3][7]="# #  !%  # ##M#",
	LV[3][8]="#   ####   ##>#",
	LV[3][9]="###############",
	LVN[3]=9,LVM[3]=14,LVX[3]=2,LVY[3]=1,
	LV[4][1]="######====###########",
	LV[4][2]="#<#    T          #>#",
	LV[4][3]="# # ##   # #$  ##M# #",
	LV[4][4]="! #  ###=# ### #$$# #",
	LV[4][5]="! #% ##%   ##  M$$# #",
	LV[4][6]="# ## ##$ ###= ===## #",
	LV[4][7]="# #  ##  #$#$       #",
	LV[4][8]="#   ##H   H###==###$#",
	LV[4][9]="###############==####",
	LVN[4]=9,LVM[4]=20,LVX[4]=2,LVY[4]=1,
	LV[5][1]= "####################",
	LV[5][2]= "#<   %    #        #",
	LV[5][3]= "#  #   #$ #     #  #",
	LV[5][4]= "#M###M###M## #M### #",
	LV[5][5]= "#  #  #      # $#  #",
	LV[5][6]= "#  #  #$$$#  #$$# M#",
	LV[5][7]= "##M######M########M#",
	LV[5][8]= "#  #  #$  M  #$$#  #",
	LV[5][9]= "#  M  #$$$#  M$$# >#",
	LV[5][10]="####################",
	LVN[5]=10,LVM[5]=20,LVX[5]=2,LVY[5]=1,
	LV[6][1]= "##########",
	LV[6][2]= "#< $$$$$$#",
	LV[6][3]= "#$      $#",
	LV[6][4]= "#$$$$$$ >#",
	LV[6][5]= "##########",
	LVN[6]=5,LVM[6]=10,LVX[6]=2,LVY[6]=1,
	LV[7][1]= "#####===#######################=====###......",
	LV[7][2]= "#< M     ##$$       $#                #......",
	LV[7][3]= "#  #  #   #$    #==#$#M##M####===#==# #====##",
	LV[7][4]= "!M###M#= ##==#= #$$###  #  >     M  # M     #",
	LV[7][5]= "!  #$$#      M  #$$  #  ##########  ! #===# #",
	LV[7][6]= "#  #$ #      M  #M#=M=# #$$      #  # # H # #",
	LV[7][7]= "#= ####==M===#### #   # ######===#  # M $ # #",
	LV[7][8]= "#  #  #   # $#$$  # > # #  #     #  # #===# #",
	LV[7][9]= "!  M  #   M$ M$$  #   # #  # #=# #  # #  #  #",
	LV[7][10]="! =#####==#===#####===#T#  #M#H# !  # M  #  #",
	LV[7][11]="!  M                  #T#  # #H# !  # #==#  #",
	LV[7][12]="#MM#######====#MM######T#  # #$# !  # #  #  #",
	LV[7][13]="#  #H <#              # #  #M# T M  # M  #  #",
	LV[7][14]="#  #H  #              # #  # ###===## ####MM#",
	LV[7][15]="#  #$$ #              M M  #        # #HH#  #",
	LV[7][16]="#  #== #==============# #  # # #==# # #  #  #",
	LV[7][17]="#  MM  M              M #  # # #$$# # #     #",
	LV[7][18]="#  ####M#####======######==# # #K$# # #     #",
	LV[7][19]="#                              M  #   #######",
	LV[7][20]="####################====###########==##......",
	LVN[7]=20,LVM[7]=45,LVX[7]=2,LVY[7]=1,
	LV[8][ 1]="##################################################",
	LV[8][ 2]="#<H#>             $$#                      MMMMMM#",
	LV[8][ 3]="#MT####################-#############M########## #",
	LV[8][ 4]="#$M$$#MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM######$$$$$#",
	LV[8][ 5]="#MT$$MM#<##TT###############################M#####",
	LV[8][ 6]="######TTT###MMMM#$$$KM#   HHHH$$$###########M#$$##",
	LV[8][ 7]="#$M$$#MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM######$$$$$#",
	LV[8][ 8]="#MT$$MM#<##T################################M#####",
	LV[8][ 9]="######TTT#>#MMMM#$$$KM#   HHHH$$$#>#########M#$$##",
	LV[8][10]="#######$#$MMMMMM#$THM#    $$$$#K# MM$$#    #  M$$#",
	LV[8][11]="##$$MMMH#######T#M$M  M####### #  #$#$#M#    # M$#",
	LV[8][12]="#$$$MM#H#$$HK#$M#$$M  #$$$#$$#  # M$$#$K|M# #   M#",
	LV[8][13]="####### #$M####$####  #$$$#M## #   ###$$#  # $ M #",
	LV[8][14]="#$|KH$# #$M #  #      #$$M#$$#    #  ##$#   # M  #",
	LV[8][15]="#HM$$T# #-#   #  ####M#KMKM$$##  #     # #   M   #",
	LV[8][16]="#MTMT$M #$T#### #$$$$$#M######  #  ###    # M # T#",
	LV[8][17]="####### !$$$$$$$#$$$$$|        #  #$$$###  #   T #",
	LV[8][18]="#$$M  M ######## ### ########### #$MMM   #  # T ##",
	LV[8][19]="#$$#  #                       M  #       M   #   #",
	LV[8][20]="#-T#M#  #$####################M##  ========##$#  #",
	LV[8][21]="#MM# # ###KM       M     $#   #H$M          M$$#H#",
	LV[8][22]="# #  # M  #$M##########M #$M#M##########M######$##",
	LV[8][23]="#M#  ####  #$M#  !!!$#  #$M#  #        M M$$$#   #",
	LV[8][24]="# # M$$$#=M #$M# =#>#  #$M#  =#   #===M M M$$#   #",
	LV[8][25]="# # |$#M# =  #$M# M#  #$M#  =$#   #$$M M$M M$#   #",
	LV[8][26]="# # |TH$#$ =  #$M#   #$M# M=$$#   #$M M$M$M M#   #",
	LV[8][27]="# # |=-=# $ =  #$M# #$M# M-$$$#   #T#MTMTMT#T#   #",
	LV[8][28]="#H# |$HH#$ $ =  #$M#$M#  =$$$$#  #HHH#$T$T#HHH#  #",
	LV[8][29]="##< |$MM# H M =  #$$M#  =$$$$$#  #MTM#H$H$#MTM#  #",
	LV[8][30]="##  |$$$#$ M T M  #$#  =$$$$$$#  #$$$#$H$H#$$$#  #",
	LV[8][31]="#$##M###$ H M T =  #  =$$$$$$$#   #M# #### #M#  M#",
	LV[8][32]="#$$$$$$$#$ $ M T = M =$$$$$$$$#                MM#",
	LV[8][33]="######################M#########################M#",
	LV[8][34]="#$$$$$$$|$$$$$$$$MMMMM$$$$$MMMMMMMMMMMMMMMMMMMMMM#",
	LV[8][35]="#$$$$MMMMMMMM$$$$$$$MMMMMMMMM#MMMMMM$$$$$$$$MMMMM#",
	LV[8][36]="##################################################",
	LVN[8]=36,LVM[8]=50,LVX[8]=2,LVY[8]=1,lv=1;
	for (Rint move = 1;;){
		_map[1]="|                         Level "+intosnum(lv,0)+"                          |";
		for (Rint i=5; i<11; i++)
			for (Rint j=36; j<47; j++){
				Rint nx=i-7+LVX[lv],ny=j-40+LVY[lv];
				if (nx<1||nx>LVN[lv]||ny<0||ny>LVM[lv])
					_map[i][j]='.';
				else _map[i][j]=LV[lv][nx][ny];
			}
		_map[7][40]='@',
		ChangeMap(0,16,0,59);
		for (;;){
			for (Rint i=5; i<11; i++)
				for (Rint j=36; j<47; j++){
					Rint nx=i-7+LVX[lv],ny=j-40+LVY[lv];
					if (nx<1||nx>LVN[lv]||ny<0||ny>LVM[lv])
						_map[i][j]='.';
					else _map[i][j]=LV[lv][nx][ny];
				}
			_map[7][40]='@';
			if (move)
				pmp(),Exprint--,move=0;
			while (!_kbhit())
				cursor(12,41),cout<<intosnum(clock()/1000,6),
				cursor(11,54),cout<<intosloat(score,5);
			char ch=getch();
			int kx=LVX[lv],ky=LVY[lv];
			switch (ch){
				case 'w':
					kx--,move=1;
					break;
				case 's':
					kx++,move=1;
					break;
				case 'a':
					ky--,move=1;
					break;
				case 'd':
					ky++,move=1;
					break;
				case 'e':
					gotoshop();
					continue;
				case 'q':
					_map[3] ="| +------------------------------+ |HP:"+intosnum(HP,5)+"   | ATK |Money|   ",
					_map[4] ="| |         Information          | +-----------+ "+intosnum(atk,3)+" |"+intosnum(money,5)+"|   ",
					_map[5] ="| +------------------------------+ |           |     +-----+   ",
					_map[6] ="| |"+Infor(0,0,0,1)+"| |           |     |K:"+intosnum(key,3)+"|   ",
					_map[7] ="| |"+Infor(0,0,0,2)+"| |           | DEF |K: 1 |   ",
					_map[8] ="| |"+Infor(0,0,0,3)+"| |           | "+intosnum(def,3)+" |K: 1 |   ",
					_map[9] ="| |"+Infor(0,0,0,4)+"| |           |     +-----+   ",
					_map[10]="| |"+Infor(0,0,0,5)+"| |           |     |Score|   ",
					_map[11]="| |"+Infor(0,0,0,6)+"| +-----------+     |"+intosloat(score,5)+"|   ",
					_map[12]="| +------------------------------+ |Time:"+intosnum(clock()/1000,6)+"|     |     |   ";
					for (Rint i=3,j; i<13; i++)
						for (cursor(i,j=1); j<34; j++)
							putchar(_map[i][j]);
					quit = 1;
					continue;
				case 'r':
					if (quit)
						return;
			}
			if (move)
			{
				switch (LV[lv][kx][ky]){
					case '!':
					case '=':
					case '-':
					case '|':
					case '#':
						move = 0;
						continue;
					case '%':
						_map[3] ="| +------------------------------+ |HP:"+intosnum(HP,5)+"   | ATK |Money|   ",
						_map[4] ="| |         Information          | +-----------+ "+intosnum(atk,3)+" |"+intosnum(money,5)+"|   ",
						_map[5] ="| +------------------------------+ |           |     +-----+   ",
						_map[6] ="| |"+Infor(lv,kx,ky,1)+"| |           |     |K:"+intosnum(key,3)+"|   ",
						_map[7] ="| |"+Infor(lv,kx,ky,2)+"| |           | DEF |K: 1 |   ",
						_map[8] ="| |"+Infor(lv,kx,ky,3)+"| |           | "+intosnum(def,3)+" |K: 1 |   ",
						_map[9] ="| |"+Infor(lv,kx,ky,4)+"| |           |     +-----+   ",
						_map[10]="| |"+Infor(lv,kx,ky,5)+"| |           |     |Score|   ",
						_map[11]="| |"+Infor(lv,kx,ky,6)+"| +-----------+     |"+intosloat(score,5)+"|   ",
						_map[12]="| +------------------------------+ |Time:"+intosnum(clock()/1000,6)+"|     |     |   ";
						Exprint = 3;
						break;
					case '$':
						if (lv%6) score+=0.2;
						LV[lv][kx][ky]=' ',money++,cursor(4,54),
							cout<<intosnum(money,5)<<endl;
						_map[11]="|   +-----+-----+-----+-----+      +-----------+     |"+intosloat(score,5)+"|   ",
						_map[4] ="| +-----+-----+-----+-----+        +-----------+ "+intosnum(atk,3)+" |"+intosnum(money,5)+"|   ";
						break;
					case 'K':
						LV[lv][kx][ky]=' ',key++,score+=0.3,cursor(6,56),cout<<intosnum(key,3)<<endl,
						_map[11]="|   +-----+-----+-----+-----+      +-----------+     |"+intosloat(score,5)+"|   ",
						_map[6]="| | Quit|  Up | Shop|Agree|        |           |     |K:"+intosnum(key,3)+"|   ";
						break;
					case 'M':
						if (!key)
						{
							move=0;
							continue;
						}
						LV[lv][kx][ky]=' ',score+=0.1,key--;cursor(6,56),cout<<intosnum(key,3)<<endl,
						_map[11]="|   +-----+-----+-----+-----+      +-----------+     |"+intosloat(score,5)+"|   ",
						_map[6]="| | Quit|  Up | Shop|Agree|        |           |     |K:"+intosnum(key,3)+"|   ";
						break;
					case 'T':
					{
						cursor(14,0),
						cout<<(_map[14]="|                 You steppend on a trap.                  |   ")<<endl,
						LV[lv][kx][ky]=' ',HP-=20,score-=(0.2),cursor(3,39),cout<<intosnum(HP,gx=5)<<endl,
						_map[11]="|   +-----+-----+-----+-----+      +-----------+     |"+intosloat(score,5)+"|   ",
						_map[3]="|                                  |HP:"+intosnum(HP,5)+"   | ATK |Money|   ";
						if(HP<=0){
							system("cls");
							puts("You lose");
							system("pause");
							return;
						}
						break;
					}
					case 'H':
					{
						cursor(14,0),
						cout<<(_map[14]="|                         HP++                             |   ")<<endl,
						LV[lv][kx][ky]=' ',HP+=10,score+=(0.1),cursor(3,39),cout<<intosnum(HP,gx=5)<<endl;
						_map[11]="|   +-----+-----+-----+-----+      +-----------+     |"+intosloat(score,5)+"|   ",
						_map[3]="|                                  |HP:"+intosnum(HP,5)+"   | ATK |Money|   ";
						break;
					}
				}
				gx--;
				if (!gx)
					cursor(14,0),cout<<(_map[14]="|               This game is provided by HTJ.              |   ")<<endl;
				if (LV[lv][kx][ky]=='>')
				{
					lv++,
					system("cls");
					break;
				}
				else if (LV[lv][kx][ky]=='<')
				{
					lv--,
					system("cls");
					break;
				}
				LVX[lv]=kx,LVY[lv]=ky;
			}
			else{
				cursor(12,41);
				cout<<intosnum(clock()/1000,6);
			}
		}
		Sleep(500);
	}
}
int main()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = false;
//	CursorInfo.dwSize = 1;
	SetConsoleCursorInfo(handle, &CursorInfo);
	Labyrinth();
	return 0;
}


