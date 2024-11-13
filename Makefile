CSRC = $(shell find $(abspath $(COM_HOME/src)) -name "*.c")
INC_PATH ?= $(COM_HOME)/compiler/include
INCFLAGS = $(addprefix -I, $(INC_PATH))

CC = gcc
CFLAGS = -Wall

TARGET = main

ifdef SIM
    CFLAGS += -DENABLE_SIM_MODE 
	INCFLAGS += -I$(COM_HOME)/sim/include
endif

com: ${CSRC} ${INC_PATH}
	${CC} $(CFLAGS) -o ${TARGET} ${CSRC} ${INCFLAGS}

run: com
	./${TARGET}

clean:
	rm -rf ${TARGET}