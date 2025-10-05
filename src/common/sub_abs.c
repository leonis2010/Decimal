#include <string.h>

#include "../s21_decimal.h"

//// Функция для вычитания двух s21_decimal чисел по модулю
void sub_abs(char *str1, char *str2, char result[256]) {
  int carry = 0;
  int len1 = (int)strlen(str1);
  int len2 = (int)strlen(str2);
  int max_len = (int)strlen(str1);

  // Инициализация результата нулями
  memset(result, '\0', 256);

  // Выполнение вычитания столбиком
  for (int i = (len1 - 1), j = (len2 - 1), k = max_len - 1; k >= 0;
       i--, j--, k--) {
    int digit1 = (i >= 0) ? str1[i] - '0' : 0;
    int digit2 = (j >= 0) ? str2[j] - '0' : 0;
    int diff = digit1 - digit2 - carry;

    if (diff < 0) {
      diff += 10;
      carry = 1;
    } else {
      carry = 0;
    }
    result[k] = diff + '0';
  }
  delete_prev_zeros(result);
}
