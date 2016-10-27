(load "helpers")

; Original
(defun my-length (lst)
  (labels ((f (lst acc)
			  (if lst
				(f (cdr lst) (1+ acc))
				acc)))
	(f lst 0)))

; Macros 1
(defun my-length (lst)
  (labels ((f (lst acc)
			  (split lst
				(f tail (1+ acc))
				acc)))
	(f lst 0)))

; Macros Final
(defun my-length (lst)
  (recurse (lst lst
			acc 0)
		   (split lst
			 (self tail (1+ acc))
			 acc)))

; Functional
(defun my-length (lst)
  (reduce (lambda (x i)
			(1+ x))
		  lst
		  :initial-value 0))
