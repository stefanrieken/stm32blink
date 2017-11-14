stm32blink
==========

This code can be uploaded to a 'blue pill' device fitted with the stm32duino bootloader:

	make
	sudo make upload

It is assuming the presence of dfu-util in the Arduino dot-directory of the superuser.
It also assumes the presence of arm-none-eabi-gcc and friends.

Once uploaded, it blinks.

In doing so, it proves that the basic C project setup is solid.

It functions without any external dependency on headers or libraries.

After uploading, the sketch won't immediately run, but it will do so after resetting or unplugging.
I'm not yet sure why yet; maybe it's the very sparse vector table (see start.s).

Note that I'm not using the actual 'blue pill' board, but a 100% compatible (and less buggy)
clone made by RobotDyn.

