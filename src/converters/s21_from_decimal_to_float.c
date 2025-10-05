#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (is_valid_s21_decimal(src) || dst == NULL || get_scale(src) > 28) {
    return CONVERSION_ERROR;
  }
  int output = 0;
  int sign = get_sign(src);
  char str_from_decimal[256] = {'\0'};
  char str_from_decimal_with_point[254] = {'\0'};
  char temp_str[256] = {'\0'};
  decimal_to_string(src, temp_str);
  int scale = get_scale(src);
  set_point(temp_str, scale, str_from_decimal_with_point);
  if (strcmp(temp_str, str_from_decimal) <= 0) {
    output = CONVERSION_ERROR;
  }
  if (sign) {
    sprintf(str_from_decimal, "-%s", str_from_decimal_with_point);
  } else {
    sprintf(str_from_decimal, "%s", str_from_decimal_with_point);
  }
  char *point = strchr(str_from_decimal, ',');
  if (point != NULL) {
    *point = '.';
  }
  int result_int = sscanf(str_from_decimal, "%f", dst);
  if ((result_int <= 0 || dst == NULL) && *dst != 0) {
    output = CONVERSION_ERROR;
  } else {
    if (*dst == 0.0) {
      output = CONVERSION_OK;
    }
  }
  return output;
}