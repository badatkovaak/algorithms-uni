INCLUDE_DIR := include
INCLUDE_FLAG := -I./${INCLUDE_DIR}

CC := clang
CFLAGS := --std=c23 -g -O0
C_WARNING_FLAGS := -Wall -Wextra -Wpedantic -Wshadow -Wno-unused-function -Wcast-qual -Wignored-qualifiers -Wno-comment -Wsign-compare -Wno-unknown-warning-option -Wno-psabi -Wno-mismatched-new-delete -Wimplicit-fallthrough


BUILD_DIR := build
SUB_DIR := test
SOURCES_DIR := src/${SUB_DIR}
SRC := ${wildcard ${SOURCES_DIR}/*.c}
OBJ := ${SRC:${SOURCES_DIR}/%.c=${BUILD_DIR}/%.o}
EXE_NAME := test

all: lang part_clean

${BUILD_DIR}/%.o : ${SOURCES_DIR}/%.c
	${CC} -c ${CFLAGS} ${C_WARNING_FLAGS} ${INCLUDE_FLAG} $< -o $@

lang: ${OBJ}
	${CC} ${CFLAGS} -o ${BUILD_DIR}/${EXE_NAME} ${OBJ}

clean:
	rm -f ${wildcard build/*.o} ${BUILD_DIR}/${EXE_NAME}

part_clean:
	rm -f ${wildcard *.o} ${wildcard build/*.o}
