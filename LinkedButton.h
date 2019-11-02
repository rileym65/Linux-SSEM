#include <SmrFramework.h>
#include <SmrAppFramework.h>

using namespace SmrFramework;

class LinkedButton : public RadioButton {
  protected:
    Image  *pressedImage;
    Pixmap  pressedPixmap;
  public:
    LinkedButton(Control* parent, int x, int y, int w, int h);
    ~LinkedButton();
    virtual void PressedImage(Image *i);
    virtual void Redraw();
  };

