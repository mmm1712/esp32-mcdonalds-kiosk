#include "touch.h"
#include "config.h"
#include <XPT2046_Touchscreen.h>

// пины
#define T_CS  33
#define T_IRQ 36
#define T_CLK 25
#define T_DIN 32
#define T_DO  39

SPIClass touchSPI(HSPI);
XPT2046_Touchscreen ts(T_CS, T_IRQ);

// глобальные координаты
int tx = -1;
int ty = -1;

void initTouch() {
  touchSPI.begin(T_CLK, T_DO, T_DIN, T_CS);
  ts.begin(touchSPI);
  ts.setRotation(1);
}

bool pollTouch() {
  if (!ts.touched()) return false;

  TS_Point p = ts.getPoint();
  tx = map(p.x, 200, 3800, 0, SCREEN_W);
  ty = map(p.y, 200, 3800, 0, SCREEN_H);
  return true;
}

bool touchInRect(int x, int y, int w, int h) {
  return (tx >= x && tx <= x + w &&
          ty >= y && ty <= y + h);
}
