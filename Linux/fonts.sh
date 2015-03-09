(echo '<html><body>' && (fc-list | sort | sed 's/.*:\(.*\):.*/<font face="\1">\1<\/font><br>/') && echo '</body></html>') > fonts.html
