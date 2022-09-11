FDIR=src
BDIR=src/backend
SOURCES=$(FDIR)/main.cpp $(BDIR)/simulator.cpp $(BDIR)/node.cpp $(BDIR)/endhost.cpp
HEADERS=$(BDIR)/simulator.hpp $(BDIR)/node.hpp $(BDIR)/endhost.hpp
OBJECTS=$(SOURCES:cpp=o)
TSOURCES=tests/simulator_init_test.cpp tests/dataflow_test.cpp tests/node_test.cpp
TOBJECTS=$(TSOURCES:cpp=o)
EXECNAME=src
TEXECNAME=tests/test
SRC=src