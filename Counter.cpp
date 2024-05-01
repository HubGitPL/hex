//
// Created by Mateusz on 01/05/2024.
//
#include "Counter.h"

void Counter::restart() {
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            board[i][j] = EMPTY_FIELD;
        }
    }
    counterLessThanSign = 0;
    counterRedPawnsNumber = 0;
    counterBluePawnsNumber = 0;
    threeMinusSigns = 1;
    xBoard = 0;
    yBoard = 0;
    isInTheMiddle = false;
    isYesRed = false;
    isYesBlue = false;
    printf("\n");
}
bool Counter::dfs(int color, int x, int y, int boardSize, bool (& alreadyVisited)[BOARD_SIZE][BOARD_SIZE]){
    if(x < 0 || x >= boardSize || y < 0 || y >= boardSize){
        return false;
    }
    if(board[x][y] != color){
        return false;
    }
    if(alreadyVisited[x][y]){
        return false;
    }
    alreadyVisited[x][y] = true;
    return dfs(color, x-1, y, boardSize, alreadyVisited)
           || dfs(color, x+1, y, boardSize, alreadyVisited)
           || dfs(color, x, y-1, boardSize , alreadyVisited)
           || dfs(color, x, y+1, boardSize, alreadyVisited)
           || dfs(color, x-1, y-1, boardSize, alreadyVisited)
           || dfs(color, x+1, y+1, boardSize, alreadyVisited);
}
bool Counter::handleDFS(int color, int x, int y, int boardSize, bool isToPrint){
    bool alreadyVisited[BOARD_SIZE][BOARD_SIZE] = {{false}};
    if(color == RED_FIELD){
        dfs(RED_FIELD, x, y, boardSize, alreadyVisited);
        for(int i = 0; i < boardSize; i++) {
            if(alreadyVisited[boardSize-1][i]){
                if(isToPrint){
                    printf("YES RED\n");
                }else{
                    isYesRed = true;
                }
                return true;
            }
        }
    }else{
        dfs(BLUE_FIELD, x, y, getBOARD_SIZE(), alreadyVisited);
        for(int i = 0; i < getBOARD_SIZE(); i++) {
            if(alreadyVisited[i][getBOARD_SIZE()-1]){
                if(isToPrint){
                    printf("YES BLUE\n");
                }else{
                    isYesBlue = true;
                }
                return true;
            }
        }
    }
    return false;
}
bool Counter::isGameOver(bool isToPrint) {
    for(int i=0; i < getBOARD_SIZE(); i++){
        if(board[0][i] == RED_FIELD){
            if(handleDFS(RED_FIELD, 0, i, getBOARD_SIZE(), isToPrint)){
                return true;
            }
        }
        if(board[i][0] == BLUE_FIELD){
            if(handleDFS(BLUE_FIELD, i, 0, getBOARD_SIZE(), isToPrint)){
                return true;
            }
        }
    }
    if(isToPrint){
        printf("NO\n");
    }
    return false;
}
void Counter::toPrintYesorNo(bool isYes){
    if(isYes){
        printf("YES\n");
    }
    else{
        printf("NO\n");
    }
}
bool Counter::isBoardCorrect (bool isToPrint) const{
    if(counterRedPawnsNumber == counterBluePawnsNumber ||
       counterRedPawnsNumber == counterBluePawnsNumber + 1){
        if(isToPrint){
            toPrintYesorNo(true);
        }
        return true;
    }
    else{
        if(isToPrint){
            toPrintYesorNo(false);
        }
        return false;
    }
}
bool Counter::takeDownPawn(int color, bool isToPrint, int colorToPutOn){
    for(int i = 0; i < getBOARD_SIZE(); i++){
        for(int j = 0; j < getBOARD_SIZE(); j++) {
            if(board[i][j] == color) {
                board[i][j] = colorToPutOn;
                if(!isGameOver(false)) {
                    if(isToPrint){
                        toPrintYesorNo(true);
                    }
                    return true;
                }else{
                    board[i][j] = color;
                }
            }
        }
    }
    return false;
}
bool Counter::isBoardPossible(bool isToPrint){
    //jak wygrywa niebieski i jest o 1 lub wiecej czerwonych pionków to false
    switch (isYesBlue){
        case true:
            if(counterRedPawnsNumber != counterBluePawnsNumber){
                if(isToPrint){
                    toPrintYesorNo(false);
                }
                return false;
            }else{
                if(takeDownPawn(BLUE_FIELD, isToPrint)){
                    return true;
                }
            }
            break;
        case false:
            if(isYesRed){
                if(counterRedPawnsNumber-1 != counterBluePawnsNumber) {
                    if (isToPrint) {
                        toPrintYesorNo(false);
                    }
                    return false;
                }
                if(takeDownPawn(RED_FIELD, isToPrint)){
                    return true;
                }
            }
            break;
    }
    if(isToPrint){
        toPrintYesorNo(false);
    }
    return false;
}
bool Counter::lookForThreeMinusSigns(char *input) {
    int counterMinusSigns = 0;
    char thirdChar = *(input+2);
    for(char *i = input; *i; i++){
        if(*i == '-'){
            counterMinusSigns++;
        }
    }
    if(counterMinusSigns == 2 && thirdChar == '>'){
        return true;
    }
    return counterMinusSigns == 3;
}
bool Counter::whichTurn() const{
    return counterRedPawnsNumber == counterBluePawnsNumber;
}
int Counter::getNumberOfemptyFields() const{
    return getBOARD_SIZE()*getBOARD_SIZE() - getSumPAWNS_NUMBER();
}
bool Counter::getIsNaive(char *input){
    return *(input+27) == 'N' || *(input+28) == 'N' || *(input+29) == 'N';
}
bool Counter::isGameOver2(bool isToPrint, int color) {
    if(color == RED_FIELD) {
        for (int i = 0; i < getBOARD_SIZE(); i++) {
            if (board[0][i] == RED_FIELD) {
                if (handleDFS(RED_FIELD, 0, i, getBOARD_SIZE(), isToPrint)) {
                    return true;
                }
            }
        }
    }
    else{
        for (int i = 0; i < getBOARD_SIZE(); i++) {
            if (board[i][0] == BLUE_FIELD && color == BLUE_FIELD) {
                if (handleDFS(BLUE_FIELD, i, 0, getBOARD_SIZE(), isToPrint)) {
                    return true;
                }
            }
        }
    }
    return false;
}
int Counter::howDeepDepth(int moves, bool turnOfRed, bool isRedToWin){
    switch(moves){
        case 1:
            if(turnOfRed) {
                if (isRedToWin) {
                    return 1;
                } else {
                    return 2;
                }
            }else{
                if(isRedToWin){
                    return 2;
                }else{
                    return 1;
                }
            }
        case 2:
            if(turnOfRed){
                if(isRedToWin){
                    return 3;
                }else{
                    return 4;
                }
            }else{
                if(isRedToWin){
                    return 4;
                }else{
                    return 3;
                }
            }
    }
    return 0;
}
int Counter::gradeOfPosition(bool isRedToWin){
    if(isRedToWin){
        if(isGameOver2(false, RED_FIELD)) {
            return 1;
        }
        else{
            return 0;
        }
    }else{
        if(isGameOver2(false, BLUE_FIELD)){
            return 1;
        }
        else{
            return 0;
        }
    }
    return 0;
}
int Counter::toFindTheResultatOfNaive(bool turnOfRed, bool isNaive, bool isRedToWin, int moves){
    int bestScore = 0;
    int score;
    int color = (isRedToWin == RED_FIELD) ? RED_FIELD : BLUE_FIELD;
    for(int i = 0; i < getBOARD_SIZE(); i++) {
        for (int j = 0; j < getBOARD_SIZE(); j++) {
            if ((board[i][j] == EMPTY_FIELD) || (counterRedPawnsNumber == 0 && board[i][j] == EMPTY_FIELD)) {
                board[i][j] = color;
                score = minMaxNaive(turnOfRed, isNaive, isRedToWin, moves - 1);
                board[i][j] = EMPTY_FIELD;
                if (score > bestScore) {
                    bestScore = score;
                    return bestScore;
                }
            }
        }
    }
    return bestScore;
}
int Counter::minMaxNaive(bool turnOfRed, bool isNaive, bool isRedToWin, int moves){
    int bestScore;
    if(moves == 0){
        //jezeli zwroci to 1 to koncz jak najszybciej
        return gradeOfPosition(isRedToWin);
    }
    if(moves > 0){
        if(isRedToWin){
            if(isGameOver2(false, RED_FIELD)) {
                return 0;
            }
        }else{
            if(isGameOver2(false, BLUE_FIELD)){
                return 0;
            }
        }
    }
    if(isRedToWin){
        bestScore = toFindTheResultatOfNaive(turnOfRed, isNaive, isRedToWin, moves);
    }else{
        bestScore = toFindTheResultatOfNaive(!turnOfRed, isNaive, isRedToWin, moves);
    }
    return bestScore;
}
int Counter::oneMoveHandler(bool turnOfRed, bool isNaive, bool isRedToWin, int moves){
    return minMaxNaive(turnOfRed, isNaive, isRedToWin, moves);
}
int Counter::twoMovesHandler(bool turnOfRed, bool isNaive, bool isRedToWin, int moves){
    int color = (turnOfRed == RED_FIELD) ? RED_FIELD : BLUE_FIELD;
    int color2 = (turnOfRed == RED_FIELD) ? BLUE_FIELD : RED_FIELD;
    int counter = 0;
    //jesli przeciwnik moze wygrac w jednym ruchu to zwracam 0
    if(minMaxNaive(color, isNaive, !isRedToWin, 1) == 1){
        return 0;
    }
    for (int i = 0; i < getBOARD_SIZE(); i++) {
        for (int j = 0; j < getBOARD_SIZE(); j++) {
            if (board[i][j] == EMPTY_FIELD) {
                board[i][j] = color2;
                if(isGameOver2(false, color2)){
                    counter++;
                    if(counter >= 2){
                        board[i][j] = EMPTY_FIELD;
                        return 1;
                    }
                }
                board[i][j] = EMPTY_FIELD;
            }
        }
    }
    return 0;
}
int Counter::threeMovesHandler(bool turnOfRed, bool isNaive, bool isRedToWin, int moves){
    int color = (turnOfRed == RED_FIELD) ? RED_FIELD : BLUE_FIELD;
    for (int i = 0; i < getBOARD_SIZE(); i++) {
        for (int j = 0; j < getBOARD_SIZE(); j++) {
            if (board[i][j] == EMPTY_FIELD) {
                board[i][j] = color;
                if(isGameOver2(false, color)){
                    board[i][j] = EMPTY_FIELD;
                    continue;
                }
                if(twoMovesHandler(!turnOfRed, isNaive, isRedToWin, 2) == 1){
                    board[i][j] = EMPTY_FIELD;
                    return 1;
                }
                board[i][j] = EMPTY_FIELD;
            }
        }
    }
    return 0;
}
int Counter::fourMovesHandler(bool turnOfRed, bool isNaive, bool isRedToWin, int moves){
    int color = (turnOfRed == RED_FIELD) ? RED_FIELD : BLUE_FIELD;
    if(minMaxNaive(color, isNaive, !isRedToWin, 1) == 1){
        return 0;
    }
    for (int i = 0; i < getBOARD_SIZE(); i++) {
        for (int j = 0; j < getBOARD_SIZE(); j++) {
            if (board[i][j] == EMPTY_FIELD) {
                board[i][j] = color;
                if(isGameOver2(false, color)){
                    board[i][j] = EMPTY_FIELD;
                    continue;
                }
                if(threeMovesHandler(!turnOfRed, isNaive, isRedToWin, 3) == 0){
                    board[i][j] = EMPTY_FIELD;
                    return 0;
                }
                board[i][j] = EMPTY_FIELD;
            }
        }
    }
    return 1;
}
int Counter::minMaxPerfect(bool turnOfRed, bool isNaive, bool isRedToWin, int moves){
    int bestScore;
    if(moves == 1){
        bestScore = oneMoveHandler(turnOfRed, isNaive, isRedToWin, moves);
    }else if(moves == 2){
        bestScore = twoMovesHandler(turnOfRed, isNaive, isRedToWin, moves);
    }else if(moves == 3){
        bestScore = threeMovesHandler(turnOfRed, isNaive, isRedToWin, moves);
    }else{
        bestScore = fourMovesHandler(turnOfRed, isNaive, isRedToWin, moves);
    }
    return bestScore;
}
void Counter::minMaxDecider(bool turnOfRed, bool isNaive, bool isRedToWin, int moves, bool isToPrint) {
    int bestScore;
    int movesOfThePlayer = moves;
    int colorToCount = (isRedToWin == RED_FIELD) ? counterRedPawnsNumber : counterBluePawnsNumber;
    if(colorToCount + moves < getBOARD_SIZE()){
        if(isToPrint){
            toPrintYesorNo(false);
            return;
        }
    }
    moves = howDeepDepth(moves, turnOfRed, isRedToWin);
    if(moves > getNumberOfemptyFields()){
        if(isToPrint){
            toPrintYesorNo(false);
            return;
        }
    }
    if(isNaive){
        bestScore = minMaxNaive(turnOfRed, isNaive, isRedToWin, movesOfThePlayer);
    }
    else{
        bestScore = minMaxPerfect(turnOfRed, isNaive, isRedToWin, moves);
    }
    if(isToPrint) {
        if(bestScore == 1) {
            toPrintYesorNo(true);
        } else {
            toPrintYesorNo(false);
        }
    }
}
void Counter::redOrBlueMove(char *input, int moves, bool isToPrint){
    bool turnOfRed = whichTurn();
    bool isNaive = getIsNaive(input);
    bool isRedToWin = *(input+4) == 'R';
    minMaxDecider(turnOfRed, isNaive, isRedToWin, moves, isToPrint);
}
void Counter::oneOrTwoMoves(char *input, bool isToPrint){
    if(*(input+15) == '1' || *(input+16) == '1'){
        redOrBlueMove(input, 1, isToPrint);
    }
        //inaczej dwa ruchy
    else{
        redOrBlueMove(input, 2, isToPrint);
    }
}
void Counter::inputHandler(char *input) {
    switch(*input){
        case '<':
            counterLessThanSign++;
            break;
        case '-':
            if(lookForThreeMinusSigns(input)){
                threeMinusSigns++;
                if(threeMinusSigns > 2) {
                    restart();
                }
            }
            else if(*(input+2) == '<'){
                counterLessThanSign++;
            }
            break;
        case '>':
            if(strlen(input) >=3){
                if(*(input+2) == '<'){
                    counterLessThanSign++;
                    xBoard++;
                    yBoard--;
                    break;
                }
            }
            else{
                isInTheMiddle = true;
            }
            if(!isInTheMiddle) {
                xBoard = xBoard+1;
                yBoard=xBoard;
                xBoard=0;
            }else{
                int temp = xBoard;
                yBoard = yBoard+1;
                xBoard = yBoard;
                yBoard = temp;
            }
            break;
        case 'r':
            counterRedPawnsNumber++;
            board[xBoard][yBoard] = RED_FIELD;;
            break;
        case 'b':
            counterBluePawnsNumber++;
            board[xBoard][yBoard] = BLUE_FIELD;
            break;
        case 'B':
            printf("%d\n", (int)getBOARD_SIZE());
            break;
        case 'P':
            printf("%d\n", getSumPAWNS_NUMBER());
            break;
        case 'I':
            if(*(input+3) == 'B' && *(input+9) == 'C'){
                isBoardCorrect(true);
            }
            else if(*(input+3) == 'G'){
                if(!isBoardCorrect(false)){
                    toPrintYesorNo(false);
                    break;
                }else{
                    isGameOver(true);
                }
            }
            else if(*(input+9) == 'P'){
                if(!isBoardCorrect(false)){
                    toPrintYesorNo(false);
                }
                else if(!isGameOver(false)){
                    toPrintYesorNo(true);
                }
                else{
                    isBoardPossible(true);
                }
            }
            break;
        case 'C':
            if(!isBoardCorrect(false)){
                toPrintYesorNo(false);
            }
            else if(isGameOver(false)){
                toPrintYesorNo(false);
            }
            else{
                oneOrTwoMoves(input, true);
            }
        default:
            break;
    }
}
int Counter::getSumPAWNS_NUMBER() const{
    return counterRedPawnsNumber + counterBluePawnsNumber;
}
int Counter::getBOARD_SIZE() const{
    return (int)sqrt((double)counterLessThanSign);
}
