#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

typedef u_int32_t  UInt32;
typedef int32_t    Int32;

UInt32   ram[32];
UInt32   address;
char     labels[32][256];
UInt32   values[32];
char     refs[32][256];
UInt32   refValues[32];
UInt32   numRefs;
UInt32   numLabels;
UInt32   errors;
UInt32   pass;
char     srcName[1024];
char     showLabels;
char     showList;
char     showMap;
char     createMapFile;
char     listFile;
FILE    *lstFile;
FILE    *mapFile;
char     lastLabel[256];
UInt32   lines;
UInt32   code;
char     currentLine[1024];
UInt32   lineNumber;
char     ebuffer[1024];
char     baseName[1024];
char     listName[1024];
char     mapName[1024];
char     outName[1024];
char     outLine[1024];

void Error(char* msg) {
  printf("Error: %s\n",msg);
  printf("%d: %s\n",lineNumber, currentLine);
  errors++;
  }

void AddReference(char* label) {
  UInt32 i;
  if (pass == 2) return;
  if (numRefs == 32) {
    Error("Too many references");
    return;
    }
  for (i=0; i<numRefs; i++) {
    if (strcmp(label,refs[i]) == 0) {
      return;
      }
    }
  strcpy(refs[numRefs++], label);
  }

void AddLabel(char* label, UInt32 value) {
  UInt32 i;
  if (pass == 2) return;
  if (numLabels == 32) {
    Error("Too many labels");
    return;
    }
  for (i=0; i<numLabels; i++) {
    if (strcmp(label,labels[i]) == 0) {
      sprintf(ebuffer,"Duplicate label: %s",label);
      Error(ebuffer);
      return;
      }
    }
  strcpy(labels[numLabels], label);
  values[numLabels++] = value;
  }

void SetLabel(char* label, UInt32 value) {
  UInt32 i;
  for (i=0; i<numLabels; i++) {
    if (strcmp(label,labels[i]) == 0) {
      values[i] = value;
      return;
      }
    }
  sprintf(ebuffer,"Label not found: %s",label);
  Error(ebuffer);
  }

void Output(UInt32 value) {
  if (address >= 32) {
    sprintf(ebuffer,"Address exceeds memory: %d\n",address);
    Error(ebuffer);
    return;
    }
  sprintf(ebuffer,"%02x %08x ",address,value);
  strcat(outLine, ebuffer);
  ram[address++] = value;
  code++;
  }


UInt32 GetLabel(char* label) {
  UInt32 i;
  for (i=0; i<numLabels; i++) {
    if (strcmp(label,labels[i]) == 0) return values[i];
    }
  if (pass == 1) return 0;
  sprintf(ebuffer,"Label not defined: %s",label);
  Error(ebuffer);
  return 0;
  }

int compare(char* line, char* what) {
  if (strncasecmp(line, what, strlen(what)) != 0) return -1;
  if (line[strlen(what)] == 0) return 0;
  if (line[strlen(what)] == ' ') return 0;
  if (line[strlen(what)] == '\t') return 0;
  return -1;
  }

Int32 getArg(char *line) {
  Int32 ret;
  char  label[256];
  int   pos;
  while (*line == ' ' || *line == '\t') line++;
  if (*line == 0) return 0;
  if (*line == '-' || (*line >= '0' && *line <= '9')) {
    ret = atoi(line);
    return ret;
    }
  if ((*line >= 'a' && *line <= 'z') ||
      (*line >= 'A' && *line <= 'Z')) {
    pos = 0;
    while ((*line >= 'a' && *line <= 'z') ||
           (*line >= 'A' && *line <= 'Z') ||
           (*line >= '0' && *line <= '9') ||
           *line == '_') label[pos++] = *line++;
    label[pos] = 0;
    return GetLabel(label);
    }
  if (*line == '[') {
    line++;
    pos = 0;
    label[pos++] = '$';
    while ((*line >= 'a' && *line <= 'z') ||
           (*line >= 'A' && *line <= 'Z') ||
           (*line >= '0' && *line <= '9') ||
           *line == '_') label[pos++] = *line++;
    label[pos] = 0;
    if (pass == 1) {
      AddReference(label);
      return 0;
      }
    return GetLabel(label);
    }
  return 0;
  }

void assemble(char* line) {
  UInt32 i;
  UInt32 opcode;
  char   label[256];
  char   buffer[256];
  UInt32 pos;
  if (strchr(line, ';') != NULL) {
    *(strchr(line,';')) = 0;
    while (strlen(line) > 0 && line[strlen(line)-1] <= ' ')
      line[strlen(line)-1] = 0;
    }
  strcpy(lastLabel, "");
  if (*line != ' ' && *line != '\t') {
    pos = 0;
    while (*line != 0 && *line != ' ' && *line != '\t' && *line != ':')
      label[pos++] = *line++;
    label[pos] = 0;
    if (*line == ':') line++;
    AddLabel(label, address);
    strcpy(lastLabel, label);
    }
  while (*line == ' ' || *line == '\t') line++;
  if (compare(line, "ORG") == 0) {
    address = getArg(line+3);
    if (address > 0x1f) {
      sprintf(ebuffer,"Address exceeds range: %x",address);
      }
    }
  else if (compare(line, "DW") == 0) {
    Output(getArg(line+3));
    }
  else if (compare(line, "EQU") == 0) {
    SetLabel(lastLabel, getArg(line+4));
    }
  else if (compare(line, "REFS") == 0) {
    while (strlen(outLine) < 19) strcat(outLine," ");
    strcat(outLine,"  ");
    strcat(outLine,currentLine);
    if (pass == 2 && showList) printf("%s\n",outLine);
    if (pass == 2 && listFile) fprintf(lstFile,"%s\n",outLine);
    strcpy(currentLine,"");
    for (i=0; i<numRefs; i++) {
      strcpy(outLine,"       ");
      sprintf(buffer,"%s:    dw       %d",refs[i],GetLabel(refs[i]+1));
      assemble(buffer);
      while (strlen(outLine) < 19) strcat(outLine," ");
      strcat(outLine,"  ");
      strcat(outLine,buffer);
      if (pass == 2 && showList) {
        if (i < numRefs-1) printf("%s\n",outLine);
        }
      if (pass == 2 && listFile) {
        if (i < numRefs-1) fprintf(lstFile,"%s\n",outLine);
        }
      }
    }
  else if (compare(line, "JMP") == 0) {
    opcode = 0x0000 | getArg(line+4);
    Output(opcode);
    }
  else if (compare(line, "JRP") == 0) {
    opcode = 0x2000 | getArg(line+4);
    Output(opcode);
    }
  else if (compare(line, "LDN") == 0) {
    opcode = 0x4000 | getArg(line+4);
    Output(opcode);
    }
  else if (compare(line, "STO") == 0) {
    opcode = 0x6000 | getArg(line+4);
    Output(opcode);
    }
  else if (compare(line, "SUB") == 0) {
    opcode = 0x8000 | getArg(line+4);
    Output(opcode);
    }
  else if (compare(line, "CMP") == 0) {
    opcode = 0xc000 | getArg(line+4);
    Output(opcode);
    }
  else if (compare(line, "STP") == 0) {
    opcode = 0xf000;
    Output(opcode);
    }
  else {
    Error("Unknown opcode");
    }
  }

void assemblyPass(char *filename) {
  FILE* infile;
  char  line[1024];
  lineNumber = 0;
  address = 0;
  lines = 0;
  code = 0;
  infile = fopen(filename,"r");
  if (infile == NULL) {
    sprintf(ebuffer,"Could not open source file: %s",filename);
    Error(ebuffer);
    return;
    }
  if (pass == 2 && listFile != 0) lstFile = fopen(listName, "w");
  while (fgets(line,1023,infile) != NULL) {
    while (strlen(line) > 0 && line[strlen(line)-1] <= ' ')
      line[strlen(line)-1] = 0;
    strcpy(currentLine, line);
    sprintf(outLine, "[%03d]: ",lines);
    if (strcasecmp(line,".list") == 0) showList = 0xff;
    else if (strcasecmp(line,".symbols") == 0) showLabels = 0xff;
    else if (strcasecmp(line,".lstfile") == 0) listFile = 0xff;
    else if (strcasecmp(line,".map") == 0) showMap = 0xff;
    else if (strcasecmp(line,".mapfile") == 0) createMapFile = 0xff;
    else if (strlen(line) > 0) assemble(line);
    while (strlen(outLine) < 19) strcat(outLine," ");
    strcat(outLine,"  ");
    strcat(outLine,currentLine);
    if (pass == 2 && showList) printf("%s\n",outLine);
    if (pass == 2 && listFile) fprintf(lstFile,"%s\n",outLine);
    lines++;
    }
  fclose(infile);
  if (pass == 2 && listFile) fclose(lstFile);
  }

int main(int argc, char** argv) {
  int i;
  int j;
  UInt32 u;
  FILE *outFile;
  numRefs = 0;
  numLabels = 0;
  errors = 0;
  strcpy(srcName, "");
  showLabels = 0;
  showList = 0;
  listFile = 0;
  showMap = 0;
  i = 1;
  while (i < argc) {
    if (strcmp(argv[i], "-l") == 0) showList = 0xff;
    else if (strcmp(argv[i], "-s") == 0) showLabels = 0xff;
    else if (strcmp(argv[i], "-m") == 0) showMap = 0xff;
    else if (strcmp(argv[i], "-M") == 0) createMapFile = 0xff;
    else if (strcmp(argv[i], "-L") == 0) listFile = 0xff;
    else if (argv[i][0] != '-') strcpy(srcName, argv[i]);
    else {
      printf("Error: Unknown switch: %s\n",argv[i]);
      exit(1);
      }
    i++;
    }
  if (strlen(srcName) == 0) {
    printf("Error: No input file specified\n");
    exit(1);
    }
  strcpy(baseName, srcName);
  if (strchr(baseName, '.') != NULL)
    *(strchr(baseName, '.')) = 0;
  strcpy(listName, baseName);
  strcat(listName, ".lst");
  pass = 1;
  assemblyPass(srcName);
  if (errors > 0) {
    printf("Errors detected during pass 1. Aborting\n");
    exit(1);
    }
  pass = 2;
  assemblyPass(srcName);

  printf("\n");
  printf("Lines assembled: %d\n", lines);
  printf("Code generate  : %d\n", code);
  printf("Errors         : %d\n\n", errors);

  if (errors == 0) {
    if (showLabels) {
    printf("Labels:\n");
      for (i=0; i<numLabels; i++) {
        printf("  %-20s: %02x\n",labels[i], values[i]);
        }
      printf("\n");
      }
    strcpy(outName, baseName);
    strcat(outName, ".mb");
    outFile = fopen(outName,"w");
    for (i=0; i<32; i++) {
      fprintf(outFile,"%d\n",ram[i]);
      }
    fclose(outFile);
    if (showMap || createMapFile) {
      if (createMapFile) {
        strcpy(mapName, baseName);
        strcat(mapName, ".map");
        mapFile = fopen(mapName,"w");
        }
      if (showMap) printf("Input Map:\n");
      if (showMap) printf("               0   4 5   9 10 14 15 19 20 24 25 29 30\n");
      if (createMapFile)
        fprintf(mapFile,"               0   4 5   9 10 14 15 19 20 24 25 29 30\n");
      for (i=0; i<32; i++) {
        if (ram[i] != 0) {
          if (showMap) printf("  [%02x] ",i);
          if (createMapFile) fprintf(mapFile,"  [%02x] ",i);
          u = i;
          for (j=0; j<5; j++) {
            if (showMap) {
              if (u & 1) printf("1"); else printf("0");
              }
            if (createMapFile) {
              if (u & 1) fprintf(mapFile,"1"); else fprintf(mapFile,"0");
              }
            u >>= 1;
            }
          if (showMap) printf("   ");
          if (createMapFile) fprintf(mapFile,"   ");
          u = ram[i];
          for (j=0; j<32; j++) {
            if (j != 0 && j % 5 == 0) {
              if (showMap) printf(" ");
              if (createMapFile) fprintf(mapFile," ");
              }
            if (showMap) {
              if (u & 1) printf("*"); else printf(".");
              }
            if (createMapFile) {
              if (u & 1) fprintf(mapFile,"*"); else fprintf(mapFile,".");
              }
            u >>= 1;
            }
          if (showMap) printf("\n");
          if (createMapFile) fprintf(mapFile,"\n");
          }
        }
      if (showMap) printf("\n");
      if (createMapFile) fclose(mapFile);
      }
    }
  else {
    printf("Errors encountered.  Output suppressed\n");
    }

  return (errors > 0) ? 1 : 0;
  }



