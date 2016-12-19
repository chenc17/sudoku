## Synopsis:

This file contains information on how to generate or solve sudoku puzzles using the Python programming language.

Requirements:
* Python 3.5
* Source code: generator.py, solver.py, sudoku.py, sudokuIO.py

Via the terminal or command line navigate to the folder containing the source code. Run sudoku.py: 
```
python ./sudoku.py
```
Alternatively, open sudoku.py in IDLE, and run file. 

## Solving puzzles:

#### Usage:
```
Commandline: python -c 'import sudoku; sudoku.solve(FileName)'
Running file from IDLE: solve(FileName) 
e.g. solve("puzzles/puzzle6430.txt")
```

**Parameters:**

* FileName - path to file containing an unsolved sudoku puzzle

**Output:**

- On the screen: If the puzzle is solvable, a solution will be displayed. 
- In the folder: If the puzzle is solvable, a solved puzzle will be written to a new file. If ```puzzle.txt``` is provided, the solution will be found at ```puzzle_solution.txt```.

## Generating Puzzles:

#### Usage:
```
Commandline: python -c 'import sudoku; sudoku.generate(N)'
Running file from IDLE: generate(N).
e.g. generate(2)
```

**Parameters:**

* N - the number of puzzles and solutions to generate.

**Output:**

- On the screen: The filenames of the puzzles created.
- In the folder: An unsolved puzzle will be written to a new file. If ```puzzle.txt``` is the unsolved, then the solution will be found at ```puzzle_solution.txt```.
