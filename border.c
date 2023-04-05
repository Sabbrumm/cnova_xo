//
// Created by Sabbrumm on 26.10.2022.
//
#include <stdio.h>
#include <conio.h>
#include <windows.h>

int width = 14;
int height = 14;
int mass[14][14] = {{0}};

char getsym(int i, int j){
    if (mass[i][j] == 1){
        return 'X';
    }
    if (mass[i][j] == 2){
        return 'O';
    }
    return ' ';
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    mass[0][0] = 2;
    mass[1][1] = 1;
    for (int j = 0; j<height; j++){
        if (j==0){
            for (int i = 0; i<width; i++){
                if (i==0){
                    printf("┏━━━━");
                }
                else if (i==width-1){
                    printf("┳━━━━┓");
                }
                else{
                    printf("┳━━━━");
                }
            }
            printf("\n");
            for (int i = 0; i<width; i++){
                if (i!=width-1){
                    printf("┃ %c  ", getsym(i, j));
                }

                else{
                    printf("┃ %c  ┃", getsym(i, j));
                }
            }
        }

        else if (j==height-1){
            for (int i = 0; i<width; i++){
                if (i==0){
                    printf("┣━━━━");
                }
                else if (i==width-1){
                    printf("╋━━━━┫");
                }
                else{
                    printf("╋━━━━");
                }
            }
            printf("\n");
            for (int i = 0; i<width; i++){
                if (i!=width-1){
                    printf("┃ %c  ", getsym(i, j));
                }

                else{
                    printf("┃ %c  ┃", getsym(i, j));
                }
            }
            printf("\n");
            for (int i = 0; i<width; i++){
                if (i==0){
                    printf("┗━━━━");
                }
                else if (i==width-1){
                    printf("┻━━━━┛");
                }
                else{
                    printf("┻━━━━");
                }
            }
        }
        else{
            for (int i = 0; i<width; i++){
                if (i==0){
                    printf("┣━━━━");
                }
                else if (i==width-1){
                    printf("╋━━━━┫");
                }
                else{
                    printf("╋━━━━");
                }
            }
            printf("\n");
            for (int i = 0; i<width; i++){
                if (i!=width-1){
                    printf("┃ %c  ", getsym(i, j));
                }

                else{
                    printf("┃ %c  ┃", getsym(i, j));
                }
            }
        }
        printf("\n");
    }


    int c = getch();


}