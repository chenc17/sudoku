#!/usr/bin/env

import random
import sudokuIO

NUM_SQ_ROW_COL = 9
TOTAL_NUM_SQ = (NUM_SQ_ROW_COL*NUM_SQ_ROW_COL)
UNKNOWN = 0


# blank puzzle
BlankPuzzle = [[0 for x in range(NUM_SQ_ROW_COL)] for y in range(NUM_SQ_ROW_COL)]

TestPuzzle = [[0,0,0,0,0,3,2,9,0],
               [0,8,6,5,0,0,0,0,0],
               [0,2,0,0,0,1,0,0,0],
               [0,0,3,7,0,5,1,0,0],
               [9,0,0,0,0,0,0,0,8],
               [0,0,2,9,0,8,3,0,0],
               [0,0,0,4,0,0,0,8,0],
               [0,0,0,0,0,6,4,7,0],
               [0,4,7,1,0,0,0,0,0]]

def solvePuzzle(fileName):
    puzzle = sudokuIO.readSudokuFromFile(fileName)

    print("Original puzzle: ")
    printPuzzle(puzzle)

    print("Attempting to solve...")

    result = createSolved(puzzle, 0)
    
    if result is not None:
        print("Solution found!")
        printPuzzle(result)
    else:
        print("Could not solve puzzle :(")

    newFileName = sudokuIO.getNewFileName(fileName)
    sudokuIO.writeSudokuToFile(result,newFileName)
    print("Wrote solution to new file: " + newFileName)


def createSolved(puzzle, sq_num):
     # base case: got to the end of the square list
    if(sq_num >= TOTAL_NUM_SQ):
        return puzzle

    # Recursive case: If square value is already known, go to the next square.
    # otherwise, try a possible value and go to the next square. if no possible
    # values work, we've reached a dead end
    row = getRowIndex(sq_num)
    col = getColIndex(sq_num)

    copy = copyPuzzle(puzzle)

    if(puzzle[row][col] != UNKNOWN):
        return createSolved(copy, sq_num + 1)
    else:
        possibleValues = getPossibleValues()
        for val in possibleValues:
            if(isValid(puzzle, row, col, val)):
                puzzle[row][col] = val
                copy = copyPuzzle(puzzle)
                result = createSolved(copy, sq_num + 1)
                if(result is not None):
                    return result
                puzzle[row][col] = UNKNOWN

    # No possible values work, so backtrack
    return None

def printPuzzle(puzzle):
    for line in puzzle:
        print(line)

def copyPuzzle(puzzle):
    copy = [[0 for x in range(NUM_SQ_ROW_COL)] for y in range(NUM_SQ_ROW_COL)]
    for i in range(TOTAL_NUM_SQ):
        row = getRowIndex(i)
        col = getColIndex(i)

        copy[row][col] = puzzle[row][col]

    return copy

# Checks the puzzle to see if it is possible to
# set puzzle[row][col] to val according to sudoku
# rules
def isValid(puzzle, row, col, val):
    region = getSquareRegion(row,col)

    for index in range(TOTAL_NUM_SQ):
        tmp_row = getRowIndex(index)
        tmp_col = getColIndex(index)
        tmp_reg = getSquareRegion(tmp_row, tmp_col)

        if(not(tmp_row == row and tmp_col == col)):
            if(tmp_row == row or tmp_col == col or tmp_reg == region):
                if(puzzle[tmp_row][tmp_col] == val):
                    return False

    return True


def getRowIndex(square_num):
    return square_num // NUM_SQ_ROW_COL

def getColIndex(square_num):
    return square_num % NUM_SQ_ROW_COL

def getSquareRegion(row, col):
    row_region, col_region = 0, 0

    if(row <= 2):
        row_region = 0
    elif(row <= 5):
        row_region = 1
    elif(row <= 8):
        row_region = 2

    if(col <= 2):
        col_region = 0
    elif(col <= 5):
        col_region = 1
    elif(col <= 8):
        col_region = 2

    return (3 * row_region) + col_region

def getPossibleValues():
    poss_values = [x for x in range(1, 10)]
    random.shuffle(poss_values)
    return poss_values

def basicTest():
    print("Blank Puzzle:")
    printPuzzle(createSolved(BlankPuzzle, 0))
    print("\nTest Puzzle :")
    printPuzzle(createSolved(TestPuzzle, 0))
