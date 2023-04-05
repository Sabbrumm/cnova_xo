//
// Created by Sabbrumm on 25.10.2022.
//
#include <conio.h>
#include <stdio.h>
#include <windows.h>
int board[14][14] = {{0}};

int doexit = 0;

int screen = 0;
// 0 - Главное меню
// 1 - Настройка игры
// 2 - Игра
// 3 - Победа Х
// 4 - Победа 0
// 5 - Ничья
// 6 - Экран ошибки


int setupcou = 0;
// Экран Настроек
// 0 - длина
// 1 - высота
// 2 - Х для победы
// 3 - 0 для победы
// 4 - Начало игры (переключение на экран 2)



int Width = 0;
int Height = 0;

int CrossMin = 0;
int OsMin = 0;

int ChosenSqX = 0;
int ChosenSqY = 0;

int WhoTurns = 0;

void ClearAll(){
    WhoTurns = 0;
    setupcou = 0;
    Width = 0;
    Height = 0;
    CrossMin = 0;
    OsMin = 0;
}


int check_all_before_start(){
    if (Width<2 || Width > 14){
        return 0;
    }
    if (Height<2 || Height > 14){
        return 0;
    }
    if (CrossMin<2 || CrossMin > 14){
        return 0;
    }
    if (OsMin<2 || OsMin > 14){
        return 0;
    }
    return 1;
}

void CenterMenuChoses(char* S, int boo, int digit) {
    const int menulen = 62;
    unsigned int digitlen = 0;
    if (digit != -1) {
        char digitstr[10];
        itoa(digit, digitstr, 10);
        digitlen = strlen(digitstr);
    }
    unsigned int otherstringlen = strlen(S)/2;
    int somespaces = (int)(menulen-digitlen-otherstringlen)/2;
    if (!boo){
        for (int i = 0; i<somespaces; i++){
            printf(" ");
        }
        printf("%s", S);
        if (digitlen!=0){
            printf("%d", digit);
        }
    }
    else{
        for (int i = 0; i<somespaces-3; i++){
            printf(" ");
        }
        printf(">> ");
        printf("%s", S);
        if (digitlen!=0){
            printf("%d", digit);
        }
        printf(" <<");
    }


}

void VictoryScreenX(){
    PlaySound("sounds\\WinSound.wav", NULL, SND_ASYNC);
    printf("==============================================================\n"
           "\n"
           "  ########  ########  ########  ########      ####    ######\n"
           "  ##    ##  ##    ##  ##        ##          ##  ##  ##    ##\n"
           "  ##    ##  ##    ##  ######    ########    ##  ##  ##    ##\n"
           "  ##    ##  ##    ##  ##    ##  ##          ##  ##  ########\n"
           "  ##    ##  ##    ##  ##    ##  ##        ########  ##    ##\n"
           "  ##    ##  ########  ########  ########  ##    ##  ##    ##\n"
           "\n"
           "\n"
           "                          XX    XX\n"
           "                          XX    XX\n"
           "                            XXXX  \n"
           "                          XX    XX\n"
           "                          XX    XX\n"
           "                          XX    XX\n"
           "\n"
           "==============================================================");
}

void clear_board(){
    ChosenSqX = 0;
    ChosenSqY = 0;
    for (int i=0; i<14; i++){
        for (int j=0; j<14; j++){
            board[i][j]=0;
        }
    }
}

void VictoryScreenO(){
    PlaySound("sounds\\WinSound.wav", NULL, SND_ASYNC);
    printf("==============================================================\n"
           "\n"
           "  ########  ########  ########  ########      ####    ######\n"
           "  ##    ##  ##    ##  ##        ##          ##  ##  ##    ##\n"
           "  ##    ##  ##    ##  ######    ########    ##  ##  ##    ##\n"
           "  ##    ##  ##    ##  ##    ##  ##          ##  ##  ########\n"
           "  ##    ##  ##    ##  ##    ##  ##        ########  ##    ##\n"
           "  ##    ##  ########  ########  ########  ##    ##  ##    ##\n"
           "\n"
           "\n"
           "                          OOOOOOOO\n"
           "                          OO    OO\n"
           "                          OO    OO\n"
           "                          OO    OO\n"
           "                          OO    OO\n"
           "                          OOOOOOOO\n"
           "\n"
           "==============================================================");
}


void DrawScreen(){
    PlaySound("sounds\\DrawSound.wav", NULL, SND_ASYNC);
    printf("==============================================================\n"
           "\n"
           "       ##    ##  ##    ##  ##    ##  ##          ######     \n"
           "       ##    ##  ##  ####  ##    ##  ##        ##    ##     \n"
           "       ########  ####  ##  ##    ##  ######    ##    ##     \n"
           "       ##    ##  ##    ##    ######  ##    ##    ######     \n"
           "       ##    ##  ##    ##        ##  ##    ##  ##    ##     \n"
           "       ##    ##  ##    ##        ##  ######    ##    ##     \n"
           "       \n"
           "\n"
           "                      OOOOOOOO  XX    XX\n"
           "                      OO    OO  XX    XX\n"
           "                      OO    OO    XXXX  \n"
           "                      OO    OO  XX    XX\n"
           "                      OO    OO  XX    XX\n"
           "                      OOOOOOOO  XX    XX\n"
           "\n"
           "==============================================================");
}

void checkforwin(int X, int Y){
    int who_in_cell = board[X][Y];
    // проверка по строкам
    int maxstack = 1;
    int cou = 1;
    for (int i = 1; i<Width; i++){
        if (board[i][Y]==who_in_cell && board[i-1][Y]==who_in_cell){
            cou++;
            maxstack = max(maxstack, cou);
        }
        else {
            maxstack = max(maxstack, cou);
            cou = 1;
        }

    }
    // проверка по столбцам

    for (int j = 1; j<Height; j++){
        if (board[X][j]==who_in_cell && board[X][j-1]==who_in_cell){
            cou++;
            maxstack = max(maxstack, cou);
        }
        else{
            maxstack = max(maxstack, cou);
            cou=1;
        }

    }

    // проверка по главной диагонали
    int i = X;
    int j = Y;
    while (i>1 && j>1){
        i--;
        j--;
    }
    if (i==0 || j==0){
        i++;
        j++;
    }

    for (i, j; i<Width && j<Height; i++, j++){
        if (board[i][j]==who_in_cell && board[i-1][j-1]==who_in_cell) {
            cou++;
            maxstack = max(maxstack, cou);
        }
        else {
            maxstack = max(maxstack, cou);
            cou=1;
        }
    }

    // проверка по побочной диагонали
    i = X;
    j = Y;
    while (i>1 && j<Height-2){
        i--;
        j++;
    }
    if (i==0 || j==Height-1){
        i++;
        j--;
    }
    for (i, j; i<Width && j>-1; i++, j--) {
        if (board[i][j] == who_in_cell && board[i - 1][j + 1] == who_in_cell) {
            cou++;
            maxstack = max(maxstack, cou);
        } else {
            maxstack = max(maxstack, cou);
            cou = 1;
        }
    }

    // финальная проверка подряд идущих значений и реакция
    if ((maxstack >=OsMin && who_in_cell==2) || (maxstack >= CrossMin && who_in_cell==1)){
        if (who_in_cell==2){
            screen = 4;
        }
        else if (who_in_cell==1){
            screen = 3;
        }

    }
}

void checkfordraw(){
    int boo = 1;
    for (int i = 0; i<Width; i++){
        for (int j = 0; j<Height; j++){
            if (board[i][j]==0){
                boo = 0;
                break;
            }
        }
    }
    if (boo){
        screen = 5;
    }
}

void StartScreen(){
    printf("==============================================================\n"
           "\n"
           "                      XX    XX  OOOOOOOO\n"
           "                      XX    XX  OO    OO\n"
           "                        XXXX    OO    OO\n"
           "                      XX    XX  OO    OO\n"
           "                      XX    XX  OO    OO\n"
           "                      XX    XX  OOOOOOOO\n"
           "\n"
           "                   Нажмите Enter для начала\n"
           "                    Нажмите Esc для выхода\n"
           "\n"
           "==============================================================");
}

void SetupScreen(){
    printf("==============================================================\n"
           "\n");
    printf("                 === Экран настроек игры ===");
    printf("\n");
    printf("\n");
    printf("        ==! Ограничения на все значения: от 2 до 14 !==");
    printf("\n");
    printf("\n");
    CenterMenuChoses("Длина поля: ", setupcou==0, Width);
    printf("\n");
    CenterMenuChoses("Высота поля: ", setupcou==1, Height);
    printf("\n");
    printf("\n");
    CenterMenuChoses("Крестиков для победы: ", setupcou==2, CrossMin);
    printf("\n");
    CenterMenuChoses("Ноликов для победы: ", setupcou==3, OsMin);
    printf("\n");
    printf("\n");
    CenterMenuChoses("[Начать игру!]", setupcou==4, -1);
    printf("\n");
    printf("\n");
    printf("==============================================================");
}

void ErrorScreen(){
    PlaySound("sounds\\ChooseError.wav", NULL, SND_ASYNC);
    printf("==============================================================\n"
           "\n"
           "\n"
           "\n"
           "                            Ой-ой!\n"
           "\n"
           "          Кажется, вы ввели значение которое нельзя!\n"
           "           Измените настройки и попробуйте еще раз!\n"
           "                 \n"
           "        (ESC или Enter для возвращения в меню настроек)\n"
           "\n"
           "\n"
           "\n"
           "==============================================================");
}

char getsym(int i, int j){
    if (board[i][j] == 1){
        return 'X';
    }
    if (board[i][j] == 2){
        return 'O';
    }
    return ' ';
}

void ConsoleColorBlank(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
}

void ConsoleColorChosen(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);
}

void ConsoleColorRed(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
}

void ConsoleColorBlue(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
}

void print_board(int chosenX, int chosenY){
    for (int j = 0; j<Height; j++){
        if (j==0){
            for (int i = 0; i<Width; i++){
                if (i==0){
                    printf("┏━━━━");
                }
                else if (i==Width-1){
                    printf("┳━━━━┓");
                }
                else{
                    printf("┳━━━━");
                }
            }
            printf("\n");
            for (int i = 0; i<Width; i++){



                printf("┃");

                if (i==chosenX && j==chosenY){
                    ConsoleColorChosen();
                }
                else {
                    ConsoleColorBlank();
                }
                printf(" %c  ", getsym(i, j));
                ConsoleColorBlank();

                if (i==Width-1){
                    printf("┃");
                }
            }
        }

        else if (j==Height-1){
            for (int i = 0; i<Width; i++){
                if (i==0){
                    printf("┣━━━━");
                }
                else if (i==Width-1){
                    printf("╋━━━━┫");
                }
                else{
                    printf("╋━━━━");
                }
            }
            printf("\n");
            for (int i = 0; i<Width; i++){



                printf("┃");

                if (i==chosenX && j==chosenY){
                    ConsoleColorChosen();
                }
                else {
                    ConsoleColorBlank();
                }
                printf(" %c  ", getsym(i, j));
                ConsoleColorBlank();

                if (i==Width-1){
                    printf("┃");
                }
            }
            printf("\n");
            for (int i = 0; i<Width; i++){
                if (i==0){
                    printf("┗━━━━");
                }
                else if (i==Width-1){
                    printf("┻━━━━┛");
                }
                else{
                    printf("┻━━━━");
                }
            }
        }
        else{
            for (int i = 0; i<Width; i++){
                if (i==0){
                    printf("┣━━━━");
                }
                else if (i==Width-1){
                    printf("╋━━━━┫");
                }
                else{
                    printf("╋━━━━");
                }
            }
            printf("\n");
            for (int i = 0; i<Width; i++){



                printf("┃");

                if (i==chosenX && j==chosenY){
                    ConsoleColorChosen();
                }
                else {
                    ConsoleColorBlank();
                }
                printf(" %c  ", getsym(i, j));
                ConsoleColorBlank();

                if (i==Width-1){
                    printf("┃");
                }
            }
        }
        printf("\n");
        ConsoleColorBlank();
    }

}


void GameScreen(){
    printf("==============================================================\n"
           "\n");
    print_board(ChosenSqX, ChosenSqY);
    printf("\n\n");
    printf("Сейчас ход ");
    if (WhoTurns==0){
        ConsoleColorRed();
        printf("X Крестиков X");
    }
    else {
        ConsoleColorBlue();
        printf("O Ноликов O");
    }
    ConsoleColorBlank();
    printf("\n\n");
    printf("==============================================================");
}

void UI(){
    if (screen == 0){
        StartScreen();
    }
    if (screen == 1){
        SetupScreen();
    }
    if (screen == 2){
        GameScreen();
    }
    if (screen == 3){
        VictoryScreenX();
    }
    if (screen == 4){
        VictoryScreenO();
    }
    if (screen == 5){
        DrawScreen();
    }
    if (screen == 6){
        ErrorScreen();
    }
}





#define KEY_ESC 27
#define KEY_CONTROL 224
#define KEY_BACKSPACE 8
#define KEY_ENTER 13
#define KEY_CONTROL_DOWN 80
#define KEY_CONTROL_UP 72

#define KEY_CONTROL_RIGHT 77
#define KEY_CONTROL_LEFT 75

#define KEY_0 48
#define KEY_9 57

void Intercept(){
    int key = _getch();
    if (key == KEY_ESC){
        if (screen == 0){
            PlaySound("sounds\\ChooseError.wav", NULL, SND_ASYNC);
            doexit=1;
        }
        else if (screen == 1){
            PlaySound("sounds\\ChooseChange.wav", NULL, SND_ASYNC);
            setupcou = 0;
            screen = 0;
        }
        else if (screen == 6 || screen == 2 || screen==3 || screen==4 || screen==5){
            PlaySound("sounds\\ChooseChange.wav", NULL, SND_ASYNC);
            clear_board();
            ClearAll();
            setupcou = 0;
            screen = 1;
        }
    }
    if (key == KEY_ENTER){
        if (screen == 0){
            screen = 1;
            PlaySound("sounds\\ChooseMain.wav", NULL, SND_ASYNC);
        }
        else if (screen == 1){
            if (setupcou == 4){
                if (check_all_before_start()){
                    clear_board();
                    setupcou = 0;
                    screen = 2;
                    PlaySound("sounds\\ChooseMain.wav", NULL, SND_ASYNC);
                }
                else {
                    screen = 6;
                    setupcou = 0;
                    PlaySound("sounds\\ChooseError.wav", NULL, SND_ASYNC);
                }
            }
        }
        else if (screen == 2){
            if (board[ChosenSqX][ChosenSqY] == 0){
                PlaySound("sounds\\UserTurn.wav", NULL, SND_ASYNC);
                board[ChosenSqX][ChosenSqY] = (WhoTurns)?2:1;
                WhoTurns = !WhoTurns;
                checkforwin(ChosenSqX, ChosenSqY);
                checkfordraw();
            }
            else{
                PlaySound("sounds\\ChooseError.wav", NULL, SND_ASYNC);
            }
        }
        else if (screen == 6 || screen==3 || screen==4 || screen==5){
            PlaySound("sounds\\ChooseMain.wav", NULL, SND_ASYNC);
            setupcou = 0;
            screen = 1;
            clear_board();
            ClearAll();
        }
    }
    if (key == KEY_CONTROL){
        int key2 = _getch();
        if (key2 == KEY_CONTROL_DOWN){
            if (screen == 1){
                PlaySound("sounds\\ChooseChange.wav", NULL, SND_ASYNC);
                setupcou+=1;
                if (setupcou==5){
                    setupcou = 0;
                }
            }
            if (screen == 2){
                if (ChosenSqY<Height-1){
                    PlaySound("sounds\\ChooseChange.wav", NULL, SND_ASYNC);
                    ChosenSqY+=1;
                }
            }
        }
        if (key2 == KEY_CONTROL_UP){
            if (screen == 1){
                PlaySound("sounds\\ChooseChange.wav", NULL, SND_ASYNC);
                setupcou-=1;
                if (setupcou==-1){
                    setupcou = 4;
                }
            }
            if (screen == 2){
                if (ChosenSqY>0){
                    PlaySound("sounds\\ChooseChange.wav", NULL, SND_ASYNC);
                    ChosenSqY-=1;
                }
            }
        }
        if (key2 == KEY_CONTROL_LEFT){
            if (screen == 2){
                PlaySound("sounds\\ChooseChange.wav", NULL, SND_ASYNC);
                if (ChosenSqX>0){
                    ChosenSqX-=1;
                }
                else {
                    if (ChosenSqY>0){
                        ChosenSqX = Width-1;
                        ChosenSqY-=1;
                    }
                }
            }
        }
        if (key2 == KEY_CONTROL_RIGHT){
            if (screen == 2){
                PlaySound("sounds\\ChooseChange.wav", NULL, SND_ASYNC);
                if (ChosenSqX<Width-1){
                    ChosenSqX+=1;
                }
                else {
                    if (ChosenSqY<Height-1){
                        ChosenSqX = 0;
                        ChosenSqY+=1;
                    }
                }
            }
        }

    }
    if (key >=KEY_0 && key<=KEY_9){
        if (screen == 1){
            int num = key-48;
            if (setupcou==0){
                if (Width*10+num<=14){
                    PlaySound("sounds\\ChooseChange.wav", NULL, SND_ASYNC);
                    Width=Width*10+num;
                }
                else PlaySound("sounds\\ChooseError.wav", NULL, SND_ASYNC);
            }
            if (setupcou==1){
                if (Height*10+num<=14){
                    PlaySound("sounds\\ChooseChange.wav", NULL, SND_ASYNC);
                    Height=Height*10+num;
                }
                else PlaySound("sounds\\ChooseError.wav", NULL, SND_ASYNC);
            }
            if (setupcou==2){
                if (CrossMin*10+num<=14){
                    PlaySound("sounds\\ChooseChange.wav", NULL, SND_ASYNC);
                    CrossMin=CrossMin*10+num;
                }
                else PlaySound("sounds\\ChooseError.wav", NULL, SND_ASYNC);
            }
            if (setupcou==3){
                if (OsMin*10+num<=14){
                    PlaySound("sounds\\ChooseChange.wav", NULL, SND_ASYNC);
                    OsMin=OsMin*10+num;
                }
                else PlaySound("sounds\\ChooseError.wav", NULL, SND_ASYNC);
            }

        }
    }
    if (key == KEY_BACKSPACE){
        if (screen == 1){
            if (setupcou==0){
                Width=Width/10;
                PlaySound("sounds\\ChooseChange.wav", NULL, SND_ASYNC);
            }
            if (setupcou==1){
                Height=Height/10;
                PlaySound("sounds\\ChooseChange.wav", NULL, SND_ASYNC);
            }
            if (setupcou==2){
                CrossMin=CrossMin/10;
                PlaySound("sounds\\ChooseChange.wav", NULL, SND_ASYNC);
            }
            if (setupcou==3){
                OsMin=OsMin/10;
                PlaySound("sounds\\ChooseChange.wav", NULL, SND_ASYNC);
            }
        }
    }
}

int main(){
    PlaySound("sounds\\Startup.wav", NULL, SND_ASYNC);
    SetConsoleOutputCP(CP_UTF8);
    while (!doexit){
        system("cls");
        UI();
        Intercept();
    }
    return 0;
}