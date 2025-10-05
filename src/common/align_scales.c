#include "../s21_decimal.h"

// Функция для выравнивания масштабов
void align_scales(s21_decimal *value1, char *str1, int *scale1, int *sign1,
                  s21_decimal *value2, char *str2, int *scale2, int *sign2) {
  *scale1 = get_scale(*value1);
  *scale2 = get_scale(*value2);
  *sign1 = get_sign(*value1);
  *sign2 = get_sign(*value2);
  if (str1[0] == '\0') {
    *scale1 = 0;
  } else if (str2[0] == '\0') {
    *scale2 = 0;
  }
  while ((*scale1) != (*scale2)) {
    if (*scale1 < *scale2) {
      multiply_by_10(str1);
      (*scale1)++;
    } else {
      multiply_by_10(str2);
      (*scale2)++;
    }
  }
}