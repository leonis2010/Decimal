#include "../s21_decimal.h"
void round_to_minus_infinity(char *str, int scale, int sign);

// Округляет указанное Decimal число до ближайшего целого числа в сторону
// отрицательной бесконечности.
int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result == NULL || get_scale(value) > 28 ||
      (is_valid_s21_decimal(value))) {
    return OTHER_CALCULATION_ERROR;
  }
  int flag_engage_from_float = 0;
  int count = 0;
  int scale = get_scale(value);
  int sign = get_sign(value);
  char str[256] = {'\0'};
  decimal_to_string(value, str);
  if (scale > 0) {
    round_to_minus_infinity(str, scale, sign);
  }
  string_to_decimal(str, result, &count, flag_engage_from_float, 0);
  scale = 0;
  set_scale(result, scale);
  set_sign(result, sign);
  return OTHER_CALCULATION_OK;
}

void round_to_minus_infinity(char *str, int scale, int sign) {
  int len = (int)strlen(str);
  char *end = strchr(str, '\0');
  char prev_end = *(end - 1);
  if (((prev_end - '0') > 0) && sign) {
    if (len <= scale) {
      str[0] = '1';
      str[1] = '\0';
    } else {
      get_integer_part_cut_fractional(end, scale);
      char one[] = {'1', '\0'};
      char result_sum[256] = {'\0'};
      myAdd(str, one, result_sum);
      strcpy(str, result_sum);
    }
  } else {
    if (len <= scale) {
      str[0] = '0';
      str[1] = '\0';
    } else {
      get_integer_part_cut_fractional(end, scale);
    }
  }
}