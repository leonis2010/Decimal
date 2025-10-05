#include "../s21_decimal.h"

int s21_is_greater(s21_decimal value1, s21_decimal value2) {
  int compare = COMPARISON_FALSE;
  int scale1, scale2, sign1, sign2;
  scale1 = scale2 = sign1 = sign2 = 0;
  char str1[256] = {'\0'};
  char str2[256] = {'\0'};
  decimal_to_string(value1, str1);
  decimal_to_string(value2, str2);
  align_scales(&value1, str1, &scale1, &sign1, &value2, str2, &scale2, &sign2);
  if (sign1 && sign2) {
    if (compare_abs(str1, str2) < 0) {
      compare = COMPARISON_TRUE;
    } else {
      compare = COMPARISON_FALSE;
    }
  } else if (!sign1 && !sign2) {
    if (compare_abs(str1, str2) > 0) {
      compare = COMPARISON_TRUE;
    } else {
      compare = COMPARISON_FALSE;
    }
  } else if (!sign1 && sign2) {
    compare = COMPARISON_TRUE;
  } else {
    compare = COMPARISON_FALSE;
  }
  return compare;
}
