CSRC = $(shell find $(abspath $(COM_HOME/src)) -name "*.c")
INC_PATH ?= $(COM_HOME)/compiler/include
INCFLAGS = $(addprefix -I, $(INC_PATH))

TARGET = main

ifeq ($(SIM), true)
INCFLAGS += -I$(COM_HOME)/sim/include
endif

com: ${CSRC} ${INC_PATH}
	gcc -o ${TARGET} ${CSRC} ${INCFLAGS}

run: com
	./${TARGET}

clean:
	rm -rf ${TARGET}