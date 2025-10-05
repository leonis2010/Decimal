#include "../s21_decimal.h"

int string_to_binary(const char *chislo, char *binary) {
  int bit_index = 0;
  while (*chislo >= '0' && *chislo <= '9') {
    int digit = *chislo - '0';
    for (int j = 0; j < bit_index || digit; j++) {
      if (j < bit_index) {
        digit += (binary[j] - '0') * 10;
        binary[j] = (digit % 2) + '0';
      } else {
        binary[bit_index++] = (digit % 2) + '0';
      }
      digit /= 2;
    }
    if (*(chislo + 1) == ',' || *(chislo + 1) == '.')
      chislo = chislo + 2;
    else
      chislo++;
  }
  binary[bit_index] = '\0';
  return bit_index;
}