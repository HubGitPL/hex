//
// Created by Mateusz on 01/05/2024.
//
#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "Defines.h"
#ifndef HEX_COUNTER_H
#define HEX_COUNTER_H

class Counter {
private:
    //0 - empty 1 - red 2 - blue
    int board [BOARD_SIZE][BOARD_SIZE] = {{0}};
    int counterLessThanSign = 0;
    int counterRedPawnsNumber = 0;
    int counterBluePawnsNumber = 0;
    int threeMinusSigns = 0;
    int xBoard = 0, yBoard = 0;
    bool isInTheMiddle = false;
    bool isYesRed = false;
    bool isYesBlue = false;
public:
    void restart();
    bool dfs(int color, int x, int y, int boardSize, bool (& alreadyVisited)[BOARD_SIZE][BOARD_SIZE]);
    bool handleDFS(int color, int x, int y, int boardSize, bool isToPrint);
    bool isGameOver(bool isToPrint);
    void static toPrintYesorNo(bool isYes);
    bool isBoardCorrect (bool isToPrint) const;
    bool takeDownPawn(int color, bool isToPrint, int colorToPutOn = EMPTY_FIELD);
    bool isBoardPossible(bool isToPrint);
    bool static lookForThreeMinusSigns(char *input);
    bool whichTurn() const;
    int getNumberOfemptyFields() const;
    bool static getIsNaive(char *input);
    bool isGameOver2(bool isToPrint, int color);
    int static howDeepDepth(int moves, bool turnOfRed, bool isRedToWin);
    int gradeOfPosition(bool isRedToWin);
    int toFindTheResultatOfNaive(bool turnOfRed, bool isNaive, bool isRedToWin, int moves);
    int minMaxNaive(bool turnOfRed, bool isNaive, bool isRedToWin, int moves);
    int oneMoveHandler(bool turnOfRed, bool isNaive, bool isRedToWin, int moves);
    int twoMovesHandler(bool turnOfRed, bool isNaive, bool isRedToWin, int moves);
    int threeMovesHandler(bool turnOfRed, bool isNaive, bool isRedToWin, int moves);
    int fourMovesHandler(bool turnOfRed, bool isNaive, bool isRedToWin, int moves);
    int minMaxPerfect(bool turnOfRed, bool isNaive, bool isRedToWin, int moves);
    void minMaxDecider(bool turnOfRed, bool isNaive, bool isRedToWin, int moves, bool isToPrint);
    void redOrBlueMove(char *input, int moves, bool isToPrint);
    void oneOrTwoMoves(char *input, bool isToPrint);
    void inputHandler(char *input);
    int getSumPAWNS_NUMBER() const;
    int getBOARD_SIZE() const;
};


#endif //HEX_COUNTER_H
