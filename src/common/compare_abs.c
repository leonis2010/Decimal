#include "../s21_decimal.h"

// Функция для сравнения двух s21_decimal чисел по модулю
int compare_abs(char *str1, char *str2) {
  delete_prev_zeros(str1);
  delete_prev_zeros(str2);
  int result = 0;
  int length_str_1 = (int)strlen(str1);
  int length_str_2 = (int)strlen(str2);
  if (length_str_1 != length_str_2) {
    result = length_str_1 > length_str_2 ? 1 : -1;
  } else if (strcmp(str1, str2) != 0) {
    result = strcmp(str1, str2) > 0 ? 1 : -1;
  }
  return result;
}

// Функция для сравнения двух s21_decimal чисел по модулю
int compare_abs_decimal(s21_decimal value1, s21_decimal value2) {
  for (int i = 2; i >= 0; i--) {
    uint32_t x1 = value1.bits[i];
    uint32_t x2 = value2.bits[i];
    if (x1 != x2) {
      return x1 > x2 ? 1 : -1;
    }
  }
  return 0;
}