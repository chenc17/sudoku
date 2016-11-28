## Synopsis:

This file contains information on how to generate or solve sudoku puzzles using the Prolog programming language.

Requirements:
* SWI-Prolog: http://www.swi-prolog.org/
* Source code: solver.pl, generator.pl, sudokuIO.pl

Via the terminal or command line, navigate to the folder containing the source code. Open SWI Prolog in that folder. Load the files using the commands:

```
consult(solver), consult(generator).
```

## Solving puzzles:

#### Usage:
```
solve(FileName).
```

**Parameters:**

* FileName - the name of the file that contains an unsolved sudoku puzzle

**Output:**

- On the screen: If the puzzle is solvable, a solution will be displayed. Otherwise, **false** will be displayed.
- In the folder: If the puzzle is solvable, a solved puzzle will be written to a new file. If ```puzzle.txt``` is provided, the solution will be found at ```puzzle_solution.txt```.

## Generating Puzzles:

#### Usage:
```
generator(N).

```

**Parameters:**

* N - the number of puzzles and solutions to generate.

**Output:**

- On the screen: The filenames of the puzzles created.
- In the folder: An unsolved puzzle will be written to a new file. If ```puzzle.txt``` is the unsolved, then the solution will be found at ```puzzle_solution.txt```.
