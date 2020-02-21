# Test of natural sort
option fail 0
option malloc 0
new
ih rfc1.txt
ih rfc2086.txt
ih rfc822.txt
sort
rh rfc1.txt
rh rfc822.txt
rh rfc2086.txt
free
