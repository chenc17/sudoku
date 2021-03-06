;;; Generator

(defconstant INVALID_VAL 100)
(defconstant NUM_SQ_ROW_COL 9)
(defconstant TOTAL_NUM_SQ (* NUM_SQ_ROW_COL NUM_SQ_ROW_COL))
(defconstant MAX_SUD_VAL 9)
(defconstant UNKNOWN 0)
(defconstant MIN_SUD_VAL 1)
(defconstant MAX_ROW_COL 8)
(defconstant MIN_ROW_COL 0)

(defconstant POS_ROW 0)
(defconstant POS_COL 1)
(defconstant POS_REG 2)
(defconstant POS_VAL 3)
(defconstant POS_SQ_NUM 4)
(defconstant POS_POSS_VALS 5)

(defconstant MED_LEVEL 50)

(defconstant IO_VALUES '(#\- #\1 #\2 #\3 #\4 #\5 #\6 #\7 #\8 #\9))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;generates puzzles and their solutions
;location of puzzles/solutions specified by full_path

(defun generate_puzzles (num_puzzles full_path)
	(loop for i from 1 to num_puzzles do (generator full_path i)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;helper function for generate puzzles that does all the grunt worker

(defun generator (full_path puzzle_id)
	(let* ((solved_grid (create_solved (add_blank_square (1- TOTAL_NUM_SQ) ()) 0)))
		(write_grid_to_file solved_grid
			(concatenate 'string	full_path
														"/solutions/puzzle"
														(write-to-string puzzle_id)
														".txt"))

		;; now 'unsolve' the puzzle and create a file with unsolved version
		(setf solved_grid (create_unsolved solved_grid MED_LEVEL))
		(write_grid_to_file solved_grid
			(concatenate 'string	full_path
														"/puzzles/puzzle"
														(write-to-string puzzle_id)
														".txt"))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;parses the contents of the sudoku file specified by path
;initializes a sudoku_puzzle structure to correspond to the sudoku file
;solves the puzzle and writes the result to a file

(defun solve_puzzle (path)
	(let* ((init_list (read_sudoku_file path))
				(init_puzzle (initialize_grid init_list)))

				; for debugging
				;(format t "~a~%" init_list)
				;(pretty_print_grid init_puzzle)
				;(pretty_print_grid (create_solved init_puzzle 0))

				 ;; write the solution to
				 (write_grid_to_file (create_solved init_puzzle 0)
	 				(concatenate 'string	path
	 															"_solution"
	 															".txt"))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;makes a blank square with number and value as specified by parameters

(defun create_blank_square (sq_num val)

	(if (validate sq_num val)
		(progn (let* ((row (get_row_idx sq_num))
					 (col (get_col_idx sq_num))
					 (reg (get_reg_row_col row col))
					 (possible_vals (set_possible_vals)))
		(return-from create_blank_square (list row col reg val sq_num possible_vals))))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;creates a list of blank n+1 blank squares (with square numbers 0 through n)

(defun add_blank_square (n intermediate)
	(if (< n 0)
	(return-from add_blank_square intermediate))

	;will need to do some hard core () matching……
	;assuming n gets updated
	;CONS should append blank square to the back end…

	(add_blank_square (1- n) (CONS (create_blank_square n UNKNOWN) intermediate)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;sanity check on sq_num and value (make sure within bounds)

(defun validate (sq_num val)

	(if (and (< sq_num TOTAL_NUM_SQ)
		(>= sq_num MIN_ROW_COL)
		(>= val UNKNOWN)
		(<= val MAX_SUD_VAL))
	t
	nil))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;get row of square with square number = sq_num

(defun get_row_idx (sq_num)
	(return-from get_row_idx (floor sq_num NUM_SQ_ROW_COL)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;get column of square with square number = sq_num

(defun get_col_idx (sq_num)
	(return-from get_col_idx (mod sq_num NUM_SQ_ROW_COL)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;return the region of a square based on it's row and column.

(defun get_reg_row_col (row col)
	(let ((row_region 0) (col_region 0))

	(cond ((<= row 2) (setq row_region 0))
	      ((<= row 5) (setq row_region 1))
	      ((<= row 8) (setq row_region 2)))

	(cond ((<= col 2) (setq col_region 0))
	      ((<= col 5) (setq col_region 1))
	      ((<= col 8) (setq col_region 2)))

	(return-from get_reg_row_col (+ (* 3 row_region) col_region))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;return a shuffled list of possible values (1-9) each square could be

(defun set_possible_vals ()
	(return-from set_possible_vals (SHUFFLE (list 1 2 3 4 5 6 7 8 9))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Returns a random permutation of the list
;Example:
;(shuffle '(1 2 3 4 5 6 7 8 9 10))
;=> (2 8 5 1 7 3 10 6 4 9)
;;From http://computer-programming-forum.com/50-lisp/2ff7fc6d728e6fd3.htm

(defun SHUFFLE (list)
  (let ((vector (coerce list 'simple-vector)))
    (loop for i fixnum from (length vector) downto 2
					;rotatef modifies by rotating values from one place into another
					;svref accesses the element of simple vector specified by idx
					;random returns a pseudo-random number that is a non-neg number less
					;than limit and of same type as limit
          do (rotatef (svref vector (1- i)) (svref vector (random i))))
    (coerce vector 'list)
    ))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;takes in sudoku_grid structure and the square to start at
;returns solved sudoku grid

(defun create_solved (sudoku_grid sq_num)
		;; base case: got to the end of the square list
		(if (>= sq_num TOTAL_NUM_SQ)
				(return-from create_solved sudoku_grid))

		;; Recursive case: If square value is already known, skip over
		;; otherwise check possible values and recurse
		(if (not (= (get_square_val sudoku_grid sq_num) UNKNOWN))
				(return-from create_solved (create_solved sudoku_grid (1+ sq_num))))

		(dolist (poss_val (get_possible_values sudoku_grid sq_num))
				(if (valid sudoku_grid sq_num poss_val)
						(progn
							(setf sudoku_grid (set_value sudoku_grid sq_num poss_val))
							(let ((tmp_puzzle (create_solved sudoku_grid (1+ sq_num))))
									(if tmp_puzzle
										(return-from create_solved tmp_puzzle)))))
				(setf sudoku_grid (set_value sudoku_grid sq_num UNKNOWN)))

		(return-from create_solved NIL))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; takes a *solved_sudoku_grid* - one that is fully populated - and
; sets *num_to_remove* squares to an unknown value. first we try
; and remove an element from a list, then we ensure that the puzzle
; is still solvable. if it is solvable, then continue on, otherwise
; reset the element and try again.
; returns a sudoku_grid that contains *num_to_remove* squares with unknown values.

(defun create_unsolved (solved_sudoku_grid num_to_remove)
	(let ((candidates (range 81))
				(squares_to_remove ())
				(removed_grid solved_sudoku_grid)
				(new_sq 0))

	;(format t "Before loop!~%")
	(loop

		;get the index of the square to remove from candidates
		(setf new_sq (get_rand candidates))

		;remove that value from candidates
		(setf candidates (remove new_sq candidates))

		(setf squares_to_remove (CONS new_sq squares_to_remove))

		(setf removed_grid (set_unknown solved_sudoku_grid squares_to_remove))

		(if (not (create_solved removed_grid 0))
			(setf squares_to_remove (CDR squares_to_remove)))

		(when (or (>= (list-length squares_to_remove) num_to_remove)
					(= (list-length candidates) 0))
		(return-from create_unsolved (set_unknown solved_sudoku_grid squares_to_remove))))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; gets a random element from a list called *values*

(defun get_rand (values)
	(return-from get_rand (CAR (SHUFFLE values))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; sets the value of the square at list position *sq_num* in the *sudoku_grid* to unknown (0)

(defun set_unknown (sudoku_grid squares_to_remove)
	(dolist (sq_num squares_to_remove)
		(setf sudoku_grid (set_value sudoku_grid sq_num UNKNOWN)))
	(return-from set_unknown sudoku_grid))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; gets the value of square at list position *sq_num* in the *sudoku_grid*

(defun get_square_val (sudoku_grid sq_num)
		(let ((square (nth sq_num sudoku_grid)))
			(return-from get_square_val (nth POS_VAL square))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; gets the list of possible values a square could have

(defun get_possible_values (sudoku_grid sq_num)
		(let ((square (nth sq_num sudoku_grid)))
			(return-from get_possible_values (nth POS_POSS_VALS square))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; this function checks if it is ok to place 'val' at a given
;; 'sq_num' in the sudoku grid, following the sudoku rules
;; of no repeated values in a row, column, or 'grid'.

(defun valid (sudoku_grid sq_num val)
		(let* ((row (get_row_idx sq_num))
					(col (get_col_idx sq_num))
					(reg (get_reg_row_col row col)))

				;; loop through the puzzle and do the checks
				(dolist (tmp_square sudoku_grid)
					(if (and	(not (= sq_num (nth POS_SQ_NUM tmp_square)))
								(or (= row (nth POS_ROW tmp_square))
									 (= col (nth POS_COL tmp_square))
									 (= reg (nth POS_REG tmp_square))))
							 (if (= val (nth POS_VAL tmp_square))
							 		 (return-from valid NIL))))

				;; no repeats in rows/columns/regions :D
				(return-from valid t)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; sets sudoku_grid[sq_num] = val and returns the newly modified grid

(defun set_value (sudoku_grid sq_num val)
		(let ((tmp_sq (nth sq_num sudoku_grid)))
				(setf (nth POS_VAL tmp_sq) val)
				(setf (nth sq_num sudoku_grid) tmp_sq)
				(return-from set_value sudoku_grid)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;courtesy of http://stackoverflow.com/questions/13937520/pythons-range-analog-in-common-lisp
; creates a list that starts at min and increments by step, up until max
(defun range (max &optional (min 0) (step 1))
   (loop for n from min below max by step
      collect n))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; prints the grid in a human readable format for testing.

(defun pretty_print_grid (sudoku_grid)
	(dolist (square sudoku_grid)
			(if (= (mod (nth POS_SQ_NUM square) 9) 0)
					(format t "~%"))
			(format t "~D " (nth POS_VAL square))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; writes the grid in a human readable format.

(defun write_grid_to_file (sudoku_grid filename)
	(with-open-file (str filename
	                     :direction :output
	                     :if-exists :supersede
	                     :if-does-not-exist :create)
		(if (not sudoku_grid)
			(progn
				(format str "Unable to find a solution :|")
				(return-from write_grid_to_file)))

		(dolist (square sudoku_grid)
				(if (and (not (= (nth POS_SQ_NUM square) 0))
						     (= (mod (nth POS_SQ_NUM square) 9) 0))
						(format str "|~%"))
				(if (= (mod (nth POS_SQ_NUM square) 27) 0)
						(format str "+=======================+~%"))
				(if (= (mod (nth POS_SQ_NUM square) 3) 0)
						(format str "| "))
				(if (= (nth POS_VAL square) 0)
					(format str "- ")
					(format str "~D " (nth POS_VAL square))))
		(format str "|~%+=======================+~%")))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;reads in the file holding the sudoku puzzle (specified by path) character by character
;if the character is in the IO_VALUES list, it gets put into a list that is eventually returned
;the values in the list correspond to the values in the sudoku grid squares

(defun read_sudoku_file (path)
	(let ((myList ()))
	   (with-open-file (stream path)
	       (do ((char (read-char stream nil)
	                  (read-char stream nil)))
	           ((null char))
	           (if (member char IO_VALUES) (setq myList (CONS (char_to_num char) myList)))))
	    (return-from read_sudoku_file (nreverse myList))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;converts a character to a number

(defun char_to_num (char)
  (if (CHAR= char #\-)
    (return-from char_to_num 0))
  (return-from char_to_num (digit-char-p char)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;takes a list of numbers and uses it to initialize a sudoku grid

(defun initialize_grid (initialize_list)
	(let ((sudoku_grid (add_blank_square (1- TOTAL_NUM_SQ) ())))
		(loop for i from 0 to (1- (list-length initialize_list))
			do (setf sudoku_grid (set_value sudoku_grid i (nth i initialize_list))))

		(return-from initialize_grid sudoku_grid)))
