#ifndef _ASSEMBLER_H
#define _ASSEMBLER_H

#include <SmrFramework.h>

using namespace SmrFramework;

class Assembler {
  protected:
    Boolean        showList;
    Boolean        outputToFile;
    List<String*> *source;
    List<String*> *tokens;
    String        *token;
    List<String*> *labels;
    List<Byte>    *labelValues;
    void CleanUp();
  public:
    Assembler(int argc,char** argv);
    ~Assembler();
    Boolean Assemble(String* filename);
  };

#endif

