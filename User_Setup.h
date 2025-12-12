#define USER_SETUP_ID 2432
#define LOAD_GFXFF
#define SMOOTH_FONT

#define ILI9341_DRIVER

#define TFT_RGB_ORDER TFT_BGR

#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14


#define TFT_CS   15      // Chip Select
#define TFT_DC    2      // Data/Command
#define TFT_RST   4      // Reset (if white screen, set to -1)
#define TFT_BL   21      // Backlight


#define TOUCH_CS 33
#define TOUCH_IRQ 36

#define XPT2046_CS 33
#define XPT2046_IRQ 36
#define TOUCH_DRIVER 2046


#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF
#define SMOOTH_FONT


#define SPI_FREQUENCY       27000000
#define SPI_READ_FREQUENCY  20000000
#define SPI_TOUCH_FREQUENCY 2500000
