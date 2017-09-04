(defun find2 (fn lst)
  (if (null lst)
	  nil
	  (let ((val (funcall fn (car lst))))
		(if val
		    (values (car lst) val)
			(find2 fn (cdr lst))))))

(defun before (x y lst &key (test #'eql))
  (and lst
	   (let ((first (car lst)))
		 (cond ((funcall test y first) nil)
			   ((funcall test x first) lst)
			   (t (before x y (cdr lst) :test test))))))

(defun after (x y lst &key (test #'eql))
  (let ((rest (before y x :test test)))
	(and rest (member x rest :test test))))

(defun duplicate (obj lst &key (test #'eql))
  (member obj (cdr (member obj lst :test test))
		  :test test))

(defun split-if (fn lst)
  (let ((acc nil))
	(do ((src lst (cdr src)))
	    ((or (null src) (funcall fn (car src)))
		 (values (nreverse acc) src))
	  (push (car src) acc))))

