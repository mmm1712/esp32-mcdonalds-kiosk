#pragma once

void initDisplay();
void drawHeader();
void drawPage(int page);
void drawCheckoutPage();
void drawOrderPlacedPage();

void drawQuantityControls(int index, int y);

// Handle + / − logic
void handleQuantityButton(int index, int y);

void updateTotalValue();