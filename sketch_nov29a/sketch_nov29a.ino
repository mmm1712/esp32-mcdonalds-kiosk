#include <TFT_eSPI.h>
#include <SPI.h>
#include "custom_logo.h"
#include "teriyaki.h"
#include "fileto.h"
#include "shaka.h"
#include "gracoro.h"
#include "mcflurry.h"
#include "letters.h"
#include <XPT2046_Touchscreen.h>

// screen size
#define SCREEN_W 320
#define SCREEN_H 240

// prototypes
void drawHeader();
void drawPage();
void drawItemCard(int index, int y);
bool touchInRect(int x, int y, int w, int h);
void drawCheckoutPage();
void drawOrderPlacedPage();  

// touch pins
#define T_CS  33
#define T_IRQ 36
#define T_CLK 25
#define T_DIN 32
#define T_DO  39

SPIClass touchSPI(HSPI);
XPT2046_Touchscreen ts(T_CS, T_IRQ);

// backlight
#define TFT_BL 21

TFT_eSPI tft = TFT_eSPI();

// menu
struct MenuItem {
  const uint16_t* img;
  uint16_t w;
  uint16_t h;
  const char* name;
  int price;
};

// menu items
MenuItem jpMenu[] = {
  { teriyaki, teriyakiWidth, teriyakiHeight, "Teriyaki Burger",            420 },
  { fileto,   filetoWidth,   filetoHeight,   "Filet-O",                    440 },
  { shaka,    shakaWidth,    shakaHeight,    "Shaka Chicken",              250 },
  { gracoro,  gracoroWidth,  gracoroHeight,  "Gracoro Burger",             450 },
  { mcflurry, mcflurryWidth, mcflurryHeight, "McFlurry Strawberry Oreo",   320 }
};

bool addedFlags[5] = { false, false, false, false, false };

int currentPage = 1; 

void setup() {
  Serial.begin(115200);

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true);

  touchSPI.begin(T_CLK, T_DO, T_DIN, T_CS);
  ts.begin(touchSPI);
  ts.setRotation(1);

  drawHeader();
  drawPage();
}

void loop() {
  if (!ts.touched()) return;

  TS_Point p = ts.getPoint();
  int tx = map(p.x, 200, 3800, 0, SCREEN_W);
  int ty = map(p.y, 200, 3800, 0, SCREEN_H);

  //page 1
  if (currentPage == 1) {


    if (touchInRect(SCREEN_W - 60, SCREEN_H - 25, 60, 20)) {
      currentPage = 2;
      drawPage();
      delay(200);
      return;
    }

    // Teriyaki
    if (touchInRect(SCREEN_W - 75, 115, 60, 30)) {
      addedFlags[0] = !addedFlags[0];
      drawPage();
      delay(200);
      return;
    }

    // Filet-O
    if (touchInRect(SCREEN_W - 75, 175, 60, 30)) {
      addedFlags[1] = !addedFlags[1];
      drawPage();
      delay(200);
      return;
    }
  }

  // page 2
  else if (currentPage == 2) {

    // BACK
    if (touchInRect(10, SCREEN_H - 25, 60, 20)) {
      currentPage = 1;
      drawPage();
      delay(200);
      return;
    }

    // Shaka
    if (touchInRect(SCREEN_W - 75, 115, 60, 30)) {
      addedFlags[2] = !addedFlags[2];
      drawPage();
      delay(200);
      return;
    }

    // Gracoro
    if (touchInRect(SCREEN_W - 75, 175, 60, 30)) {
      addedFlags[3] = !addedFlags[3];
      drawPage();
      delay(200);
      return;
    }

    // NEXT 
    if (touchInRect(SCREEN_W - 60, SCREEN_H - 25, 60, 20)) {
      currentPage = 3;
      drawPage();
      delay(200);
      return;
    }
  }

  // page 3
  else if (currentPage == 3) {

    // BACK
    if (touchInRect(10, SCREEN_H - 25, 60, 20)) {
      currentPage = 2;
      drawPage();
      delay(200);
      return;
    }

    // McFlurry
    if (touchInRect(SCREEN_W - 75, 145, 60, 30)) {
      addedFlags[4] = !addedFlags[4];
      drawPage();
      delay(200);
      return;
    }

    // CHECKOUT 
    if (touchInRect(SCREEN_W - 90, SCREEN_H - 25, 90, 20)) {
      currentPage = 4;
      drawCheckoutPage();
      delay(200);
      return;
    }
  }

  // page 4
  else if (currentPage == 4) {

    // BACK 
    if (touchInRect(10, SCREEN_H - 25, 60, 20)) {
      currentPage = 3;
      drawPage();
      delay(200);
      return;
    }

    if (touchInRect(90, SCREEN_H - 45, 140, 30)) {
      currentPage = 5;
      drawOrderPlacedPage();
      delay(200);
      return;
    }
  }

  // page 5
  else if (currentPage == 5) {

    if (touchInRect(10, SCREEN_H - 25, 60, 20)) {
      currentPage = 1;
      drawPage();
      delay(200);
      return;
    }
  }
}

void drawHeader() {
  tft.fillScreen(TFT_WHITE);
  uint16_t mcYellow = tft.color565(255, 199, 44);
  tft.fillRect(0, 0, SCREEN_W, 90, mcYellow);

  int logoX = SCREEN_W/2 - customLogoWidth/2;
  int logoY = 45 - customLogoHeight/2;
  tft.pushImage(logoX, logoY, customLogoWidth, customLogoHeight, customLogo);
}

void drawTotalBar() {
  int total = 0;
  for (int i = 0; i < 5; i++) {
    if (addedFlags[i]) total += jpMenu[i].price;
  }

  tft.setTextColor(TFT_BLACK);
  tft.setCursor(10, SCREEN_H - 25);
  tft.printf("Total: ¥%d", total);
}

void drawPage() {
  tft.fillRect(0, 90, SCREEN_W, SCREEN_H - 90, TFT_WHITE);

  if (currentPage == 1) {
    drawItemCard(0, 100);
    drawItemCard(1, 160);
    drawTotalBar();
    tft.setTextColor(TFT_BLACK);
    tft.setCursor(SCREEN_W - 55, SCREEN_H - 10);
    tft.print("NEXT");
  }

  else if (currentPage == 2) {
    drawItemCard(2, 100);
    drawItemCard(3, 160);
    drawTotalBar();
    tft.setTextColor(TFT_BLACK);
    tft.setCursor(10, SCREEN_H - 10);
    tft.print("BACK");
    tft.setCursor(SCREEN_W - 55, SCREEN_H - 10);
    tft.print("NEXT");
  }

  else if (currentPage == 3) {
    drawItemCard(4, 130);
    drawTotalBar();
    tft.setTextColor(TFT_BLACK);
    tft.setCursor(10, SCREEN_H - 10);
    tft.print("BACK");
    tft.setCursor(SCREEN_W - 90, SCREEN_H - 10);
    tft.print("CHECKOUT");
  }
}

void drawItemCard(int index, int y) {
  tft.fillRoundRect(10, y, 300, 60, 8, TFT_WHITE);

  tft.pushImage(15, y+8, jpMenu[index].w, jpMenu[index].h, jpMenu[index].img);

  tft.setTextColor(TFT_BLACK);
  tft.setCursor(80, y+18);
  tft.print(jpMenu[index].name);

  tft.setTextColor(TFT_RED);
  tft.setCursor(80, y+38);
  tft.printf("¥%d", jpMenu[index].price);

  int addX = SCREEN_W - 75;
  int addY = y + 15;

  uint16_t red   = tft.color565(220, 30, 30);
  uint16_t green = tft.color565(0, 180, 0);

  if (!addedFlags[index]) {
    tft.fillRoundRect(addX, addY, 60, 30, 6, red);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(addX+12, addY+20);
    tft.print("ADD");
  } else {
    tft.fillRoundRect(addX, addY, 60, 30, 6, green);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(addX+5, addY+20);
    tft.print("ADDED");
  }
}

void drawCheckoutPage() {
  tft.fillRect(0, 90, SCREEN_W, SCREEN_H - 90, TFT_WHITE);

  tft.setTextColor(TFT_BLACK);
  tft.setCursor(20, 100);
  tft.print("Your Order:");

  int y = 130;
  int total = 0;

  for (int i = 0; i < 5; i++) {
    if (addedFlags[i]) {
      tft.setCursor(20, y);
      tft.printf("- %s  ¥%d", jpMenu[i].name, jpMenu[i].price);
      total += jpMenu[i].price;
      y += 20;
    }
  }

  tft.setCursor(20, y + 10);
  tft.printf("TOTAL: ¥%d", total);


  tft.setCursor(10, SCREEN_H - 10);
  tft.print("BACK");


int btnW = 110; 
int btnH = 28;   
int btnX = SCREEN_W - btnW - 10; 
int btnY = SCREEN_H - btnH - 12; 

uint16_t green = tft.color565(0, 180, 0);

tft.fillRoundRect(btnX, btnY, btnW, btnH, 6, green);


tft.setTextColor(TFT_WHITE);
tft.setCursor(btnX + 12, btnY + 18);
tft.print("PLACE ORDER");
}


void drawOrderPlacedPage() {
  tft.fillRect(0, 90, SCREEN_W, SCREEN_H - 90, TFT_WHITE);


  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(70, 105);     
  tft.print("Order Placed!");


  int imgX = (SCREEN_W - lettersWidth) / 2;   
  int imgY = 145;                           
  tft.pushImage(imgX, imgY, lettersWidth, lettersHeight, letters);

  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(1);
  tft.setCursor(40, imgY + lettersHeight + 15); 
  tft.print("Order No: A3K1");


  tft.setCursor(10, SCREEN_H - 10);
  tft.print("BACK");
}


bool touchInRect(int x, int y, int w, int h) {
  TS_Point p = ts.getPoint();
  int tx = map(p.x, 200, 3800, 0, SCREEN_W);
  int ty = map(p.y, 200, 3800, 0, SCREEN_H);

  return (tx >= x && tx <= x+w && ty >= y && ty <= y+h);
}