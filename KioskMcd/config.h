#pragma once

// Screen size
constexpr int SCREEN_W = 320;
constexpr int SCREEN_H = 240;

// Backlight
constexpr int BACKLIGHT_PIN = 21;

// Page enum 
enum Page {
  PAGE_MENU_1 = 0,
  PAGE_MENU_2,
  PAGE_MENU_3,
  PAGE_CHECKOUT,
  PAGE_CONFIRMED
};


struct CardLayout {
  int index;
  int y;
};

constexpr CardLayout page1Cards[] = {
  {0, 100},
  {1, 160}
};

constexpr CardLayout page2Cards[] = {
  {2, 100},
  {3, 160}
};

constexpr CardLayout page3Cards[] = {
  {4, 130}
};

// Max quantity per item
constexpr int MAX_QTY = 9;