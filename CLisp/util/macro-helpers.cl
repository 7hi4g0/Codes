(defmacro mac (expr)
  `(pprint (macroexpand-1 ',expr)))

