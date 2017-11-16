blink_base4
===========

Blinks the value of an int, a nybble at a time.
A long blink '_' serves both as the zero value and positional separator,
so that e.g. '..._..' forms the number '32' in base 4, which is '14' in decimal.
The (two-nybble) hexadecimal value 'B2' would be blinked as as '.._... ..'
Note the positional separator on the high value 'B' but not on the low (<4) value '2'.

To reconstruct the blinks back to hexadecimal one starts with writing down the base-4
 values, e.g.:

	23 2 -> (2*4)+3 2 -> 11 2 -> B2

To continue to decimal:

	(11*16)+2=178

This code can be uploaded to a 'blue pill' device fitted with the stm32duino bootloader:

	make
	sudo make upload

It is assuming the presence of dfu-util in the Arduino dot-directory of the superuser.
It also assumes the presence of arm-none-eabi-gcc and friends.
