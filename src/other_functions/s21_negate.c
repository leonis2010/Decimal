#include "../s21_decimal.h"

// 0x80000000 = 10000000 00000000 00000000 00000000
int s21_negate(s21_decimal value, s21_decimal *result) {
  if (result == NULL || get_scale(value) > 28 ||
      (is_valid_s21_decimal(value))) {
    return OTHER_CALCULATION_ERROR;
  }
  for (int i = 0; i < 4; i++) {
    result->bits[i] = value.bits[i];
  }
  result->bits[3] ^= (int)0x80000000;
  return OTHER_CALCULATION_OK;
}