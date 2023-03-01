;test6.asm
;rectification of errors of test5.asm
ldc val1 ;Error rectified colon replaced by semicolon
HALT	;End of code
val1: SET 045	;Error rectified, numerical octal value
val2: data 34 	;Error rectified, numerical decimal value
val3: SET 0x65	;Error rectified, hexadecimal value
