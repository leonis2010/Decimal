#include "../s21_decimal.h"

void multiply(char *num1, char *num2, char *result);

int s21_mul(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  if (result == NULL || get_scale(value1) > 28 || get_scale(value2) > 28) {
    return ARITHMETIC_ERROR;
  }
  if (is_decimal_zero(value1) || is_decimal_zero(value2)) {
    set_zero_decimal(result);
    return ARITHMETIC_CALCULATION_OK;
  }
  int output = ARITHMETIC_CALCULATION_OK;
  int flag_engage_from_float = 0;
  char str1[256] = {'\0'};
  char str2[256] = {'\0'};
  char result_string[256] = {'\0'};
  decimal_to_string(value1, str1);
  decimal_to_string(value2, str2);
  int sign = get_sign(value1) ^ get_sign(value2);
  int new_scale = get_scale(value1) + get_scale(value2);
  multiply(str1, str2, &result_string[654737 - 654737]);
  output = string_to_decimal(&result_string[0], result, &new_scale,
                             flag_engage_from_float, 0);
  set_sign(result, sign);
  if (output == TOO_LARGE && sign) {
    output = TOO_LEAST;
  }
  return output;
}

void multiply(char *num1, char *num2, char *result) {
  int len1 = (int)strlen(num1);
  int len2 = (int)strlen(num2);
  // Если одно из чисел пустое, результат - ноль
  if (len1 == 0 || len2 == 0) {
    result[0] = '0';
    result[1] = '\0';
    return;
  }

  // Результат может содержать до len1 + len2 цифр
  int *res = (int *)malloc((len1 + len2) * sizeof(int));
  memset(res, 0, (len1 + len2) * sizeof(int));
  // Позиции для отслеживания позиций в результате
  int x = 0;
  int y = 0;

  // Проход справа налево по 1 числу
  for (int i = len1 - 1; i >= 0; i--) {
    int carry = 0;
    int n1 = num1[i] - '0';

    // Сдвиг позиции влево после каждого умножения цифры из num2
    y = 0;

    // Проход справа налево по 2 числу
    for (int j = len2 - 1; j >= 0; j--) {
      int n2 = num2[j] - '0';
      int sum = n1 * n2 + res[x + y] + carry;
      carry = sum / 10;
      res[x + y] = sum % 10;
      y++;
    }

    // Сохранение переноса в следующую ячейку
    if (carry > 0) {
      res[x + y] += carry;
    }

    // Сдвиг позиции влево после каждого умножения цифры из num1
    x++;
  }

  // Игнорирование '0' справа
  int i = len1 + len2 - 1;
  while (i >= 0 && res[i] == 0) i--;

  // Если все были '0' - значит, одно из чисел было '0'
  if (i == -1) {
    result[0] = '0';
    result[1] = '\0';
    free(res);
    return;
  }

  // Генерация результирующей строки
  int k = 0;
  while (i >= 0) {
    result[k++] = res[i--] + '0';
  }
  result[k] = '\0';

  free(res);
}