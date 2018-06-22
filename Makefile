CPP  = g++
OBJ  = app.o mainFrame.o setdlg.o aboutDialog.o tool.o
LIBS =  -L"./" `wx-config --libs core,base`
CXXINCS = -I"./" `wx-config --cxxflags`
CXXFLAGS = $(CXXINCS) -fno-pcc-struct-return -fstrict-aliasing -Wall -DNDEBUG
BIN  = arraycode

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	rm -rf $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(OBJ) -o $(BIN) $(LIBS)
	strip $(BIN)

app.o: app.cpp
	$(CPP) -c app.cpp -o app.o $(CXXFLAGS)

mainFrame.o: mainFrame.cpp
	$(CPP) -c mainFrame.cpp -o mainFrame.o $(CXXFLAGS)

setdlg.o: setdlg.cpp
	$(CPP) -c setdlg.cpp -o setdlg.o $(CXXFLAGS)
	
aboutDialog.o: aboutDialog.cpp
	$(CPP) -c aboutDialog.cpp -o aboutDialog.o $(CXXFLAGS)	

tool.o: tool.cpp
	$(CPP) -c tool.cpp -o tool.o $(CXXFLAGS)

