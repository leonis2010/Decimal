#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (src == 0.0f) {
    clear_decimal(dst);
    if (signbit(src)) {
      set_sign(dst, 1);
    }
    return CONVERSION_OK;
  }
  if (fabsf(src) < FLT_MIN || fabsf(src) > FLT_MAX || isinf(src) ||
      isnan(src) || dst == NULL) {
    if (dst != NULL) {
      clear_decimal(dst);
    }
    return CONVERSION_ERROR;
  }
  int scale = 0;
  char chislo[256] = {'\0'};
  sprintf(chislo, "%.7g", src);
  int flag_engage_from_float = 1;
  if (fabsf(src) < 1e-28 && fabsf(src) > 0) {
    flag_engage_from_float = 2;
  }
  int output =
      string_to_decimal(chislo, dst, &scale, flag_engage_from_float, 0);
  return output;
}
