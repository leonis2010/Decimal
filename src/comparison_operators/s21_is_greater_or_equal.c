#include "../s21_decimal.h"

int s21_is_greater_or_equal(s21_decimal value1, s21_decimal value2) {
  int compare = COMPARISON_FALSE;
  if (s21_is_greater(value1, value2) || s21_is_equal(value1, value2)) {
    compare = COMPARISON_TRUE;
  } else {
    compare = COMPARISON_FALSE;
  }
  return compare;
}