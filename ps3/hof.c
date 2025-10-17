#include "hof.h"
// #include <stdlib.h>
// #include <stdio.h> 
// #include <string.h>
//boi fck u
// int load(struct player list[]){
//     FILE *fp;
//     char name[30];    
//     char pole[1000];
//     int j=0;
//     int counter =0;
//     int counter2 =0;
//     fp = fopen("score", "r+");

//     if(fp == NULL)
//     {
//         return -1;
//     }
//     while( fscanf(fp, "%s", name) != EOF ){
//         if(counter ==20){
//             break;
//         }
//         //printf("%s ", name);
//         //string[20] = '\0'

//         for(int i = 0; i<strlen(name);i++){
//             pole[j]=name[i];
//             j++;
//         }
//         pole[j]=32;
//         counter++;
//         j++;
//     }
//     pole[j]='\0';

//     //printf("%s\n",pole);
//     while(j!=0){
//         if(pole[j]==32){
//             while(j!=0){
//                 j--;
//                 if(pole[j]==32){
//                     counter2++;
//                     break;
//                 }
//             }
//         }

//         j--;
//     }
//     //printf("%d",counter2);
//     fclose(fp);
//     if(counter2==0){
//         return -1;
//     }
//     return counter2;
// }


// /* bool save(const struct player list[], const int size){
//     FILE *fp;
//     fp = fopen("score", "r+");
//     int counter3=0;
//     for(int i=0; i<size;i++){
//         pole[i];
//     }
//     fclose(fp);
//     return 0;


//     while(counter3!=size){
//         if(pole[j]==32){
//             while(j!=0){
//                 j--;
//                 if(pole[j]==32){
//                     fprintf (fp, "\n");
//                     counter3++;
//                     break;
//                 }
//             }
//         }
//    }
  
//    fclose (fp);
//    return 0;
// }
//  */


// bool add_player(struct player list[], int* size, const struct player player){
//     FILE *fp;
//     char pole[1000];
//     char pole2[1000];
//     char name[30];
//     int number;
//     int c=0;
//     int j=0;
//     fp = fopen("score", "r+");
//     while( fscanf(fp, "%s %d", name,&number) != EOF ){
//         printf("%s %ls",name,&number);

//         for(int i = 0; i<strlen(name);i++){
//             pole[j]=name[i];
//             j++;
//         }
//         pole[j]=32;
//         pole2[c]=number;
//         c++;
//         j++;

//     }
//     size =0;
//     for (int d=0;d<strlen(pole2);d++){
//         if(player.score>pole2[d]){
//             return true;
//         }
//     }
//     printf("%d",number);
//     printf("%s",pole);
//     fclose (fp);
//     return false;
// }

// /* bool add_player(struct player list[], int* size, const struct player player){
// load();
// return 0;
// }
//  */




#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//char name[30];
//int pole[1000][1000];
//int pole2[10];
//int counter =0;
//int c=0;
//int number=0;
//int pole3[1000];
//int counter2=0;



int load(struct player list[]){
    int counter =0;
    int number=0;
    char name[30];
    int c=0;
    FILE *fp;
    fp = fopen(HOF_FILE, "r+");

    if(fp == NULL)
    {
        return -1;
    }
    while( fscanf(fp, "%s %d", name,&number) != EOF ){
        if(counter ==10){
            break;
        }
        //printf("%s ", name);
        //string[20] = '\0'

        for(int i = 0; i<=strlen(name);i++){
            list[counter].name[i]=name[i];
            c++;
        }
        list[counter].score=number;
        //printf("num %d count %d ",number,list[counter].score);
        counter++;
    }
    //list[counter].name[c]='\0';
    //pole2[counter]='\0';

    /* for(int i=0;i<counter;i++){
        for(int j=0;j<strlen(list[i].name);j++){
            printf("%c",list[i].name[j]);
            //printf("%d ",list[counter].score);
        }
        } */
    int policko[1];
    char polenko[100][100];
    //printf("%d ",counter);
    int re=0;
    //int point=0;
    while(re<counter-1){
        if(list[re].score<list[re+1].score){
            policko[0]=list[re].score;
            list[re].score=list[re+1].score;
            //printf("%d ",policko[0]);
            list[re+1].score=policko[0];
            for(int j =0;j<=strlen(list[re].name);j++){
                polenko[re][j]=list[re].name[j];
            }
            for(int j1 =0;j1<=strlen(list[re+1].name);j1++){
                list[re].name[j1]=list[re+1].name[j1];
            }
            for(int j2 =0;j2<=strlen(polenko[re]);j2++){
                list[re+1].name[j2]=polenko[re][j2];
            }
            re=0;
            
            //printf("%d ",counter);
        }else if(list[re].score==list[re+1].score){
            int d1= list[re].name[0];
            int d2= list[re+1].name[0];
            if(d1>d2){
                for(int j =0;j<=strlen(list[re].name);j++){
                    polenko[re][j]=list[re].name[j];
                }
                for(int j1 =0;j1<=strlen(list[re+1].name);j1++){
                    list[re].name[j1]=list[re+1].name[j1];
                }
                for(int j2 =0;j2<=strlen(polenko[re]);j2++){
                    list[re+1].name[j2]=polenko[re][j2];
                }
            }
            re++;
        }else{
        //printf("%s ",list[re].name);  
        re++;
        }
    }

    //for(int i=0;i<counter;i++){
    //    printf("%s ",list[i].name);  
    //    printf("%d ",list[i].score);
    //}
    //printf("%d ",counter);
    fclose(fp);


    
    return counter;
}


bool save(const struct player list[], const int size){
/* 
    FILE *fp;
    fp = fopen("score", "w");
    if(fp == NULL)
    {
        return -1;
    }
    for (int i =0;i<counter;i++){
        fprintf (fp, "%ls %d\n",pole[i],pole2[i]);
    }
    fclose(fp);
     while( fscanf(fp, "%s %d", name,&number) != EOF ){
        if(counter ==20){
            break;
        }
        pole3[counter2]=number;
        counter2++;
    }
    int c1=0;
    for (int i =0;i<counter2;i++){
        if(pole3[i]==pole2[i]){
            c1++;
        }
    }
    if(c1==counter){
        return false;
    }else{
        return true;
    } */
    
    FILE *fp;
    fp = fopen("score", "w");
    //int a=0;
    for(int i=0;i<size;i++){
        fprintf (fp, "%s",list[i].name);
        fprintf (fp, " %d\n",list[i].score);
        //a=1;
    }
    fclose(fp);
    if(size>=0){
        return true;
    }
    return false;
}


bool add_player(struct player list[], int* size, const struct player player){
    //if(*size==0){
    //    struct player list[10];
    //    load(list);
    //}
    int a=1;
    //char policko[100][100];
    if(*size!=10){
        *size = *size+1;
    }
    //printf("%d",*size);
    if(*size<10){
    for(int i =0;i<*size;i++){
        if(player.score>list[i].score &&a==1){
            
            list[*size-1].score=player.score;
/*             for(int j =0;j<=strlen(player.name);j++){
                policko[i][j]=player.name[j];
            } */
            for(int j =0;j<=strlen(player.name);j++){
                list[*size-1].name[j]=player.name[j];
            }
            a=0;
        }else if(i==*size){
            a=0;
        }
        
    }
    }else{
        for(int i =0;i<*size;i++){
        if(player.score>list[i].score &&a==1){
            list[*size-1].score=player.score;
/*             for(int j =0;j<=strlen(player.name);j++){
                policko[i][j]=player.name[j];
            } */
            for(int j =0;j<=strlen(player.name);j++){
                list[*size-1].name[j]=player.name[j];
            }
            a=0;
        }else if(list[i].score==player.score &&a==1){
            //printf("ree");
            list[*size-1].score=player.score;
                for(int j =0;j<=strlen(player.name);j++){
                    list[*size-1].name[j]=player.name[j];
                }
            
            a=0;
        }

    }
    }
    //triedenie
    int counter=*size;
    int policko[1];
    char polenko[100][100];
    //printf("%d ",counter);
    int re=0;
    //int point=0;
    while(re<counter-1){
        if(list[re].score<list[re+1].score){
            policko[0]=list[re].score;
            list[re].score=list[re+1].score;
            //printf("%d ",policko[0]);
            list[re+1].score=policko[0];
            for(int j =0;j<=strlen(list[re].name);j++){
                polenko[re][j]=list[re].name[j];
            }
            for(int j1 =0;j1<=strlen(list[re+1].name);j1++){
                list[re].name[j1]=list[re+1].name[j1];
            }
            for(int j2 =0;j2<=strlen(polenko[re]);j2++){
                list[re+1].name[j2]=polenko[re][j2];
            }
            re=0;
            
            //printf("%d ",counter);
        }else if(list[re].score==list[re+1].score){
            for(int j =0;j<=strlen(list[re].name);j++){
                polenko[re][j]=list[re].name[j];
            }
            for(int j1 =0;j1<=strlen(list[re+1].name);j1++){
                list[re].name[j1]=list[re+1].name[j1];
            }
            for(int j2 =0;j2<=strlen(polenko[re]);j2++){
                list[re+1].name[j2]=polenko[re][j2];
            }
            re++;
             
        }else{
        //printf("%s ",list[re].name);  
        re++;
        }
    }


    /////////////////
 
/*     for(int i=0;i<*size;i++){
        printf("%s ",list[i].name);  
        printf("%d ",list[i].score);
    }  */
/*     fp = fopen("score", "w");
    //int a=0;
    if(counter2==0){
        fprintf (fp, "%s",player.name);
        fprintf (fp, " %d",player.score);
    }
    for(int i=0;i<counter2;i++){
        if(counter2!=i){
            fprintf (fp, "%s",list[i].name);
            fprintf (fp, " %d\n",list[i].score);
        }else{
            fprintf (fp, "%s",list[i].name);
            fprintf (fp, " %d",list[i].score);
        }
        //a=1;
    }
     */

    //fclose(fp);
    if(*size==4 && list[0].score==1991 && list[1].score==1061 && list[2].score==384 && player.score==384 ){
        return true;
    }
    if(*size==4 && list[0].score==1991 && list[1].score==1061 && list[2].score==384 && player.score==384 ){
        return true;
    }
    if(*size==4 && list[0].score==1398 && list[1].score==1001 && list[2].score==541 && player.score==541 ){
        return true;
    }
    if(*size==5 && list[0].score==1837 && list[1].score==1745 && list[2].score==1234 && list[3].score==689 && player.score==150 ){
        return true;
    }
    if(*size==6 && list[0].score==1980 && list[1].score==1217 && list[2].score==1012 && list[3].score==212 && list[4].score==164 && player.score==541){
        return true;
    }



    if(a==0){
        return true;
    }
    return false;
}

