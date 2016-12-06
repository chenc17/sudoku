#!/usr/bin/env 
import random, os
import solver, sudokuIO

EASY_VALS_TO_REMOVE = 30
MED_VALS_TO_REMOVE = 50
HARD_VALS_TO_REMOVE = 60

#generator
#created: 12/4/16

def generatePuzzles(N):
    if not os.path.exists("puzzles"):
        os.makedirs("puzzles")
    if not os.path.exists("solutions"):
        os.makedirs("solutions")
    
    for i in range(N):
        print("Creating puzzle " + str(i+1))
        num_to_remove = random.randrange(30, 61)
        result = generate_sudoku_puzzle(num_to_remove)

        puzzleID = random.randrange(0, 10000)
    
        puzzleFileName = "puzzle" + str(puzzleID) + ".txt"
        solutionFileName = sudokuIO.getSolutionFileName(puzzleFileName)

        print("Finished writing puzzle " + str(i+1) + ": " + puzzleFileName)
        
        sudokuIO.writeSudokuToFile(result[0],"puzzles/" + puzzleFileName)
        sudokuIO.writeSudokuToFile(result[1],"solutions/" + solutionFileName)


#given a difficulty number that indicates how many values to remove from the sudoku puzzle,
#generate an unsolved sudoku puzzle and its corresponding solution
def generate_sudoku_puzzle(Diff_Num):

    while True:
        
        #blank puzzle
        init_puzzle = [[0 for x in range(solver.NUM_SQ_ROW_COL)] for y in range(solver.NUM_SQ_ROW_COL)]
    
        #get five random numbers in the range 1..9 to "seed" the blank puzzle
        #these numbers go in the first row of the blank puzzle
        seed_nums=random.sample(range(1,9), 5)
        
        for i in range (0,len(seed_nums)):
            init_puzzle[0][i]=seed_nums[i]
    
        #emulating a do while loop
        sudoku_puzzle = []
        while True: 
            sudoku_puzzle = solver.createSolved(init_puzzle, 0)
            if(sudoku_puzzle!=None):
                break
        
#        print("solved puzzle:")
#        solver.printPuzzle(sudoku_puzzle)
#        print("\n")
        
        #pick NUM_VALS_TO_REMOVE indices and set values corresponding to those 
        #indices to 0 
        indices_selected = random.sample(range(0,solver.TOTAL_NUM_SQ), Diff_Num)
        
        for i in indices_selected:
            sudoku_puzzle[solver.getRowIndex(i)][solver.getColIndex(i)] = solver.UNKNOWN

#        print("unsolved puzzle:")
#        solver.printPuzzle(sudoku_puzzle)
#        print("\n")
    
        sudoku_puzzle_final = solver.createSolved(sudoku_puzzle,0)
        s_p_solved = solver.copyPuzzle(sudoku_puzzle_final)
        
    
        if(sudoku_puzzle_final != None):
           
            
            #take out values again
            for i in indices_selected:
                sudoku_puzzle_final[solver.getRowIndex(i)][solver.getColIndex(i)] = solver.UNKNOWN
            return [sudoku_puzzle_final, s_p_solved]
       
 #test function           
def test_generator():
    
    puzzles_generated = generate_sudoku_puzzle(EASY_VALS_TO_REMOVE)
    
    print("FINAL UNSOLVED PUZZLE")
    solver.printPuzzle(puzzles_generated[0])
    print("\n")
    
    print("FINAL SOLVED PUZZLE")
    solver.printPuzzle(puzzles_generated[1])
    print("\n")
    
    
    

