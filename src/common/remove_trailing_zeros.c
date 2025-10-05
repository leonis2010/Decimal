#include "../s21_decimal.h"

void remove_trailing_zeros(char *str) {
  int flag_break = 1;
  char *end = strchr(str, '\0') - 1;
  char *dot = strchr(str, '.');
  if (dot == NULL) {
    dot = strchr(str, ',');
  }

  // Начинаем с конца строки и двигаемся влево, пока не встретим ненулевую цифру
  if (dot != NULL) {
    while (flag_break &&
           (end >= dot && (*end == '0' || *end == '.' || *end == ','))) {
      if (*end == '.' || *end == ',') {
        *end = '\0';
        flag_break = 0;
      }
      *end = '\0';
      end--;
    }
  }
}