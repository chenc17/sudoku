;; sudoku-solver

;; create a 2D array to represent the puzzle
;; i feel like having this here violates the main
;; reason that we're doing functional programming
(defvar example-puzzle #2A((0 0 4 3 0 0 0 0 5)
                   (0 8 0 0 7 0 0 4 0)
                   (6 0 1 0 4 0 2 0 0)
                   (7 0 0 0 0 9 0 0 0)
                   (0 6 8 0 1 0 4 3 0)
                   (0 0 0 4 0 0 0 0 2)
                   (0 0 3 0 2 0 5 0 8)
                   (0 2 0 0 8 0 0 7 0)
                   (8 0 0 0 0 3 6 0 0)))

(defconstant UNKNOWN 0)
(defconstant ROW_SIZE 9)
(defconstant MAX_VAL 9)
(defconstant MIN_VAL 1)
(defconstant INVALID -1)
(defconstant BOARD_SIZE 81)

;; solve the default puzzle or pass-in a new one to be solved.
;; then print the solved sudoku puzzle
(defun solve-puzzle (&optional (new-puzzle puzzle))
  (setf puzzle new-puzzle)
  (if (backtracking-solver 0)
    (print-puzzle puzzle)
    (format t "Unable to solve puzzle")))

;; **RECURSION HAPPENING BELOW**
(defun backtracking-solver (square_no)
  ;; base case: we've gotten to the end of the puzzle
  (if (>= square_no BOARD_SIZE)
      (return t) )

  ;; get row/column information
  (let ((row (floor square_no ROW_SIZE)))
        (col (mod square_no ROW_SIZE)))

        (if (not (= (puzzle row col) UNKNOWN) )
          ;; not unknown value, RECURSE!
          (backtracking-solver (+ square_no 1))

          ;; loop over possible values, checking if valid
          ;; if valid, then set the value and recurse
          (loop for i from 1 to 9
                        do (and (check i row col)
                                (progn
                                  (setf (aref puzzle row col) i)
                                  (and (guess (+ index)) (return t))))
                        finally (progn
                                  (setf (aref puzzle row col) UNKNOWN)
                                  (return nil)))))

(defun check (num row col)
  ;; check the value agains the values of the puzzle.
)

(defun print-puzzle ()
   (dotimes (r board-size)
     (format t "~%+---+---+---+---+---+---+---+---+---+~%|")
     (dotimes (c board-size)
       (format t " ~A |" (aref board r c))))
   (format t "~%+---+---+---+---+---+---+---+---+---+~%~%"))

(solve-puzzle)
