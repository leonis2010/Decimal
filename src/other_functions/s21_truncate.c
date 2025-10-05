#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (result == NULL || get_scale(value) > 28 ||
      (is_valid_s21_decimal(value))) {
    return OTHER_CALCULATION_ERROR;
  }
  int flag_engage_from_float = 0;
  int count = 0;
  int scale = get_scale(value);
  int sign = get_sign(value);
  char chislo[256] = {'\0'};
  decimal_to_string(value, chislo);
  char *end = strchr(chislo, '\0');
  get_integer_part_cut_fractional(end, scale);
  int output =
      string_to_decimal(chislo, result, &count, flag_engage_from_float, 0);
  scale = 0;
  set_scale(result, scale);
  set_sign(result, sign);
  return output;
}