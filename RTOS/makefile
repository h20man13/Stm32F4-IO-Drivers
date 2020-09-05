SRCDIR:=./src
LDIR:=./lib
ODIR:=./obj
IDIR:=./include
BDIR:=./bin
TARGET:=main
# Define the linker script location and chip architecture.
LSCRIPT:=stm32f401.ld
MCU_SPEC:=cortex-m4
# Toolchain definitions (ARM bare metal defaults)
TOOLCHAIN:=/usr/bin
CC:=$(TOOLCHAIN)/arm-none-eabi-g++
AS:=$(TOOLCHAIN)/arm-none-eabi-as
LD:=$(TOOLCHAIN)/arm-none-eabi-ld
OC:=$(TOOLCHAIN)/arm-none-eabi-objcopy
OD:=$(TOOLCHAIN)/arm-none-eabi-objdump
OS:=$(TOOLCHAIN)/arm-none-eabi-size
# Assembly directives.
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
CFLAGS += -I$(IDIR)
# (Set system to ignore semihosted junk)
CFLAGS += --specs=nosys.specs
# Linker directives.
LFLAGS += -mcpu=$(MCU_SPEC) 
LFLAGS += --static
LFLAGS += -mthumb
LFLAGS += -Wall
LFLAGS += -Wl,-Map=$(TARGET).map
LFLAGS += -nostdlib
LFLAGS += -lgcc
LFLAGS += -Wl,--gc-sections
LFLAGS += --specs=nosys.specs
LFLAGS += -T$(LDIR)/$(LSCRIPT)

VECT_TBL:=./$(LDIR)/p2_vtable.S
LOADER:=./$(LDIR)/setup.cpp
SRC:=$(wildcard $(SRCDIR)/%.cpp)

OBJS += $($(LOADER):.cpp=.o)
OBJS += $($(VECT_TBL):.S=.o)
OBJS += $($(SRC):$(SRCDIR)/%.cpp=$(ODIR)/%.o)

.PHONY: all
all: $(BDIR)/$(TARGET).bin
%.o: %.S
	$(CC) -c $< -o $@ $(ASFLAGS)
%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)
$(BDIR)/$(TARGET).elf: $(OBJS)
	$(CC) $^ -o $@ $(LFLAGS)
$(BDIR)/$(TARGET).bin: $(BDIR)/$(TARGET).elf
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
