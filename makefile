io = io/gpio.c
timer = timer/timer_vars.c
src =  main.c
TARGET = main
# Define the linker script location and chip architecture.
LD_SCRIPT = p2.ld
MCU_SPEC  = cortex-m4
# Toolchain definitions (ARM bare metal defaults)
TOOLCHAIN = /usr
CC = $(TOOLCHAIN)/bin/arm-none-eabi-gcc
AS = $(TOOLCHAIN)/bin/arm-none-eabi-as
LD = $(TOOLCHAIN)/bin/arm-none-eabi-ld
OC = $(TOOLCHAIN)/bin/arm-none-eabi-objcopy
OD = $(TOOLCHAIN)/bin/arm-none-eabi-objdump
OS = $(TOOLCHAIN)/bin/arm-none-eabi-size
# Assembly directives.
ASFLAGS += -c
ASFLAGS += -O0
ASFLAGS += -mcpu=$(MCU_SPEC)
ASFLAGS += -mthumb
ASFLAGS += -Wall
# (Set error messages to appear on a single line.)
ASFLAGS += -fmessage-length=0
# C compilation directives
CFLAGS += -mcpu=$(MCU_SPEC)
CFLAGS += -mthumb
CFLAGS += -Wall
CFLAGS += -g
CFLAGS += -I./*/
# (Set error messages to appear on a single line.)
CFLAGS += -fmessage-length=0
# (Set system to ignore semihosted junk)
CFLAGS += --specs=nosys.specs
# Linker directives.
LSCRIPT = ./$(LD_SCRIPT)
LFLAGS += -mcpu=$(MCU_SPEC)
LFLAGS += -mthumb
LFLAGS += -Wall
LFLAGS += --specs=nosys.specs
LFLAGS += -nostdlib
LFLAGS += -lgcc
LFLAGS += -T$(LSCRIPT)
VECT_TBL = ./p2_vtable.S
AS_SRC   = ./bootloader.S
C_SRC    = $(io) $(timer) $(src)
OBJS =  $(VECT_TBL:.S=.o)
OBJS += $(AS_SRC:.S=.o)
OBJS += $(C_SRC:.c=.o)
.PHONY: all
all: $(TARGET).bin
%.o: %.S
	$(CC) -x assembler-with-cpp $< -o $@ $(ASFLAGS)
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
$(TARGET).elf: $(OBJS)
	$(CC) $^ -o $@ $(LFLAGS)
$(TARGET).bin: $(TARGET).elf
	$(OC) -S -O binary $< $@
	$(OS) $<
.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f $(TARGET).elf
	rm -f ./*~
	rm -f ./*/*#
	rm -f ./*/*~
	rm -f ./*#
	rm -f $(TARGET).bin
