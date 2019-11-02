#include "LinkedButton.h"

LinkedButton::LinkedButton(Control* parent, int x, int y, int w, int h) :
                    RadioButton(parent, x, y, w, h) {
  backgroundImage = NULL;
  pressedImage = NULL;
  }

LinkedButton::~LinkedButton() {
  }

void LinkedButton::PressedImage(Image* i) {
  Graphics* g;
  pressedImage = i;
  if (i != NULL) {
    pressedPixmap = XCreatePixmap(display, window, width, height,
       application->ScreenDepth());
    g = GetGraphics();
    g->DrawImage(pressedPixmap, 0, 0, pressedImage);
    delete(g);
    }
  }

void LinkedButton::Redraw() {
  XSetWindowAttributes attr;
  unsigned long mask;
  if (checked) {
   if (backgroundImage != NULL) {
      mask = CWBackPixmap;
      attr.background_pixmap = backgroundPixmap;
      XChangeWindowAttributes(display, window, mask, &attr);
      XClearWindow(display, window);
      }
    }
  else {
    if (pressedImage != NULL) {
      mask = CWBackPixmap;
      attr.background_pixmap = pressedPixmap;
      XChangeWindowAttributes(display, window, mask, &attr);
      XClearWindow(display, window);
      }
    }
  }

