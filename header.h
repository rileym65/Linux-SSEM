#ifndef _HEADER_H
#define _HEADER_H

#ifdef MAIN
#define LINK
#else
#define LINK extern
#endif

#include <SmrFramework.h>
#include <SmrAppFramework.h>

using namespace SmrFramework;

#include "Cpu.h"
#include "MainWindow.h"

LINK Cpu         *cpu;
LINK Application *app;
LINK MainWindow  *window;
LINK Image       *toggleOn;
LINK Image       *toggleOff;
LINK Image       *pushOn;
LINK Image       *pushOff;
LINK Image       *stopOn;
LINK Image       *stopOff;
LINK Boolean      trace;

extern void Assemble(String* filename);

#endif

