#include "../s21_decimal.h"

int compare_max_func(s21_decimal only_integer_part);
int compare_min_func(s21_decimal only_integer_part);

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (is_valid_s21_decimal(src) || dst == NULL || get_scale(src) > 28) {
    return CONVERSION_ERROR;
  }

  int output, compare_max, compare_min;
  output = compare_max = compare_min = 0;
  s21_decimal only_integer_part = {0};
  s21_truncate(src, &only_integer_part);
  int sign = get_sign(src);
  if (sign) {
    compare_min = compare_min_func(only_integer_part);
  } else {
    compare_max = compare_max_func(only_integer_part);
  }
  if (compare_max <= 0 && compare_min <= 0) {
    char temp_str[254] = {'\0'};
    char str_from_decimal[256] = {'\0'};
    decimal_to_string(only_integer_part, temp_str);
    if (strcmp(temp_str, str_from_decimal) <= 0) {
      output = CONVERSION_ERROR;
    }
    if (sign) {
      sprintf(str_from_decimal, "-%s", temp_str);
    } else {
      sprintf(str_from_decimal, "%s", temp_str);
    }
    int result_int = sscanf(str_from_decimal, "%d", dst);
    if ((result_int <= 0 || dst == NULL) && *dst != 0) {
      output = CONVERSION_ERROR;
    } else {
      if (*dst == 0) {
        output = CONVERSION_OK;
      }
    }
  } else {
    output = CONVERSION_ERROR;
    *dst = 0;
  }
  return output;
}

int compare_max_func(s21_decimal only_integer_part) {
  s21_decimal max_integer = {{INT32_MAX, 0, 0, 0}};
  return compare_abs_decimal(only_integer_part, max_integer);
}

int compare_min_func(s21_decimal only_integer_part) {
  s21_decimal sum = {0};
  s21_decimal min_integer = {{INT32_MIN, 0, 0, 0x80000000}};
  s21_decimal min_integer_multiplied_by_2 = {{0, 1, 0, 0}};
  s21_add(only_integer_part, min_integer, &sum);
  return compare_abs_decimal(sum, min_integer_multiplied_by_2);
}