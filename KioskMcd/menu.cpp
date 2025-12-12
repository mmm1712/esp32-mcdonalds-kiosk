#include "menu.h"
#include "assets/teriyaki.h"
#include "assets/fileto.h"
#include "assets/shaka.h"
#include "assets/gracoro.h"
#include "assets/mcflurry.h"

MenuItem jpMenu[] = {
  { teriyaki, teriyakiWidth, teriyakiHeight, "Teriyaki Burger", 420, 0 },
  { fileto,   filetoWidth,   filetoHeight,   "Filet-O",          440, 0 },
  { shaka,    shakaWidth,    shakaHeight,    "Shaka Chicken",    250, 0 },
  { gracoro,  gracoroWidth,  gracoroHeight,  "Gracoro Burger",   450, 0 },
  { mcflurry, mcflurryWidth, mcflurryHeight, "McFlurry Oreo",    320, 0 }
};

const int menuLength = sizeof(jpMenu) / sizeof(MenuItem);



