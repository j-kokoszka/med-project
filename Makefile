# --- MACROS
# define program name
MAIN= med-project

# define the C compiler to use
CC= gcc

# define any compile-time flags
CFLAGS= -Wall -pedantic

# Make with "make RELEASE=1" for release build
ifndef RELEASE
	CFLAGS+= -pg -O2 -g
else
	CFLAGS+= -O3
endif

# define any libraries to link into executable
LIBS= -lm

# define C source files
SRCS= src/apriori.c src/main.c src/transactions.c

# define C header files
HDRS= src/apriori.h src/transactions.h

# --- TARGETS
all: build run

#Builds the program
build: ${SRCS} ${HDRS}
	@echo #
	@echo "-- BUILDING PROGRAM --"
	${CC} ${SRCS} ${CFLAGS} ${LIBS} -o ${MAIN}.o

run:
	./${MAIN}.o output.csv 0.95

clean:
	@echo #
	@echo "-- CLEANING PROJECT FILES --"
	$(RM) *.o ${MAIN}.o
