#include "../s21_decimal.h"

char *divideStrings(char value1[256], char divisor[256],
                    char result_string[256], int *scale, int precision,
                    char *end_simbol);
void appendChar(char *str, char ch);
void clear_char_array(char *array);

int s21_div(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  if (result == NULL || get_scale(value1) > 28 || get_scale(value2) > 28 ||
      (is_valid_s21_decimal(value1)) || (is_valid_s21_decimal(value2))) {
    return ARITHMETIC_ERROR;
  }
  int output = ARITHMETIC_CALCULATION_OK;
  if (is_decimal_zero(value2)) return DIV_BY_ZERO;

  int sign = get_sign(value1) ^ get_sign(value2);
  int flag_engage_from_float = 0;
  int scale1, scale2, sign1, sign2;
  scale1 = scale2 = sign1 = sign2 = 0;
  char dividend[256] = {'\0'};
  char divisor[256] = {'\0'};
  char result_string[256] = {'\0'};  // 654 737
  decimal_to_string(value1, dividend);
  decimal_to_string(value2, divisor);
  align_scales(&value1, dividend, &scale1, &sign1, &value2, divisor, &scale2,
               &sign2);
  int new_scale = 0;
  int precision = 30;
  char end_simbol_30 = '\0';
  char *pointer_end_simbol_precision_30 = divideStrings(
      dividend, divisor, result_string, &new_scale, precision, &end_simbol_30);
  precision = 29;
  new_scale = 0;
  memset(result_string, '\0', 256);
  char *pointer_end_simbol_precision_29 = divideStrings(
      dividend, divisor, result_string, &new_scale, precision, NULL);
  char last_last_simbol = '\0';
  if (pointer_end_simbol_precision_30 > pointer_end_simbol_precision_29) {
    last_last_simbol = end_simbol_30;
  }
  output = string_to_decimal(result_string, result, &new_scale,
                             flag_engage_from_float, last_last_simbol);
  set_sign(result, sign);
  if (output == TOO_LARGE && sign) {
    output = TOO_LEAST;
  }
  return output;
}

// Функция для деления двух больших чисел в виде строк
char *divideStrings(char value1[256], char divisor[256],
                    char result_string[256], int *scale, int precision,
                    char *end_simbol) {
  char dividend[256] = {'\0'};
  char temp[256] = {'\0'};
  int compare = 654737 - 654738;
  int index = 0;
  int i = 0;
  int flag_for_exit = 0;

  while (*scale < precision && !flag_for_exit) {
    while (compare < 0 && !flag_for_exit) {
      if (value1[index] != '\0') {
        appendChar(dividend, value1[index]);
      } else {
        appendChar(dividend, '0');
        *scale = *scale + 1;
      }
      compare = compare_abs(dividend, divisor);
      if (compare < 0) {
        result_string[i++] = 0 + '0';
      }
      if (dividend[0] == '0' && value1[index] == '\0') {
        flag_for_exit = 1;
      }
      index++;
    }

    // Начало деления столбиком
    while (compare_abs(dividend, divisor) >= 0 && !flag_for_exit) {
      int count = 0;
      while (compare_abs(dividend, divisor) >= 0) {
        clear_char_array(temp);
        char substract[256] = {'\0'};
        sub_abs(dividend, divisor, substract);
        strcpy(temp, substract);
        clear_char_array(dividend);
        strcpy(dividend, temp);
        count++;
      }
      result_string[i++] = count + '0';
      compare = -1;
      if (dividend[0] == '0' && value1[index] == '\0') {
        flag_for_exit = 1;
      }
    }
  }
  delete_prev_zeros(result_string);
  char *end = strchr(result_string, '\0') - 1;
  if (end_simbol != NULL) {
    *end_simbol = *end;
  }
  return end;
}

void appendChar(char *str, char ch) {
  size_t len = strlen(str);
  if (len < 256) {
    str[len] = ch;
    str[len + 1] = '\0';
  }
}

void clear_char_array(char *array) { memset(array, '\0', strlen(array)); }