#include <stdio.h>
#include "header.h"
#include "MainWindow.h"

#define STAT_ROW  470
#define ROW1      550
#define ROW1_OFS   10
#define ROW1_SP    40
#define ROW2      630
#define TWX        10
#define TWY        230
#define SW_W       35
#define SW_H       35
#define SCOPE_X    150
#define SCOPE_Y    20
#define SW_SPC     40
#define SW_OFS     20
#define STOP_X    400
#define STOP_Y    100

void MainWindow::InitializeComponent() {
  UInt32 i;
  UInt32 x,y;
  Label* label;
  char   buffer[12];
  CsButton = new Toggle(this, SW_OFS+SW_SPC*0,ROW2, SW_W, SW_H);
  CsButton->Visible(true);
  CsButton->BorderWidth(0);
  CsButton->BackgroundImage(toggleOff);
  CsButton->PressedImage(toggleOn);
  if (cpu->Cs()) CsButton->MouseUpEvent(0,0,1);
  CsButton->OnPress(new EventHandler(MainWindow::_CsButtonChanged, this));
  CsButton->OnRelease(new EventHandler(MainWindow::_CsButtonChanged, this));
  this->Add(CsButton);
  label = new Label(this, SW_OFS+SW_SPC*0, ROW2-25, SW_W, 25,"STOP");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);
  label = new Label(this, SW_OFS+SW_SPC*0, ROW2+SW_H, SW_W, 25,"RUN");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);

  KcButton = new Button(this, SW_OFS+SW_SPC*2,ROW2, SW_W, SW_H);
  KcButton->Visible(true);
  KcButton->BorderWidth(0);
  KcButton->BackgroundImage(toggleOff);
  KcButton->PressedImage(toggleOn);
  KcButton->OnPress(new EventHandler(MainWindow::_KcButtonPressed, this));
  this->Add(KcButton);
  label = new Label(this, SW_OFS+SW_SPC*2, ROW2-25, SW_W, 25,"KC");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);

  KlcButton = new Button(this, SW_OFS+SW_SPC*4,ROW2, SW_W, SW_H);
  KlcButton->Visible(true);
  KlcButton->BorderWidth(0);
  KlcButton->BackgroundImage(toggleOff);
  KlcButton->PressedImage(toggleOn);
  KlcButton->OnPress(new EventHandler(MainWindow::_KlcButtonPressed, this));
  this->Add(KlcButton);
  label = new Label(this, SW_OFS+SW_SPC*4, ROW2-25, SW_W, 25,"KLC");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);

  KscButton = new Button(this, SW_OFS+SW_SPC*5,ROW2, SW_W, SW_H);
  KscButton->Visible(true);
  KscButton->BorderWidth(0);
  KscButton->BackgroundImage(toggleOff);
  KscButton->PressedImage(toggleOn);
  KscButton->OnPress(new EventHandler(MainWindow::_KscButtonPressed, this));
  this->Add(KscButton);
  label = new Label(this, SW_OFS+SW_SPC*5, ROW2-25, SW_W, 25,"KSC");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);

  KacButton = new Button(this, SW_OFS+SW_SPC*6,ROW2, SW_W, SW_H);
  KacButton->Visible(true);
  KacButton->BorderWidth(0);
  KacButton->BackgroundImage(toggleOff);
  KacButton->PressedImage(toggleOn);
  KacButton->OnPress(new EventHandler(MainWindow::_KacButtonPressed, this));
  this->Add(KacButton);
  label = new Label(this, SW_OFS+SW_SPC*6, ROW2-25, SW_W, 25,"KAC");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);

  KccButton = new Button(this, SW_OFS+SW_SPC*7,ROW2, SW_W, SW_H);
  KccButton->Visible(true);
  KccButton->BorderWidth(0);
  KccButton->BackgroundImage(toggleOff);
  KccButton->PressedImage(toggleOn);
  KccButton->OnPress(new EventHandler(MainWindow::_KccButtonPressed, this));
  this->Add(KccButton);
  label = new Label(this, SW_OFS+SW_SPC*7, ROW2-25, SW_W, 25,"KCC");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);

  WriteEraseButton = new Toggle(this, SW_OFS+SW_SPC*10,ROW1, SW_W, SW_H);
  WriteEraseButton->Visible(true);
  WriteEraseButton->BorderWidth(0);
  WriteEraseButton->BackgroundImage(toggleOff);
  WriteEraseButton->PressedImage(toggleOn);
  if (cpu->WriteErase()) WriteEraseButton->MouseUpEvent(0,0,1);
  WriteEraseButton->OnPress(new EventHandler(MainWindow::_WriteEraseButtonChanged, this));
  WriteEraseButton->OnRelease(new EventHandler(MainWindow::_WriteEraseButtonChanged, this));
  this->Add(WriteEraseButton);
  label = new Label(this, SW_OFS+SW_SPC*10-5, ROW1-25, SW_W+10, 25,"WRITE");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);
  label = new Label(this, SW_OFS+SW_SPC*10-5, ROW1+SW_H, SW_W+10, 25,"ERASE");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);

  LStat0Button = new Toggle(this, SW_OFS+SW_SPC*0,STAT_ROW, SW_W, SW_H);
  LStat0Button->Visible(true);
  LStat0Button->BorderWidth(0);
  LStat0Button->BackgroundImage(toggleOff);
  LStat0Button->PressedImage(toggleOn);
  if (cpu->LStat() & 1) LStat0Button->MouseUpEvent(0,0,1);
  LStat0Button->OnPress(new EventHandler(MainWindow::_LStatButtonChanged, this));
  LStat0Button->OnRelease(new EventHandler(MainWindow::_LStatButtonChanged, this));
  this->Add(LStat0Button);
  label = new Label(this, SW_OFS+SW_SPC*0, STAT_ROW-25, SW_W, 25,"0");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);
  label = new Label(this, SW_OFS+SW_SPC*0, STAT_ROW+SW_H, SW_W, 25,"1");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);

  LStat1Button = new Toggle(this, SW_OFS+SW_SPC*1,STAT_ROW, SW_W, SW_H);
  LStat1Button->Visible(true);
  LStat1Button->BorderWidth(0);
  LStat1Button->BackgroundImage(toggleOff);
  LStat1Button->PressedImage(toggleOn);
  if (cpu->LStat() & 2) LStat1Button->MouseUpEvent(0,0,1);
  LStat1Button->OnPress(new EventHandler(MainWindow::_LStatButtonChanged, this));
  LStat1Button->OnRelease(new EventHandler(MainWindow::_LStatButtonChanged, this));
  this->Add(LStat1Button);
  label = new Label(this, SW_OFS+SW_SPC*1, STAT_ROW-25, SW_W, 25,"1");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);
  label = new Label(this, SW_OFS+SW_SPC*1, STAT_ROW+SW_H, SW_W, 25,"2");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);

  LStat2Button = new Toggle(this, SW_OFS+SW_SPC*2,STAT_ROW, SW_W, SW_H);
  LStat2Button->Visible(true);
  LStat2Button->BorderWidth(0);
  LStat2Button->BackgroundImage(toggleOff);
  LStat2Button->PressedImage(toggleOn);
  if (cpu->LStat() & 4) LStat2Button->MouseUpEvent(0,0,1);
  LStat2Button->OnPress(new EventHandler(MainWindow::_LStatButtonChanged, this));
  LStat2Button->OnRelease(new EventHandler(MainWindow::_LStatButtonChanged, this));
  this->Add(LStat2Button);
  label = new Label(this, SW_OFS+SW_SPC*2, STAT_ROW-25, SW_W, 25,"2");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);
  label = new Label(this, SW_OFS+SW_SPC*2, STAT_ROW+SW_H, SW_W, 25,"4");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);

  LStat3Button = new Toggle(this, SW_OFS+SW_SPC*3,STAT_ROW, SW_W, SW_H);
  LStat3Button->Visible(true);
  LStat3Button->BorderWidth(0);
  LStat3Button->BackgroundImage(toggleOff);
  LStat3Button->PressedImage(toggleOn);
  if (cpu->LStat() & 8) LStat3Button->MouseUpEvent(0,0,1);
  LStat3Button->OnPress(new EventHandler(MainWindow::_LStatButtonChanged, this));
  LStat3Button->OnRelease(new EventHandler(MainWindow::_LStatButtonChanged, this));
  this->Add(LStat3Button);
  label = new Label(this, SW_OFS+SW_SPC*3, STAT_ROW-25, SW_W, 25,"3");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);
  label = new Label(this, SW_OFS+SW_SPC*3, STAT_ROW+SW_H, SW_W, 25,"8");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);

  LStat4Button = new Toggle(this, SW_OFS+SW_SPC*4,STAT_ROW, SW_W, SW_H);
  LStat4Button->Visible(true);
  LStat4Button->BorderWidth(0);
  LStat4Button->BackgroundImage(toggleOff);
  LStat4Button->PressedImage(toggleOn);
  if (cpu->LStat() & 16) LStat4Button->MouseUpEvent(0,0,1);
  LStat4Button->OnPress(new EventHandler(MainWindow::_LStatButtonChanged, this));
  LStat4Button->OnRelease(new EventHandler(MainWindow::_LStatButtonChanged, this));
  this->Add(LStat4Button);
  label = new Label(this, SW_OFS+SW_SPC*4, STAT_ROW-25, SW_W, 25,"4");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);
  label = new Label(this, SW_OFS+SW_SPC*4, STAT_ROW+SW_H, SW_W, 25,"16");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);

  FStat0Button = new Toggle(this, SW_OFS+SW_SPC*6,STAT_ROW, SW_W, SW_H);
  FStat0Button->Visible(true);
  FStat0Button->BorderWidth(0);
  FStat0Button->BackgroundImage(toggleOff);
  FStat0Button->PressedImage(toggleOn);
  if (cpu->FStat() & 0x2000) FStat0Button->MouseUpEvent(0,0,1);
  FStat0Button->OnPress(new EventHandler(MainWindow::_FStatButtonChanged, this));
  FStat0Button->OnRelease(new EventHandler(MainWindow::_FStatButtonChanged, this));
  this->Add(FStat0Button);
  label = new Label(this, SW_OFS+SW_SPC*6, STAT_ROW+SW_H, SW_W, 25,"13");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);

  FStat1Button = new Toggle(this, SW_OFS+SW_SPC*7,STAT_ROW, SW_W, SW_H);
  FStat1Button->Visible(true);
  FStat1Button->BorderWidth(0);
  FStat1Button->BackgroundImage(toggleOff);
  FStat1Button->PressedImage(toggleOn);
  if (cpu->FStat() & 0x4000) FStat1Button->MouseUpEvent(0,0,1);
  FStat1Button->OnPress(new EventHandler(MainWindow::_FStatButtonChanged, this));
  FStat1Button->OnRelease(new EventHandler(MainWindow::_FStatButtonChanged, this));
  this->Add(FStat1Button);
  label = new Label(this, SW_OFS+SW_SPC*7, STAT_ROW+SW_H, SW_W, 25,"14");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);

  FStat2Button = new Toggle(this, SW_OFS+SW_SPC*8,STAT_ROW, SW_W, SW_H);
  FStat2Button->Visible(true);
  FStat2Button->BorderWidth(0);
  FStat2Button->BackgroundImage(toggleOff);
  FStat2Button->PressedImage(toggleOn);
  if (cpu->FStat() & 0x8000) FStat2Button->MouseUpEvent(0,0,1);
  FStat2Button->OnPress(new EventHandler(MainWindow::_FStatButtonChanged, this));
  FStat2Button->OnRelease(new EventHandler(MainWindow::_FStatButtonChanged, this));
  this->Add(FStat2Button);
  label = new Label(this, SW_OFS+SW_SPC*8, STAT_ROW+SW_H, SW_W, 25,"15");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);

  StatAutoButton = new Toggle(this, SW_OFS+SW_SPC*10,STAT_ROW, SW_W, SW_H);
  StatAutoButton->Visible(true);
  StatAutoButton->BorderWidth(0);
  StatAutoButton->BackgroundImage(toggleOff);
  StatAutoButton->PressedImage(toggleOn);
  if (cpu->StatAuto()) StatAutoButton->MouseUpEvent(0,0,1);
  StatAutoButton->OnPress(new EventHandler(MainWindow::_StatAutoButtonChanged, this));
  StatAutoButton->OnRelease(new EventHandler(MainWindow::_StatAutoButtonChanged, this));
  this->Add(StatAutoButton);
  label = new Label(this, SW_OFS+SW_SPC*10-5, STAT_ROW-25, SW_W+10, 25,"MAN");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);
  label = new Label(this, SW_OFS+SW_SPC*10-5, STAT_ROW+SW_H, SW_W+10, 25,"AUTO");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);

  x = TWX;
  y = TWY;
  for (i=0; i<40; i++) {
    sprintf(buffer,"%d",i);
    Typewriter[i] = new Button(this, x,y, 35, 35);
    Typewriter[i]->Visible(true);
//    Typewriter[i]->Text(buffer);
    Typewriter[i]->BorderWidth(0);
    Typewriter[i]->BackgroundImage(pushOff);
    Typewriter[i]->PressedImage(pushOn);
    Typewriter[i]->OnPress(new EventHandler(MainWindow::_TypewriterPressed, this));
    Typewriter[i]->Tag(Convert::ToString(i));
    this->Add(Typewriter[i]);
    label = new Label(this, x+35, y+5, 25,25, buffer);
    label->BackgroundColor(0x8000,0x8000,0x8000);
    label->ForegroundColor(Color::Black());
    this->Add(label);
    y += 40;
    if ((i+1) % 5 == 0) {
      x += 60;
      y = TWY;
      }
    }

  Scope = new Panel(this, SCOPE_X, SCOPE_Y, 33*6, 33*6);
  Scope->BackgroundColor(Color::Black());
  Scope->Visible(true);
  Scope->OnPaint(new EventHandler(MainWindow::_ScopePaint, this));
  this->Add(Scope);
  ScopeGC = Scope->GetGraphics();
  ScopeGC->BackgroundColor(Color::Black());
  ScopeGC->ForegroundColor(Color::White());
  for (i=0; i<32; i++) DrawScanLine(i,0xfea5);

  CButton = new LinkedButton(this, ROW1_OFS+ROW1_SP*1, ROW1, 35, 35);
  CButton->BackgroundColor(0x8000, 0x8000, 0x8000);
  CButton->Text("C");
  CButton->BackgroundImage(pushOff);
  CButton->PressedImage(pushOn);
  CButton->Checked(false);
  CButton->Visible(true);
  CButton->OnCheckChanged(new EventHandler(MainWindow::_MonitorChanged, this));
  this->Add(CButton);
  label = new Label(this, ROW1_OFS+ROW1_SP*1, ROW1-25, SW_W, 25,"C");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);

  AButton = new LinkedButton(this, ROW1_OFS+ROW1_SP*2, ROW1, 35, 35);
  AButton->BackgroundColor(0x8000, 0x8000, 0x8000);
  AButton->Text("A");
  AButton->BackgroundImage(pushOff);
  AButton->PressedImage(pushOn);
  AButton->Checked(false);
  AButton->Visible(true);
  AButton->OnCheckChanged(new EventHandler(MainWindow::_MonitorChanged, this));
  this->Add(AButton);
  label = new Label(this, ROW1_OFS+ROW1_SP*2, ROW1-25, SW_W, 25,"A");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);

  SButton = new LinkedButton(this, ROW1_OFS+ROW1_SP*3, ROW1, 35, 35);
  SButton->BackgroundColor(0x8000, 0x8000, 0x8000);
  SButton->Text("S");
  SButton->BackgroundImage(pushOff);
  SButton->PressedImage(pushOn);
  SButton->Checked(true);
  SButton->Visible(true);
  SButton->OnCheckChanged(new EventHandler(MainWindow::_MonitorChanged, this));
  this->Add(SButton);
  label = new Label(this, ROW1_OFS+ROW1_SP*3, ROW1-25, SW_W, 25,"S");
  label->BackgroundColor(0x8000,0x8000,0x8000);
  label->ForegroundColor(Color::Black());
  this->Add(label);

  StopLight = new Panel(this, STOP_X, STOP_Y, 35, 35);
  StopLight->Visible(true);
  StopLight->BorderWidth(0);
  StopLight->BackgroundImage(stopOff);
  this->Add(StopLight);
  stopped = false;

  timer = new Timer();
  timer->OnTick(new EventHandler(MainWindow::_TimerTick, this));
  timer->Interval(1);
  timer->StopOnTick(true);
  timer->Start();
  }

void MainWindow::_CsButtonChanged(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->CsButtonChanged(sender, (MouseEventArgs&)args);
  }

void MainWindow::_KcButtonPressed(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->KcButtonPressed(sender, (MouseEventArgs&)args);
  }

void MainWindow::_KacButtonPressed(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->KacButtonPressed(sender, (MouseEventArgs&)args);
  }

void MainWindow::_KccButtonPressed(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->KccButtonPressed(sender, (MouseEventArgs&)args);
  }

void MainWindow::_KlcButtonPressed(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->KlcButtonPressed(sender, (MouseEventArgs&)args);
  }

void MainWindow::_KscButtonPressed(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->KscButtonPressed(sender, (MouseEventArgs&)args);
  }

void MainWindow::_FStatButtonChanged(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->FStatButtonChanged(sender, (MouseEventArgs&)args);
  }

void MainWindow::_LStatButtonChanged(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->LStatButtonChanged(sender, (MouseEventArgs&)args);
  }

void MainWindow::_MonitorChanged(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->MonitorChanged(sender, (MouseEventArgs&)args);
  }

void MainWindow::_StatAutoButtonChanged(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->StatAutoButtonChanged(sender, (MouseEventArgs&)args);
  }

void MainWindow::_WriteEraseButtonChanged(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->WriteEraseButtonChanged(sender, (MouseEventArgs&)args);
  }

void MainWindow::_TypewriterPressed(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->TypewriterPressed(sender, (MouseEventArgs&)args);
  }

void MainWindow::_TimerTick(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->TimerTick(sender);
  }

void MainWindow::_ScopePaint(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->ScopePaint(sender, (PaintEventArgs&)args);
  }

