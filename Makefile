PROJECT = ssem
CC = g++
DEFS =
INCDIR = -I/usr/include/freetype2
INCS =
LIBDIR =
#LIBS = -lSmrFramework -lSmrAppFramework -lX11 -lXft
LIBS = -lSmrFramework -lSmrAppFramework -lX11
DEFS = -std=c++11 -pthread
OBJS = \
	Assembler.o \
	Cpu.o \
	LinkedButton.o \
	MainWindow.o \
	MainWindow_init.o \
	main.o

$(PROJECT): $(OBJS)
	$(CC) $(DEFS) $(LIBDIR) $(OBJS) $(LIBS) -o $(PROJECT)

.cpp.o:
	$(CC) $(DEFS) $(INCDIR) $(INCS) -c $<

clean:
	-rm $(PROJECT)
	-rm *.o

Cpu.o:             header.h Cpu.h Cpu.cpp
LinkedButton.o:    header.h LinkedButton.h LinkedButton.cpp
MainWindow.o:      header.h Cpu.h MainWindow.h MainWindow.cpp
MainWindow_init.o: header.h Cpu.h MainWindow.h MainWindow_init.cpp

