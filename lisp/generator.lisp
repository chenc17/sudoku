;;; Generator

(defconstant INVALID_VAL 100)
(defconstant NUM_SQ_ROW_COL 9)
(defconstant TOTAL_NUM_SQ (* NUM_SQ_ROW_COL NUM_SQ_ROW_COL))
(defconstant MAX_SUD_VAL 9)
(defconstant UNKNOWN 0)
(defconstant MIN_SUD_VAL 1)
(defconstant MAX_ROW_COL 8)
(defconstant MIN_ROW_COL 0)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun generator ()

	(return-from generator (add_blank_square (1- TOTAL_NUM_SQ) ())))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun create_blank_square (sq_num val)

	(if (validate sq_num val)
		(progn (let* ((row (get_row_idx sq_num))
					 (col (get_col_idx sq_num))
					 (reg (get_reg_row_col row col)))
		;(let (possible_vals (set_possible_vals)))
		(return-from create_blank_square (list row col reg val sq_num))))))


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



(defun get_row_idx (sq_num)
	(return-from get_row_idx (floor sq_num NUM_SQ_ROW_COL)))

(defun get_col_idx (sq_num)
	(return-from get_col_idx (mod sq_num NUM_SQ_ROW_COL)))

(defun get_reg_row_col (row col)
	(let ((row_region 0) (col_region 0))

	(cond ((<= row 2) (setq row_region 0))
	      ((<= row 5) (setq row_region 1))
	      ((<= row 8) (setq row_region 2)))

	(cond ((<= col 2) (setq col_region 0))
	      ((<= col 5) (setq col_region 1))
	      ((<= col 8) (setq col_region 2)))

	(return-from get_reg_row_col (+ (* 3 row_region) col_region))))

;(defun set_possible_vals
