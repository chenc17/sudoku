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

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun generator ()

	(pretty_print_grid (create_solved (add_blank_square (1- TOTAL_NUM_SQ) ()) 0) ))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun create_blank_square (sq_num val)

	(if (validate sq_num val)
		(progn (let* ((row (get_row_idx sq_num))
					 (col (get_col_idx sq_num))
					 (reg (get_reg_row_col row col))
					 (possible_vals (set_possible_vals)))
		(return-from create_blank_square (list row col reg val sq_num possible_vals))))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun add_blank_square(n intermediate)
	(if (< n 0)
	(return-from add_blank_square intermediate))

	;will need to do some hard core () matching……
	;assuming n gets updated
	;CONS should append blank square to the back end…

	(add_blank_square (1- n) (CONS (create_blank_square n UNKNOWN) intermediate)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


(defun validate (sq_num val)

	(if (and (< sq_num TOTAL_NUM_SQ)
		(>= sq_num MIN_ROW_COL)
		(>= val UNKNOWN)
		(<= val MAX_SUD_VAL))
	t
	nil))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun get_row_idx (sq_num)
	(return-from get_row_idx (floor sq_num NUM_SQ_ROW_COL)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun get_col_idx (sq_num)
	(return-from get_col_idx (mod sq_num NUM_SQ_ROW_COL)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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

(defun set_possible_vals ()
	;shuffle to eliminate the need to select a random element from the list
	(return-from set_possible_vals (SHUFFLE (list 1 2 3 4 5 6 7 8 9))))

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun SHUFFLE (list)
  ;Returns a random permutation of the list
  ;Example:
  ;(shuffle '(1 2 3 4 5 6 7 8 9 10))
  ;=> (2 8 5 1 7 3 10 6 4 9)

  ;; This algorithm may be thought of as stacking cards pulled randomly from
  ;;a deck.  As such it is easy to see it is unbiased.
	;;From http://computer-programming-forum.com/50-lisp/2ff7fc6d728e6fd3.htm

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
(defun create_solved (sudoku_grid sq_num)
		;; base case: got to the end of the square list
		(if (>= sq_num TOTAL_NUM_SQ)
				(return-from create_solved sudoku_grid))

		;; Recursive case: If square value is already known, skip over
		;; otherwise check possible values and recurse
		(if (not (= (get_square_val sudoku_grid sq_num) UNKNOWN))
				(return-from create_solved (create_solved sudoku_grid (1+ sq_num))))

		(dolist (poss_val (get_possible_values sudoku_grid sq_num))
				(format t "Square ~D: ~D~%" sq_num poss_val)
				(if (valid sudoku_grid sq_num poss_val)
						(progn
							(setf sudoku_grid (set_value sudoku_grid sq_num poss_val))
							(let ((tmp_puzzle (create_solved sudoku_grid (1+ sq_num))))
									(if tmp_puzzle
										(return-from create_solved tmp_puzzle))))
							(setf sudoku_grid (set_value sudoku_grid sq_num UNKNOWN))))

		(return-from create_solved NIL))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun get_square_val (sudoku_grid sq_num)
		(let ((square (nth sq_num sudoku_grid)))
			(return-from get_square_val (nth POS_VAL square))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
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
(defun set_value (sudoku_grid sq_num val)
		(let ((tmp_sq (nth sq_num sudoku_grid)))
				(setf (nth POS_VAL tmp_sq) val)
				(setf (nth sq_num sudoku_grid) tmp_sq)
				(return-from set_value sudoku_grid)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun pretty_print_grid (sudoku_grid)
	(dolist (square sudoku_grid)
			(if (= (mod (nth POS_SQ_NUM square) 9) 0)
					(format t "~%"))
			(format t "~D " (nth POS_VAL square))))
