#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <stdio.h>
#define PACMAN 'P'
#define GHOST 'G'
#define DOT '.'
#define WALL 'W'
#define EMPTY ' '
#define UP 'w'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'

int rowP = 4, colomP = 12, rowG1 = 0, colomG1 = 0, rowG2 = 8, colomG2 = 24, mapcount = 0;
char g1 = 's'; //stores direction of ghost 1
char g2 = 'w'; //stores direction of ghost 2
char mover = ' '; //to check if user has inputted
void printMap(); //initialize function
void move(); //Asks user fo move an moves pacman
void ghostMove();//ghoxtmoving when it see packman
int winCheck(); //check if user won
int loseCheck(); //check if user lost
int isWall(char c, int row, int colom); //check if theres a wall
void ghostrun1(); //ghoxtmoving when it dosn't see packman
void ghostrun2(); //ghoxtmoving when it dosn't see packman

char **arrayMap = (char **) malloc(26 * sizeof(char *)); //create malloc array for the map

char **arrayMap2 = (char **) malloc(26 * sizeof(char *));  //create malloc array for the second map that stores dots

int main() { //main function

    //open both files
    FILE *fp;
    FILE *fp2;
    FILE *fout;
    fp = fopen("map.txt", "r"); //create pointer for input file
    fp2 = fopen("map.txt", "r"); //create pointer for input file

    //Create a 2D array using malloc (dynamic memory allocation)
    for (int i = 0; i < 26; i++) {
        arrayMap[i] = (char *) malloc(26 * sizeof(char));
    }

    //Create a 2D array using malloc (dynamic memory allocation)
    for (int i = 0; i < 26; i++) {
        arrayMap2[i] = (char *) malloc(26 * sizeof(char));
    }

    //Create if file is null
    if (fp == NULL) { //Check if there is an input file
        printf("\nFile not found\n");
    }
    else {

//scan the txt file and put in malloc array
        for (int j = 0; j < 9; j++) {
            for (int i = 0; i < 26; i++) {

                fscanf(fp, "%c", &arrayMap[j][i]);
            }
        }

            }


    //Create if file is null
    if (fp2 == NULL) { //Check if there is an input file
        printf("\nFile not found\n");
    }
    else {
        //scan the txt file and put in malloc array
        for (int j = 0; j < 9; j++) {
            for (int i = 0; i < 26; i++) {

                fscanf(fp2, "%c", &arrayMap2[j][i]);
            }
        }
    }

//Get rid of P charachters and G charachters from the dot storage array
    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 26; i++) {

            if(arrayMap2[j][i] == 'G' || arrayMap2[j][i] == 'P'){

                arrayMap2[j][i] = ' ';

            }
        }

    }

    //print the first map
    printMap();

    //Run a continous loop that runs the pacman program
        for (int i = 9; i < 1000; i++) {

            //move pacman
            printf("\nEnter your move; W = up, A = Left, S = Down and D = Right\n");
            move();

            if (mover != ' ') { //check if pacman has moved before mooving ghost

                //move ghost
                ghostMove();

                //check if user has lost
                if(loseCheck() == 1){
                    printMap();
                    printf("\nSorry, you lose. Press any key to exit the game");
                    i = 1000;
                }

                //check if user has won
                if(winCheck() == 1){
                    winCheck();
                    printf("\nCongratulations! You win! Press any key to exit the game");
                    i = 1000;
                }

//if the user hasn't won or lost print the map
                if (loseCheck() == 0 && winCheck() == 0) {
                    printMap();

                }

            }

    }

}
    int loseCheck() {

    //If a pacman and ghost are in same spot return 1, if not return 0

        if (rowG1 == rowP && colomG1 == colomP) {
            return 1;


        } else if (rowG2 == rowP && colomG2 == colomP) {
            return 1;
        }
        else {
            return 0;
        }
    }

int winCheck(){
int count = 0;

//If there are no dots left return 1, if there are still dots return 0

    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 26; i++) {


          if(arrayMap[j][i] == '.'){
              count++;
          }

        }
    }

    if(count == 0){
        return 1;
    }

    if(count != 0){
        return 0;
    }


}


void ghostrun1() {

    //check if the ghost1 is last moving to the right, if theres no wall it moves right
    if (g1 == 'd' && isWall('d', rowG1, colomG1) == 0) {
        arrayMap[rowG1][colomG1 + 3] = 'G';
        arrayMap[rowG1][colomG1] = arrayMap2[rowG1][colomG2];
        colomG1 += 3;
    }

    //check if the ghost1 is last moving down, if there is no wall it moves down
    else if (g1 == 's' && isWall('s', rowG1, colomG1) == 0) {
        arrayMap[rowG1 + 1][colomG1] = 'G';
        arrayMap[rowG1][colomG1] = arrayMap2[rowG1][colomG1];
        rowG1 += 1;
    }

        //check if the ghost1 is last moving left, if there is no wall it moves left
    else if (g1 == 'a' && isWall('a', rowG1, colomG1) == 0) {
        arrayMap[rowG1][colomG1 - 3] = 'G';
        arrayMap[rowG1][colomG1] = arrayMap2[rowG1][colomG1];
        colomG1 -= 3;
    }

        //check if the ghost1 is last moving up, if there is no wall it moves up
    else if (g1 == 'w' && isWall('w', rowG1, colomG1) == 0){
        arrayMap[rowG1 -1 ][colomG1] = 'G';
        arrayMap[rowG1][colomG1] = arrayMap2[rowG1][colomG1];
        rowG1 -= 1;
    }

    else {

        //ghost1 needs a random new direction becasue it has hit a wa;;

        int num = 0;
        while(num == 0) {


            //get a random new direction for ghost 1

            int r = rand() % 100;

            if(r < 25){
                r = 0;
            }

            else if(r > 25 && r < 50){
                r = 1;
            }

           else  if(r > 50 && r < 75){
                r = 2;
            }

            else  if(r > 75 && r < 100){
                r = 3;
            }


            //move in random direction if there is no wall in random direction
            if (isWall('a', rowG1, colomG1) == 0 && r == 0) {

                g1 = 'a';
                arrayMap[rowG1][colomG1 - 3] = 'G';
                arrayMap[rowG1][colomG1] = arrayMap2[rowG1][colomG1];
                colomG1 -= 3;
                num = 1;

                //move in random direction if there is no wall in random direction
            } else if (isWall('s', rowG1, colomG1) == 0 && r == 1) {
                g1 = 's';
                arrayMap[rowG1 + 1][colomG1] = 'G';
                arrayMap[rowG1][colomG1] = arrayMap2[rowG1][colomG1];
                rowG1 += 1;
                num = 1;

                //move in random direction if there is no wall in random direction
            } else if (isWall('d', rowG1, colomG1) == 0 && r == 3) {

                g1 = 'd';
                arrayMap[rowG1][colomG1 + 3] = 'G';
                arrayMap[rowG1][colomG1] = arrayMap2[rowG1][colomG1];
                colomG1 += 3;
                num = 1;
            }
                //move in random direction if there is no wall in random direction
            else if (isWall('w', rowG1, colomG1) == 0 && r == 2) {

                g1 = 'w';
                arrayMap[rowG1 - 1][colomG1] = 'G';
                arrayMap[rowG1][colomG1] = arrayMap2[rowG1][colomG1];
                rowG1 -= 1;
                num = 1;

            }

        }
    }
}

void ghostrun2() {


    //check if the ghost2 is last moving to the right, if theres no wall it moves right
    if (g2 == 'd' && isWall('d', rowG2, colomG2) == 0) {
        arrayMap[rowG2][colomG2 + 3] = 'G';
        arrayMap[rowG2][colomG2] = arrayMap2[rowG2][colomG2];
        colomG2 += 3;
    }

        //check if the ghost2 is last moving to the down, if theres no wall it moves down
    else if (g2 == 's' && isWall('s', rowG2, colomG2) == 0) {
        arrayMap[rowG2 + 1][colomG2] = 'G';
        arrayMap[rowG2][colomG2] = arrayMap2[rowG2][colomG2];
        rowG2 += 1;
    }

        //check if the ghost2 is last moving to the left, if theres no wall it moves left
    else if (g2 == 'a' && isWall('a', rowG2, colomG2) == 0) {
        arrayMap[rowG2][colomG2 - 3] = 'G';
        arrayMap[rowG2][colomG2] = arrayMap2[rowG2][colomG2];
        colomG2 -= 3;
    }

        //check if the ghost2 is last moving to the up, if theres no wall it moves up
    else if (g2 == 'w' && isWall('w', rowG2, colomG2) == 0){
        arrayMap[rowG2 -1 ][colomG2] = 'G';
        arrayMap[rowG2][colomG2] = arrayMap2[rowG2][colomG2];
        rowG2 -= 1;
    }

    else {

        int num = 0;

        //find new random direction for ghost 2 because it has hit wall

        while(num == 0) {
            //find new random direction for ghost 2

            int r = rand() % 100;

            if(r < 25){
                r = 0;
            }

            else if(r > 25 && r < 50){
                r = 1;
            }

            else  if(r > 50 && r < 75){
                r = 2;
            }

            else  if(r > 75 && r < 100){
                r = 3;
            }


            //move in random direction if there is no wall in random direction
            if (isWall('a', rowG2, colomG2) == 0 && r == 0) {

                g2 = 'a';
                arrayMap[rowG2][colomG2 - 3] = 'G';
                arrayMap[rowG2][colomG2] = arrayMap2[rowG2][colomG2];
                colomG2 -= 3;
                num = 1;


            }


                //move in random direction if there is no wall in random direction
            else if (isWall('s', rowG2, colomG2) == 0 && r == 1) {
                g2 = 's';
                arrayMap[rowG2 + 1][colomG2] = 'G';
                arrayMap[rowG2][colomG2] = arrayMap2[rowG2][colomG2];
                rowG2 += 1;
                num = 1;

            }


                //move in random direction if there is no wall in random direction
            else if (isWall('d', rowG2, colomG2) == 0 && r == 3) {

                g2 = 'd';
                arrayMap[rowG2][colomG2 + 3] = 'G';
                arrayMap[rowG2][colomG2] = arrayMap2[rowG2][colomG2];
                colomG2 += 3;
                num = 1;

            }


                //move in random direction if there is no wall in random direction
            else if (isWall('w', rowG2, colomG2) == 0 && r == 2) {

                g2 = 'w';
                arrayMap[rowG2 - 1][colomG2] = 'G';
                arrayMap[rowG2][colomG2] = arrayMap2[rowG2][colomG2];
                rowG2 -= 1;
                num = 1;

            }

        }
    }
}



void ghostMove() {

    int yes = 0; //stores whether ghost 1 sees pacman

    //if pacman and ghost are in same colom and theres no walls in between them move ghost towards packman
    if (colomG1 == colomP && rowP > rowG1) {

        int j = 0;

        for (j = rowG1; arrayMap[j][colomP] != 'W' && arrayMap[j][colomP] != 'P'; j++) {

        }

        if (arrayMap[j][colomP] == 'P') {

            arrayMap[rowG1 + 1][colomG1] = 'G';
            arrayMap[rowG1][colomG1] = arrayMap2[rowG1][colomG1];
            rowG1 += 1;
            g1 = 's';
            yes = 1; //ghost 1 sees pacman
        }

    }

        //if pacman and ghost are in same colom and theres no walls in between them move ghost towards packman
    else if (colomG1 == colomP && rowP < rowG1) {

        int j = rowG1;

        for (j = rowG1; arrayMap[j][colomP] != 'W' && arrayMap[j][colomP] != 'P'; j--) {

            printf("\n %d", j);
        }

        if (arrayMap[j][colomP] == 'P') {

            arrayMap[rowG1 - 1][colomG1] = 'G';
            arrayMap[rowG1][colomG1] = arrayMap2[rowG1][colomG1];
            rowG1 -= 1;
            g1 = 'w';
            yes = 1; //ghost 1 sees pacman
        }

    }

        //if pacman and ghost are in same row and theres no walls in between them move ghost towards packman
    else if (rowG1 == rowP && colomP > colomG1) {

        int j = rowG1;

        for (j = colomG1; arrayMap[rowP][j] != 'W' && arrayMap[rowP][j] != 'P'; j++) {

        }

        if (arrayMap[rowP][j] == 'P') {

            arrayMap[rowG1][colomG1 + 3] = 'G';
            arrayMap[rowG1][colomG1] = arrayMap2[rowG1][colomG1];
            colomG1 += 3;
            g1 = 'd';
            yes = 1; //ghost 1 sees pacman
        }

    }

        //if pacman and ghost are in same row and theres no walls in between them move ghost towards packman

    else if (rowG1 == rowP && colomP < colomG1) {

        int j = rowG1;

        for (j = colomG1; arrayMap[rowP][j] != 'W' && arrayMap[rowP][j] != 'P'; j--) {

        }

        if (arrayMap[rowP][j] == 'P') {

            arrayMap[rowG1][colomG1 - 3] = 'G';
            arrayMap[rowG1][colomG1] = arrayMap2[rowG1][colomG1];
            colomG1 -= 3;
            g1 = 'a';
            yes = 1; //ghost 1 sees pacman
        }

    }


    if (yes == 0) {
//if pacman does not see ghost move the ghost in the direction it was last moving in by calling function
        ghostrun1();
    }

    int yes2 = 0; //stores whether ghost 2 sees pacman
    //if pacman and ghost are in same colom and theres no walls in between them move ghost towards packman
    if (colomG2 == colomP && rowP > rowG2) {

        int j = 0;

        for (j = rowG2; arrayMap[j][colomP] != 'W' && arrayMap[j][colomP] != 'P'; j++) {

        }

        if (arrayMap[j][colomP] == 'P') {

            arrayMap[rowG2 + 1][colomG2] = 'G';
            arrayMap[rowG2][colomG2] = arrayMap2[rowG2][colomG2];
            rowG2 += 1;
            g2 = 's';
            yes2 = 1;  //ghost 2 sees pacman
        }

    }

        //if pacman and ghost are in same colom and theres no walls in between them move ghost towards packman
    else if (colomG2 == colomP && rowP < rowG2) {

        int j = rowG1;

        for (j = rowG2; arrayMap[j][colomP] != 'W' && arrayMap[j][colomP] != 'P'; j--) {

            printf("\n %d", j);
        }

        if (arrayMap[j][colomP] == 'P') {

            arrayMap[rowG2 - 1][colomG2] = 'G';
            arrayMap[rowG2][colomG2] = arrayMap2[rowG2][colomG2];
            rowG2 -= 1;
            g2 = 'w';
            yes2 = 1; //ghost 2 sees pacman
        }

    }

        //if pacman and ghost are in same row and theres no walls in between them move ghost towards packman
    else if (rowG2 == rowP && colomP > colomG2) {

        int j = rowG1;

        for (j = colomG2; arrayMap[rowP][j] != 'W' && arrayMap[rowP][j] != 'P'; j++) {

        }

        if (arrayMap[rowP][j] == 'P') {

            arrayMap[rowG2][colomG2 + 3] = 'G';
            arrayMap[rowG2][colomG2] = arrayMap2[rowG2][colomG2];
            colomG2 += 3;
            g2 = 'd';
            yes2 = 1; //ghost 2 sees pacman
        }

    }

        //if pacman and ghost are in same row and theres no walls in between them move ghost towards packman

    else if (rowG2 == rowP && colomP < colomG2) {

        int j = rowG1;

        for (j = colomG2; arrayMap[rowP][j] != 'W' && arrayMap[rowP][j] != 'P'; j--) {

        }

        if (arrayMap[rowP][j] == 'P') {

            arrayMap[rowG2][colomG2 - 3] = 'G';
            arrayMap[rowG2][colomG2] = arrayMap2[rowG2][colomG2];
            colomG2 -= 3;
            g2 = 'a';
            yes2 = 1; //ghost 2 sees pacman
        }

    }

//if pacman does not see ghost
    if(yes2 == 0) {
//if pacman does not see ghost move the ghost in the direction it was last moving in by calling function
        ghostrun2();
    }
}



//check if the charachter moving direction is a wall
int isWall(char c, int row, int colom){

    //check if wall is above
    if(c == 'w' && row != 0){
        if(arrayMap[row-1][colom] != 'W') {

            return 0;
        }
      else return 1;
        }

        //check if wall is below
    else if(c == 's' && row != 8){
            if(arrayMap[row+1][colom] != 'W') {

                return 0;
            }
            else return 1;

    }

        //check if wall is to the left
    else if(c == 'a' && colom != 0){
            if(arrayMap[row][colom-3] != 'W') {

                return 0;
            }
            else return 1;
        }

        //check if wall is to the right

    else if(c == 'd' && colom != 24){
            if(arrayMap[row][colom+3] != 'W') {

                return 0;
            }
            else return 1;
        }

    else{
        return 1;
    }

    }

//ask user for input and move packman in that direction
void move() {


        mover = ' ';

        mover = getchar();

        if (mover != ' ') {

            //move packman up if theres no walls
            if (mover == 'w') {

                if (isWall('w', rowP, colomP) == 0) {

                    arrayMap[rowP -1][colomP] = 'P';
                    arrayMap2[rowP -1][colomP] = ' ';


                    arrayMap[rowP][colomP] = arrayMap2[rowP][colomP];

                    rowP -= 1;

                }
                mover = ' ';
            }

            //move packman down if theres no walls

            if (mover == 's') {

                if (isWall('s', rowP, colomP) == 0) {

                    arrayMap[rowP + 1][colomP] = 'P';
                    arrayMap2[rowP + 1][colomP] = ' ';

                    arrayMap[rowP][colomP] = arrayMap2[rowP][colomP];

                    rowP += 1;

                }
                mover = ' ';
            }

            //move packman to the left if theres no walls

            if (mover == 'a') {

                if (isWall('a', rowP, colomP) == 0) {

                    arrayMap[rowP][colomP - 3] = 'P';
                    arrayMap2[rowP][colomP - 3] = ' ';

                    arrayMap[rowP][colomP] = arrayMap2[rowP][colomP];

                    colomP -= 3;

                }

                mover = ' ';
            }

            //move packman to the right if theres no walls
            if (mover == 'd') {


                if  (isWall('d', rowP, colomP) == 0)  {

                    arrayMap[rowP][colomP + 3] = 'P';
                    arrayMap2[rowP][colomP + 3] = ' ';

                    arrayMap[rowP][colomP] = arrayMap2[rowP][colomP];

                    colomP += 3;

                }
                mover = ' ';
            }



        }

    }

//print the board

    void printMap() {

    printf("\n");
        printf("\x1b[34m");

//print the outside walls
        printf("W  W  W  W  W  W  W  W  W  W  W\n");


        //print the whole map in color
        for (int j = 0; j < 9; j++) {


            for (int i = 0; i < 26; i++) {


              //print outside wall
                if(i == 0){

                    printf("\x1b[34m");
                    printf("W  ");
                }

                //print outside wall
                if(i == 25){

                    printf("\x1b[34m");
                    printf("  W");
                }

                //check if char is a wall. If so print in blue
                if (arrayMap[j][i] == 'W') {
                    printf("\x1b[34m");


                }

                //check if char is a dot. If so print in white
                if (arrayMap[j][i] == '.') {
                    printf("\x1b[0m");
                }

                //check if char is Pacman. If so print in yellow
                if (arrayMap[j][i] == 'P') {
                    printf("\x1b[33m");

                }

                //check if char is a ghost. If so print in purple

                else if (arrayMap[j][i] == 'G') {
                    printf("\x1b[35m");

                }

                if(arrayMap[j][i] == 'W' || arrayMap[j][i] == '.' || arrayMap[j][i] == 'P' || arrayMap[j][i]) {

                    //print char in proper color
                    printf("%c", arrayMap[j][i]);
                }
            }
        }

        //print outside wall
        printf("\nW  W  W  W  W  W  W  W  W  W  W\n");
    }
