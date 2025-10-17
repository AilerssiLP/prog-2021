#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "k.h"
//biatch
void add_random_tile(struct game *game){
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}

bool is_game_won(const struct game game){
    for(int i=0; i<4;i++){
        for(int j=0; j<4;j++){
            if(game.board[i][j]==75){
                return true;
            }
        }
    }
    return false;
}

bool is_move_possible(const struct game game){
    for(int i=0; i<4;i++){
        for(int j=0; j<4;j++){
            if(game.board[i][j]==10){
                return true;
            }
            if(i==3 && j==3){
                if(game.board[i][j]==game.board[i-1][j] || game.board[i][j]==game.board[i-1][j])
                    return true;
            }else if(i==0 && j==0){
                if(game.board[i][j]==game.board[i+1][j] || game.board[i][j]==game.board[i][j+1])
                    return true;
            }else if(i==3 && j==0){
                if(game.board[i][j]==game.board[i][j+1] || game.board[i][j]==game.board[i+1][j])
                    return true;
            }else if(i==0 && j==3){
                if(game.board[i][j]==game.board[i+1][j] || game.board[i][j]==game.board[i][j-1])
                    return true;
            }else if(i==0){
                if(game.board[i][j]==game.board[i+1][j] || game.board[i][j]==game.board[i][j-1] || game.board[i][j]==game.board[i][j+1])//sre
                    return true;
            }else if(i==3){
                if(game.board[i][j]==game.board[i-1][j] || game.board[i][j]==game.board[i][j-1] || game.board[i][j]==game.board[i][j+1])
                    return true;
            }else if(j==0){
                if(game.board[i][j]==game.board[i+1][j] || game.board[i][j]==game.board[i-1][j] || game.board[i][j]==game.board[i][j+1])
                    return true;
            }else if(j==3){
                if(game.board[i][j]==game.board[i+1][j] || game.board[i][j]==game.board[i-1][j] || game.board[i][j]==game.board[i][j-1])
                    return true;
            }else if(j==3){
                if(game.board[i][j]==game.board[i+1][j] || game.board[i][j]==game.board[i-1][j] || game.board[i][j]==game.board[i][j-1] || game.board[i][j]==game.board[i][j+1])
                    return true;
            }else{
                if(game.board[i][j]==game.board[i+1][j] || game.board[i][j]==game.board[i-1][j] || game.board[i][j]==game.board[i][j-1] || game.board[i][j]==game.board[i][j+1]){
                    return true;
                    }
                if(game.board[i][j]==32){
                    return true;
                    }
            }
        }
    }
    return false;
}
bool update(struct game *game, int dy, int dx){
    int a=0;
    if(is_move_possible(*game)==false){//idk about dis
        return false;
    }

    if (dy==dx){
        return false;
    }else if ((dy==1 ||dy==-1) && (dx==1 || dx==-1)){
        return false;
    }else if(dx==1){///////right move
    //int b=0;
        for(int i =3; 0<=i; i--){
            for (int j = 3; 0<j; j--){
                if(game->board[i][j] ==32 && game->board[i][j]<game->board[i][j-1]){
                    game->board[i][j]=game->board[i][j-1];
                    game->board[i][j-1]=32;
                    j=3;
                    a=1;
                }
        }
        }
        
        ////
        for(int i =3; 0<=i; i--){
            for (int j = 3; 0<j; j--){
                if(game->board[i][j]==game->board[i][j-1] && game->board[i][j]!=32){         //ak su rovnake                
                    game->board[i][j]++;
                    game->board[i][j-1]=32;

                    int c = game->board[i][j] - 64;//score problem
                    int nas =2;
                    for (int l = 1; l<c;l++){
                        nas = nas*2;
                        }
                    game->score = game->score + nas;
                    a=1;
                    c=0;

                }else if(game->board[i][j] ==32 && game->board[i][j]<game->board[i][j-1]){  //ak je space ale dalsie je vac
                    game->board[i][j]=game->board[i][j-1];
                    game->board[i][j-1]=32;


                    if(game->board[i][j]==game->board[i][j+1] && game->board[i][j]!=32){               
                        game->board[i][j+1]++;
                        game->board[i][j]=32;
                        
                        int c = game->board[i][j+1] - 64;//score problem
                        int nas =2;
                        for (int l = 1; l<c;l++){
                            nas = nas*2;
                            }
                        game->score = game->score + nas;
                        c=0;
                        a=1;
                    }

                }
            }
        }


    }else if(dx==-1){///////left move
    //int b=0;
        for(int i =0; 3>=i; i++){
            for (int j =0; 3>j; j++){
                if(game->board[i][j] ==32 && game->board[i][j]<game->board[i][j+1]){
                    game->board[i][j]=game->board[i][j+1];
                    game->board[i][j+1]=32;
                    j=0;
                    a=1;
                }
            }
        }

        //printf("%s",game->board[0]);
        ////
        for(int i =0; 3>=i; i++){
            for (int j =0; 3>j; j++){
                if(game->board[i][j]==game->board[i][j+1] && game->board[i][j]!=32){         //ak su rovnake                
                    game->board[i][j]++;
                    game->board[i][j+1]=32;

                    int c = game->board[i][j] - 64;//score problem
                    int nas =2;
                    for (int l = 1; l<c;l++){
                        nas = nas*2;
                        }
                    game->score = game->score + nas;
                    a=1;
                    c=0;
                    //if(game->board[i][0]==game->board[i][1] && game->board[i][j]!=32){
                    //    b=1;
                    //}
                }else if(game->board[i][j] ==32 && game->board[i][j]<game->board[i][j+1]){  //ak je space ale dalsie je vac
                    game->board[i][j]=game->board[i][j+1];
                    game->board[i][j+1]=32;

                    if(game->board[i][j]==game->board[i][j-1] && game->board[i][j]!=32){               
                        game->board[i][j-1]++;
                        game->board[i][j]=32;
                        
                        int c = game->board[i][j-1] - 64;//score problem
                        int nas =2;
                        for (int l = 1; l<c;l++){
                            nas = nas*2;
                            }
                        game->score = game->score + nas;
                        c=0;
                        a=1;
                    }
                }
            }
        }


    }else if(dy==-1){///////top move
        for(int j =0; 3>=j; j++){
            for (int i =0; 3>i; i++){
                if(game->board[i][j] ==32 && game->board[i][j]<game->board[i+1][j]){
                    game->board[i][j]=game->board[i+1][j];
                    game->board[i+1][j]=32;
                    i=0;
                    a=1;
                }
        }
        }
        ////
        for(int j =0; 3>=j; j++){
            for (int i =0; 3>i; i++){
                if(game->board[i][j]==game->board[i+1][j] && game->board[i][j]!=32){         //ak su rovnake                
                    game->board[i][j]++;
                    game->board[i+1][j]=32;

                    int c = game->board[i][j] - 64;//score problem
                    int nas =2;
                    for (int l = 1; l<c;l++){
                        nas = nas*2;
                        }
                    game->score = game->score + nas;
                    a=1;
                    c=0;
                }else if(game->board[i][j] ==32 && game->board[i][j]<game->board[i+1][j]){  //ak je space ale dalsie je vac
                    game->board[i][j]=game->board[i+1][j];
                    game->board[i+1][j]=32;

                    if(game->board[i][j]==game->board[i-1][j] && game->board[i][j]!=32){               
                        game->board[i-1][j]++;
                        game->board[i][j]=32;
                        
                        int c = game->board[i-1][j] - 64;//score problem
                        int nas =2;
                        for (int l = 1; l<c;l++){
                            nas = nas*2;
                            }
                        game->score = game->score + nas;
                        c=0;
                        a=1;
                    }
                }
            }
        }

    }else if(dy==1){///////down move
        for(int j =0; 3>=j; j++){
            for (int i =3; i>0; i--){
                if(game->board[i][j] ==32 && game->board[i][j]<game->board[i-1][j]){
                    game->board[i][j]=game->board[i-1][j];
                    game->board[i-1][j]=32;
                    i=3;
                    a=1;
                }
        }
        }
        ////
        for(int j =0; 3>=j; j++){
            for (int i =3; i>0; i--){
                if(game->board[i][j]==game->board[i-1][j] && game->board[i][j]!=32){         //ak su rovnake                
                    game->board[i][j]++;
                    game->board[i-1][j]=32;
                    
                    int c = game->board[i][j] - 64;//score problem
                    int nas =2;
                    for (int l = 1; l<c;l++){
                        nas = nas*2;
                        }
                    game->score = game->score + nas;
                    a=1;
                    c=0;
                }else if(game->board[i][j] ==32 && game->board[i][j]<game->board[i-1][j]){  //ak je space ale dalsie je vac
                    game->board[i][j]=game->board[i-1][j];
                    game->board[i-1][j]=32;

                    
                    if(game->board[i][j]==game->board[i+1][j] && game->board[i][j]!=32){               
                        game->board[i+1][j]++;
                        game->board[i][j]=32;
                        
                        int c = game->board[i+1][j] - 64;//score problem
                        int nas =2;
                        for (int l = 1; l<c;l++){
                            nas = nas*2;
                            }
                        game->score = game->score + nas;
                        c=0;
                        a=1;
                    }
                }
            }
        } 
    }
    if(a==1){
        return true;
    }
    return false;
}



/* else if(((game->board[i][j]>game->board[i][j+1])||(game->board[i][j]<game->board[i][j+1])) && game->board[i][j] !=32){  //ak su rozne a niesu space
                    printf("%d je %d on %d, ",game->board[i][j],j,i);
                    continue;
                } */

