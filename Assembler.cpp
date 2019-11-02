#include "header.h"
#include "Assembler.h"

Assembler::Assembler(int argc, char** argv) {
  UInt32 i;
  showList = false;
  outputToFile = false;
  for (i=0; i<argc; i++) {
    if (strcmp(argv[i],"-l") == 0) showList = true;
    if (strcmp(argv[i],"-o") == 0) outputToFile = true;
    }
  }

Assembler::~Assembler() {
  CleanUp();
  }

void Assembler::CleanUp() {
  UInt32 i;
  if (labels != NULL) {
    for (i=0; i<labels->Count(); i++)
      delete(labels->At(i));
    delete(labels);
    labels = NULL;
    }
  if (labelValues != NULL) {
    delete(labelValues);
    labelValues = NULL;
    }
  if (source != NULL) {
    for (i=0; i<source->Count(); i++)
      delete(source->At(i));
    delete(source);
    source = NULL;
    }
  if (tokens != NULL) {
    for (i=0; i<tokens->Count();i++) delete(tokens->At(i));
    delete(tokens);
    tokens = NULL;
    }
  }

Boolean Assembler::Assemble(String* filename) {
  Byte          address;
  UInt32        i;
  UInt32        j;
  UInt32        k;
  UInt32        pass;
  UInt32        value;
  Int32         pos;
  Int32         label;
  Int32         cmd;
  Int32         arg;
  String        line;
  StreamReader *file;
  StreamWriter *ofile;
  char          buffer[64];
  
  if (showList) printf("Assembling %s\n",filename->AsCharArray());
  source = new List<String*>();
  labels = new List<String*>();
  labelValues = new List<Byte>();
  file = new StreamReader(filename);
  while (!file->EndOfStream()) {
    line = file->ReadLine();
    source->Add(new String(line.Trim()));
    }
  delete(file);

  for (pass=0; pass<2; pass++) {
    address = 0;
    for (i=0; i<source->Count(); i++) {
      tokens = new List<String*>();
      line = String(source->At(i)).Trim();
      while (line.IndexOf(' ') >= 0) {
        tokens->Add(new String(line.Substring(0,line.IndexOf(' '))));
        line = line.Substring(line.IndexOf(' ')).Trim();
        }
      tokens->Add(new String(line));
      label = -1;
      cmd = -1;
      arg = -1;
      j = 0;
      while (j < tokens->Count()) {
        token = tokens->At(j);
        if (token->Length() > 0) {
          if (token->StartsWith("[")) j++;
          else if (token->EndsWith(":")) label = j++;
          else if (cmd < 0) cmd = j++;
          else if (arg < 0) arg = j++;
          else j++;
          }
        else j++;
        }
      if (pass == 0 && label >= 0) {
        token = tokens->At(label);
        token = new String(token->Substring(0,token->Length()-1).ToUpper());
        if ((token->At(0) >= 'a' && token->At(0) <= 'z') ||
            (token->At(0) >= 'A' && token->At(0) <= 'Z')) {
          }
        else {
          printf("Label must begin with a letter\n");
          printf("  %s\n",source->At(i)->AsCharArray());
          delete(token);
          CleanUp();
          return false;
          }
        for (k=0; k<labels->Count(); k++)
          if (token->Equals(labels->At(k))) {
            printf("Label multiply defined\n");
            printf("  %s\n",source->At(i)->AsCharArray());
            delete(token);
            CleanUp();
            return false;
            }
        labels->Add(token);
        labelValues->Add(address);
        }
      if (cmd >= 0) {
        token = tokens->At(cmd);
        if (token->ToUpper().Equals("JMP")) value = 0<<13;
        else if (token->ToUpper().Equals("JRP")) value = 1<<13;
        else if (token->ToUpper().Equals("LDN")) value = 2<<13;
        else if (token->ToUpper().Equals("STO")) value = 3<<13;
        else if (token->ToUpper().Equals("SUB")) value = 4<<13;
        else if (token->ToUpper().Equals("CMP")) value = 6<<13;
        else if (token->ToUpper().Equals("STP")) value = 7<<13;
        else if (token->ToUpper().Equals("NUM")) value = 0<<13;
        else {
          printf("Invalid opcode: %s\n",source->At(i)->AsCharArray());
          CleanUp();
          return false;
          }
        if (pass == 1 && arg >= 0) {
          token = tokens->At(arg);
          if (token->At(0) >= 'a' && token->At(0) <= 'z') {
            token = new String(token->ToUpper());
            pos = -1;
            for (k=0; k<labels->Count(); k++)
              if (token->Equals(labels->At(k))) pos = k;
            delete(token);
            if (pos < 0) {
              printf("Label not defined\n");
              printf("  %s\n",source->At(i)->AsCharArray());
              return false;
              }
            value |= labelValues->At(pos);
            }
          else if (token->At(0) >= 'A' && token->At(0) <= 'Z') {
            pos = -1;
            for (k=0; k<labels->Count(); k++)
              if (token->Equals(labels->At(k))) pos = k;
            if (pos < 0) {
              printf("Label not defined\n");
              printf("  %s\n",source->At(i)->AsCharArray());
              CleanUp();
              return false;
              }
            value |= labelValues->At(pos);
            }
          else value |= Convert::ToInt32(token);
          }
        if (pass == 0) {
          if (address > 31) {
            printf("Address exceeded memory\n");
            CleanUp();
            return false;
            }
          address++;
          }
        if (pass == 1) {
          if (address > 31) {
            printf("Address exceeded memory\n");
            CleanUp();
            return false;
            }
          if (showList)
            printf("  %02d: %08x  %s\n",address,value,source->At(i)->AsCharArray());
          cpu->Store(address, value);
          address++;
          }
        }


      for (j=0; j<tokens->Count();j++) delete(tokens->At(j));
      delete(tokens);
      tokens = NULL;
      }
    }
  CleanUp();
  if (outputToFile) {
    if (filename->ToUpper().EndsWith(".ASM")) {
      filename = new String(filename->Substring(0,filename->Length()-4)+String(".hex"));
      }
    else {
      filename = new String(String(filename) + String(".hex"));
      }
    ofile = new StreamWriter(filename);
    for (i=0; i<32; i++) {
      sprintf(buffer,"$%08x",cpu->Line(i));
      ofile->WriteLine(buffer);
      }
    delete(ofile);
    delete(filename);
    }
  return true;
  }

