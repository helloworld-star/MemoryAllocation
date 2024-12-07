ifdef RISCV
	include $(LINK)/link.mk
endif

CSRCS += $(wildcard $(abspath $(COM_HOME)/compiler/src/*.c))
INC_PATH ?= $(COM_HOME)/compiler/include
INCFLAGS = $(addprefix -I, $(INC_PATH))

CC := gcc
CFLAGS += -Wall -static

TARGET = main.elf

ifdef RISCV
	CC = riscv64-unknown-elf-gcc
    CFLAGS += -static
	CFLAGS += -ffunction-sections -fdata-sections -march=rv64g -mabi=lp64d -g
	CFLAGS += -mcmodel=medany
	CFLAGS += ${LDFLAGS}
endif

ifdef SIM
    CFLAGS += -DENABLE_SIM_MODE 
    INCFLAGS += -I$(COM_HOME)/sim/include
    CSRCS += $(wildcard $(COM_HOME)/sim/src/*.c)
endif

com: ${CSRCS} ${INC_PATH}
	${CC} $(CFLAGS) -o ${TARGET} ${CSRCS} ${INCFLAGS}

run: com
	./${TARGET}

clean:
	rm -rf ${TARGET}
