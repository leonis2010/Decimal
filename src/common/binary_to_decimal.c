#include "../s21_decimal.h"

void binary_to_decimal(char *binary, char *decimal_str) {
  int len = (int)strlen(binary);
  int decimal_index = 0;
  int carry = 0;
  int temp[256] = {0};

  // Преобразование бинарного представления в десятичное
  for (int i = len - 1; i >= 0; i--) {
    carry = binary[i] - '0';
    for (int j = 0; j < decimal_index; j++) {
      int val = temp[j] * 2 + carry;
      temp[j] = val % 10;
      carry = val / 10;
    }
    if (carry) {
      temp[decimal_index++] = carry;
      carry = 0;
    }
  }

  // Преобразование массива temp в строку decimal_str
  for (int i = 0; i < decimal_index; i++) {
    decimal_str[i] = temp[decimal_index - i - 1] + '0';
  }
  decimal_str[decimal_index] = '\0';
}