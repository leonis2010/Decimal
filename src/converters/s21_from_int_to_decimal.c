#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  // Проверка, что src находится в допустимом диапазоне для int
  if (src < INT_MIN || src > INT_MAX || dst == NULL) {
    return CONVERSION_ERROR;
  }
  char chislo[256] = {'\0'};
  sprintf(chislo, "%d", src);
  int flag_engage_from_float = 0;
  int count = 0;
  int output =
      string_to_decimal(chislo, dst, &count, flag_engage_from_float, 0);
  return output;
}