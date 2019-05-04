#include<fstream.h>
#include<conio.h>
#include<process.h>
#include<dos.h>
#include<string.h>
#include<ctype.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define KEY_LEFT 75
#define ESC 27
#define ENT 13

fstream fios;
char map[30][30];
int turn=1;
class Map_Data	//it is the class that contains all the properties of levels
{
	int level,rows,columns;
	public:
	int retl(){
		return level;}
	int retr(){
		return rows;}
	int retc(){
		return columns;}
}tempmap;
class character	//it is the class that contains all the properties of the characters
{
	int x,y,death,cooldown,counter;
	char piece;
	public:
	character()
	{
		x=0;
		y=0;
		cooldown=0;
	}
	int retx(){
		return x;}
	void setx(int a){
		x+=a;}
	int rety(){
		return y;}
	void sety(int a){
		y+=a;}
	int retd(){
		return death;}
	void setd(int a){
		death=a;}
	int retcool(){
		return cooldown;}
	void setcool(int a){
		cooldown+=a;}
	int retcount(){
		return counter;}
	void setcount(int a){
		counter=a;}
	char retp(){
		return piece;}
	void setp(char a){
		piece=a;}
}player,enemy[200];
int a=0,b=0,count=0,backfire=0,lev,win=0,quit=0,pos=0,restart=0;
char mirror;
void menu();
int checksmash(int p,int q,character &t)  //checks if the current location can be smashed
{
	if((map[q][p]==' ')||((map[q][p]=='A')&&t.retp()==player.retp()))
		return 0;
	else if((map[q][p]!='»'&&map[q][p]!='¼'&&map[q][p]!='È'&&map[q][p]!='É'&&map[q][p]!='º'&&map[q][p]!='Í'&&map[q][p]!='Î'&&map[q][p]!='8'&&map[q][p]!='A'&&map[q][p]!='¹'&&map[q][p]!='Ë'&&map[q][p]!='Ì'&&map[q][p]!='Ê'&&map[q][p]!='Ø'&&map[q][p]!='B')&&(t.retp()==player.retp()||map[q][p]==player.retp()))
		return 1;
	else
		return 2;
}
void retrieve();
void lose()
{
	win=0;
	quit=0;
	restart=1;
	delay(800);
	clrscr();
	cprintf("YOU LOSE!");
	delay(800);
	player.setd(1);
	retrieve();
}
void surrounded() //checks if the player is surrounded by non-smashable enemies or objects
{
	if(map[player.rety()-2][player.retx()-1]=='º'||map[player.rety()-2][player.retx()-1]=='Í'||map[player.rety()-2][player.retx()-1]=='Î'||map[player.rety()-2][player.retx()-1]=='B'||map[player.rety()-2][player.retx()-1]=='8'||map[player.rety()-2][player.retx()-1]=='¹'||map[player.rety()-2][player.retx()-1]=='»'||map[player.rety()-2][player.retx()-1]=='¼'||map[player.rety()-2][player.retx()-1]=='È'||map[player.rety()-2][player.retx()-1]=='É'||map[player.rety()-2][player.retx()-1]=='Ë'||map[player.rety()-2][player.retx()-1]=='Ì'||map[player.rety()-2][player.retx()-1]=='Ê'||map[player.rety()-2][player.retx()-1]=='Ø')
		if(map[player.rety()][player.retx()-1]=='º'||map[player.rety()][player.retx()-1]=='Í'||map[player.rety()][player.retx()-1]=='Î'||map[player.rety()][player.retx()-1]=='B'||map[player.rety()][player.retx()-1]=='8'||map[player.rety()][player.retx()-1]=='¹'||map[player.rety()][player.retx()-1]=='»'||map[player.rety()][player.retx()-1]=='¼'||map[player.rety()][player.retx()-1]=='È'||map[player.rety()][player.retx()-1]=='É'||map[player.rety()][player.retx()-1]=='Ë'||map[player.rety()][player.retx()-1]=='Ì'||map[player.rety()][player.retx()-1]=='Ê'||map[player.rety()][player.retx()-1]=='Ø')
			if(map[player.rety()-1][player.retx()-2]=='º'||map[player.rety()-1][player.retx()-2]=='Î'||map[player.rety()-1][player.retx()-2]=='B'||map[player.rety()-1][player.retx()-2]=='8'||map[player.rety()-1][player.retx()-2]=='Í'||map[player.rety()-1][player.retx()-2]=='¹'||map[player.rety()-1][player.retx()-2]=='»'||map[player.rety()-1][player.retx()-2]=='¼'||map[player.rety()-1][player.retx()-2]=='È'||map[player.rety()-1][player.retx()-2]=='É'||map[player.rety()-1][player.retx()-2]=='Ë'||map[player.rety()-1][player.retx()-2]=='Ì'||map[player.rety()-1][player.retx()-2]=='Ê'||map[player.rety()-1][player.retx()-2]=='Ø')
				if(map[player.rety()-1][player.retx()]=='º'||map[player.rety()-1][player.retx()]=='Î'||map[player.rety()-1][player.retx()]=='B'||map[player.rety()-1][player.retx()]=='8'||map[player.rety()-1][player.retx()]=='Í'||map[player.rety()-1][player.retx()]=='¹'||map[player.rety()-1][player.retx()]=='»'||map[player.rety()-1][player.retx()]=='¼'||map[player.rety()-1][player.retx()]=='È'||map[player.rety()-1][player.retx()]=='É'||map[player.rety()-1][player.retx()]=='Ë'||map[player.rety()-1][player.retx()]=='Ì'||map[player.rety()-1][player.retx()]=='Ê'||map[player.rety()-1][player.retx()]=='Ø')
					lose();
}
void push(character &r)	//function used by certain enemies to push the player
{
	delay(200);
	gotoxy(r.retx(),r.rety());
	cout<<" ";
	gotoxy(player.retx(),player.rety());
	cout<<r.retp();
	if(r.rety()<player.rety()){
		if(map[r.rety()+1][r.retx()-1]!=' ')
			lose();
		else
		{
			gotoxy(player.retx(),player.rety()+1);
			cout<<player.retp();
			map[r.rety()-1][r.retx()-1]=' ';
			map[r.rety()][r.retx()-1]=r.retp();
			map[r.rety()+1][r.retx()-1]=player.retp();
			r.sety(1);
			player.sety(1);
		}
		return;
	}
	else if(r.rety()>player.rety()){

		if(map[r.rety()-3][r.retx()-1]!=' ')
			lose();
		else
		{
			gotoxy(player.retx(),player.rety()-1);
			cout<<player.retp();
			map[r.rety()-1][r.retx()-1]=' ';
			map[r.rety()-2][r.retx()-1]=r.retp();
			map[r.rety()-3][r.retx()-1]=player.retp();
			r.sety(-1);
			player.sety(-1);
		}
		return;
	}
	if(r.retx()<player.retx()){

		if(map[r.rety()-1][r.retx()+1]!=' ')
			lose();
		else
		{
			gotoxy(player.retx()+1,player.rety());
			cout<<player.retp();
			map[r.rety()-1][r.retx()-1]=' ';
			map[r.rety()-1][r.retx()]=r.retp();
			map[r.rety()-1][r.retx()+1]=player.retp();
			r.setx(1);
			player.setx(1);
		}
		return;
	}
	else{

		if(map[r.rety()-1][r.retx()-3]!=' ')
			lose();
		else
		{
			gotoxy(player.retx()-1,player.rety());
			cout<<player.retp();
			map[r.rety()-1][r.retx()-1]=' ';
			map[r.rety()-1][r.retx()-2]=r.retp();
			map[r.rety()-1][r.retx()-3]=player.retp();
			r.setx(-1);
			player.setx(-1);
		}
		return;
	}
}
void explode(int m,int n)  //function that creates explosions when certain objects are smashed
{
	map[n][m]=' ';
	for(int j=0;j<count;j++)
	{
		if(m+1==enemy[j].retx()&&n+1==enemy[j].rety()&&!enemy[j].retd())
			enemy[j].setd(1);
	}
	for(int i=0;i<count;i++)
	{
		if(n+1==enemy[i].rety()&&m==enemy[i].retx()&&!enemy[i].retd()){
			enemy[i].setd(1);
			gotoxy(m,n+1);
			cout<<" ";
			map[n][m-1]=' ';
			if(enemy[i].retp()=='X'){
				backfire=1;
				explode(m-1,n);
				backfire=0;}
			}
		else if(n+1==enemy[i].rety()&&m+2==enemy[i].retx()&&!enemy[i].retd()){
			enemy[i].setd(1);
			gotoxy(m+2,n+1);
			cout<<" ";
			map[n][m+1]=' ';
			if(enemy[i].retp()=='X'){
				backfire=1;
				explode(m+1,n);
				backfire=0;}
			}
		else if(n==enemy[i].rety()&&m+1==enemy[i].retx()&&!enemy[i].retd()){
			enemy[i].setd(1);
			gotoxy(m+1,n);
			cout<<" ";
			map[n-1][m]=' ';
			if(enemy[i].retp()=='X'){
				backfire=1;
				explode(m,n-1);
				backfire=0;}
			}
		else if(n+2==enemy[i].rety()&&m+1==enemy[i].retx()&&!enemy[i].retd()){
			enemy[i].setd(1);
			gotoxy(m+1,n+2);
			cout<<" ";
			map[n+1][m]=' ';
			if(enemy[i].retp()=='X'){
				backfire=1;
				explode(m,n+1);
				backfire=0;}
			}
		if(map[n][m-1]=='8'||map[n][m-1]=='A'||map[n][m-1]=='O'||map[n][m-1]=='$'){
			gotoxy(m,n+1);
			cout<<" ";
			map[n][m-1]=' ';}
		else if(map[n][m-1]=='0'){
			gotoxy(m,n+1);
			cout<<" ";
			map[n][m-1]=' ';
			backfire=1;
			explode(m-1,n);
			backfire=0;}
		else if(map[n][m+1]=='8'||map[n][m+1]=='A'||map[n][m-1]=='O'||map[n][m-1]=='$'){
			gotoxy(m+2,n+1);
			cout<<" ";
			map[n][m+1]=' ';}
		else if(map[n][m+1]=='0'){
			gotoxy(m+2,n+1);
			cout<<" ";
			map[n][m+1]=' ';
			backfire=1;
			explode(m+1,n);
			backfire=0;}
		else if(map[n-1][m]=='8'||map[n-1][m]=='A'||map[n][m-1]=='O'||map[n][m-1]=='$'){
			gotoxy(m+1,n);
			cout<<" ";
			map[n-1][m]=' ';}
		else if(map[n-1][m]=='0'){
			gotoxy(m+1,n);
			cout<<" ";
			map[n-1][m]=' ';
			backfire=1;
			explode(m,n-1);
			backfire=0;}
		else if(map[n+1][m]=='8'||map[n+1][m]=='A'||map[n][m-1]=='O'||map[n][m-1]=='$'){
			gotoxy(m+1,n+2);
			cout<<" ";
			map[n+1][m]=' ';}
		else if(map[n+1][m]=='0'){
			gotoxy(m+1,n+2);
			cout<<" ";
			map[n+1][m]=' ';
			backfire=1;
			explode(m,n+1);
			backfire=0;}
		if((n+1==player.rety()&&m==player.retx())&&backfire){
			gotoxy(m,n+1);
			cout<<" ";
			player.setd(1);
			backfire=0;}
		else if((n+1==player.rety()&&m+2==player.retx())&&backfire){
			gotoxy(m+2,n+1);
			cout<<" ";
			player.setd(1);
			backfire=0;}
		else if((n==player.rety()&&m+1==player.retx())&&backfire){
			gotoxy(m+1,n);
			cout<<" ";
			player.setd(1);
			backfire=0;}
		else if((n+2==player.rety()&&m+1==player.retx())&&backfire){
			gotoxy(m+1,n+2);
			cout<<" ";
			player.setd(1);
			backfire=0; }
	}
}
void smash(int p,int q,character &r)  //function used by most characters to smash
{

	if(r.retp()==player.retp()){
		for(int i=0;i<count;i++)
		{
			if(p+1==enemy[i].retx()&&q+1==enemy[i].rety()&&!enemy[i].retd()){
				enemy[i].setd(1);
				break;}
		}
	}
	delay(200);
	cout<<"\b ";
	gotoxy(p+1,q+1);
	cout<<r.retp();
	delay(200);
	cout<<"\b ";
	delay(200);
	gotoxy(r.retx(),r.rety());
	cout<<r.retp();
	if(r.retp()==player.retp())
		gotoxy(r.retx(),r.rety());
	if(map[q][p]==player.retp())
		lose();
	else if(map[q][p]=='#')
	{
		delay(800);
		clrscr();
		gotoxy(16,8);
		cout<<"º   º ÉÍÍÍÍ» º    º      º     º   ÉÍÍÍÍ» Û";
		gotoxy(16,9);
		cout<<"º   º º É» º º    º      º     º º º    º Û";
		gotoxy(16,10);
		cout<<"ÈÍËÍ¼ º ºº º º    º      º  º  º º º    º Û";
		gotoxy(16,11);
		cout<<"  º   º ºº º º    º      º  º  º º º    º Û";
		gotoxy(16,12);
		cout<<"  º   º È¼ º º    º      º  º  º º º    º  ";
		gotoxy(16,13);
		cout<<"  º   ÈÍÍÍÍ¼ ÈÍÍÍÍ¼      ÈÍÍÊÍÍ¼          ß";
		delay(1000);
		player.setd(1);
		win=1;
		retrieve();
	}
	else if(map[q][p]=='0'||map[q][p]=='X'){
		explode(p,q);
		if(player.retd())
			lose();
	}
	else
		map[q][p]=' ';
}
void spawn(int p, int q, character &z)	//function used by certain enemies to spawn more
{
	if(z.retp()=='°'){
		if(q==z.rety()-1||q==z.rety()+1){
			map[q-1][p-1]='|';
			enemy[count].setp('|');}
		else{
			map[q-1][p-1]='-';
			enemy[count].setp('-');}
		}
	else if(z.retp()=='X'){
		map[q-1][p-1]='X';
		enemy[count].setp('X');
	}
	else if(z.retp()=='B'){
		map[q-1][p-1]='B';
		enemy[count].setp('B');
	}
	else if(z.retp()=='±'){
		map[q-1][p-1]='+';
		enemy[count].setp('+');
	}
	else if(z.retp()=='²'){
		if(q==z.rety()-1){
			map[q-1][p-1]='Ê';
			enemy[count].setp('Ê');
			}
		else if(q==z.rety()+1){
			map[q-1][p-1]='Ë';
			enemy[count].setp('Ë');
			}
	       else if(p==z.retx()-1){
			map[q-1][p-1]='¹';
			enemy[count].setp('¹');
			}
	       else{
			map[q-1][p-1]='Ì';
			enemy[count].setp('Ì');
			}
	}
	if(z.retp()!='X')
		enemy[count].setcool(1);
	else{
		enemy[count].setcount(turn+2);
		enemy[count].setcool(3);}
	enemy[count].setd(0);
	enemy[count].setx(p);
	enemy[count].sety(q);
	gotoxy(p,q);
	cout<<enemy[count].retp();
	count++;
}
char compthink(character &temp)	//contains conditions that decide enemy movement 
{
	if(((temp.retx()-player.retx())*(temp.retx()-player.retx())+(temp.rety()-player.rety())*(temp.rety()-player.rety()))<25||(((temp.retx()-player.retx())*(temp.retx()-player.retx())+(temp.rety()-player.rety())*(temp.rety()-player.rety()))<36&&temp.retp()=='X')||temp.retp()=='°'||temp.retp()=='²'||temp.retp()=='±'){
		if(temp.retx()<player.retx()&&(map[temp.rety()-1][temp.retx()]==' '||map[temp.rety()-1][temp.retx()]==player.retp()))
			return KEY_RIGHT;
		else if(temp.rety()<player.rety()&&(map[temp.rety()][temp.retx()-1]==' '||map[temp.rety()][temp.retx()-1]==player.retp()))
			return KEY_DOWN;
		else if(temp.rety()>player.rety()&&(map[temp.rety()-2][temp.retx()-1]==' '||map[temp.rety()-2][temp.retx()-1]==player.retp()))
			return KEY_UP;
		else if(temp.retx()>player.retx()&&(map[temp.rety()-1][temp.retx()-2]==' '||map[temp.rety()-1][temp.retx()-2]==player.retp()))
			return KEY_LEFT;
		else
		{
			if(map[temp.rety()-1][temp.retx()-2]==' ')
				return KEY_LEFT;
			else if(map[temp.rety()-2][temp.retx()-1]==' ')
				return KEY_UP;
			else if(map[temp.rety()][temp.retx()-1]==' ')
				return KEY_DOWN;
			else if(map[temp.rety()-1][temp.retx()]==' ')
				return KEY_RIGHT;
			else
				return 0;
		}
	}
	else
		return 0;
}
void move(character &temp2)  //function to move that also uses the smash, push and spawn functions           
{
	if(!temp2.retd()){
	if(!temp2.retcool()){
		char c='\0';
		if(temp2.retp()==player.retp())
			c=getch();
		else
			c=compthink(temp2);
		gotoxy(temp2.retx()+1,temp2.rety());
		switch(c)
		{
			case KEY_UP:
				if(!checksmash(temp2.retx()-1,temp2.rety()-2,temp2))
				{
					if(temp2.retp()!='-'&&temp2.retp()!='¹'&&temp2.retp()!='Ë'&&temp2.retp()!='Ì'&&temp2.retp()!='°'&&temp2.retp()!='X'&&temp2.retp()!='B'&&temp2.retp()!='±'&&temp2.retp()!='²'&&temp2.retp()!='´'&&temp2.retp()!='Á'&&temp2.retp()!='Â'&&temp2.retp()!='Ã'&&temp2.retp()!='Ø'){
						if(map[temp2.rety()-2][temp2.retx()-1]=='A'){
							map[temp2.rety()-1][temp2.retx()-1]='A';
							cout<<"\bA";}
						else{
							map[temp2.rety()-1][temp2.retx()-1]=' ';
							cout<<"\b ";}
						temp2.sety(-1);
						map[temp2.rety()-1][temp2.retx()-1]=temp2.retp();
						gotoxy(temp2.retx(),temp2.rety());
						cout<<temp2.retp();}
					else if(temp2.retp()=='-'){
						cout<<"\b|";
						temp2.setp('|');}
					else if(temp2.retp()=='¹'||temp2.retp()=='Ë'||temp2.retp()=='Ì'){
						cout<<"\bÊ";
						temp2.setp('Ê');}
					else if((temp2.retp()=='°'&&turn%4==2)||((temp2.retp()=='±')&&turn%6==2)||((temp2.retp()=='²')&&turn%8==2)||((temp2.retp()=='X')&&(turn-temp2.retcount())%6==0)||(temp2.retp()=='B'&&(turn&&turn%8==0)))
						spawn(temp2.retx(),temp2.rety()-1,temp2);

				}
				else if(checksmash(temp2.retx()-1,temp2.rety()-2,temp2)==1)
				{
					if((temp2.retp()=='Î'||temp2.retp()=='Ê'||temp2.retp()=='Ø')&&temp2.retx()==player.retx()&&temp2.rety()==player.rety()+1)
						push(temp2);
					else if(temp2.retp()!='¹'&&temp2.retp()!='Ë'&&temp2.retp()!='Ì'&&temp2.retp()!='-'&&temp2.retp()!='°'&&temp2.retp()!='X'&&temp2.retp()!='B'&&temp2.retp()!='±'&&temp2.retp()!='²'&&temp2.retp()!='´'&&temp2.retp()!='Â'&&temp2.retp()!='Ã')
						smash(temp2.retx()-1,temp2.rety()-2,temp2);
					else if(temp2.retp()=='-'){
						cout<<"\b|";
						temp2.setp('|');}
					else if(temp2.retp()=='¹'||temp2.retp()=='Ë'||temp2.retp()=='Ì'){
						cout<<"\bÊ";
						temp2.setp('Ê');}
					else if((temp2.retp()=='°'&&turn%4==2)||((temp2.retp()=='±')&&turn%6==2)||((temp2.retp()=='²')&&turn%8==2)||((temp2.retp()=='X')&&(turn-temp2.retcount())%6==0)||(temp2.retp()=='B'&&(turn&&turn%8==0))){
						if(!checksmash(temp2.retx()-2,temp2.rety()-1,temp2))
							spawn(temp2.retx()-1,temp2.rety(),temp2);
						else if(!checksmash(temp2.retx(),temp2.rety()-1,temp2))
							spawn(temp2.retx()+1,temp2.rety(),temp2);
						else if(!checksmash(temp2.retx()-1,temp2.rety(),temp2))
							spawn(temp2.retx(),temp2.rety()+1,temp2);}
				}
				else{
					if(temp2.retp()==player.retp()){
						surrounded();
						move(temp2);}
				    }
				break;
			case KEY_DOWN:
				if(!checksmash(temp2.retx()-1,temp2.rety(),temp2))
				{
					if(temp2.retp()!='-'&&temp2.retp()!='B'&&temp2.retp()!='¹'&&temp2.retp()!='Ê'&&temp2.retp()!='Ì'&&temp2.retp()!='°'&&temp2.retp()!='X'&&temp2.retp()!='±'&&temp2.retp()!='²'&&temp2.retp()!='´'&&temp2.retp()!='Á'&&temp2.retp()!='Â'&&temp2.retp()!='Ã'&&temp2.retp()!='Ø'){
						if(map[temp2.rety()][temp2.retx()-1]=='A'){
							map[temp2.rety()-1][temp2.retx()-1]='A';
							cout<<"\bA";}
						else{
							map[temp2.rety()-1][temp2.retx()-1]=' ';
							cout<<"\b ";}
						temp2.sety(1);
						map[temp2.rety()-1][temp2.retx()-1]=temp2.retp();
						gotoxy(temp2.retx(),temp2.rety());
						cout<<temp2.retp();}
					else if(temp2.retp()=='-'){
						cout<<"\b|";
						temp2.setp('|');}
					else if(temp2.retp()=='¹'||temp2.retp()=='Ê'||temp2.retp()=='Ì'){
						cout<<"\bË";
						temp2.setp('Ë');}
					else if((temp2.retp()=='°'&&turn%4==2)||((temp2.retp()=='±')&&turn%6==2)||((temp2.retp()=='²')&&turn%8==2)||((temp2.retp()=='X')&&(turn-temp2.retcount())%6==0)||(temp2.retp()=='B'&&(turn&&turn%8==0)))
						spawn(temp2.retx(),temp2.rety()+1,temp2);
				}
				else if(checksmash(temp2.retx()-1,temp2.rety(),temp2)==1)
				{
					if((temp2.retp()=='Î'||temp2.retp()=='Ë'||temp2.retp()=='Ø')&&temp2.retx()==player.retx()&&temp2.rety()==player.rety()-1)
						push(temp2);
					else if(temp2.retp()!='-'&&temp2.retp()!='¹'&&temp2.retp()!='Ê'&&temp2.retp()!='Ì'&&temp2.retp()!='°'&&temp2.retp()!='X'&&temp2.retp()!='±'&&temp2.retp()!='²'&&temp2.retp()!='´'&&temp2.retp()!='Á'&&temp2.retp()!='B'&&temp2.retp()!='Ã')
						smash(temp2.retx()-1,temp2.rety(),temp2);
					else if(temp2.retp()=='-'){
						cout<<"\b|";
						temp2.setp('|');}
					else if(temp2.retp()=='¹'||temp2.retp()=='Ê'||temp2.retp()=='Ì'){
						cout<<"\bË";
						temp2.setp('Ë');}
					else if((temp2.retp()=='°'&&turn%4==2)||((temp2.retp()=='±')&&turn%6==2)||((temp2.retp()=='²')&&turn%8==2)||((temp2.retp()=='X'||temp2.retp()=='B')&&(turn-temp2.retcount())%6==0)||(temp2.retp()=='B'&&(turn&&turn%8==0))){
						if(!checksmash(temp2.retx()-2,temp2.rety()-1,temp2))
							spawn(temp2.retx()-1,temp2.rety(),temp2);
						else if(!checksmash(temp2.retx(),temp2.rety()-1,temp2))
							spawn(temp2.retx()+1,temp2.rety(),temp2);
						else if(!checksmash(temp2.retx()-1,temp2.rety()-2,temp2))
							spawn(temp2.retx(),temp2.rety()-1,temp2);}
				}
				else{
					if(temp2.retp()==player.retp()){
						surrounded();
						move(temp2);}
				    }
				break;
			case KEY_RIGHT:
				if(!checksmash(temp2.retx(),temp2.rety()-1,temp2))
				{
					if(temp2.retp()!='|'&&temp2.retp()!='B'&&temp2.retp()!='¹'&&temp2.retp()!='Ê'&&temp2.retp()!='Ë'&&temp2.retp()!='°'&&temp2.retp()!='X'&&temp2.retp()!='±'&&temp2.retp()!='²'&&temp2.retp()!='´'&&temp2.retp()!='Á'&&temp2.retp()!='Â'&&temp2.retp()!='Ã'&&temp2.retp()!='Ø'){
						if(map[temp2.rety()-1][temp2.retx()]=='A'){
							map[temp2.rety()-1][temp2.retx()-1]='A';
							cout<<"\bA";}
						else{
							map[temp2.rety()-1][temp2.retx()-1]=' ';
							cout<<"\b ";}
						temp2.setx(1);
						map[temp2.rety()-1][temp2.retx()-1]=temp2.retp();
						gotoxy(temp2.retx(),temp2.rety());
						cout<<temp2.retp();}
					else if(temp2.retp()=='|'){
						cout<<"\b-";
						temp2.setp('-');}
					else if(temp2.retp()=='¹'||temp2.retp()=='Ê'||temp2.retp()=='Ë'){
						cout<<"\bÌ";
						temp2.setp('Ì');}
					else if((temp2.retp()=='°'&&turn%4==2)||((temp2.retp()=='±')&&turn%6==2)||((temp2.retp()=='²')&&turn%8==2)||((temp2.retp()=='X')&&(turn-temp2.retcount())%6==0)||(temp2.retp()=='B'&&(turn&&turn%8==0)))
						spawn(temp2.retx()+1,temp2.rety(),temp2);
				}
				else if(checksmash(temp2.retx(),temp2.rety()-1,temp2)==1)
				{
					if((temp2.retp()=='Î'||temp2.retp()=='Ì'||temp2.retp()=='Ø')&&temp2.retx()==player.retx()-1&&temp2.rety()==player.rety())
						push(temp2);
					else if(temp2.retp()!='|'&&temp2.retp()!='¹'&&temp2.retp()!='Ê'&&temp2.retp()!='Ë'&&temp2.retp()!='B'&&temp2.retp()!='°'&&temp2.retp()!='X'&&temp2.retp()!='±'&&temp2.retp()!='²'&&temp2.retp()!='´'&&temp2.retp()!='Á'&&temp2.retp()!='Â')
						smash(temp2.retx(),temp2.rety()-1,temp2);
					else if(temp2.retp()=='|'){
						cout<<"\b-";
						temp2.setp('-');}
					else if(temp2.retp()=='¹'||temp2.retp()=='Ê'||temp2.retp()=='Ë'){
						cout<<"\bÌ";
						temp2.setp('Ì');}
					else if((temp2.retp()=='°'&&turn%4==2)||((temp2.retp()=='±')&&turn%6==2)||((temp2.retp()=='²')&&turn%8==2)||((temp2.retp()=='X')&&(turn-temp2.retcount())%6==0)||(temp2.retp()=='B'&&(turn&&turn%8==0))){
						if(!checksmash(temp2.retx()-1,temp2.rety(),temp2))
							spawn(temp2.retx(),temp2.rety()+1,temp2);
						else if(!checksmash(temp2.retx()-1,temp2.rety()-2,temp2))
							spawn(temp2.retx(),temp2.rety()-1,temp2);
						else if(!checksmash(temp2.retx()-2,temp2.rety()-1,temp2))
							spawn(temp2.retx()-1,temp2.rety(),temp2);}
				}
				else{
					if(temp2.retp()==player.retp()){
						surrounded();
						move(temp2);}
				    }
				break;
			case KEY_LEFT:
				if(!checksmash(temp2.retx()-2,temp2.rety()-1,temp2))
				{
					if(temp2.retp()!='|'&&temp2.retp()!='B'&&temp2.retp()!='Ì'&&temp2.retp()!='Ê'&&temp2.retp()!='Ë'&&temp2.retp()!='°'&&temp2.retp()!='X'&&temp2.retp()!='±'&&temp2.retp()!='²'&&temp2.retp()!='´'&&temp2.retp()!='Á'&&temp2.retp()!='Â'&&temp2.retp()!='Ã'&&temp2.retp()!='Ø'){
						if(map[temp2.rety()-1][temp2.retx()-2]=='A'){
							map[temp2.rety()-1][temp2.retx()-1]='A';
							cout<<"\bA";}
						else{
							map[temp2.rety()-1][temp2.retx()-1]=' ';
							cout<<"\b ";}
						temp2.setx(-1);
						map[temp2.rety()-1][temp2.retx()-1]=temp2.retp();
						gotoxy(temp2.retx(),temp2.rety());
						cout<<temp2.retp();}
					else if(temp2.retp()=='|'){
						cout<<"\b-";
						temp2.setp('-');}
					else if(temp2.retp()=='Ì'||temp2.retp()=='Ê'||temp2.retp()=='Ë'){
						cout<<"\b¹";
						temp2.setp('¹');}
					else if((temp2.retp()=='°'&&turn%4==2)||((temp2.retp()=='±')&&turn%6==2)||((temp2.retp()=='²')&&turn%8==2)||((temp2.retp()=='X')&&(turn-temp2.retcount())%6==0)||(temp2.retp()=='B'&&(turn&&turn%8==0)))
						spawn(temp2.retx()-1,temp2.rety(),temp2);

				}
				else if(checksmash(temp2.retx()-2,temp2.rety()-1,temp2)==1)
				{
					if((temp2.retp()=='Î'||temp2.retp()=='¹'||temp2.retp()=='Ø')&&temp2.retx()==player.retx()+1&&temp2.rety()==player.rety())
						push(temp2);
					else if(temp2.retp()!='|'&&temp2.retp()!='Ì'&&temp2.retp()!='Ê'&&temp2.retp()!='Ë'&&temp2.retp()!='°'&&temp2.retp()!='X'&&temp2.retp()!='B'&&temp2.retp()!='±'&&temp2.retp()!='²'&&temp2.retp()!='Á'&&temp2.retp()!='Â'&&temp2.retp()!='Ã')
						smash(temp2.retx()-2,temp2.rety()-1,temp2);
					else if(temp2.retp()=='|'){
						cout<<"\b-";
						temp2.setp('-');}
					else if(temp2.retp()=='Ì'||temp2.retp()=='Ê'||temp2.retp()=='Ë'){
						cout<<"\b¹";
						temp2.setp('¹');}
					else if((temp2.retp()=='°'&&turn%4==2)||((temp2.retp()=='±')&&turn%6==2)||((temp2.retp()=='²')&&turn%8==2)||((temp2.retp()=='X')&&(turn-temp2.retcount())%6==0)||(temp2.retp()=='B'&&(turn&&turn%8==0))){
						if(!checksmash(temp2.retx()-1,temp2.rety(),temp2))
							spawn(temp2.retx(),temp2.rety()+1,temp2);
						else if(!checksmash(temp2.retx()-1,temp2.rety()-2,temp2))
							spawn(temp2.retx(),temp2.rety()-1,temp2);
						else if(!checksmash(temp2.retx(),temp2.rety()-1,temp2))
							spawn(temp2.retx()+1,temp2.rety(),temp2);}
				}
				else{
					if(temp2.retp()==player.retp()){
						surrounded();
						move(temp2);}
				    }
				break;
			case 'r':restart=1;
				retrieve();
				break;
			case ESC:quit=1;
				retrieve();
			default: if(temp2.retp()==player.retp()){
			move(temp2);}

		}
	}
	else
		temp2.setcool(-1);
	}
}
void mapscan()	//scans the level and assigns all character variables
{
	count=0;
	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			if(map[i][j]=='@'){
				player.setd(0);
				player.setp('@');
				player.setx(j+1);
				player.sety(i+1);}
			else if(map[i][j]=='+'||map[i][j]=='Î'||map[i][j]=='-'||map[i][j]=='|'||map[i][j]=='¹'||map[i][j]=='Ë'||map[i][j]=='Ì'||map[i][j]=='Ê'||map[i][j]=='°'||map[i][j]=='X'||map[i][j]=='±'||map[i][j]=='²'||map[i][j]=='´'||map[i][j]=='Á'||map[i][j]=='Â'||map[i][j]=='Ã'||map[i][j]=='Ø'||map[i][j]=='B'){
				enemy[count].setd(0);
				enemy[count].setcount(2);
				enemy[count].setp(map[i][j]);
				enemy[count].setx(j+1);
				enemy[count].sety(i+1);
				count++;
				}
		}
	}
}
void levsel(int &x, int &y, int z[2],int z2[4],int x2=0, int y2=0)
{
	for(int l=0;l<3;l++)
		z[l]=0;
	for(int m=0;m<5;m++)
		z2[m]=0;
	textattr(7);
	cprintf("%d",lev);
	x+=x2;
	y+=y2;
	if((x2>0&&!y2)||(x2<0&&y2>0))
		lev++;
	else if((x2<0&&!y2)||(x2>0&&y2<0))
		lev--;
	gotoxy(x,y);
	textattr(128+7);
	cprintf("%d",lev);
	if(lev<10)
		cprintf("\b");
	else
		cprintf("\b\b");
}
void retrieve()	//retrieves the selected level
{
	clrscr();
	char c;
	int tempx=player.retx(),tempy=player.rety();
	player.setx(-tempx);
	player.sety(-tempy);
	for(int cd=0;cd<20;cd++)
		for(int dc=0;dc<20;dc++)
			map[cd][dc]='\0';
	for(int ab=0;ab<70;ab++){
		int tempc=enemy[ab].retcool();
		tempx=enemy[ab].retx();
		tempy=enemy[ab].rety();
		enemy[ab].setd(1);
		enemy[ab].setcool(-tempc);
		enemy[ab].setcount(2);
		enemy[ab].setx(-tempx);
		enemy[ab].sety(-tempy);
		}
	turn=1;
	if((!win||quit||lev+1>21)&&!restart){
		int x=2,y=4,check=0,secret[2],secret2[5];
		for(int l=0;l<3;l++)
			secret[l]=0;
		for(int m=0;m<5;m++)
			secret2[m]=0;
		quit=0;
		lev=1;
		cout<<"Choose a level\n\n"
		    <<"ÉÍ» ÉÍ» ÉÍ» ÉÍ» ÉÍ» ÉÍ» ÉÍ» ÉÍ» ÉÍ» ÉÍÍ» ÉÍÍ» ÉÍÍ» ÉÍÍ» ÉÍÍ» ÉÍÍ» ÉÍÍ» ÉÍÍ»\n"
		    <<"º1º º2º º3º º4º º5º º6º º7º º8º º9º º10º º11º º12º º13º º14º º15º º16º º17º\n"
		    <<"ÈÍ¼ ÈÍ¼ ÈÍ¼ ÈÍ¼ ÈÍ¼ ÈÍ¼ ÈÍ¼ ÈÍ¼ ÈÍ¼ ÈÍÍ¼ ÈÍÍ¼ ÈÍÍ¼ ÈÍÍ¼ ÈÍÍ¼ ÈÍÍ¼ ÈÍÍ¼ ÈÍÍ¼\n\n"
		    <<"ÉÍÍ» ÉÍÍ» ÉÍÍ» ÉÍÍ»\n"
		    <<"º18º º19º º20º º21º\n"
		    <<"ÈÍÍ¼ ÈÍÍ¼ ÈÍÍ¼ ÈÍÍ¼";
		gotoxy(x,y);
		textattr(128+7);
		cprintf("%d",lev);
		cprintf("\b");
		for(;;){
			switch(c=getch()){

				case KEY_RIGHT:
				if(lev<10)
					levsel(x,y,secret,secret2,4);
				else if(lev%17==0)
					levsel(x,y,secret,secret2,-71,4);
				else if(lev<21&&lev>=10)
					levsel(x,y,secret,secret2,5);
				break;
				case KEY_LEFT:
				if(lev<11&&lev>1)
					levsel(x,y,secret,secret2,-4);
				else if(((lev-1)%17==0)&&lev>1)
					levsel(x,y,secret,secret2,71,-4);
				else if(lev>=11)
					levsel(x,y,secret,secret2,-5);
				break;
				case 49:
				if(!secret[0])
					secret[0]=1;
				else
					secret[1]=1;
				break;
				case 55:
					if(secret[0]&&secret[1])
						secret[2]=1;
				break;
				case 'r':
					if(!secret2[0])
						secret2[0]=1;
				break;
				case 'a':
					if(secret2[0]&&!secret2[1])
						secret2[1]=1;
				break;
				case 's':
					if(secret2[0]&&secret2[1]&&!secret2[2])
						secret2[2]=1;
				break;
				case 'e':
					if(secret2[0]&&secret2[1]&&secret2[2]&&!secret2[3])
						secret2[3]=1;
				break;
				case 'n':
					if(secret2[0]&&secret2[1]&&secret2[2]&&secret2[3]&&!secret2[4])
						secret2[4]=1;
				break;
				case ENT:
					textattr(7);
					check=1;
				break;
				case ESC:
					textattr(7);
					menu();
				break;
				default:for(int l=0;l<3;l++)
						secret[l]=0;
			}
			if(secret[0]&&secret[1]&&secret[2]){
				lev=117;
				break;}
			else if(secret2[0]&&secret2[1]&&secret2[2]&&secret2[3]&&secret2[4]){
				lev=118;
				break;}
			else if(check)
				break;
		}
	}
	else if(restart)
		restart=0;
	else{
		win=0;
		lev++;}
	textattr(7);
	clrscr();
	fios.open("maps.dat",ios::in|ios::binary);
	while(!fios.eof())
	{
		if(!fios.eof())
		{
			fios.read((char*)&tempmap,sizeof(Map_Data));
			if(tempmap.retl()==lev)
			{
				a=tempmap.retr();
				b=tempmap.retc();
				break;
			}
			else
				pos+=tempmap.retr()*tempmap.retc();
		}
	}
	fios.close();
	fios.open("level.txt",ios::in);
	fios.seekg(pos);
	for(int i=0;i<a;i++){
		   for(int j=0;j<b;j++)
			fios.get(map[i][j]);}
	fios.close();
	pos=0;
	mapscan();
	for(int k=0;k<a;k++){
		for(int j=0;j<b;j++)
			cout<<map[k][j];
		cout<<endl;}
	while(1)
	{
		if(turn%2!=0){
			gotoxy(player.retx(),player.rety());
				move(player);}
		else{
			for(int j=0;j<count;j++)
				move(enemy[j]);
		}
		turn++;
	}
}

void credits()	//displays credits
{
	char cred[4][35];
	clrscr();
	strcpy(cred[0],"Game Design: Deviah and Manoj");
	strcpy(cred[1],"Programming: Deviah");
	strcpy(cred[2],"Artwork: Deviah and Manoj");
	strcpy(cred[3],"Tester: Sai");
	delay(400);
	for(int i=3;i>=0;i--){
		for(int j=i,k=1;j<=3;k++,j++){
			gotoxy(39-(strlen(cred[j])/2),k);
			cout<<cred[j];
		}
		if(i){
			delay(400);}
		clrscr();
	}
	for(int l=1;l<23;l++){
		for(int j=0;j<4;j++){
			gotoxy(39-(strlen(cred[j])/2),l+j);
			cout<<cred[j];
		}
		if(l<22){
			delay(400);}
		clrscr();
	}
	for(int n=3;n>=0;n--){
		for(int j=0;j<=n;j++){
			gotoxy(39-(strlen(cred[j])/2),25+j-n);
			cout<<cred[j];
		}
		delay(400);
		clrscr();
	}
	menu();
}
void menu()	//displays menu
{
	char b;
	clrscr();
	cout<<" º ÉÍÍÍËÍÍÍ» ÉÍÍÍÍÍ» ÉÍÍÍÍÍ» ÉÍÍÍÍ» ÉÍÍÍÍ» º     º ÉÍÍÍÍ»\n"
	    <<" º º   º   º º     º º     º º É» º º      º     º º É» º\n"
	    <<" º º   º   º ÌÍÍÍÍÍ¹ ÌÍÍÍËÍ¼ º ºº º º ÍÍÍ» º     º º ºº º\n"
	    <<" º º   º   º º     º º   º   º È¼ º º    º º     º º È¼ º\n"
	    <<" º º   º   º ÈÍÍÍÍÍ¼ º   º   ÈÍÍÍÍ¼ ÈÍÍÍÍ¼ ÈÍÍÍÍ º ÈÍÍÍÍ¼\n\n"
	    <<"1.INSTRUCTIONS\n\n2.LEVEL SELECT\n\n3.CREDITS\n\n4.QUIT\n";
	for(int cd=0;cd<20;cd++)
		for(int dc=0;dc<20;dc++)
			map[cd][dc]='\0';
	for(int ab=0;ab<70;ab++){
		int tempc = enemy[ab].retcool();
		enemy[ab].setd(1);
		enemy[ab].setcool(-tempc);
		enemy[ab].setcount(2);}
	turn=1;
	switch(b=getch())
	{
		case 49:clrscr();
			cout<<"\nYou are the '@' and must reach the '#' to win. Use arrow keys to move. Press ESC to quit to menu or press r to reset the level. "
			    <<"You can smash most adjacent     pieces, without replacing them. "
			    <<"'O's are normal smashable blocks but '8's cannot be smashed. "
			    <<"You switch with 'A's on moving into them. "
			    <<"'0's are bombs which     destroy adjacent pieces on smashing. "
			    <<"'+'s are enemies which can  move and smash you if you are adjacent to them. "
			    <<"'-'s and '|'s are enemies  like '+'s but must  change into one another to maneuvre. "
			    <<"'Î's are invulnerable enemies which can    move and push you if you are adjacent to them. "
			    <<"'Ë's, 'Ê's, '¹'s and 'Ì's are    enemies like 'Î's but must change into one another to maneuvre. "
			    <<"'°'s are enemies that cannot move or attack but can spawn '-'s or '|'s. "
			    <<"'±'s are enemies that   cannot  move or attack but can spawn '+'s. "
			    <<"'²'s are enemies that cannot move or  attack but can spawn '¹'s, 'Ë's, 'Ê's, or 'Ì's. "
			    <<"'X's are enemies that cannot   move or attack but can multiply and act like '0's. "
			    <<"'Á's, 'Â's, '´'s and 'Ã's are enemies that cannot move and can only smash in one direction. "
			    <<"'Ø's are like    'Î's but cannot move unless it can push.\n"
			    <<"\nPress Esc to return to the menu";
			type:
			b=getch();
			if(b==ESC)
				menu();
			else
				goto type;
			break;
		case 50:retrieve();
			break;
		case 51:credits();
			break;
		case 52:exit(0);
			break;
		default:
			menu();
	}
}
void main()
{
	clrscr();
	menu();
}
