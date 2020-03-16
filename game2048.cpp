#include <iostream>
#include <stdlib.h>
#include <time.h>// for srand() function
#include <string>

using namespace std;

const int GAMESIZE = 4; //4 for 4x4 game
const int WINVALUE = 2048; //get 2048 to win!

string changeZeroToSpace(int i){
        if (i == 0)
                return " ";
        return to_string(i);
}

void printGameBoard(int arr1[][GAMESIZE]){
        cout << endl;
        for(int i = 0; i<GAMESIZE; i++) {
                for(int j = 0; j<GAMESIZE; j++)
                        cout << changeZeroToSpace(arr1[i][j]) << "\t";
                cout << endl << endl;
        }
}

void putTile(int arr[][GAMESIZE]){
        int *ptrArr[GAMESIZE*GAMESIZE];
        int numberOfZero = 0;

        for(int i = 0; i<GAMESIZE; i++) {
                for(int j = 0; j<GAMESIZE; j++) {
                        if (arr[i][j] == 0) {
                                ptrArr[numberOfZero] = &arr[i][j];
                                numberOfZero++;
                        }
                }
        }

        srand(time(NULL));
        int newTile = (rand()%2+1)*2;         // 2 or 4
        srand(time(NULL));
        int *ranPo = ptrArr[rand()%numberOfZero];
        *ranPo = newTile;
}

bool checkWin(int arr[][GAMESIZE]){//check existence of 32
        for(int i = 0; i<GAMESIZE; i++) {
                for(int j = 0; j<GAMESIZE; j++) {
                        if(arr[i][j]>=WINVALUE)
                                return true;
                }
        }
        return false;
}

bool checkLose(int arr[][GAMESIZE]){//check existence of 0
        for(int i = 0; i<GAMESIZE; i++) {
                for(int j = 0; j<GAMESIZE; j++) {
                        if(arr[i][j]==0)
                                return false;
                }
        }
        for(int i = 0; i<GAMESIZE; i++) { //horizontal
                int previousNum = -1;
                for(int j = 0; j<GAMESIZE; j++) {
                        if(arr[i][j]==previousNum) //there are consecutive same numbers!
                                return false;
                        else
                                previousNum = arr[i][j];
                }
        }
        for(int i = 0; i<GAMESIZE; i++) { //vertical
                int previousNum = -1;
                for(int j = 0; j<GAMESIZE; j++) {
                        if(arr[j][i]==previousNum) //there are consecutive same numbers!
                                return false;
                        else
                                previousNum = arr[j][i];
                }
        }
        return true;
}

void slideMechanism(int *arr[GAMESIZE]){ //an array of int pointers
        for (int i = 0; i<GAMESIZE; i++) {
                if (*arr[i]!=0) {
                        for (int j = i+1; j<GAMESIZE; j++) {
                                if(*arr[j]!=0) {
                                        if(*arr[j]== *arr[i]) { //can add together!
                                                *arr[i] *= 2;
                                                *arr[j] = 0;
                                        }
                                        break;
                                }
                        }
                }
        }

        int zeroPos = -1;
        for (int i = 0; i<GAMESIZE; i++) { //find first zero space
                if(*arr[i] == 0) {
                        zeroPos = i;
                        break;
                }
        }
        if (zeroPos != -1) { //if there is zero space
                for (int i = zeroPos + 1; i<GAMESIZE; i++) {
                        if (*arr[i] != 0) {
                                *arr[zeroPos] = *arr[i];
                                *arr[i] = 0;
                                zeroPos++;
                        }
                }
        }
}

bool isArrSame(int arr1[][GAMESIZE], int arr2[][GAMESIZE]){
        for (int i = 0; i<GAMESIZE; i++) {
                for (int j = 0; j<GAMESIZE; j++) {
                        if (arr1[i][j] != arr2[i][j])
                                return false;
                }
        }
        return true;
}

bool slideTile(char direction, int arr[][GAMESIZE]){
        int arrPrevious[GAMESIZE][GAMESIZE];
        for (int i = 0; i<GAMESIZE; i++) { //copy a backup to check if slide is valid
                for (int j = 0; j<GAMESIZE; j++)
                        arrPrevious[i][j] = arr[i][j];
        }

        if (direction == 'a') { //go leftwards
                for (int i = 0; i<GAMESIZE; i++) {
                        int *arrSent[GAMESIZE];
                        for (int j = 0; j<GAMESIZE; j++) {
                                arrSent[j] = &arr[i][j];
                        }
                        slideMechanism(arrSent);
                }
        }
        else if (direction == 'd') { //go rightwards
                for (int i = 0; i<GAMESIZE; i++) {
                        int *arrSent[GAMESIZE];
                        for (int j = 0; j<GAMESIZE; j++) {
                                arrSent[GAMESIZE - 1 - j] = &arr[i][j];
                        }
                        slideMechanism(arrSent);
                }
        }
        else if (direction == 'w') { //go upwards
                for (int i = 0; i<GAMESIZE; i++) {
                        int *arrSent[GAMESIZE];
                        for (int j = 0; j<GAMESIZE; j++) {
                                arrSent[j] = &arr[j][i];
                        }
                        slideMechanism(arrSent);
                }
        }
        else if (direction == 's') { //go downwards
                for (int i = 0; i<GAMESIZE; i++) {
                        int *arrSent[GAMESIZE];
                        for (int j = 0; j<GAMESIZE; j++) {
                                arrSent[GAMESIZE - 1 - j] = &arr[j][i];
                        }
                        slideMechanism(arrSent);
                }
        }

        return isArrSame(arrPrevious, arr);
}

int main()
{
        cout << "Welcome to 2048 Game!" << endl
             << "input w|a|s|d to slide the tiles." << endl
             << "Game start! Get 2048 to win!" << endl << endl;
        // 3x3 empty game board
        //default all blank
        int gameBoard[GAMESIZE][GAMESIZE] ={0};
        while(true) {
                //put tile
                putTile(gameBoard);
                //print game board
                printGameBoard(gameBoard);
                //check lose
                if(checkLose(gameBoard)) {
                        cout << "Sorry! You Lose!\n" << endl;
                        break;
                }
                //grab player's choice
                cout << "Input direction: ";
                char direction;
                cin >> direction;
                //slide tile
                while(slideTile(direction,gameBoard)) {
                        cout << "No change on this direction. Please choose another direction." << endl;
                        cout << "Input direction: ";
                        direction;
                        cin >> direction;
                }
                //check win
                if(checkWin(gameBoard)) {
                        cout << "Congratulations! You Win!\n" << endl;
                        break;
                }
        }//end of game loop
        //printGameBoard(gameBoard);
        return 0;
}
