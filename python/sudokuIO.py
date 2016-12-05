#!/usr/bin/env
import re

SPACER_LINE = "+=======================+"

def readSudokuFromFile(fileName):
    puzzle = []
    with open(fileName, 'r') as f:
        for line in f:
            if(line[0] != '+'):
                parsed = lineToSudokuRow(line)
                puzzle.append(parsed)

    return puzzle

def writeSudokuToFile(puzzle, fileName):
    with open(fileName, 'w') as f:
        for i in range(len(puzzle)):
            if(i % 3 == 0):
                f.write(SPACER_LINE + "\n")
            f.write(sudokuRowToLine(puzzle[i]))
        f.write(SPACER_LINE)

# takes a file name: 'example.txt' removes the file extension,
# and adds '_solution.txt' to the end.
# result: 'example_solution.txt'
def getNewFileName(fileName):
    lastDot = fileName.rfind(".")
    newFileName = fileName[:lastDot] + "_solution.txt"
    return newFileName
    

def sudokuRowToLine(row):
    result = ""
    for i in range(len(row)):
        if( i % 3 == 0):
            result += "| "
        if(row[i] == 0):
            result += "- "
        else:
            result += str(row[i]) + " "
    
    result += "|\n"
    return result

def lineToSudokuRow(line):
    line = re.sub('[\s|]', '', line)
    return list(map(sudokuConverter, list(line)))

    
def sudokuConverter(c):
    if(c == '-'):
        return 0
    else:
        return int(c)
