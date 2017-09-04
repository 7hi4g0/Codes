(defun map0-n (fn n)
  (mapa-b fn 0 n))

(defun map1-n (fn n)
  (mapa-b fn 1 n))

(defun mapa-b (fn a b &optional (step 1))
  (do ((i a (+ i step))
	   (result nil))
	  ((> i b) (nreverse result))
	(push (funcall fn i) result)))

(defun map-> (fn start test-fn succ-fn)
  (do ((i start (funcall succ-fn i))
	   (result nil))
	  ((funcall test-fn i) (nreverse result))
	(push (funcall fn i) result)))

(defun mappend (fn &rest lsts)
  (apply #'append (apply #'mapcar fn lsts)))

(defun mapcars (fn &rest lsts)
  (let ((result nil))
	(dolist (lst lsts)
	  (dolist (obj lst)
		(push (funcall fn obj) result)))
	(nreverse result)))

(defun rmapcar (fn &rest args)
  (if (some #'atom args)
	(apply fn args)
	(apply #'mapcar
		   #'(lambda (&rest args)
			   (apply #'rmapcar fn args))
		   args)))
