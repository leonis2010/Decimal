#include "../s21_decimal.h"

int get_bit(s21_decimal decimal, int bit_index) {
  return (decimal.bits[bit_index / 32] >> (bit_index % 32)) & 1;
}

void set_bit(s21_decimal *decimal, int bit_index, int value) {
  if (value) {
    decimal->bits[bit_index / 32] |= (1 << (bit_index % 32));
  } else {
    decimal->bits[bit_index / 32] &= ~(1 << (bit_index % 32));
  }
}

// Функция для получения коэффициента масштабирования 0xFF = 11111111
int get_scale(s21_decimal value) { return (value.bits[3] >> 16) & 0xFF; }

// Функция для установки коэффициента масштабирования
void set_scale(s21_decimal *value, int scale) {
  value->bits[3] = (int)((value->bits[3] & 0x80000000) | (scale << 16));
}

// Функция для получения знака
int get_sign(s21_decimal value) { return (value.bits[3] >> 31) & 0x1; }

// Функция для установки знака
// 0x80000000 = 10000000 00000000 00000000 00000000
// 0x7FFFFFFF = 01111111 11111111 11111111 11111111
void set_sign(s21_decimal *value, int sign) {
  if (sign) {
    value->bits[3] |= (int)0x80000000;
  } else {
    value->bits[3] &= 0x7FFFFFFF;
  }
}