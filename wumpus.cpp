#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;

/*
 * s is for stench
 * w is for wumpus
 * g if for gold
 * b is for breeze
 * p if for pit
 * for now, a single fixed set of parameters have been taken . Run the code to see the setup of the parameters in the grid.
 * play according to the instructions.
 * reach the goal ( gold is present )
 * you have only one life and only 1 arrow to use.
 */



//structure for a tile in the grid
typedef struct tile{
	int xcord;
	int ycord;
	char features[5];
	}tile;
	

typedef struct tile* tileptr;

//structure for current loc of player
typedef struct player{
	int xcord;
	int ycord;
	
	}player;

	
tileptr* environment;
int score=1000;//initial score of the player.
player pos;//current position.
int arrow=1; // arrow to shoot the wumpus.




int checkInput(player pos,int x,int y){
	
	if(x==0 || x==3 ){
		if(y==0 || y==3){
			if((pos.xcord==x && pos.ycord==y+1) ||(pos.xcord==x+1 && pos.ycord==y) || (pos.xcord==x-1 && pos.ycord==y)){
				return 1;
				
				}
			else{
				return -1;
				}
			}
		else if(y==1 || y==2){
			if((pos.xcord==x && pos.ycord==y+1) ||(pos.xcord==x+1 && pos.ycord==y) || (pos.xcord==x && pos.ycord==y-1)){
				
				}
			else{
				
				return -1;
				}
			
			}
		}
	else if(x>=1 || x<3){
		if(y==0 || y==3){
			if((pos.xcord==x && pos.ycord==y+1) ||(pos.xcord==x+1 && pos.ycord==y) || (pos.xcord==x-1 && pos.ycord==y)){
				return 1;
				
				}
			else{
				return -1;
				}
			}
		else if(y==1 || y==2){
			if((pos.xcord==x && pos.ycord==y+1) ||(pos.xcord==x+1 && pos.ycord==y) || (pos.xcord==x-1 && pos.ycord==y) || (pos.xcord==x && pos.ycord==y-1)){
				return 1;
				}
			else{
				return -1;
				}
			}
		
		}
	
	}




void startgame(tileptr* environment,player pos){
	
	
	//cout<<"enter coordinates to move from available moves"<<endl<<'['<<x+1<<','<<y<<']'<<'\t'<<'['<<x<<','<<y+1<<']';
	
	cin>>pos.xcord>>pos.ycord;
	
	int ch=0;
	int stat=0;
	int x,y;//last loc
	// pos is for current loc
	
	while(ch!=-1){
		
		
		x=pos.xcord;
		y=pos.ycord;
		
		
		char features_temp[5];
		strcpy(features_temp,environment[x][y].features);
		
		
		if(stat!=-1){
		cout<<"CURRENT LOC FEATURES : "<<features_temp<<endl;
		if(strcmp(features_temp,"blank")==0){
			cout<<"OK\n";
			}
			
		else {
			
			
			
			int death=0;
			if(features_temp[0]=='p' || features_temp[1]=='p' ||features_temp[2]=='p' ||features_temp[3]=='p' ||features_temp[4]=='p'){
				cout<<"YOU FELL IN THE PIT : GAME OVER\n\n";
				cout<<"FINAL SCORE :  "<<score;
				death=1;
				exit(1);
				
				}
			
			if(features_temp[0]=='w' || features_temp[1]=='w' ||features_temp[2]=='w' ||features_temp[3]=='w' ||features_temp[4]=='w'){
				cout<<"WUMPUS. DEATH. GAME OVER\n";
				if(features_temp[0]=='g' || features_temp[1]=='g' ||features_temp[2]=='g' ||features_temp[3]=='g' ||features_temp[4]=='g'){
					cout<<"SADLY GOLD WAS ALSO THERE, SHOULD HAVE USED ARROW\n"<<endl;
					
					}
				cout<<"\n";
				cout<<"FINAL SCORE :  "<<score;
				death=1;
				exit(1);
				
				}
			if(features_temp[0]=='g' || features_temp[1]=='g' ||features_temp[2]=='g' ||features_temp[3]=='g' ||features_temp[4]=='g'){
				cout<<"GOLD FOUND . VICTORY\n\n";
				death=1;
				cout<<"FINAL SCORE :  "<<score;
				exit(1);
				
				}
			
			if(death!=1){
			if(features_temp[0]=='s' || features_temp[1]=='s' ||features_temp[2]=='s' ||features_temp[3]=='s' ||features_temp[4]=='s'){
				cout<<"STENCH FOUND, BEWARE OF NEXT MOVE\n";
				
				
				}
			if(features_temp[0]=='b' || features_temp[1]=='b' ||features_temp[2]=='b' ||features_temp[3]=='b' ||features_temp[4]=='b'){
				cout<<"BREEZE, BEWARE OF NEXT MOVE\n";}
			
			
				}
			
			}
		
		}
	
	
	
	
		cout<<"ENTER 1 TO CONTINUE AND -1 TO EXIT OR 2 TO SHOOT ARROW"<<endl;
		cin>>ch;
		
		if(ch==1){
	
			score--;
			//decrease score by 1 on each move.
			
			cout<<endl<<"Enter next pos"<<endl;
			cin>>pos.xcord>>pos.ycord;
			
			stat=checkInput(pos,x,y);
			
			if(stat==-1){
			pos.xcord=x;
			pos.ycord=y;
			cout<<"INVALID LOC, ENTER AGAIN\n";
			ch=1;		
			
			}
		}
		else if(ch==2){
			//shoot arrow. only once it ll be executed
				//decrease score by 10.
				score-=10;
				if(arrow>0){
				arrow--;		//arrow=0
				char choice;	//input choice for shooting arrow.
				cout<<"ENTER DIRECTION TO SHOOT ARROW 1 for LEFT 2 for RIGHT 3 for UP 4 for DOWN\n";
				cin>>choice;
				if(choice=='1'){
					
					
					int xa=pos.xcord;
					int ya=pos.ycord;
					
					char features_temp[5];
					char update[5];
					int killflag=0;
					
					//strcpy(features_temp,environment[xa][ya].features);
					//cout<<"CURR LOC FEATURES : "<<features_temp<<endl;
					
					int j;
					int i=0;
					int killpos;
					
					for(i=ya-1;i>=0;i--){
							
							memset(update,0,5);
							strcpy(features_temp,environment[xa][i].features);
							cout<<features_temp<<"\t\t";
							
							for(j=0;j<5;j++){
								
								if(features_temp[j]=='w'){
						
									killflag=1;
									killpos=i;
									break;	
									
									}
								else{
									strncat(update,&features_temp[j],1);
									
									}
								
								}
						if(killflag==1)
						break;
						
						}
					if(killflag==1){
						cout<<"WUMPUS KILLED"<<endl;
						//memset(environment[xa][i].features,0,5);
						strcpy(environment[xa][killpos].features,update);
						cout<<"UPDATED LOCATION CHANGES\t"<<update<<endl;
						
						}
						
						
					}
				else if(choice=='2'){
					
					
					int xa=pos.xcord;
					int ya=pos.ycord;
					
					char features_temp[5];
					char update[5];
					int killflag=0;
					
					//strcpy(features_temp,environment[xa][ya].features);
					//cout<<"CURR LOC FEATURES : "<<features_temp<<endl;
					
					int j;
					int i=0;
					int killpos;
					
					for(i=ya+1;i<=3;i++){
							
							memset(update,0,5);
							strcpy(features_temp,environment[xa][i].features);
							cout<<features_temp<<"\t\t";
							
							for(j=0;j<5;j++){
								
								if(features_temp[j]=='w'){
						
									killflag=1;
									killpos=i;
									break;	
									
									}
								else{
									strncat(update,&features_temp[j],1);
									
									}
								
								}
						if(killflag==1)
						break;
						
						}
					if(killflag==1){
						cout<<"WUMPUS KILLED"<<endl;
						//memset(environment[xa][i].features,0,5);
						strcpy(environment[xa][killpos].features,update);
						cout<<"UPDATED LOCATION CHANGES\t"<<update<<endl;
						
						}
						
						
					}
				else if(choice=='3'){
					
					
					int xa=pos.xcord;
					int ya=pos.ycord;
					
					char features_temp[5];
					char update[5];
					int killflag=0;
					
					//strcpy(features_temp,environment[xa][ya].features);
					//cout<<"CURR LOC FEATURES : "<<features_temp<<endl;
					
					int j;
					int i=0;
					int killpos;
					
					for(i=xa+1;i<=3;i++){
							
							memset(update,0,5);
							strcpy(features_temp,environment[i][ya].features);
							cout<<features_temp<<"\t\t";
							
							for(j=0;j<5;j++){
								
								if(features_temp[j]=='w'){
						
									killflag=1;
									killpos=i;
									break;	
									
									}
								else{
									strncat(update,&features_temp[j],1);
									update[j]=features_temp[j];
									
									}
								
								}
						if(killflag==1)
						break;
						
						}
					if(killflag==1){
						cout<<"WUMPUS KILLED"<<endl;
						//cout<<update;
						memset(environment[killpos][ya].features,0,5);
						strcpy(environment[killpos][ya].features,update);
						cout<<"UPDATED LOCATION CHANGES\t"<<update<<endl;
						
						}
						
						
					}
				else if(choice=='4'){
					
					
					int xa=pos.xcord;
					int ya=pos.ycord;
					
					char features_temp[5];
					char update[5];
					int killflag=0;
					
					//strcpy(features_temp,environment[xa][ya].features);
					//cout<<"CURR LOC FEATURES : "<<features_temp<<endl;
					
					int j;
					int i=0;
					int killpos=0;
					
					for(i=xa-1;i>=0;i--){
							
							memset(update,0,5);
							strcpy(features_temp,environment[i][ya].features);
							cout<<features_temp<<"\t\t";
							
							for(j=0;j<5;j++){
								
								if(features_temp[j]=='w'){
						
									killflag=1;
									killpos=i;
									break;	
									
									}
								else{
									strncat(update,&features_temp[j],1);
									
									}
								
								}
						if(killflag==1)
						break;
						}
					if(killflag==1){
						cout<<"WUMPUS KILLED"<<endl;
						//memset(environment[xa][i].features,0,5);
						strcpy(environment[killpos][ya].features,update);
						cout<<"UPDATED LOCATION CHANGES\t"<<update<<endl;
						
						}
						
						
					}
				
				}
			
			
			}
		
		else{
			return;
		}
	}
}


int main(){
	
	
	int i,j;
	
	pos.xcord=0;
	pos.ycord=0;
	environment=(tileptr*)malloc(4*sizeof(tileptr));
	for(i=0;i<4;i++){
		environment[i]=(tileptr)malloc(4*sizeof(tile));
		
		}
		
	j=0;
	//fixed objects for testing.
	tile node;
	node.xcord=0;
	node.ycord=0;
	strcpy(node.features,"blank");
	environment[0][0]=node;
	node.xcord=0;
	node.ycord=1;
	strcpy(node.features,"b");
	environment[0][1]=node;
	node.xcord=0;
	node.ycord=2;
	strcpy(node.features,"p");
	environment[0][2]=node;
	node.xcord=0;
	node.ycord=3;
	strcpy(node.features,"b");
	environment[0][3]=node;
	node.xcord=1;
	node.ycord=0;
	strcpy(node.features,"s");
	environment[1][0]=node;
	node.xcord=1;
	node.ycord=1;
	strcpy(node.features,"blank");
	environment[1][1]=node;
	node.xcord=1;
	node.ycord=2;
	strcpy(node.features,"b");
	environment[1][2]=node;
	node.xcord=1;
	node.ycord=3;
	strcpy(node.features,"b");
	environment[1][3]=node;
	node.xcord=2;
	node.ycord=0;
	strcpy(node.features,"sbw");
	environment[2][0]=node;
	node.xcord=2;
	node.ycord=1;
	strcpy(node.features,"sg");
	environment[2][1]=node;
	node.xcord=2;
	node.ycord=2;
	strcpy(node.features,"b");
	environment[2][2]=node;
	node.xcord=2;
	node.ycord=3;
	strcpy(node.features,"p");
	environment[2][3]=node;
	node.xcord=3;
	node.ycord=0;
	strcpy(node.features,"sp");
	environment[3][0]=node;
	node.xcord=3;
	node.ycord=1;
	strcpy(node.features,"b");
	environment[3][1]=node;
	node.xcord=3;
	node.ycord=2;
	strcpy(node.features,"blank");
	environment[3][2]=node;
	node.xcord=3;
	node.ycord=3;
	strcpy(node.features,"b");
	environment[3][3]=node;
	
	
	for(i=3;i>=0;i--){
		for(j=0;j<4;j++){
			//cout<<environment[i][j].xcord<<','<<environment[i][j].ycord<<','<<environment[i][j].features<<'\t';
			
			cout<<environment[i][j].features<<'\t';
			}
		cout<<endl;
		}
		
		
	//int x=0;
	//int y=0;
	//cout<<endl;
	
	pos.xcord=0;
	pos.ycord=0;
	cout<<endl<<"enter coordinates to start game"<<endl;
	startgame(environment,pos);//start the game.
	
	
	
}
