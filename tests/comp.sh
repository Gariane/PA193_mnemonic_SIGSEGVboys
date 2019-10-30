#!/usr/bin/bash

[ $# -ne 4 ] && exit 2

#$1 -> our program invocation
#$2 -> referential program invocation
#$3 -> our output file
#$4 -> referential output file

$1 > $3 2>&1

OURVAL=$?
$2 > $4 2>&1
REFVAL=$?

[ $OURVAL -ne $REFVAL ] && exit 1
[ $OURVAL -eq 1 ] && exit 0
[ $OURVAL -gt 1 ] && exit 1

sed $3 -i '1,2d'

diff $3 $4 > /dev/null

exit [ $? -eq 0 ]

