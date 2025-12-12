#include "ui.h"
#include <TFT_eSPI.h>
#include "menu.h"
#include "assets/custom_logo.h"
#include "assets/letters.h"
#include "config.h"
#include "touch.h"

extern TFT_eSPI tft;
extern int currentPage;


void initDisplay() {
  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true);
}

// header
void drawHeader() {
  tft.fillScreen(TFT_WHITE);

  uint16_t yellow = tft.color565(255, 199, 44);
  tft.fillRect(0, 0, SCREEN_W, 90, yellow);

  int x = SCREEN_W / 2 - customLogoWidth / 2;
  int y = 45 - customLogoHeight / 2;
  tft.pushImage(x, y, customLogoWidth, customLogoHeight, customLogo);
}

// item card
static void drawItemCard(int i, int y) {
  tft.fillRoundRect(10, y, 300, 60, 8, TFT_WHITE);
  tft.pushImage(15, y + 8, jpMenu[i].w, jpMenu[i].h, jpMenu[i].img);

  tft.setTextColor(TFT_BLACK);
  tft.setCursor(80, y + 18);
  tft.print(jpMenu[i].name);

  tft.setTextColor(TFT_RED);
  tft.setCursor(80, y + 38);
  tft.printf("¥%d", jpMenu[i].price);

  drawQuantityControls(i, y);
}

// quantity controls
void drawQuantityControls(int index, int y) {
  tft.fillRect(SCREEN_W - 120, y + 8, 120, 44, TFT_WHITE);

  tft.setTextSize(2);
  tft.setTextColor(TFT_BLACK);

  int baseY = y + 20;

  // minus
  tft.setCursor(SCREEN_W - 95, baseY);
  tft.print("-");

  // quantity
  tft.setCursor(SCREEN_W - 65, baseY);
  tft.print(jpMenu[index].quantity);

  // plus
  tft.setCursor(SCREEN_W - 35, baseY);
  tft.print("+");

  tft.setTextSize(1);
}

// page draw
void drawPage(int page) {
  tft.fillRect(0, 90, SCREEN_W, SCREEN_H - 90, TFT_WHITE);

  if (page == PAGE_MENU_1) {
    drawItemCard(0, 100);
    drawItemCard(1, 160);

    tft.setTextColor(TFT_BLACK);
    tft.setCursor(SCREEN_W - 55, SCREEN_H - 10);
    tft.print("NEXT");
  }

  else if (page == PAGE_MENU_2) {
    drawItemCard(2, 100);
    drawItemCard(3, 160);

    tft.setTextColor(TFT_BLACK);
    tft.setCursor(10, SCREEN_H - 10);
    tft.print("BACK");

    tft.setCursor(SCREEN_W - 55, SCREEN_H - 10);
    tft.print("NEXT");
  }

  else if (page == PAGE_MENU_3) {
    drawItemCard(4, 130);

    tft.setTextColor(TFT_BLACK);
    tft.setCursor(10, SCREEN_H - 10);
    tft.print("BACK");

    tft.setCursor(SCREEN_W - 90, SCREEN_H - 10);
    tft.print("CHECKOUT");
  }
}

// quantity handler
void handleQuantityButton(int index, int y) {
  bool changed = false;

  // plus
  if (touchInRect(SCREEN_W - 40, y + 8, 30, 44)) {
    if (jpMenu[index].quantity < MAX_QTY) {
      jpMenu[index].quantity++;
      changed = true;
    }
  }

  // minus
  if (touchInRect(SCREEN_W - 100, y + 8, 30, 44)) {
    if (jpMenu[index].quantity > 0) {
      jpMenu[index].quantity--;
      changed = true;
    }
  }

  if (changed) {
    drawQuantityControls(index, y);
    delay(150); // debounce
  }
}

// checkout page
void drawCheckoutPage() {
  tft.fillRect(0, 90, SCREEN_W, SCREEN_H - 90, TFT_WHITE);

  // calculate total first
  int total = 0;
  for (int i = 0; i < menuLength; i++) {
    total += jpMenu[i].price * jpMenu[i].quantity;
  }

  // header line
  tft.setTextColor(TFT_BLACK);
  tft.setCursor(20, 100);
  tft.printf("Your order total: ¥%d", total);

  // items
  int y = 130;
  const int bottomSafeY = SCREEN_H - 55;

  for (int i = 0; i < menuLength; i++) {
    if (jpMenu[i].quantity > 0) {
      if (y > bottomSafeY) break;

      int sub = jpMenu[i].quantity * jpMenu[i].price;

      tft.setCursor(20, y);
      tft.printf("- %s x%d  ¥%d",
                 jpMenu[i].name,
                 jpMenu[i].quantity,
                 sub);

      y += 20;
    }
  }

  // buttons
  uint16_t green = tft.color565(0, 180, 0);
  tft.fillRoundRect(SCREEN_W - 120, SCREEN_H - 40, 110, 28, 6, green);

  tft.setTextColor(TFT_WHITE);
  tft.setCursor(SCREEN_W - 105, SCREEN_H - 22);
  tft.print("PLACE ORDER");

  tft.setTextColor(TFT_BLACK);
  tft.setCursor(10, SCREEN_H - 10);
  tft.print("BACK");
}

// confirm page
void drawOrderPlacedPage() {
  tft.fillRect(0, 90, SCREEN_W, SCREEN_H - 90, TFT_WHITE);

  tft.setTextSize(2);
  tft.setTextColor(TFT_BLACK);
  tft.setCursor(70, 105);
  tft.print("Order Placed!");

  int x = (SCREEN_W - lettersWidth) / 2;
  tft.pushImage(x, 145, lettersWidth, lettersHeight, letters);

  tft.setTextSize(1);
  tft.setCursor(40, 200);
  tft.print("Order No: A3K1");

  tft.setCursor(20, SCREEN_H - 15);
  tft.print("BACK");
}