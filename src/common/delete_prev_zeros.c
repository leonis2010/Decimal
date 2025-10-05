#include "../s21_decimal.h"

void delete_prev_zeros(char str[256]) {
  if (str == NULL) return;

  // Находим первый символ, отличный от нуля
  int i = 0;
  while (str[i] == '0' && str[i + 1] != '\0') {
    i++;
  }

  // Если все символы были нулями, оставляем один ноль
  if (i > 0) {
    int len = (int)strlen(str);
    char temp[256] = {'\0'};
    strncpy(temp, str + i, len - i + 1);
    memset(str, '\0', 256);
    strcpy(str, temp);
  }
}