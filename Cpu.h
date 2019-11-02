#ifndef _CPU_H
#define _CPU_H

#include <SmrFramework.h>

using namespace SmrFramework;

class Cpu : public Thread {
  protected:
    UInt32 ci;
    UInt32 pi;
    UInt32 ac;
    UInt32 statLines;
    Boolean cs;
    Boolean skip;
    Boolean step;
    Boolean stopped;
    Boolean statAuto;
    Boolean writeErase;
    UInt32 mem[32];
    virtual void    execute(void* arg);
  public:
    Cpu();
    ~Cpu();
    UInt32  Ac();
    UInt32  Ci();
    Boolean Cs();
    Boolean Cs(Boolean state);
    UInt32  FStat();
    UInt32  FStat(UInt32 i);
    void    Kac();
    void    Kc();
    void    Kcc();
    void    Key(Byte i);
    void    Klc();
    void    Ksc();
    UInt32  Line(Byte i);
    UInt32  LStat();
    UInt32  LStat(UInt32 i);
    UInt32  Pi();
    Boolean StatAuto();
    Boolean StatAuto(Boolean state);
    void    Step();
    Boolean Stopped();
    void    Store(Byte address, UInt32 value);
    Boolean WriteErase();
    Boolean WriteErase(Boolean state);
  };

#endif

