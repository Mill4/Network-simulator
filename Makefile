include vars.make
CXXFLAGS = -g -std=c++14 -Wall -Wextra -pedantic
CPPFLAGS += -c
VALGRINDFLAGS = --trace-children=yes --leak-check=full --show-leak-kinds=all

ifeq ($$(shell uname),Windows_NT)
	APPEND=QT += widgets >> $(SRC)/frontend.pro
	RMF=$(SRC)/*.Debug $(SRC)/*.Release
	RMD=$(SRC)/release $(SRC)/debug
	EXECUTABLE:=$(SRC)/release/$(EXECNAME).exe
	TEXECUTABLE:=$(TEXECNAME).out
else ifeq ($(shell uname),Darwin)
 	APPEND="QT += widgets" | tee -a $(SRC)/$(EXECNAME).pro
	RMF=$(SRC)/moc_* \
		$(SRC)/*.o
	RMD=$(SRC)/*.app
	EXECUTABLE:=$(SRC)/$(EXECNAME).app/Contents/MacOS/$(EXECNAME)
	TEXECUTABLE:=$(TEXECNAME).out
else
	APPEND="QT += widgets" | tee -a $(SRC)/$(EXECNAME).pro
	RMF=$(SRC)/moc_* \
		$(SRC)/*.o
	EXECUTABLE:=$(SRC)/$(EXECNAME)
endif

.PHONY: all clean run valgrind-run

all: main
  
main:
	@echo "You might want to run one of these: \n \"make build\"\n \"make test\"\n \"make run\"\n \"make clean\""

build:
	cd $(SRC) && qmake -project && qmake
	awk 'NR==8{print "QT += widgets"}1' src/src.pro > tmp.pro
	cat tmp.pro > src/src.pro 
	rm tmp.pro
	
#	@{echo -n 'QT += widgets\n'; cat src.tmp; } > src/src.pro 
#	@echo -n "QT += widgets";tac src/src.pro| tac > newfilename.txt
#	@echo $(APPEND)

test: $(TOBJECTS) $(COBJECTS)
	@echo "Test Running"
	$(CXX) $(TOBJECTS) $(CTOBJECTS) $(LDFLAGS) -o $(TEXECUTABLE)
	@./$(TEXECUTABLE)

clean:
	rm -rf $(RMD)
	rm -f $(ERC)/.qmake.stash \
		  $(SRC)/*.pro \
		  $(SRC)/Makefile \
		  $(RMF) \
		  tests/*.o \
		  tests/*.out
	

run: 
	@echo "Running \"$(EXECUTABLE)\""
	cd $(SRC) && make
	@./$(EXECUTABLE)
	
	
valgrind-run: main
	@valgrind $(VALGRINDFLAGS) ./$(EXECUTABLE)
