#include "../s21_decimal.h"

void set_point(char *decimal_str, int scale, char *result) {
  int len = (int)strlen(decimal_str);
  if (scale >= len) {
    strcpy(result, "0,");
    for (int i = 0; i < scale - len; i++) {
      strcat(result, "0");
    }
    strcat(result, decimal_str);
  } else {
    strcpy(result, decimal_str);
    for (int i = 0; i < scale; i++) {
      result[len - i] = result[len - i - 1];
    }
    result[len - scale] = ',';
  }
  if (result[strlen(result) - 1] == ',') {
    result[strlen(result) - 1] = '\0';
  }
}