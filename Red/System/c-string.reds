Red/System [
	Title: "Test with c-string! comparison"
	Author: "Thiago Dourado de Andrade"
]

s: "hello"
r: "world"

print-line [ "s = r == " s = r ]
print-line [ "s <> r == " s <> r ]
print-line [ "s > r == " s > r ]
print-line [ "s < r == " s < r ]

print-line [ "s pointer == " as pointer! [integer!] s ]
print-line [ "r pointer == " as pointer! [integer!] r ]

q: "hello"

print-line [ "s = q == " s = q ]
print-line [ "s <> q == " s <> q ]
print-line [ "s > q == " s > q ]
print-line [ "s < q == " s < q ]

print-line [ "q pointer == " as pointer! [integer!] q ]
