# PROGRAMA
PROG = resolveEDO
OBJS = $(PROG).o edo.o utils.o
VERIF = verificaEP02

# Compilador
CC     = gcc

# --- CONFIGURAÇÃO DO LIKWID ---
LIKWID_HOME = /home/soft/likwid
LIKWID_INCLUDE = ${LIKWID_HOME}/include
LIKWID_LIB = ${LIKWID_HOME}/lib
# ----------------------------------------------------

# Flags de compilação com as opções do LIKWID
# -DLIKWID_PERFMON: Ativa as macros do LIKWID no código C
# -I${LIKWID_INCLUDE}: Diz ao compilador onde encontrar o arquivo "likwid.h"
CFLAGS = -O0 -DLIKWID_PERFMON -I${LIKWID_INCLUDE}

# Flags de linkagem com as opções do LIKWID
# -lm: Linka a biblioteca matemática (para funções como sqrt, cos, etc)
# -L${LIKWID_LIB}: Diz ao linker onde encontrar os arquivos da biblioteca LIKWID
# -llikwid: Linka a biblioteca LIKWID
LFLAGS = -lm -L${LIKWID_LIB} -llikwid


# Lista de arquivos para distribuição.
DISTFILES = *.c *.h LEIAME* Makefile *.dat
DISTDIR = ${USER}

.PHONY: clean purge dist all

%.o: %.c %.h utils.h
	$(CC) -c $(CFLAGS) -o $@ $<

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

$(VERIF): $(VERIF).c
	$(CC) -Wno-format -o $@ $<

testeFormato: $(PROG) $(VERIF)
	@cat teste.dat | ./$(PROG) | ./$(VERIF)

clean:
	@rm -f *~ *.bak

purge:  clean
	@rm -f core a.out $(OBJS)
	@rm -f $(PROG) $(VERIF) $(DISTDIR) $(DISTDIR).tgz

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tgz) ..."
	@ln -s . $(DISTDIR)
	@tar -chzvf $(DISTDIR).tgz $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)