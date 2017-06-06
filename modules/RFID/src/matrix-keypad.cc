/**
 * \file      matrix-keypad.cc
 * \brief     Library for a 4x4 keypad
 * \author    Tim IJntema, René de Kluis
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "matrix-keypad.hh"
#include <iostream>

MatrixKeypad::MatrixKeypad(const int *row, const int *column, int colSize):
    colSize(colSize),
    row(row),
    column(column)
{
    /**
     * Making sure the columnsize is within range
     */
    if (colSize < 0 || colSize > 4){
        std::cerr << "Columnsize " << colSize << " higher or lower than the allowed range\n";
        exit(EXIT_FAILURE);
    }
}

char MatrixKeypad::getKey() {
    for (int i = 0; i < colSize; ++i) {
        pinMode(column[i], OUTPUT);
        digitalWrite(column[i], 0);
    }

    for (int i = 0; i < rowSize; ++i) {
        pinMode(row[i], INPUT);
        pullUpDnControl(row[i], PUD_UP);
    }

    keypadRow = -1;
    for (int i = 0; i < rowSize; ++i) {
        if (digitalRead(row[i]) == 0) {
            keypadRow = i;
        }
    }

    if (keypadRow == -1) {
        return 'h';
    }

    for (int i = 0; i < colSize; ++i) {
        pinMode(column[i], INPUT);
        pullUpDnControl(column[i], PUD_UP);
    }

    pinMode(row[keypadRow], OUTPUT);
    digitalWrite(column[keypadRow], 0);
    
    keypadColumn = -1;
    for (int i = 0; i <  colSize; i++) {
        if (digitalRead(column[i]) == 0) {
            keypadColumn = i;
        }
    }

    if ((keypadRow != -1) && (keypadColumn != -1)) {
        return keypad[keypadRow][keypadColumn];
    }
    return 'h';
}

int MatrixKeypad::getString(char *charArray, int lenCharArray) {
    char pressedKey;
    int i = 0;

    while ((pressedKey = getKey()) != '#' && i < (lenCharArray-1)) {
        if (keypadColumn != -1 && pressedKey != 'h') {
            charArray[i] = pressedKey;
            ++i;

            while (digitalRead(column[keypadColumn]) == 1) {}
        }
    }
    charArray[i] = '\0';
    return i;
}