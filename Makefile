TARGET_PREFIX?=arm-eabi-
TARGET_AS=${TARGET_PREFIX}as
TARGET_GCC=${TARGET_PREFIX}gcc
TARGET_LD=${TARGET_PREFIX}ld.bfd
TARGET_OBJCOPY=${TARGET_PREFIX}objcopy

CFLAGS= -O2 -Werror

controller.bin: controller.elf
	${TARGET_OBJCOPY} -j ".text" -j ".data" -O binary controller.elf controller.bin

controller.elf: init.o controller.o one-wire.o
	${TARGET_LD} -g -T ld.ld -e 0x00000300 $^ -o controller.elf

init.o: init.S
	${TARGET_AS} -k -mthumb -mlittle-endian init.S -o init.o


#controller.o: controller.c 
#	${TARGET_GCC} ${CFLAGS} -mthumb -mcpu=cortex-m3 -c $^ -o controller.o

#one-wire.o: one-wire.c
#	${TARGET_GCC} ${CFLAGS} -mthumb -mcpu=cortex-m3 -c $^ -o one-wire.o
#
#
%.o: %.c
	${TARGET_GCC} ${CFLAGS} -mthumb -mcpu=cortex-m3 -c $< -o $@
	

clean:
	rm -fr *.o
	rm -fr controller.bin
	rm -fr controller.elf
