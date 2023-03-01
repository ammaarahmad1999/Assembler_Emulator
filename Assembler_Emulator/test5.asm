;test5.asm
;code to demonstrate few errors
val1: SET val2	;SET instruction need numerical value
val2: data val1 ;data instruction need numerical value
val3: SET 089 	;Invalid octal number representation
val4: SET 0xfdh ;Invalid hexadeimal number representation
val5: SET 665d	;Invalid decimal number representation
ldc val1 :Error due to colon instead of comma
HALT	;End of code

