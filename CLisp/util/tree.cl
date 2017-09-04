(defun flatten (x)
  (labels ((rec (x acc)
			 (cond ((null x) acc)
				   ((atom x) (cons x acc))
				   (t (rec (car x) (rec (cdr x) acc))))))
	(rec x nil)))

(defun prune (test tree)
  (labels ((rec (tree acc)
			 (cond ((null tree) (nreverse acc))
				   ((consp (car tree))
					(rec (cdr tree)
						 (cons (rec (car tree) nil) acc)))
				   (t (rec (cdr tree)
						   (if (funcall test (car tree))
							 acc
							 (cons (car tree) acc)))))))
	(rec tree nil)))

