#include <stdio.h>
#include "header.h"
#include "MainWindow.h"

MainWindow::MainWindow(Cpu* c, int w,int h) : Form(NULL, 0, 0, w, h) {
  cpu = c;
  scanLine = 0;
  scopeMode = 'S';
  InitializeComponent();
  }

MainWindow::~MainWindow() {
  }

void MainWindow::TypewriterPressed(void* sender, MouseEventArgs args) {
  Byte key;
  key = Convert::ToByte(((Button*)sender)->Tag());
  cpu->Key(key);
  }

void MainWindow::CsButtonChanged(void* sender, MouseEventArgs args) {
  if (CsButton->IsPressed()) cpu->Cs(true); else cpu->Cs(false);
  }

void MainWindow::KcButtonPressed(void* sender, MouseEventArgs args) {
  cpu->Kc();
  }

void MainWindow::KacButtonPressed(void* sender, MouseEventArgs args) {
  cpu->Kac();
  }

void MainWindow::KccButtonPressed(void* sender, MouseEventArgs args) {
  cpu->Kcc();
  }

void MainWindow::KlcButtonPressed(void* sender, MouseEventArgs args) {
  cpu->Klc();
  }

void MainWindow::KscButtonPressed(void* sender, MouseEventArgs args) {
  cpu->Ksc();
  }

void MainWindow::FStatButtonChanged(void* sender, MouseEventArgs args) {
  UInt32 i;
  i = 0; 
  i |= (FStat0Button->IsPressed()) ? 0x2000 : 0;
  i |= (FStat1Button->IsPressed()) ? 0x4000 : 0;
  i |= (FStat2Button->IsPressed()) ? 0x8000 : 0;
  }

void MainWindow::LStatButtonChanged(void* sender, MouseEventArgs args) {
  UInt32 i;
  i = 0; 
  i |= (LStat0Button->IsPressed()) ? 1 : 0;
  i |= (LStat1Button->IsPressed()) ? 2 : 0;
  i |= (LStat2Button->IsPressed()) ? 4 : 0;
  i |= (LStat3Button->IsPressed()) ? 8 : 0;
  i |= (LStat4Button->IsPressed()) ? 16 : 0;
  cpu->LStat(i);
  }

void MainWindow::MonitorChanged(void* sender, MouseEventArgs args) {
  if (CButton->Checked()) scopeMode = 'C';
  if (AButton->Checked()) scopeMode = 'A';
  if (SButton->Checked()) scopeMode = 'S';
  RedrawScope();
  }

void MainWindow::StatAutoButtonChanged(void* sender, MouseEventArgs args) {
  cpu->StatAuto(StatAutoButton->IsPressed());
  }

void MainWindow::WriteEraseButtonChanged(void* sender, MouseEventArgs args) {
  cpu->WriteErase(WriteEraseButton->IsPressed());
  }

void MainWindow::TimerTick(void* sender) {
  UInt32 value;
  for (scanLine=0; scanLine < 32; scanLine++) {
    switch (scopeMode) {
      case 'C': if (cpu->Cs()) {
                if (scanLine & 1) value = cpu->Pi();
                  else value = cpu->Ci();
                  }
                else value = cpu->Ci();
                break;
      case 'A': value = cpu->Ac(); break;
      case 'S': value = cpu->Line(scanLine); break;
      }
    if (value != scanLines[scanLine]) DrawScanLine(scanLine, value);
    if (stopped != cpu->Stopped()) {
      stopped = cpu->Stopped();
      if (stopped) StopLight->BackgroundImage(stopOn);
        else StopLight->BackgroundImage(stopOff);
      }
    }
  timer->Start();
  }

void MainWindow::DrawScanLine(Byte line, UInt32 value) {
  UInt32 i;
  UInt32 y;
  scanLines[line] = value;
  y = 6 + line * 6;
  ScopeGC->ForegroundColor(Color::Black());
  ScopeGC->FillRectangle(0,y-2,34*6,6);
  ScopeGC->ForegroundColor(Color::Green());
  for (i=0; i<32; i++) {
    if (value & 1) {
      ScopeGC->LineWidth(4);
      ScopeGC->DrawLine(6+i*6-2,y,6+i*6+2,y);
      }
    else {
      ScopeGC->LineWidth(1);
      ScopeGC->DrawPoint(6+i*6,y);
      }
    value >>= 1;
    }
  ScopeGC->Flush();
  }

void MainWindow::RedrawScope() {
  UInt32 i;
  UInt32 value;
  for (i=0; i<32; i++) {
    switch (scopeMode) {
      case 'C': if (cpu->Cs()) {
                  if (i & 1) value = cpu->Pi();
                    else value = cpu->Ci();
                  }
                else value = cpu->Ci();
                break;
      case 'A': value = cpu->Ac(); break;
      case 'S': value = cpu->Line(scanLine); break;
      }
    DrawScanLine(i, value);
    }
  }

void MainWindow::ScopePaint(void* sender, PaintEventArgs args) {
  RedrawScope();
  }

