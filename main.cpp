#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>

using namespace std;

void game(char mode);
void loadgame(void);
void login_page(void);
void start_menu(void);
int Height , Width, mines, difficulty;
char uName[10];

struct user{
    char username[10];
    char password[10];
}*pUser;

struct SAVE{
    char username[10];
    int Difficulty;
    int revealed;
    int flagged;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int sec;
    int Height;
    int Width;
    int mines;
    char mainboard[100][100];
    char gameboard[100][100];
};

void more_details(SAVE save){
    switch (save.Difficulty){
    case 0:
        cout << "EASY,";
        break;
    case 1:
        cout << "NORMAL,";
        break;
    case 2:
        cout << "DIFFICULT,";
        break;
    case 3:
        cout << "CUSTOM,";
        break;
    }
    cout << " Revealed: "<< save.revealed <<", Flagged: " << save.flagged << ", " << save.year << "-" << save.month << "-" << save.day << ", " << save.hour << ":" << save.minute << ":" << save.sec ;
}

void savegame(char gameboard[100][100],char mainboard[100][100]){
    SAVE save, copysave;
    FILE *sf1, *sf2, *sf3, *csf1, *csf2, *csf3;
    if ( ( sf1=fopen("save1.txt", "r+")) == NULL) {
            if ( (sf1=fopen("save1.txt", "w+")) == NULL) {
                    cout << "Could not open file\n" ;
                    exit ( 1);}}
    if ( ( sf2=fopen("save2.txt", "r+")) == NULL) {
            if ( ( sf2=fopen("save2.txt", "w+")) == NULL) {
                    cout << "Could not open file\n" ;
                    exit ( 1);}}
    if ( ( sf3=fopen("save3.txt", "r+")) == NULL) {
            if ( ( sf3=fopen("save3.txt", "w+")) == NULL) {
                    cout << "Could not open file\n" ;
                    exit ( 1);}}
    bool found1=0 , found2=0 , found3=0;
    //1
    cout << endl <<"1. ";
    while ( fread (&save, sizeof(struct SAVE), 1, sf1) == 1) {
        if( strcmp ( save.username, uName) == 0) {
            found1=1;
            more_details(save);
            fseek(sf1, 0, SEEK_SET);
            break;}
    }
    if (found1==0){
        cout << "EMPTY";}
    //2
    cout << endl << endl <<"2. ";
    while ( fread (&save, sizeof(struct SAVE), 1, sf2) == 1) {
        if( strcmp ( save.username, uName) == 0) {
            found2=1;
            more_details(save);
            fseek(sf2, 0, SEEK_SET);
            break;}
    }
    if (found2==0){
        cout << "EMPTY";}
    //3
    cout << endl << endl <<"3. ";
    while ( fread (&save, sizeof(struct SAVE), 1, sf3) == 1) {
        if( strcmp ( save.username, uName) == 0) {
            found3=1;
            more_details(save);
            fseek(sf3, 0, SEEK_SET);
            break;}
    }
    if (found3==0){
        cout << "EMPTY" << endl;}
   time_t now = time(0);
   tm *ltm = localtime(&now);
   save.year = 1900 + ltm->tm_year;
   save.month=1 + ltm->tm_mon;
   save.day=ltm->tm_mday;
   save.hour=ltm->tm_hour;
   save.minute= ltm->tm_min;
   save.sec=ltm->tm_sec;

    for (int i=0; i<10; i++){
        save.username[i]=uName[i];}
    save.Difficulty=difficulty;
    save.revealed=Height*Width;
    save.flagged=0;
    save.Height=Height;
    save.Width=Width;
    save.mines=mines;
    for (int i=0; i<Height; i++){
            for (int j=0; j<Width; j++){
                save.gameboard[i][j]=gameboard[i][j];
                save.mainboard[i][j]=mainboard[i][j];
                if (gameboard[i][j]=='@'){
                    save.flagged++;}
                if (gameboard[i][j]=='@' || gameboard[i][j]=='#'){
                    save.revealed--;}
                }}
    cout << endl << "Save in: ";
    int saveplace;
    cin >> saveplace;
    switch (saveplace){
    case 1:

        if (found1==1){
            if ( ( csf1=fopen("copysave1.txt", "r+")) == NULL) {
            if ( ( csf1=fopen("copysave1.txt", "w+")) == NULL) {
                    cout << "Could not open file\n" ;
                    exit ( 1);}}
        while ( fread (&copysave, sizeof(struct SAVE), 1, sf1) == 1) {
            if( strcmp ( copysave.username, uName) != 0) {
                fwrite (&copysave, sizeof(struct SAVE), 1, csf1);}

            else{
                fwrite (&save, sizeof(struct SAVE), 1, csf1);}
        }
        fseek(sf1, 0, SEEK_SET );
        fseek(csf1, 0, SEEK_SET );

        while ( fread (&copysave, sizeof(struct SAVE), 1, csf1) == 1) {
            fwrite (&copysave, sizeof(struct SAVE), 1, sf1);}
        fclose(csf1);
        }
        else{
        fwrite (&save, sizeof(struct SAVE), 1, sf1);}
        break;
    case 2:
        if (found2==1){
            if ( ( csf2=fopen("copysave2.txt", "r+")) == NULL) {
            if ( ( csf2=fopen("copysave2.txt", "w+")) == NULL) {
                    cout << "Could not open file\n" ;
                    exit ( 1);}}
        while ( fread (&copysave, sizeof(struct SAVE), 1, sf2) == 1) {
            if( strcmp ( copysave.username, uName) != 0) {
                fwrite (&copysave, sizeof(struct SAVE), 1, csf2);}

            else{
                fwrite (&save, sizeof(struct SAVE), 1, csf2);}
        }
        fseek(sf2, 0, SEEK_SET );
        fseek(csf2, 0, SEEK_SET );

        while ( fread (&copysave, sizeof(struct SAVE), 1, csf2) == 1) {
            fwrite (&copysave, sizeof(struct SAVE), 1, sf2);}
        fclose(csf2);
        }
        else{
        fwrite (&save, sizeof(struct SAVE), 1, sf2);}
        break;

    case 3:
        if (found3==1){
            if ( ( csf3=fopen("copysave3.txt", "r+")) == NULL) {
            if ( ( csf3=fopen("copysave3.txt", "w+")) == NULL) {
                    cout << "Could not open file\n" ;
                    exit ( 1);}}
        while ( fread (&copysave, sizeof(struct SAVE), 1, sf3) == 1) {
            if( strcmp ( copysave.username, uName) != 0) {
                fwrite (&copysave, sizeof(struct SAVE), 1, csf3);}

            else{
                fwrite (&save, sizeof(struct SAVE), 1, csf3);}
        }
        fseek(sf3, 0, SEEK_SET );
        fseek(csf3, 0, SEEK_SET );

        while ( fread (&copysave, sizeof(struct SAVE), 1, csf3) == 1) {
            fwrite (&copysave, sizeof(struct SAVE), 1, sf3);}
        fclose(csf3);
        }
        else{
        fwrite (&save, sizeof(struct SAVE), 1, sf3);}
        break;
    }
    fclose(sf1);
    fclose(sf2);
    fclose(sf3);
}

void start_menu(){
    FILE *fp, *cfp;
    SAVE save;
    FILE *sf1, *sf2, *sf3;
    int k=0, q=0, menu_selected_choice;
    bool found1=0 , found2=0 , found3=0;
    pUser=(struct user *)malloc(sizeof(struct user));
    cout << endl <<"{MENU}" << endl;
    cout << endl << "[0].NEW GAME" << endl << "[1].LOAD GAME" << endl << "[2].CHANGE PASSWORD" << endl << "[3].LOG OUT" <<endl ;
    cin >> menu_selected_choice;
    switch (menu_selected_choice){
    case 0:
        //new game
        cout << endl << "Choose Difficulty:" << endl << endl << "[0].EASY " << endl << "[1].NORMAL" << endl << "[2].DIFFICULT" << endl << "[3].CUSTOM" << endl;
        cin >> difficulty;
        switch (difficulty)
        {
        case 0:
            Height = 9;
            Width =9;
            mines = 10;
            break;

        case 1:
            Height = 16;
            Width =16;
            mines = 40;
            break;

        case 2:
            Height = 16;
            Width =30;
            mines = 99;
            break;

        case 3:
            cout << "Height:";
            cin >> Height;
            cout << "Width:";
            cin >> Width;
            cout << "Mines:";
            cin >> mines;
            break;
        }

        game ('N');
        break;

    case 1:
        //load game
        game ('L');
    break;


    case 2:
        //change pass

        if ( ( fp=fopen("user.txt", "r+")) == NULL) {
            if ( ( fp=fopen("user.txt", "w+")) == NULL) {
                    cout << "Could not open file\n" ;
                    exit ( 1);
            }
        }
        if ( ( cfp=fopen("copyuser.txt", "r+")) == NULL) {
            if ( ( cfp=fopen("copyuser.txt", "w+")) == NULL) {
                    cout << "Could not open file\n" ;
                    exit ( 1);
            }
        }
        while ( fread (pUser, sizeof(struct user), 1, fp) == 1) {
            if( strcmp ( pUser->username, uName) != 0) {

                fwrite (pUser, sizeof(struct user), 1, cfp);}

            else{
                cout << "New Password: ";
                cin >> pUser->password;
                fwrite (pUser, sizeof(struct user), 1, cfp);
            }}
        fseek(fp, 0, SEEK_SET );
        fseek(cfp, 0, SEEK_SET );

        while ( fread (pUser, sizeof(struct user), 1, cfp) == 1) {
            fwrite (pUser, sizeof(struct user), 1, fp);
        }

        free ( pUser);
        fclose(fp);
        fclose(cfp);
        break;

    case 3:
        cout << "Logged out" << endl;
        login_page();
        break;}
}

void place_mines(char mainboard[100][100]){
    int k;
    int mcnt = 0;
while(mcnt<mines)
     {
        srand(time(0)+rand());
        int x = rand() % Height;
        int y = rand() % Width;

        if (mainboard[x][y] != '*')
        {
            mainboard[x][y] = '*';
            mcnt++;
        }
    }

    return;
}

void complete_mainboard(char mainboard[100][100]){
    for (int i=0; i<Height; i++){
        for (int j=0; j<Width; j++){
            if (mainboard[i][j]!= '*'){
            int num=0;
            if (mainboard[i+1][j+1]=='*')
                num++;
            if (mainboard[i][j+1]=='*')
                num++;
            if (mainboard[i+1][j]=='*')
                num++;
            if (mainboard[i-1][j-1]=='*')
                num++;
            if (mainboard[i+1][j-1]=='*')
                num++;
            if (mainboard[i-1][j+1]=='*')
                num++;
            if (mainboard[i-1][j]=='*')
                num++;
            if (mainboard[i][j-1]=='*')
                num++;
            if (num==0)
            mainboard[i][j]= '0';
            if (num==1)
            mainboard[i][j]= '1';
            if (num==2)
            mainboard[i][j]= '2';
            if (num==3)
            mainboard[i][j]= '3';
            if (num==4)
            mainboard[i][j]= '4';
            if (num==5)
            mainboard[i][j]= '5';
            if (num==6)
            mainboard[i][j]= '6';
            if (num==7)
            mainboard[i][j]= '7';
            if (num==8)
            mainboard[i][j]= '8';
            }
        }
    }
}

void zero(char gameboard[100][100],char mainboard[100][100],int i,int j){
    gameboard[i][j]=mainboard[i][j];

    if (mainboard[i+1][j+1]=='0' && gameboard[i+1][j+1]=='#')
         zero(gameboard,mainboard,i+1,j+1);
    else
        gameboard[i+1][j+1]=mainboard[i+1][j+1];

    if (mainboard[i][j+1]=='0' && gameboard[i][j+1]=='#')
         zero(gameboard,mainboard,i,j+1);
    else
        gameboard[i][j+1]=mainboard[i][j+1];

    if (mainboard[i+1][j]=='0' && gameboard[i+1][j]=='#')
         zero(gameboard,mainboard,i+1,j);
    else
        gameboard[i+1][j]=mainboard[i+1][j];

    if (mainboard[i-1][j-1]=='0' && gameboard[i-1][j-1]=='#')
         zero(gameboard,mainboard,i-1,j-1);
    else
        gameboard[i-1][j-1]=mainboard[i-1][j-1];

    if (mainboard[i+1][j-1]=='0' && gameboard[i+1][j-1]=='#')
         zero(gameboard,mainboard,i+1,j-1);
    else
        gameboard[i+1][j-1]=mainboard[i+1][j-1];

    if (mainboard[i-1][j+1]=='0' && gameboard[i-1][j+1]=='#')
         zero(gameboard,mainboard,i-1,j+1);
    else
        gameboard[i-1][j+1]=mainboard[i-1][j+1];

    if (mainboard[i-1][j]=='0' && gameboard[i-1][j]=='#')
         zero(gameboard,mainboard,i-1,j);
    else
        gameboard[i-1][j]=mainboard[i-1][j];

    if (mainboard[i][j-1]=='0' && gameboard[i][j-1]=='#')
         zero(gameboard,mainboard,i,j-1);
    else
        gameboard[i][j-1]=mainboard[i][j-1];

}

void game (char mode){
SAVE save;
FILE *sf1, *sf2, *sf3;
int found1=0, found2=0, found3=0;
char mainboard[100][100];
char gameboard[100][100];
int step=0;
char savedboards[100][100][5];

if (mode=='L'){

    if ( ( sf1=fopen("save1.txt", "r+")) == NULL) {
            if ( (sf1=fopen("save1.txt", "w+")) == NULL) {
                    cout << "Could not open file\n" ;
                    exit ( 1);}}
    if ( ( sf2=fopen("save2.txt", "r+")) == NULL) {
            if ( ( sf2=fopen("save2.txt", "w+")) == NULL) {
                    cout << "Could not open file\n" ;
                    exit ( 1);}}
    if ( ( sf3=fopen("save3.txt", "r+")) == NULL) {
            if ( ( sf3=fopen("save3.txt", "w+")) == NULL) {
                    cout << "Could not open file\n" ;
                    exit ( 1);}}
    //1
    cout << endl <<"1. ";
    while ( fread (&save, sizeof(struct SAVE), 1, sf1) == 1) {
        if( strcmp ( save.username, uName) == 0) {
            found1=1;
            more_details(save);
            fseek(sf1, 0, SEEK_SET);
            break;}
    }
    if (found1==0){
        cout << "EMPTY";
    }
    //2
    cout << endl << endl <<"2. ";
    while ( fread (&save, sizeof(struct SAVE), 1, sf2) == 1) {
        if( strcmp ( save.username, uName) == 0) {
            found2=1;
            more_details(save);
            fseek(sf2,0, SEEK_SET);

            break;}
    }
    if (found2==0){
        cout << "EMPTY";
    }
    //3
    cout << endl << endl <<"3. ";
    while ( fread (&save, sizeof(struct SAVE), 1, sf3) == 1) {
        if( strcmp ( save.username, uName) == 0) {
            found3=1;
            more_details(save);
            fseek(sf3, 0, SEEK_SET);
            break;}
    }
    if (found3==0){
        cout << "EMPTY" << endl;
    }
    cout << endl << endl << "4. BACK";

    int loadgame;
    cout << endl << endl <<  "Choose game: ";
    cin >> loadgame;
    switch (loadgame){
    case 1:
    while ( fread (&save, sizeof(struct SAVE), 1, sf1) == 1) {
        if( strcmp ( save.username, uName) == 0) {
            break;}}
    break;

    case 2:
    while ( fread (&save, sizeof(struct SAVE), 1, sf2) == 1) {
        if( strcmp ( save.username, uName) == 0) {
            break;}}
    break;

    case 3:
    while ( fread (&save, sizeof(struct SAVE), 1, sf3) == 1) {
        if( strcmp ( save.username, uName) == 0) {
            break;}}
    case 4:
        start_menu();
        return;
        }

    difficulty= save.Difficulty;
    Height= save.Height;
    Width= save.Width;
    mines= save.mines;
    for (int i=0; i<Height; i++){
        for (int j=0; j<Width; j++){
                gameboard[i][j]=save.gameboard[i][j];
                mainboard[i][j]=save.mainboard[i][j];
    }}

    fclose(sf1);
    fclose(sf2);
    fclose(sf3);}

if (mode=='N'){
    for (int i=0; i<Height; i++){
        for (int j=0; j<Width; j++){
            mainboard[i][j] = gameboard[i][j]='#';}}
    place_mines(mainboard);
    complete_mainboard(mainboard);}

for (int i=0; i<Height; i++){
    for (int j=0; j<Width; j++){
        savedboards[i][j][0]=gameboard[i][j];}}

    while (true){
        int x, y, input, gameoverinput;
        cout << endl;
        for (int ii=0; ii<Height; ii++){
            if (Height-ii<10)
                cout <<" "<< Height-ii << "  ";
            else
                cout << Height-ii << "  ";
            for (int jj=0; jj<Width; jj++){
                cout << " "<< gameboard[ii][jj] << " ";}
                cout << endl;}
        cout << endl << "    ";
        for (int iii=1; iii<=Width; iii++){
            if (iii<10)
                cout <<" "<< iii << " ";
            else
                cout << " "<< iii;
        }
        //win check
        bool win=1;
        for (int i=0; i<Height; i++){
            for (int j=0; j<Width; j++){
                if (mainboard[i][j] != gameboard[i][j]){
                    if ( mainboard[i][j]=='*' && (gameboard[i][j]=='@' || gameboard[i][j]=='#'))
                        continue;
                    else{
                        win=0;
                        break;}}}}
        if (win==0){
        cout << endl << endl << "[0].REVEAL\n[1].PUT FLAG\n[2].DELETE FLAG\n[3].UNDO\n[4].SAVE GAME\n[5].QUIT\n";
        cin >> input;
        switch (input){

        case 0:
            //reveal
            cout << "Enter row and column: ";
            cin >> x >> y;
            step++;

            x=Height-x;
            y=y-1;
            if (gameboard[x][y]=='#'){
                cout << endl;
                    if (mainboard[x][y]=='*'){
                    //mainboard[x][y]='&';
                    for (int ii=0; ii<Height; ii++){
                        if (Height-ii<10)
                            cout <<" "<< Height-ii << "  ";
                        else
                            cout << Height-ii << "  ";
                        for (int jj=0; jj<Width; jj++){
                                if (ii==x && jj==y)
                                    cout <<" "<< '&' << " ";
                                else
                                    cout << " "<< mainboard[ii][jj] << " ";}
                        cout << endl;}
                    cout << endl << "    ";
                    for (int iii=1; iii<=Width; iii++){
                        if (iii<10)
                            cout <<" "<< iii << " ";
                        else
                            cout << " "<< iii;}
                    cout <<endl << endl << "GAMEOVER!" << endl << endl << "[0].UNDO\n[1].MENU" << endl;
                    cin >>  gameoverinput;
                    switch( gameoverinput){
                        case 0:
                            //undo
                            step--;
                            for (int i=0; i<Height; i++){
                                for (int j=0; j<Width; j++){
                                    gameboard[i][j]=savedboards[i][j][step%5]; }}

                            break;
                        case 1:
                            start_menu();
                            break;}}
                    else {
                    if (mainboard[x][y]=='0')
                        zero(gameboard,mainboard,x,y);
                    gameboard[x][y]=mainboard[x][y];}}
            break;

        case 1:
            cout << "Enter row and column: ";
            cin >> x >> y;
            x=Height-x;
            y=y-1;
            if (gameboard[x][y]=='#'){
                gameboard[x][y]='@';}
            step++;
            break;

        case 2:
            cout << "Enter row and column: ";
            cin >> x >> y;
            x=Height-x;
            y=y-1;
            if (gameboard[x][y]=='@'){
                gameboard[x][y]='#';}
            step++;
            break;

        case 3:
            //undo
            step--;
            for (int i=0; i<Height; i++){
            for (int j=0; j<Width; j++){
                gameboard[i][j]=savedboards[i][j][step%5]; }}
            break;

        case 4:
            //save game
            savegame(gameboard,mainboard);
            cout << "SAVED!" << endl;
            break;

        case 5:
            start_menu();
            break;
        }

        if (step%5==0){
            for (int i=0; i<Height; i++){
            for (int j=0; j<Width; j++){
                savedboards[i][j][0]=gameboard[i][j]; }}}

         if (step%5==1){
            for (int i=0; i<Height; i++){
            for (int j=0; j<Width; j++){
                savedboards[i][j][1]=gameboard[i][j]; }}}

        if (step%5==2){
            for (int i=0; i<Height; i++){
            for (int j=0; j<Width; j++){
                savedboards[i][j][2]=gameboard[i][j]; }}}

        if (step%5==3){
            for (int i=0; i<Height; i++){
            for (int j=0; j<Width; j++){
                savedboards[i][j][3]=gameboard[i][j]; }}}

        if (step%5==4){
            for (int i=0; i<Height; i++){
            for (int j=0; j<Width; j++){
                savedboards[i][j][4]=gameboard[i][j]; }}}
    }
    if(win==1) {
        cout << endl << endl << "YOU WON =)" << endl;
        start_menu();
        break;}
    }
}

void login_page(){
    FILE *fp;
    char  pwd[10];int i;char c;
    int found=0, x;
    pUser=(struct user *)malloc(sizeof(struct user));
    cout << endl <<"[0].SIGN UP" << endl << "[1].LOGIN" << endl << "[2].EXIT" << endl;
    cin >> x;
    switch (x){
    case 0:
        if ( ( fp=fopen("user.txt", "a+")) == NULL) {
            if ( ( fp=fopen("user.txt", "w+")) == NULL) {
                cout << "Could not open file\n";
                exit ( 1);}
        }
        cout << "Choose A Username: ";
        cin >> pUser->username ;
        cout << "Choose A Password: ";
        cin >> pUser->password;
        fwrite (pUser, sizeof(struct user), 1, fp);
        cout << "Saved!\n" ;
        free ( pUser);
        fclose(fp);
        start_menu();
        break;

    case 1:
        if ( ( fp=fopen("user.txt", "r+")) == NULL) {
            if ( ( fp=fopen("user.txt", "w+")) == NULL) {
                    cout << "Could not open file\n" ;
                    exit ( 1);}
            }
            cout << "Username: ";
            cin >> uName;
              while ( fread (pUser, sizeof(struct user), 1, fp) == 1) {
                if( strcmp ( pUser->username, uName) == 0) {
                    found=1;
                    cout << "Password: ";
                    cin >> pwd;
                    if( strcmp ( pUser->password, pwd) == 0) {
                        cout << "Logged in successfully\n";
                        start_menu();
                        break;}
                    else
                        cout << "Wrong password\n";
                        login_page();
                }
            }
            if (found==0)
                cout << "User not found\n";
                login_page();
        break;

    case 2:
        cout << "Bye!";
        break;
    }
    free ( pUser);
    fclose(fp);
}

int main(){
    cout << "Welcome to *MINESWEEPER* " << endl;
    login_page ();
}
