#define MAIN

#include <stdio.h>
#include <string.h>
#include "header.h"
#include "images.h"
#include "Assembler.h"

int main(int argc, char** argv) {
  Int32  prog;
  UInt32 i,v;
  FILE  *file;
  String filename;
  char   buffer[1024];
  Assembler* assembler;
  prog = -1;
  trace = false;
  for (i=0; i<argc; i++) {
    if (strcmp(argv[i],"-t") == 0) trace = true;
    if (argv[i][0] != 0 && argv[i][0] != '-') prog = i;
    }
  cpu = new Cpu();
  app = new Application();
  if (app == NULL) {
    printf("Could not create application object\n");
    exit(1);
    }

  toggleOff = new Image(new MemoryStream(toggle_up, toggle_up_length));
  toggleOn = new Image(new MemoryStream(toggle_dn, toggle_dn_length));
  stopOn = new Image(new MemoryStream(stop_on, stop_on_length));
  stopOff = new Image(new MemoryStream(stop_off, stop_off_length));
  pushOn = new Image(new MemoryStream(push_on, push_on_length));
  pushOff = new Image(new MemoryStream(push_off, push_off_length));

  app->LoopDelay(1000);
  window = new MainWindow(cpu, 500, 700);
  window->BorderWidth(5);
  window->BackgroundColor(0x8000, 0x8000, 0x8000);
  window->Text("SSEM - Manchester Baby");
  app->AddForm(window);
  window->Visible(true);
  cpu->Start(NULL);
  if (prog > 0) {
    filename = String(argv[prog]);
    if (filename.ToUpper().EndsWith(".ASM")) {
      assembler = new Assembler(argc, argv);
      assembler->Assemble(&filename);
      delete(assembler);
      }
    else {
      file = fopen(argv[prog],"r");
      if (file != NULL) {
        i = 0;
        while (fgets(buffer,1023,file) != NULL) {
          while (buffer[strlen(buffer)-1] > 0 &&
                 buffer[strlen(buffer)-1] < 32) buffer[strlen(buffer)-1] = 0;
          if (buffer[0] == '-')
            cpu->Store(i, Convert::ToInt32(buffer));
          else 
            cpu->Store(i, Convert::ToUInt32(buffer));
          i++;
          }
        fclose(file);
        }
      }
    }
  try {
    app->Run();
    }
  catch (Exception &e) {
    printf("Exception caught: %s\n",e.Message());
    if (e.Sender() != NULL) printf("  Type: %s\n",e.Sender()->Type());
      else printf("Sender is NULL\n");
    fflush(stdout);
    }
  cpu->Terminate();
  delete(cpu);
  delete(app);
  delete(window);
  return 0;
  }

