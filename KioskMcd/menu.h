#pragma once
#include <stdint.h>

// Структура одного элемента меню
struct MenuItem {
  const uint16_t* img;  // Изображение товара
  uint16_t w;           // Ширина изображения
  uint16_t h;           // Высота изображения
  const char* name;     // Название товара
  int price;            // Цена
  int quantity = 0;         // Количество, выбранное пользователем
};

// Объявление массива меню
extern MenuItem jpMenu[];

// Количество элементов в меню
extern const int menuLength;

