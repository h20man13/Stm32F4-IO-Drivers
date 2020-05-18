io = io/gpio.cpp io/io.cpp io/analog.cpp
timer = timer/timer_pre.cpp timer/timer_src.cpp timer/timer_speed.cpp timer/timer_enable.cpp
math = math/rand.cpp math/algebra.cpp
data_structures = data_structures/linkedList.cpp
src =  setup.cpp main.cpp
TARGET = main
# Define the linker script location and chip architecture.
LD_SCRIPT = p2.ld
MCU_SPEC  = cortex-m4
# Toolchain definitions (ARM bare metal defaults)
TOOLCHAIN = /usr
CC = $(TOOLCHAIN)/bin/arm-none-eabi-g++
AS = $(TOOLCHAIN)/bin/arm-none-eabi-as
LD = $(TOOLCHAIN)/bin/arm-none-eabi-ld
OC = $(TOOLCHAIN)/bin/arm-none-eabi-objcopy
OD = $(TOOLCHAIN)/bin/arm-none-eabi-objdump
OS = $(TOOLCHAIN)/bin/arm-none-eabi-size
# Assembly directives.
ASFLAGS += -c
ASFLAGS += -mcpu=$(MCU_SPEC)
ASFLAGS += -mthumb
ASFLAGS += -Wall
# C compilation directives
CFLAGS += -mcpu=$(MCU_SPEC)
CFLAGS += -mthumb
CFLAGS += -fno-exceptions
CFLAGS += -fno-rtti
CFLAGS += -Wall
CFLAGS += -g
CFLAGS += -I./*/
# (Set system to ignore semihosted junk)
CFLAGS += --specs=nosys.specs
# Linker directives.
LSCRIPT = ./$(LD_SCRIPT)
LFLAGS += -mcpu=$(MCU_SPEC) 
LFLAGS += --static
LFLAGS += -mthumb 
LFLAGS += -Wall
LFLAGS += -Wl,-Map=$(TARGET).map
LFLAGS += -nostdlib
LFLAGS += -Wl,--gc-sections
LFLAGS += --specs=nosys.specs
LFLAGS += -T$(LSCRIPT)
VECT_TBL = ./p2_vtable.S
C_SRC = $(io) $(timer) $(math) $(src) $(data_structures)
OBJS = $(VECT_TBL:.S=.o)
OBJS += $(C_SRC:.cpp=.o)
.PHONY: all
all: $(TARGET).bin
%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)
%.o: %.S
	$(CC) $< -o $@ $(ASFLAGS)
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
	rm -f $(TARGET).map
