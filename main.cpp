#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <conio.h> //for getch(), system("cls")
#include <bitset>
#include <algorithm> //for sort function
//#include <Windows.h>
//#include "mmsystem.h"
//#pragma comment(lib, "winmm.lib")
using namespace std;



struct Player {
    string name;
    int highScore;
    
    //constructor
    Player() : name(""), highScore(0) {} //default
    Player(string n, int s) : name(n), highScore(s) {}

};  Player players[10];

struct Scoreboard {
    int currentScore;
    int highestScore;
};

struct Game {
    int board[8][8];
    int size=4;
    Scoreboard scores;
    Game() :board{}, scores() {}//default
};


bool compare(const Player& a, const Player& b) {
    //returns condition for sorting in descending order
    return a.highScore > b.highScore;
} 
void printRrankList(Player arr[], int size) {
    /* we used sort function in algorithm header file
    this function takes 3 parameters start iterator, end iterator
    comparison function(This function defines sorting order), > indicates
    descending order, < indicates ascending; default
    It utilizes an efficient sorting algorithm (Quicksort, Introsort, or TimSort)
    */
    sort(arr, arr + size, compare);//void function

    system("cls");//system clear screen
    cout << "\n\n\t\tPlayer\t\t" << "\t\tHighScore\n\n\n";
    for (int i = 0; i < size; i++) {
        cout << "\t\t" << i + 1 << ". " << arr[i].name << "\t\t\t" << arr[i].highScore << endl;
    }
    cout << "\n\n" << "Press any key to go Back to Menu";
        getch();
    

}


void print(Game& game) {
    
    cout << "\n \t\t Press space to pause, Esc to quit";
    cout << "\n\n Current Score: " << game.scores.currentScore
        << "\t\t\tHighscore: " << game.scores.highestScore << "\n\n";

    for (int i = 0; i < game.size; i++) {
        //Printing dashes for each row
        for (int k = 0; k < game.size; k++) {
            cout << "------";
        }
        cout << "-\n|"; //to print each coloumn alone

        for (int j = 0; j < game.size; j++) {
            if (game.board[i][j] == 0)
                cout << setw(6) << "|";
            else
                cout << setw(3) << game.board[i][j] << setw(3) << "|";
        }
        cout << "\n";
    }

    // to print bottom dashes
    for (int k = 0; k < game.size; k++) {
        cout << "------";
    }
    cout << "-\n";
}

void newTile(Game& game) {
    int x, y;
    srand(time(0));
    while (true) {
        x = rand() % game.size; //generate random index bet.0-3
        y = rand() % game.size;
        
        if (game.board[x][y] == 0) {
            game.board[x][y] = pow(2, x % 2 + 1);//also rand()%2? 2:4 //random numbers are only 2/4
            break;
        }
    }
}
void startTiles(Game& game) {
    //for generating 2,4 at random places when game begins
    srand(time(0));
    int a, b, c, d;
    a = rand() % game.size; //0-3
    b = rand() % game.size; 
    do {
        c = rand() % game.size; 
        d = rand() % game.size;
    } while (c==d); //This ensures different places for tiles 2/4

    game.board[a][c] = 2;
    game.board[b][d] = 4;
}

int check(Game& game, int test[8][8]) { //will be used when 
    for (int i = 0; i < game.size; i++) {      //sapawning new random tile
        for (int j = 0; j < game.size; j++) {    //instead of implementing on 
            if (game.board[i][j] != test[i][j]) { // every move function
                return 0;
            }
        }
    }
    return 1;
}

void scoreIncrement(Game& game, int merge) { //to be used in movement functions
    game.scores.currentScore += merge;      //adds the sum of 2 merged tiles to score

}

void moveUp(Game& game) {
    int i, j, ref;
    for (j = 0; j < game.size; j++) {
        ref = 0; //ref tile for checking
        for (i = 1; i < game.size; i++) {
            if (game.board[i][j] != 0) {
                //check current tile not=0, if so then new iteration
                //with SAME checking tile
                if (game.board[i - 1][j] == 0 || game.board[i - 1][j] == game.board[i][j]) {
                    //check if above tile is 0 or equal, if not then 
                    //new iteration with NEXT checking tile 
                    if (game.board[ref][j] == game.board[i][j]) {
                        game.board[ref][j] *= 2;   //if equal, add tiles
                        game.board[i][j] = 0;    //old tile =0
                        scoreIncrement(game, game.board[ref][j]);
//                        PlaySound(TEXT("gamesound.wav"), NULL, SND_ASYNC);
                    }
                    else {
                        if (game.board[ref][j] == 0) {
                            game.board[ref][j] = game.board[i][j];
                            game.board[i][j] = 0;
                        }
                        else { //above tile is of a different number
                            game.board[++ref][j] = game.board[i][j];
                            //This will ensure that if there were
                            //any gaps in between, current cell goes
                            //directly below checking cell
                            game.board[i][j] = 0;
                        }
                    }
                }
                else ref++; //to prevent comparing the same tile
            }
        }
    }
}
void moveDown(Game& game) {
    int i, j, ref;
    for (j = 0; j < game.size; j++) {
        ref = game.size-1;
        for (i = game.size-2; i >= 0; i--) {
            if (game.board[i][j] != 0) {
                if (game.board[i + 1][j] == 0 || game.board[i + 1][j] == game.board[i][j]) {

                    if (game.board[ref][j] == game.board[i][j]) {
                        game.board[ref][j] *= 2;
                        game.board[i][j] = 0;
                        scoreIncrement(game, game.board[ref][j]);
//                        PlaySound(TEXT("gamesound.wav"), NULL, SND_ASYNC);
                    }
                    else {
                        if (game.board[ref][j] == 0) {
                            game.board[ref][j] = game.board[i][j];
                            game.board[i][j] = 0;
                        }
                        else {
                            game.board[--ref][j] = game.board[i][j];
                            game.board[i][j] = 0;
                        }
                    }
                }
                else ref--;
            }
        }
    }

}
void moveLeft(Game& game) {
    int i, j, ref;
    for (i = 0; i < game.size; i++) {
        ref = 0;
        for (j = 1; j < game.size; j++) {
            if (game.board[i][j] != 0) {
                if (game.board[i][j - 1] == 0 || game.board[i][j - 1] == game.board[i][j]) {

                    if (game.board[i][ref] == game.board[i][j]) {
                        game.board[i][ref] *= 2;
                        game.board[i][j] = 0;
                        scoreIncrement(game, game.board[i][ref]);
//                        PlaySound(TEXT("gamesound.wav"), NULL, SND_ASYNC);
                    }
                    else {
                        if (game.board[i][ref] == 0) {
                            game.board[i][ref] = game.board[i][j];
                            game.board[i][j] = 0;
                        }
                        else {
                            game.board[i][++ref] = game.board[i][j];
                            game.board[i][j] = 0;
                        }
                    }
                }
                else ref++;
            }
        }
    }
}
void moveRight(Game& game) {
    int i, j, ref;
    for (i = 0; i <game.size; i++) {
        ref = game.size-1;
        for (j = game.size-2; j >= 0; j--) {
            if (game.board[i][j] != 0) {
                if (game.board[i][j + 1] == 0 || game.board[i][j + 1] == game.board[i][j]) {

                    if (game.board[i][ref] == game.board[i][j]) {
                        game.board[i][ref] *= 2;
                        game.board[i][j] = 0;
                        scoreIncrement(game, game.board[i][ref]);
//                        PlaySound(TEXT("gamesound.wav"), NULL, SND_ASYNC);
                    }
                    else {
                        if (game.board[i][ref] == 0) {
                            game.board[i][ref] = game.board[i][j];
                            game.board[i][j] = 0;
                        }
                        else {
                            game.board[i][--ref] = game.board[i][j];
                            game.board[i][j] = 0;
                        }
                    }
                }
                else ref--;
            }
        }
    }
}

int testGameOver(Game& game) {
    int flag1 = 0, flag2 = 0;
    for (int i = 0; i < game.size; i++) {
        for (int j = 0; j < game.size; j++) {
            if (game.board[i][j] == 0) { //check if cell is empty
                flag1 = 1;
                break;
            }
        }
    }
    for (int i = 0; i < game.size; i++) {
        for (int j = 0; j < game.size; j++) {
            if ((i < (game.size-1) && game.board[i + 1][j] == game.board[i][j]) || (j < (game.size-1) && game.board[i][j + 1] == game.board[i][j])) {
                //checks if any identical surrounding tiles
                flag2 = 1;
                break;
            }
        }
    }
    if (flag1 || flag2) return 0; 
    else return 1;


}

void displayMenu() {
    //output
    system("cls");
    cout << "\n\n\n\t\t\t2048 game\t\t\t\n\n";
    cout << "\t\t\tMain menu \n\n";
    cout << "\t\tPress S to Start New Game\n \t\tR for Ranking List\n"
        << "\t\tEsc to Close Game";
}

void displayGameOver(Game& game, Player players[]) {
    system("cls"); //system clear screen
    cout << "\n\n\t\t\tGAME OVER!\n\n\n\n"
    << "\tPress B go Back to Menu" << "\n\n\tPress R for Ranklist";

    while (true) {
        int x = getch();//in <conio.h> like cin, but doesnt need enter
        if (x == 'b' || x == 'B') {
            break;
        }
        else if (x == 'r' || x == 'R') {
            printRrankList(players, 6); // Show ranklist
            break;
        }

    }
}

void updateHighscore(Game& game, Player& player){

    if( game.scores.currentScore > game.scores.highestScore ){
        //if current score greater than last highscore, update it in
        //scoreboard and for player in ranlist
    game.scores.highestScore=game.scores.currentScore;
    player.highScore=game.scores.highestScore;
    }
}
void checklevelUp(Game& game){
    if(game.scores.currentScore>400)
        game.size=6;
    if(game.scores.currentScore>500)
        game.size=8;

    }

void startGame(Game& game, Player players[]) {

    system("cls");
    game.scores.currentScore = 0;

    for (int i = 0; i < game.size; i++)
        for (int j = 0; j < game.size; j++)
            game.board[i][j] = 0;


    startTiles(game);
    print(game);

    bool gameOver = false;
    bool pause = false;

    while (!gameOver) {
        if (!pause) {
            
            int arr[8][8] = {};
            for (int i = 0; i < game.size; i++)
                for (int j = 0; j < game.size; j++)
                    arr[i][j] = game.board[i][j];
                    
            int ch = getch();
            system("cls");
            switch (ch) {
            case 72: moveUp(game); break;
            case 80: moveDown(game); break;
            case 75: moveLeft(game); break;
            case 77: moveRight(game); break;
            case 32:
                system("cls");
                cout << "Game Paused. Press any key to resume...";
                pause = true;
                break;
            }
            if (ch == 27)
                break;
            if (!pause) {
                checklevelUp(game);
                

                if (testGameOver(game)) {//0 means test failed (no game over)
                    gameOver = true;
                    displayGameOver(game, players); //output game over screen
                    break;
                }
                updateHighscore(game,players[5]);
                if (!check(game, arr))  //board state changed
                    newTile(game); //spawn random in empty tiles

                print(game);
            }
        }
        else {
            if (kbhit()) {
                getch();
                pause = false;
                system("cls");
                print(game);
            }

        }

    }

    }


int main() {
    
    Game newGame;
    static Player p[10];
    p[0] = Player("Omar ", 112);
    p[1] = Player("Nada ", 100);
    p[2] = Player("Hani ", 114);
    p[3] = Player("Yomna", 100);
    p[4] = Player("Fotoh", 90);
    p[5] = Player("Guest", 0);
    //initialise player array of 5 players

    while (true) {

        displayMenu();
        char ch = getch();

        if (ch == 'S' || ch == 's') {
            startGame(newGame, p);
        }
        else {
            if (ch == 'R' || ch == 'r') {
                printRrankList(p, 6); system("cls");
            }
            else if (ch == 27)
                return 0;
        }
    
    }

    return 0;
}