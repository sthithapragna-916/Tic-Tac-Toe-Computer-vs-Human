#include<bits/stdc++.h>
using namespace std;

 #define COMPUTER 1
 #define HUMAN 2

#define SIDE 3

#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

void ShowBoard(char board[][SIDE]){
    cout<<"\t\t\t"<<board[0][0]<<"|"<<board[0][1]<<"|"<<board[0][2]<<"\n";
    cout<<"\t\t\t-----------\n";
     cout<<"\t\t\t"<<board[1][0]<<"|"<<board[1][1]<<"|"<<board[1][2]<<"\n";
    cout<<"\t\t\t-----------\n";
     cout<<"\t\t\t"<<board[2][0]<<"|"<<board[2][1]<<"|"<<board[2][2]<<"\n";
    cout<<"\t\t\t-----------\n";
}


void ShowInstructions(){
      cout<<"\nChoose a cell numbered from 1 to 9 as below and play\n\n";

      cout<<"\t\t\t 1 | 2 | 3 \n";
      cout<<"\t\t\t-----------\n";
      cout<<"\t\t\t 4 | 5 | 6 \n";
      cout<<"\t\t\t-----------\n";
      cout<<"\t\t\t 7 | 8 | 9 \n\n"; 
}

void initialise(char board[][SIDE]){
      for(int i=0; i<SIDE ;++i){
        for(int j=0; j<SIDE ;++j){
            board[i][j]='*';
        }
      }
}

void DeclareWinner(int WhoseTurn){
    if(WhoseTurn==COMPUTER){
        cout<<"COMPUTER has won\n";
    }
    else{
        cout<<"HUMAN has won\n";
    }
}

bool RowCrossed(char board[][SIDE]){
    for(int i=0; i<SIDE;++i){
       if(board[i][0]==board[i][1] && board[i][1]==board[i][2] && board[i][0]!='*') return true;
    }
    return false;
}

bool ColumnCrossed(char board[][SIDE]){
     for(int i=0; i<SIDE;++i){
       if(board[0][i]==board[1][i] && board[1][i]==board[2][i] && board[0][i]!='*') return true;
    }
    return false; 
}

bool DiagnolCrossed(char board[][SIDE]){
      if((board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[0][0]!='*') || (board[2][0]==board[1][1] && board[1][1]==board[0][2] && board[2][0]!='*'))
         return true;

         return false;  
}

bool GameOver(char board[][SIDE]){
    return RowCrossed(board) || ColumnCrossed(board) || DiagnolCrossed(board);
}

int minimax(char board[][SIDE], int depth ,bool isAI){
    int score=0;
    int BestScore=0;
    if(GameOver(board)==true){
        if(isAI==true)
          return -10;
        if(isAI==false)
          return +10;  
    }
    else{
        if(depth<9){
            if(isAI==true){
                BestScore=-999;
                for(int i=0;i<SIDE;++i){
                    for(int j=0;j<SIDE;++j){
                        if(board[i][j]=='*'){
                            board[i][j]=COMPUTERMOVE;
                            score=minimax(board,depth+1,false);
                            board[i][j]='*';
                            if(score>BestScore){
                                BestScore=score;
                            }
                        }
                    }
                }
                return BestScore;
            }
            else{
                BestScore=999;
                for(int i=0;i<SIDE;++i){
                    for(int j=0;j<SIDE;++j){
                        if(board[i][j]=='*'){
                            board[i][j]=HUMANMOVE;
                            score=minimax(board,depth+1,true);
                            board[i][j]='*';
                            if(score<BestScore){
                                BestScore=score;
                            }
                        }
                    }
                }
                return BestScore;
            }
        }
        else{
            return 0;
        }
    }
}

int BestMove(char board[][SIDE] ,int MoveIndex){
    int x=-1,y=-1;
    int score=0, BestScore=-999;
    for(int i=0;i<SIDE;++i){
        for(int j=0;j<SIDE;++j){
            if(board[i][j]=='*'){
                board[i][j]=COMPUTERMOVE;
                score=minimax(board,MoveIndex+1,false);
                board[i][j]='*';
                if(score>BestScore){
                    BestScore=score;
                    x=i;
                    y=j;
                }
            }
        }
    }
    return x*3+y;
}

void playTicTacToe(int WhoseTurn){
       char board[SIDE][SIDE];
       int  MoveIndex=0, x=0 ,y=0;

       initialise(board);
       ShowInstructions();

       while(GameOver(board)==false && MoveIndex!=SIDE*SIDE){
          int n;
          if(WhoseTurn==COMPUTER){
            n=BestMove(board, MoveIndex);
            x=n/SIDE;
            y=n%SIDE;
            board[x][y]=COMPUTERMOVE;
            cout<<"COMPUTER has put a "<<COMPUTERMOVE<<" in cell "<<n+1<<"\n\n";
            ShowBoard(board);
            MoveIndex++;
            WhoseTurn=HUMAN;
          }

          else if(WhoseTurn==HUMAN){
            cout<<"You can insert in the following positions : ";
            for(int i=0;i<SIDE ;++i){
                for(int j=0;j<SIDE;++j){
                    if(board[i][j]=='*')
                     cout<<(i*3+j)+1<<" ";
                }
            }
            cout<<"\n\nEnter the position = ";
            cin>>n;
            n--;
            x=n/SIDE;
            y=n%SIDE;
            if(board[x][y]=='*' && n<9 && n>=0){
                board[x][y]=HUMANMOVE;
                 cout<<"HUMAN has put a "<<HUMANMOVE<<" in cell "<<n+1<<"\n\n";
                 ShowBoard(board);
                 MoveIndex++;
                 WhoseTurn=COMPUTER;
            }
            else if(board[x][y]!='*' && n<9 && n>=0){
                cout<<"\nPosition is occupied, select any one place from the available places";
            }
            else if(n<0 || n>8){
                cout<<"Invalid Position\n";
            }
          }
       }

       if(GameOver(board)==false && MoveIndex==SIDE*SIDE){
        cout<<"It's a draw\n";
       }
       else{
           if(WhoseTurn==COMPUTER)
             WhoseTurn=HUMAN;
           else if(WhoseTurn==HUMAN)
             WhoseTurn=COMPUTER;

           DeclareWinner(WhoseTurn);    
       }   
}

int main(){
    cout<<"\n------------------------------------------------------------------------\n\n";
    cout<<"\t\t\t Tic-Tac-Toe\n";
    cout<<"\n------------------------------------------------------------------------\n\n";
    char cont='y';
    do{
       char choice;
       cout<<"Do you want to start first?(y/n) : ";
       cin>>choice;

       if(choice=='n')
             playTicTacToe(COMPUTER);
       else if(choice=='y')
             playTicTacToe(HUMAN);
       else
            cout<<"Invalid choice\n";

        cout<<"\nDo you want to quit(y/n) : ";
        cin>>cont;                   
    }while(cont=='n');
}