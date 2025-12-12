#include <Arduino.h>
#include <TFT_eSPI.h>
#include "config.h"
#include "menu.h"
#include "ui.h"
#include "touch.h"

TFT_eSPI tft;
int currentPage = PAGE_MENU_1;

extern int tx;
extern int ty;

void setup() {
  pinMode(BACKLIGHT_PIN, OUTPUT);
  digitalWrite(BACKLIGHT_PIN, HIGH);

  initDisplay();
  initTouch();

  drawHeader();
  drawPage(currentPage);
}

void switchPage(int newPage) {
  currentPage = newPage;

  if (newPage == PAGE_CHECKOUT) {
    drawCheckoutPage();
  } else if (newPage == PAGE_CONFIRMED) {
    drawOrderPlacedPage();
  } else {
    drawPage(newPage);
  }

  delay(200); // защита от случайных двойных касаний
}

void loop() {
  if (!pollTouch()) return;

  if (currentPage == PAGE_MENU_1) {
    for (auto &c : page1Cards) {
      handleQuantityButton(c.index, c.y);
    }

    if (touchInRect(SCREEN_W - 60, SCREEN_H - 25, 60, 20)) {
      switchPage(PAGE_MENU_2);
      return;
    }
  }

  else if (currentPage == PAGE_MENU_2) {
    for (auto &c : page2Cards) {
      handleQuantityButton(c.index, c.y);
    }

    if (touchInRect(10, SCREEN_H - 25, 60, 20)) {
      switchPage(PAGE_MENU_1);  
      return;
    }
    else if (touchInRect(SCREEN_W - 60, SCREEN_H - 25, 60, 20)) {
      switchPage(PAGE_MENU_3);  
      return;
    }
  }

  else if (currentPage == PAGE_MENU_3) {
    for (auto &c : page3Cards) {
      handleQuantityButton(c.index, c.y);
    }

    if (touchInRect(10, SCREEN_H - 25, 60, 20)) {
      switchPage(PAGE_MENU_2);  
      return;
    }
    else if (touchInRect(SCREEN_W - 90, SCREEN_H - 25, 90, 20)) {
      switchPage(PAGE_CHECKOUT); 
      return;
    }
  }

  else if (currentPage == PAGE_CHECKOUT) {
    if (touchInRect(10, SCREEN_H - 25, 60, 20)) {
      switchPage(PAGE_MENU_3);  
      return;
    }
    else if (touchInRect(SCREEN_W - 120, SCREEN_H - 40, 110, 28)) {
      switchPage(PAGE_CONFIRMED);  
      return;
    }
  }

  else if (currentPage == PAGE_CONFIRMED) {
    if (touchInRect(10, SCREEN_H - 25, 60, 20)) {
      switchPage(PAGE_MENU_1);  
      return;
    }
  }
}
