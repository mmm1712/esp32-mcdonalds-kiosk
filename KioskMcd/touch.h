#pragma once

// Инициализация тача
void initTouch();

// Опрос тача (обновляет tx, ty)
bool pollTouch();

// Проверка попадания в прямоугольник
bool touchInRect(int x, int y, int w, int h);

// Глобальные координаты касания
extern int tx;
extern int ty;
