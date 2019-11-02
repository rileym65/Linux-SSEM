#include <stdio.h>
#include <unistd.h>
#include "header.h"
#include "Cpu.h"

Cpu::Cpu() : Thread() {
  UInt32 i;
  for (i=0; i<32; i++) mem[i] = 0;
  ci = 0;
  pi = 0;
  ac = 0;
  statLines = 0xe01f;
  skip = false;
  stopped = true;
  statAuto = true;
  cs = false;
  writeErase = false;
  step = false;
  }

Cpu::~Cpu() {
  }

UInt32 Cpu::Ac() {
  return ac;
  }

UInt32 Cpu::Ci() {
  return ci;
  }

Boolean Cpu::Cs() {
  return cs;
  }

Boolean Cpu::Cs(Boolean state) {
  cs = state;
  step = state;
  return cs;
  }

UInt32 Cpu::FStat() {
  return (statLines & 0xe000);
  }

UInt32 Cpu::FStat(UInt32 i) {
  i &= 0xe0;
  statLines &= 0xffff1fff;
  statLines |= i;
  return (statLines & 0xe000);
  }

UInt32 Cpu::Line(Byte i) {
  if (i > 31) return 0;
  return mem[i];
  }

void Cpu::Kac() {
  ac = 0;
  }

void Cpu::Kc() {
  stopped = false;
  if (!cs) step = true;
  }

void Cpu::Kcc() {
  ci = 0;
  ac = 0;
  }

void Cpu::Key(Byte i) {
  if (i > 31) return;
  if (writeErase) {
    mem[statLines & 0x1f] &= ~(1 << i);
    }
  else {
    mem[statLines & 0x1f] |= (1 << i);
    }
  }

void Cpu::Klc() {
  mem[statLines & 0x1f] = 0;
  }

void Cpu::Ksc() {
  UInt32 i;
  for (i=0; i<32; i++) mem[i] = 0;
  }

UInt32 Cpu::LStat() {
  return (statLines & 0x1f);
  }

UInt32 Cpu::LStat(UInt32 i) {
  i &= 0x1f;
  statLines &= 0xffffffe0;
  statLines |= i;
  return (statLines & 0x1f);
  }

UInt32 Cpu::Pi() {
  return pi;
  }

Boolean Cpu::StatAuto() {
  return statAuto;
  }

Boolean Cpu::StatAuto(Boolean state) {
  statAuto = state;
  return statAuto;
  }

void Cpu::Step() {
  ci++;
  if (skip) {
    ci++;
    skip = false;
    }
  if (statAuto) pi = mem[ci & 0x1f] & statLines;
    else pi = statLines;
  if (trace) printf("[%02d] ",ci);
  switch ((pi >> 13) & 0x7) {
    case 0:
         ci = mem[pi & 0x1f];
         if (trace) printf("JMP %02d -> %d",pi & 0x1f, ci);
         break;
    case 1:
         ci += mem[pi & 0x1f];
         if (trace) printf("JRP %02d -> %d",pi & 0x1f, ci);
         break;
    case 2:
         ac = -mem[pi & 0x1f];
         if (trace) printf("LDN %02d -> %d",pi & 0x1f, ac);
         break;
    case 3:
         mem[pi & 0x1f] = ac;
         if (trace) printf("STO %02d",pi & 0x1f);
         break;
    case 4:
         ac -= mem[pi & 0x1f];
         if (trace) printf("SUB %02d [%d] -> %d",pi & 0x1f, mem[pi & 0x1f], ac);
         break;
    case 5:
         ac -= mem[pi & 0x1f];
         if (trace) printf("SUB %02d [%d] -> %d",pi & 0x1f, mem[pi & 0x1f], ac);
         break;
    case 6: if (ac & 0x80000000) skip = true;
         if (trace) {
           printf("CMP %d -> ",ac);
           if (skip) printf("Skip"); else printf("No skip");
           }
         break;
    case 7:
         stopped = true;
         if (trace) printf("STP");
         break;
    }
  if (trace) printf("\n");
  }

Boolean Cpu::Stopped() {
  return stopped;
  }

void Cpu::Store(Byte address, UInt32 value) {
  if (address > 31) return;
  mem[address] = value;
  }

Boolean Cpu::WriteErase() {
  return writeErase;
  }

Boolean Cpu::WriteErase(Boolean state) {
  writeErase = state;
  return writeErase;
  }

void Cpu::execute(void* arg) {
  HrTimer timer;
  timer.Restart();
  while (!terminate) {
    while (timer.Microseconds() < 1428) {
      usleep(100);
      }
    timer.Restart();
    if (step && !stopped) {
      Step();
      step = cs;
      }
    }
  }

