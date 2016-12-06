#!/usr/bin/env 

import solver, generator

def main():
    print("Welcome to the sudoku suite!\n" + 
          "If you would like to create sudoku puzzles, please type:\n" +
          "\tgenerate(N)")
    print("Where 'N' is the number of puzzles you would like to make\n")
    print("Otherwise, if you would like to solve a sudoku puzzle, type:")
    print("\tsolve(FileName)")
    print("Where 'FileName' is the path to the file containing the puzzle.\n")

    print("Note: please ensure that your file is of the appropriate format")
    print("if there are any questions, refer to the parent folder's README.\n")
    
    print("Thanks, and we hope you enjoy solving these sudoku puzzles!")

def solve(FileName):
    solver.solvePuzzle(FileName)

def generate(N):
    generator.generatePuzzles(N)

if  __name__ =='__main__':main()


