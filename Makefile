CC = clang
CFLAGS = --std=c99 -g -O0
C_WARNING_FLAGS = -Wall -Wextra -Wpedantic -Wshadow -Wno-unused-function -Wcast-qual -Wignored-qualifiers -Wno-comment -Wsign-compare -Wno-unknown-warning-option -Wno-psabi -Wno-mismatched-new-delete -Wimplicit-fallthrough

BUILD_DIR := build
SOURCES_DIR := src
SRC := ${wildcard ${SOURCES_DIR}/*.c}
OBJ := ${SRC:${SOURCES_DIR}/%.c=${BUILD_DIR}/%.o}
EXE_NAME := test

all: lang part_clean

${BUILD_DIR}/%.o : ${SOURCES_DIR}/%.c
	${CC} -c ${CFLAGS} ${C_WARNING_FLAGS} $< -o $@

lang: ${OBJ}
	${CC} -o ${BUILD_DIR}/${EXE_NAME} ${OBJ}

clean:
	rm -f ${wildcard build/*.o} ${BUILD_DIR}/${EXE_NAME}

part_clean:
	rm -f ${wildcard *.o} ${wildcard build/*.o}
