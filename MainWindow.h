#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <SmrFramework.h>
#include <SmrAppFramework.h>

using namespace SmrFramework;

#include "Cpu.h"
#include "LinkedButton.h"

class MainWindow : public Form {
  protected:
    Byte      scanLine;
    UInt32    scanLines[32];
    char      scopeMode;
    Boolean   stopped;
    Cpu      *cpu;
    Panel    *Scope;
    Graphics *ScopeGC;
    Toggle   *CsButton;
    Button   *KcButton;
    Button   *KlcButton;
    Button   *KscButton;
    Button   *KacButton;
    Button   *KccButton;
    Toggle   *LStat0Button;
    Toggle   *LStat1Button;
    Toggle   *LStat2Button;
    Toggle   *LStat3Button;
    Toggle   *LStat4Button;
    Toggle   *FStat0Button;
    Toggle   *FStat1Button;
    Toggle   *FStat2Button;
    Toggle   *StatAutoButton;
    Toggle   *WriteEraseButton;
    LinkedButton *CButton;
    LinkedButton *AButton;
    LinkedButton *SButton;
    Panel    *StopLight;
    Button   *Typewriter[40];
    Timer    *timer;
    void InitializeComponent();
    void DrawScanLine(Byte line, UInt32 value);
    void RedrawScope();
    void CsButtonChanged(void* sender, MouseEventArgs args);
    void KcButtonPressed(void* sender, MouseEventArgs args);
    void KacButtonPressed(void* sender, MouseEventArgs args);
    void KccButtonPressed(void* sender, MouseEventArgs args);
    void KlcButtonPressed(void* sender, MouseEventArgs args);
    void KscButtonPressed(void* sender, MouseEventArgs args);
    void FStatButtonChanged(void* sender, MouseEventArgs args);
    void LStatButtonChanged(void* sender, MouseEventArgs args);
    void MonitorChanged(void* sender, MouseEventArgs args);
    void StatAutoButtonChanged(void* sender, MouseEventArgs args);
    void WriteEraseButtonChanged(void* sender, MouseEventArgs args);
    void TypewriterPressed(void* sender, MouseEventArgs args);
    void TimerTick(void* sender);
    void ScopePaint(void* sender, PaintEventArgs args);
    void static _CsButtonChanged(void* obj, void* sender, EventArgs args);
    void static _KcButtonPressed(void* obj, void* sender, EventArgs args);
    void static _KacButtonPressed(void* obj, void* sender, EventArgs args);
    void static _KccButtonPressed(void* obj, void* sender, EventArgs args);
    void static _KlcButtonPressed(void* obj, void* sender, EventArgs args);
    void static _KscButtonPressed(void* obj, void* sender, EventArgs args);
    void static _FStatButtonChanged(void* obj, void* sender, EventArgs args);
    void static _LStatButtonChanged(void* obj, void* sender, EventArgs args);
    void static _MonitorChanged(void* obj, void* sender, EventArgs args);
    void static _StatAutoButtonChanged(void* obj, void* sender, EventArgs args);
    void static _WriteEraseButtonChanged(void* obj, void* sender, EventArgs args);
    void static _TypewriterPressed(void* obj, void* sender, EventArgs args);
    void static _TimerTick(void* obj, void* sender, EventArgs args);
    void static _ScopePaint(void* obj, void* sender, EventArgs args);
  public:
    MainWindow(Cpu* c, int w, int h);
    ~MainWindow();
  };

#endif

