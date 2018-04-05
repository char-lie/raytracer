THIRD_PARTY_DIR=${PWD}/third-party

FLAGS=-I${THIRD_PARTY_DIR}/include -Wall -O3
CXX=clang++-5.0
CXXFLAGS=${FLAGS} --std=c++17
CXXLINKFLAGS=-lglfw -lGL -ldl -lOpenCL
CC=clang-5.0
CCFLAGS=${FLAGS}

SRCDIR=src
OBJDIR=obj
BINDIR=bin

SOURCE_FILES= \
	gui/program.cpp gui/texture.cpp gui/gui.cpp \
	cpu/image.cpp \
	gpu/cl.cpp gpu/image.cpp \
	raytracer/sphere.cpp raytracer/cpu.cpp raytracer/raytracer.cpp
GLAD_SRC=${THIRD_PARTY_DIR}/glad.c
MAIN_SRC=${SRCDIR}/main.cpp

SOURCES=$(SOURCE_FILES:%=${SRCDIR}/%)
OBJECTS=$(SOURCES:${SRCDIR}/%.cpp=${OBJDIR}/%.o)

MAIN_OBJ=${OBJDIR}/main.o
GLAD_OBJ=${OBJDIR}/glad.o

all: ${GLAD_OBJ} ${OBJECTS} ${MAIN_OBJ}
	mkdir -p ${BINDIR}
	${CXX} ${CXXFLAGS} ${CXXLINKFLAGS}     \
		${GLAD_OBJ} ${OBJECTS} ${MAIN_OBJ} \
		-o ${BINDIR}/raytracer

${OBJECTS}: ${OBJDIR}/%.o : ${SRCDIR}/%.cpp
	mkdir -p `dirname $@`
	${CXX} ${CXXFLAGS} $< -c -o $@

${SRCDIR}/main.cpp: ${SOURCES}
${OBJDIR}/main.o: ${SRCDIR}/main.cpp

${GLAD_OBJ}:
	mkdir -p `dirname ${GLAD_OBJ}`
	${CC} ${CCFLAGS} ${GLAD_SRC} -c -o ${GLAD_OBJ}

${MAIN_OBJ}: ${MAIN_SRC}
	mkdir -p `dirname ${MAIN_OBJ}`
	${CXX} ${CXXFLAGS} ${MAIN_SRC} -c -o ${MAIN_OBJ}

clean:
	rm -rf ${BINDIR}
	rm -rf ${OBJDIR}
	# rm -rf ~/.nv/ComputeCache/
