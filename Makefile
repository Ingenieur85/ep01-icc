# PROGRAMA
PROG = perfSL

# Compilador
CC     = gcc
LIKWID_HOME=/home/soft/likwid
CFLAGS = -O0 -Wall -Wextra -I${LIKWID_HOME}/include -DLIKWID_PERFMON
LFLAGS = -lm -L${LIKWID_HOME}/lib -llikwid

# Lista de arquivos para distribuição
DISTFILES = *.c *.h *.sh LEIAME* Makefile
DISTDIR = fasf22 #`basename ${PWD}`
DISTNAME = fasf22.tar.gz

SRCS = main.c utils.c genUtils.c helpers.c seidel.c triSeidel.c gaussian.c triGaussian.c
OBJECTS = $(SRCS:.c=.o)

all: $(OBJECTS)
	$(CC) -o $(PROG) $(OBJECTS) $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean purge dist

clean:
	@echo "Limpando sujeira ..."
	@rm -f *~ *.bak

purge:  clean
	@echo "Limpando tudo ..."
	@rm -f $(PROG) *.o core a.out $(DISTDIR) $(DISTDIR).tar

dist: purge
	@echo "Generating distribution file ($(DISTNAME)) ..."
	@mkdir -p $(DISTDIR) && cp -r $(DISTFILES) $(DISTDIR)
	@tar -czvf $(DISTNAME) $(DISTDIR)
	@rm -rf $(DISTDIR)
