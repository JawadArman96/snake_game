#pragma comment(lib, "Winmm.lib")
# include "iGraphics.h"
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include<MMSystem.h>
#define MAX 100000
int myflag=0;
int p=200,q=200;  // food co ordinates
int flag=0;
int gameover=0;
int len=4;
int level=0;
int total_food=0;
//int speed= 100000-level*10000;
int score=0;
//int game_music_on=1;
int snakebody[MAX][2]={
	150,70,
	160,70,
	170,70,
	180,70
};
int saved;                  // game is saved or not
int snake_body_x[MAX];   //for svaing game
int snake_body_y[MAX];
int save_it=0;				//user decision of saving
int quit_it=0;                //quit

int load_it=0;          // load saved game
int load_flag=0;

int direction=-1;
int dir=-1;
int pause=0;
int done=0,final_score;
int bonus=0,bonus_x,bonus_y;
clock_t bonus_t,bonus_s;
//int len_b=0;
int high_score[10];
int score_board=0;
/*void play_music(){
	if(game_music_on) ;
}*/
void mydelay(int mseconds)
{
	clock_t start, end;
	double elapsed;
	start = clock();
	while(1)
	{
		end = clock();
		elapsed = ((double) (end - start)) / ((double)CLOCKS_PER_SEC/1000.0);
		if(elapsed>mseconds)break;
	}
}
void draw_score(int final_score,int z,int p){
	int y;
	if(!final_score) iText(z,p,"0",GLUT_BITMAP_TIMES_ROMAN_24);
		while(final_score){
			y=final_score%10;
			if(y==0) iText(z,p,"0",GLUT_BITMAP_TIMES_ROMAN_24);
			else if(y==1) iText(z,p,"1",GLUT_BITMAP_TIMES_ROMAN_24);
			else if(y==2) iText(z,p,"2",GLUT_BITMAP_TIMES_ROMAN_24);
			else if(y==3) iText(z,p,"3",GLUT_BITMAP_TIMES_ROMAN_24);
			else if(y==4) iText(z,p,"4",GLUT_BITMAP_TIMES_ROMAN_24);
			else if(y==5) iText(z,p,"5",GLUT_BITMAP_TIMES_ROMAN_24);
			else if(y==6) iText(z,p,"6",GLUT_BITMAP_TIMES_ROMAN_24);
			else if(y==7) iText(z,p,"7",GLUT_BITMAP_TIMES_ROMAN_24);
			else if(y==8) iText(z,p,"8",GLUT_BITMAP_TIMES_ROMAN_24);
			else if(y==9) iText(z,p,"9",GLUT_BITMAP_TIMES_ROMAN_24);
			final_score/=10;
			z-=15;
		}
}
void time()
{
}
void saving_display(){
	iClear();
	iText(100,400,"SAVE CUREENT GAME",GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(0,0,255);
	iFilledRectangle(180,240,70,70);
	iSetColor(255,255,255);
	iText(200,250,"YES",GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(0,0,255);
	iFilledRectangle(180,140,70,70);
	iSetColor(255,255,255);
	iText(200,150,"NO",GLUT_BITMAP_TIMES_ROMAN_24);
}
void save_game() {
	int i;
	for(i=0;i<len;i++) {
		snake_body_x[i]=snakebody[i][0];
		snake_body_y[i]=snakebody[i][1];
	}
	saved=1;
	FILE *fp;
	if((fp=fopen("save_game.txt","w"))==NULL) {
		printf("CANNOT OPEN SAVE_GAME FILE TO WRITE");
		exit(1);
	}
	if(fwrite(&saved,sizeof saved,1,fp)!=1) {
		printf("ERROR WRITING FILE");
		exit(1);
	}
	if(fwrite(&len,sizeof len,1,fp)!=1) {
		printf("ERROR WRITING FILE");
		exit(1);
	}
	if(fwrite(&p,sizeof p,1,fp)!=1) {                 
		printf("ERROR WRITING FILE");
		exit(1);
	}
	if(fwrite(&q,sizeof q,1,fp)!=1) {
		printf("ERROR WRITING FILE");
		exit(1);
	}
	if(fwrite(&score,sizeof score,1,fp)!=1) {
		printf("ERROR WRITING FILE");
		exit(1);
	}
	if(fwrite(&bonus_x,sizeof bonus_x,1,fp)!=1) {
		printf("ERROR WRITING FILE");
		exit(1);
	}
	if(fwrite(&bonus_y,sizeof bonus_y,1,fp)!=1) {
		printf("ERROR WRITING FILE");
		exit(1);
	}
	if(fwrite(snake_body_x,sizeof snake_body_x,1,fp)!=1) {
		printf("ERROR WRITING FILE");
		exit(1);
	}
/*	if(fwrite(snake_body_y,sizeof snake_body_y,1,fp)!=1) {
		printf("ERROR WRITING FILE");
		exit(1);
	}*/
	fclose(fp);
}
void load_game(){
	FILE *fp;
	if((fp=fopen("save_game.txt","r"))==NULL) {
		printf("CANNOT OPEN SAVE_GAME FILE TO READ");
		exit(1);
	}
	if(fread(&saved,sizeof saved,1,fp)!=1) {
		printf("ERROR READING FILE1");
		exit(1);
	}
	
	if(fread(&len,sizeof len,1,fp)!=1) {
		printf("ERROR WRITING FILE2");
		exit(1);
	}

	if(fread(&p,sizeof p,1,fp)!=1) {                 
		printf("ERROR READING FILE3");
		exit(1);
	}
	if(fread(&q,sizeof q,1,fp)!=1) {
		printf("ERROR READING FILE4");
		exit(1);
	}
	if(fread(&score,sizeof score,1,fp)!=1) {
		printf("ERROR READING FILE5");
		exit(1);
	}
	if(fread(&bonus_x,sizeof bonus_x,1,fp)!=1) {
		printf("ERROR READING FILE6");
		exit(1);
	}
	if(fread(&bonus_y,sizeof bonus_y,1,fp)!=1) {
		printf("ERROR READING FILE7");
		exit(1);
	}
	if(fread(snake_body_x,sizeof snake_body_x,1,fp)!=1) {
		printf("ERROR READING FILE8");
		exit(1);
	}
/*	if(fread(snake_body_y,sizeof snake_body_y,1,fp)!=1) {
		printf("ERROR READING FILE9");
		exit(1);
	}*/
	fclose(fp);
	int i;
	for(i=0;i<len;i++) {
		snakebody[i][0]=snake_body_x[i];
		snakebody[i][1]=snake_body_y[i];
	}
	for(;i<MAX;i++) {snakebody[i][0]=0,snakebody[i][1]=0;}
	printf("%d %d\n",p,q);
	printf("%d saved\n",saved);
	printf("%d len\n",len);
	printf("%d\n",score);

}
void insert_score()
{
	FILE *fp;
	if((fp=fopen("hall_of_fame.txt","r"))==NULL) {
		printf("ERROR READING FILE");
		exit(1);
	}
	if(fread(high_score,sizeof high_score,1,fp)!=1) {
		printf("CANNOT READ.");
		exit(1);
	}
	fclose(fp);
	int i,j;
	for(i=0;i<10;i++) if(score>high_score[i]) break;
	for(j=9;j>i;j--) high_score[j]=high_score[j-1];
	high_score[i]=score;

	if((fp=fopen("hall_of_fame.txt","w"))==NULL) {
		printf("ERROR WRITING FILE");
		exit(1);
	}
	if(fwrite(high_score,sizeof high_score,1,fp)!=1) {
		printf("CANNOT WRITE.");
		exit(1);
	}
	fclose(fp);
}

void _score()
{
	FILE *fp;
	if((fp=fopen("hall_of_fame.txt","r"))==NULL) {
		printf("ERROR READING FILE");
		exit(1);
	}
	if(fread(high_score,sizeof high_score,1,fp)!=1) {
		printf("CANNOT READ.");
		exit(1);
	}
	fclose(fp);
	iShowBMP(0,0,"download2.bmp");
	iSetColor(255,255,255);
	iText(40,390,":HIGHSCORES:",GLUT_BITMAP_TIMES_ROMAN_24);
	int i,value,x=80,y=350;
	for(i=0;i<5;i++) {
		value=high_score[i];
		draw_score(value,x,y);
		y-=30;
	}
	iSetColor(0,0,255);
	iFilledRectangle(280,20,140,70);
	iSetColor(255,255,255);
	iText(300,40,"<<Back",GLUT_BITMAP_TIMES_ROMAN_24);
}
void gameinitialize(){
	myflag=0;
	p=200,q=200;
	flag=0;
	bonus=0,gameover=0;
	len=4;
	level=0;
//	speed= 100000-level*10000;
	score=0;
	snakebody[0][0]=150,snakebody[0][1]=70;
	snakebody[1][0]=160,snakebody[1][1]=70;
	snakebody[2][0]=170,snakebody[2][1]=70;
	snakebody[3][0]=180,snakebody[3][1]=70;
	total_food=0;
	int i;
	for(i=4;i<MAX;i++) {snakebody[i][0]=0,snakebody[i][1]=0;}
	direction=-1;
	dir=-1;
	pause=0;
	done=0,final_score=0;
}
/*void mydelay(int mseconds)
{
	clock_t start, end;
	double elapsed;
	start = clock();
	while(1)
	{
		end = clock();
		elapsed = ((double) (end - start)) / ((double)CLOCKS_PER_SEC/1000.0);
		if(elapsed>mseconds)break;
	}
}*/
void snake(){
    int i;
	for(i=0;i<len;i++) {
		if(i==0) iSetColor(255,255,0);
		else iSetColor(255,0,0);
		iFilledRectangle(snakebody[i][0],snakebody[i][1],8,8);
	}
}
void snakemove(int direction){
	int i;
	int h_x=snakebody[0][0],h_y=snakebody[0][1];
	if(direction==1){
		for(i=len-1;i>0;i--) {
			snakebody[i][0]=snakebody[i-1][0];
			snakebody[i][1]=snakebody[i-1][1];
		}
		snakebody[0][0]+=10;
		if(h_x==490) snakebody[0][0]=10;
	}
    else if(direction==-1){
		for(i=len-1;i>0;i--) {
			snakebody[i][0]=snakebody[i-1][0];
			snakebody[i][1]=snakebody[i-1][1];
		}
		snakebody[0][0]-=10;
		if(h_x==10) snakebody[0][0]=490;	
	}
	else if (direction==2){
		for(i=len-1;i>0;i--) {
			snakebody[i][0]=snakebody[i-1][0];
			snakebody[i][1]=snakebody[i-1][1];
		}
		snakebody[0][1]+=10;
		if(h_y==480) snakebody[0][1]=0;
	}
	else if (direction==-2){
		for(i=len-1;i>0;i--) {
			snakebody[i][0]=snakebody[i-1][0];
			snakebody[i][1]=snakebody[i-1][1];
		}
		snakebody[0][1]-=10;
		if(h_y==0) snakebody[0][1]=480;
	}
}
int food(int f_x ,int f_y) {
	int h_x=snakebody[0][0]+4,h_y=snakebody[0][1]+4;
	int s=((h_x-f_x)*(h_x-f_x))+((h_y-f_y)*(h_y-f_y))-49;
	/*for(i=1;i<=len;i++) {
		if(snakebody[i][0]==h_x-4 && snakebody[i][1]==h_y-4) return 0;  // game over
	}*/
	if(s<0) return 1;  // food has just eaten
	return -1;
}
int game_over(){
	int i,h_x=snakebody[0][0],h_y=snakebody[0][1];
	for(i=1;i<=len;i++) {
		if(snakebody[i][0]==h_x && snakebody[i][1]==h_y) return 0;  // game over
	}
	if((h_x<50) || (h_x>430) ||( h_y<40) || (h_y>420)) return 0;
	return -1;
}
void maze(){
	iSetColor(0,0,255);
	iFilledRectangle(30,20,430,20);
	iFilledRectangle(30,20,20,430);
	iFilledRectangle(30,430,430,20);
	iFilledRectangle(440,20,20,430);
}
void frontpage()
{
//	iSetColor(255,255,255);
	iShowBMP(0,0,"download2.bmp");
	iSetColor(0,0,255);
	iFilledRectangle(30,60,150,70);
	iFilledRectangle(30,220,150,70);
	iFilledRectangle(200,220,150,70);
	iSetColor(255,255,255);
	iText(70,90,"NEW GAME");
	iText(60,250,"HALL OF FAME");
	iText(240,250,"QUIT GAME");
	iText(80,10,"click NEW GAME to start");
	iSetColor(0,0,255);
	iText(150,440,"SNAKE XENZIA",GLUT_BITMAP_TIMES_ROMAN_24);
//	load_game();
	/*if(saved) {
		iFilledRectangle(200,60,150,70);
		iSetColor(255,255,255);
		iText(240,90,"LOAD GAME");
		if(load_it) load_flag=1;
	}
	else */
	gameinitialize();
}
void iDraw()
{
	int result;
	double leng;
	if(quit_it) {
		saving_display();
		return ;
	}
	if(load_flag){
		gameover=0;
		done=0;
		myflag=1;
		score_board=0;
		load_flag=0;
	}
	if(gameover) {
		done=0;
		PlaySound(TEXT("ass_7.wav"), NULL, SND_ASYNC );
		insert_score();
		mydelay(2000);
		PlaySound(TEXT("GoT.wav"), NULL, SND_ASYNC );
	}
	if(done) {
		iSetColor(255,255,255);
		iText(100,225,"GAME OVER YOUR SCORE IS:",GLUT_BITMAP_TIMES_ROMAN_24);
		final_score=score;
/*		iText(150,200,final_score,GLUT_BITMAP_TIMES_ROMAN_24);*/
	//	z=230;
		draw_score(final_score,230,195);
		myflag=0;
		gameover=1;
		return ;
	}
	iClear();
	if(score_board) {
		iSetColor(255,255,255);
		_score();
		return ;
	}
	if (myflag==0) {
		frontpage();
	}
	else{
//	if(game_music_on) game_music_on=!game_music_on;  // 
	score_board=0;
	maze();
	iSetColor(0,255,0);
	iFilledRectangle(0,0,50,50);
	iSetColor(0,0,255);
	iText(5,5,"QUIT");
	iSetColor(255,0,255);
	iFilledCircle(p,q,4);
	iSetColor(255,0,0);
	snake();

	iText(50,460,"Score:",GLUT_BITMAP_TIMES_ROMAN_24);    //showing scores while playing
	draw_score(score,150,460);

	clock_t start,end;
	start=clock();
	end=clock();
	while(end-start<=50) end=clock();
	
	if(pause){
		iSetColor(255,255,255);
		iText(100,250,"PAUSE",GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(0,0,255);
		iFilledCircle(bonus_x,bonus_y,4);
		return ;
	}
	if(!(dir==-direction || dir==direction)) direction=dir;
	result=food(p,q);
	if(result==1) {
		total_food++;
		score+=5;
		len++;
		p=rand();q=rand();
		while((p<60) || (p>420) ||( q<60) || (q>420)){
			p=rand(),q=rand();
		}
		/*p=p*10,q=q*10;
		if(p<=10) p=10;
		if(q<=10) q=10;*/
	}
	if(total_food%5==0 && total_food) {
		bonus=1;
		while((bonus_x<60) || (bonus_x>420) ||( bonus_y<60) || (bonus_y>420)) {
			bonus_x=rand()%420;
			bonus_y=rand()%420;
		}
		total_food=0;
		bonus_s=clock();
	}
	if(bonus) {
		iSetColor(0,0,255);
		iFilledCircle(bonus_x,bonus_y,4);
		if(food(bonus_x,bonus_y)==1) {
			score+=15;
			snakebody[len][0]=snakebody[len-1][0];
			snakebody[len][1]=snakebody[len-1][1];
			len++;
//			total_food=0;
			bonus=0;
			bonus_x=0,bonus_y=500;
		}
		bonus_t=clock();
		leng=300-((bonus_t-bonus_s)*0.1);
		iSetColor(255,255,255);
		iRectangle(200,445,300,18);
		iSetColor(0,255,0);
		iFilledRectangle(200,445,leng,18);
		if(bonus_t-bonus_s>=3000) {
//			total_food=0;
			bonus=0;
			bonus_x=0,bonus_y=500;
		}
	}
	/*iText(100,460,"Score:",GLUT_BITMAP_TIMES_ROMAN_24);
	draw_score(score,200,460);*/
	if(game_over()==-1) {
		snakemove(direction);
//		len_b++;
	}
	else {
		done=1;
		return ;
		}
	}
	//iFilledRectangle(ct,ct,ct,20);
	//iSetColor(0,255,0);		
	//iLine(0,0,500,500);
	//ct++;
	//mydelay(100);
	//iText(25,575,"Hello World",GLUT_BITMAP_TIMES_ROMAN_24);	
}

void iMouseMove(int mx, int my)
{
}	
void iMouse(int button, int state, int mx, int my)
{
	if(((mx>=30)&&(mx<=180)) && ((my>=60) && (my<=130))) {
		myflag=1;
	//	gameinitialize();
	}                  
	if(((mx>=30)&&(mx<=180)) && ((my>=220) && (my<=290))) {score_board=1;}
	if(((mx>=280)&&(mx<=420)) && ((my>=20) && (my<=90))) {score_board=0;}
	if(((mx>=200)&&(mx<=350)) && ((my>=220) && (my<=290))) {
		quit_it=1;
		exit(1);
	}
	if(((mx>=180)&&(mx<=250)) && ((my>=140) && (my<=210))) {      //user quits
		if(quit_it) {
			exit(1);
		}
	}
	if(((mx>=180)&&(mx<=250)) && ((my>=240) && (my<=310))) {     // user saves game
		if(quit_it) {
			save_game();
			exit(1);
		}
	}
	if(((mx>=200)&&(mx<=350)) && ((my>=220) && (my<=290))) {       // user loads saved game
		load_it=1;
	}
	if(((mx>=0)&&(mx<=50)) && ((my>=0) && (my<=50))) {
		quit_it=1;                              //quit_from_game
	}
}
void iPassiveMouseMove(int mx,int my)
{
	

}
void iKeyboard(unsigned char key)
{
	if(key=='w' ) dir=2;
	else if(key=='s') dir=-2;
	else if(key=='a') dir=-1;
	else if(key=='d') dir=1;
	else if(key==' ') {
		pause=!pause;
	}
}
	
void iSpecialKeyboard(unsigned char key)
{

}

int main()
{
	load_game();
	PlaySound(TEXT("GoT.wav"), NULL, SND_ASYNC );
	iInitialize(500, 500, "Final");
	getchar();
	return 0;
}
