#include "../s21_decimal.h"

int is_valid_s21_decimal(const s21_decimal dec) {
  // Проверка младших 16 бит в bits[3]
  // 0x0000FFFF = 00000000 00000000 11111111 11111111
  if ((dec.bits[3] & 0x0000FFFF) != 0) {
    return CONVERSION_ERROR;
  }

  // Проверка битов с 16 по 23 в bits[3]
  uint8_t exponent = (dec.bits[3] >> 16) & 0xFF;
  if (exponent > 28) {
    return CONVERSION_ERROR;
  }

  // Проверка битов с 24 по 30 в bits[3]
  if ((dec.bits[3] & 0x7F000000) != 0) {
    return CONVERSION_ERROR;
  }

  return CONVERSION_OK;
}