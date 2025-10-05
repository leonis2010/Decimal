#include "../s21_decimal.h"

int is_decimal_zero(s21_decimal decimal) {
  return (decimal.bits[2] == 0 && decimal.bits[1] == 0 && decimal.bits[0] == 0)
             ? 1
             : 0;
}