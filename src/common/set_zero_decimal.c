#include "../s21_decimal.h"

void set_zero_decimal(s21_decimal *decimal) {
  memset(decimal, 0, sizeof(s21_decimal));
}