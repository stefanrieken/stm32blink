CFLAGS = -I. -Os -g -mcpu=cortex-m3 -mthumb -march=armv7-m -nostdlib -nostartfiles -ffunction-sections -fdata-sections -Wl,--gc-sections

all:
	arm-none-eabi-gcc $(CFLAGS) -c main.c -o main.o
	arm-none-eabi-gcc $(CFLAGS) -c start.s -o start.o
	arm-none-eabi-ld -o blink -T stm32duino.ld start.o main.o
	arm-none-eabi-objcopy -O binary blink blink.bin

upload:
	~/.arduino15/packages/stm32duino/tools/stm32tools/2017.10.19/linux/dfu-util/dfu-util -a 2 -D blink.bin

list:
	~/.arduino15/packages/stm32duino/tools/stm32tools/2017.10.19/linux/dfu-util/dfu-util --list
inspect:
	arm-none-eabi-objdump -Mforce-thumb -D blink

clean:
	rm blink blink.bin *.o
