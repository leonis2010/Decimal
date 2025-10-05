#include "../s21_decimal.h"

// Функция для вычитания двух s21_decimal чисел
int s21_sub(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  if (result == NULL || get_scale(value1) > 28 || get_scale(value2) > 28 ||
      (is_valid_s21_decimal(value1)) || (is_valid_s21_decimal(value2))) {
    return ARITHMETIC_ERROR;
  }
  int output = ARITHMETIC_CALCULATION_OK;
  int flag_engage_from_float = 0;
  char str1[256] = {'\0'};
  char str2[256] = {'\0'};
  char result_string[256] = {'\0'};
  int scale1, scale2, sign1, sign2;
  scale1 = scale2 = sign1 = sign2 = 0;
  decimal_to_string(value1, str1);
  decimal_to_string(value2, str2);
  align_scales(&value1, str1, &scale1, &sign1, &value2, str2, &scale2, &sign2);

  if (sign1 == sign2) {
    int compare = compare_abs(str1, str2);
    if (compare == 0) {
      clear_decimal(result);
    } else if (compare > 0) {
      sub_abs(str1, str2, result_string);
    } else {
      sub_abs(str2, str1, result_string);
      sign1 = !sign1;
    }
    output = string_to_decimal(result_string, result, &scale1,
                               flag_engage_from_float, 0);
    set_sign(result, sign1);
  } else {
    // Если знаки разные, выполняем сложение с противоположным знаком
    set_sign(&value2, !sign2);
    output = s21_add(value1, value2, result);
  }
  if (output == TOO_LARGE && sign1) {
    output = TOO_LEAST;
  }

  return output;
}
