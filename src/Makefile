#CC=mpic++
CC=g++

#default flags
CFLAGS= 
LFLAGS= 

#default directories
LDIR =
RUNDIR = ../wrk

EXE= vulcan

OBJ = main.o Household_Agent.o Job.o Public_Info_Board.o Initialization_Parameters.o \
Firm_Agent.o Consumer_Firm_Agent.o Consumer_Good.o Loan.o  General_Good.o\
Job.o Job_Market.o Capital_Firm_Agent.o Capital_Good.o

#library rules
$(OBJ): Household_Agent.hpp Job.hpp Public_Info_Board.hpp Initialization_Parameters.hpp  \
Firm_Agent.hpp Consumer_Firm_Agent.hpp Consumer_Good.hpp Loan.hpp  General_Good.hpp \
Capital_Firm_Agent.hpp Capital_Good.hpp


#options
ifeq ($(DEBUG),1)
  CFLAGS += -Ddebug
  CFLAGS += -O0
else
  CFLAGS += -O2
endif


%.o: %.cpp
	$(CC) $(CFLAGS) -g -c --std=c++14 -o $@ $< $(INCLUDE_PATH)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS) $(LIBS_PATH) $(LIBS)
	mv $(EXE) $(RUNDIR)
	$(call echogreen," SUCCESS")

all: $(EXE)

prepare: 
	mkdir -p $(RUNDIR)

run: all
	mpirun --oversubscribe -np 2 $(RUNDIR)/$(EXE)

debug:
	../../../gdbgui/launch_mpi_debugger 2 $(RUNDIR)/$(EXE)

.PHONY: clean all run

clean:
	rm -f *.o *~ core $(RUNDIR)/$(EXE)

flags:
	$(call echoblue," RUNDIR =  ")
	@echo $(RUNDIR)
	$(call echoblue," compile flags  CFLAGS=  ")
	@echo $(CFLAGS)
	$(call echoblue," linking flags  LFLAGS=  ")
	@echo "LFLAGS = $(LFLAGS) "

#=============== color schemes 
define echored
      @tput setaf 1
      @echo $1
      @tput sgr0
endef
define echogreen
      @tput setaf 2
      @echo $1
      @tput sgr0
endef
define echoblue
      @tput setaf 4
      @echo $1
      @tput sgr0
endef
define echocyan
      @tput setaf 6
      @echo $1
      @tput sgr0
endef
define echoinfo
      @tput setaf 2
      @echo $1 "  :  "  `tput setaf 0` $2
      @tput sgr0
endef	 
