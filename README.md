# ESP32 McDonald’s Kiosk

I recreated a McDonald’s-style self-ordering kiosk on the ESP32, inspired by ordering at McDonald’s in Tokyo and wanting to bring that experience onto an embedded touchscreen device.

This project focuses on UI design, touch interaction, and embedded system constraints rather than real-world payment or backend integration.


## Features

- Touchscreen UI built for a 2.8" ILI9341 display
- Multi-page menu navigation (Next / Back / Checkout)
- Interactive `+ / −` buttons with live quantity updates
- Dynamic price calculation as items are added or removed
- Checkout screen displaying selected items and order total
- “Place Order” button leading to an order confirmation screen
- Japanese-style order message (`ありがとうございました`)
- All images converted to RGB565 `.h` files for embedded displays


## Architecture Overview

The project is structured to separate concerns:

- **UI rendering** (`ui.cpp / ui.h`)
- **Touch handling** (`touch.cpp / touch.h`)
- **Menu data model** (`menu.cpp / menu.h`)
- **Application flow / state machine** (page-based navigation)

The UI avoids full screen redraws during interaction and only updates the necessary regions (e.g. quantity controls), which improves responsiveness and reflects real embedded UI design practices.


## Hardware

- ESP32
- 2.8" Touchscreen Module  
  - Display: **ILI9341**
  - Touch Controller: **XPT2046**


## Notes & Limitations

- McDonald’s ordering APIs are private, so real orders cannot be placed
- This project does **not** communicate with external services
- Built for educational, experimental, and portfolio purposes only


## What I Learned

- Designing responsive UIs under embedded constraints
- Managing state and navigation without a full OS
- Optimizing redraw regions instead of refreshing entire screens
- Structuring larger Arduino projects beyond a single `.ino` file

## Demo

### Menu Pages
<img src="images/menu1.jpg" width="500">
<img src="images/menu2.jpg" width="500">

### Checkout
<img src="images/checkout.jpg" width="500">

### Order Confirmation
<img src="images/confirmation.jpg" width="500">
