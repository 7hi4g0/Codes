(defun memoize (fn)
  (let ((cache (make-hash-table :test #'equal)))
	#'(lambda (&rest args)
		(multiple-value-bind (val win) (gethash args cache)
		  (if win
			  val
			  (setf (gethash args cache)
					(apply fn args)))))))

(defun compose (&rest fns)
  (if fns
	  (let ((fn1 (car (last fns)))
			(fns (butlast fns)))
		#'(lambda (&rest args)
			(reduce #'funcall fns
					:from-end t
					:initial-value (apply fn1 args))))
	  #'identity))

(defun fif (if then &optional else)
  #'(lambda (x)
	  (if (funcall if x)
		  (funcall then x)
		  (if else (funcall else x)))))

(defun fint (fn &rest fns)
  (if (null fns)
	  fn
	  (let ((chain (apply #'fint fns)))
		#'(lambda (x)
			(and (funcall fn x) (funcall chain x))))))

(defun fun (fn &rest fns)
  (if (null fns)
	  fn
	  (let ((chain (apply #'fun fns)))
		#'(lambda (x)
			(or (funcall fn x) (funcall chain x))))))
