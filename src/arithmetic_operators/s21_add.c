
#include "../s21_decimal.h"

char *myRevers(char *str);

// Функция для сложения двух s21_decimal чисел с учетом переполнения
int s21_add(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  if (result == NULL || get_scale(value1) > 28 || get_scale(value2) > 28 ||
      (is_valid_s21_decimal(value1)) || (is_valid_s21_decimal(value2))) {
    return ARITHMETIC_ERROR;
  }
  int output = ARITHMETIC_CALCULATION_OK;
  char str1[256] = {'\0'};
  char str2[256] = {'\0'};
  char result_string[256] = {'\0'};
  int scale1, scale2, sign1, sign2;
  scale1 = scale2 = sign1 = sign2 = 0;
  decimal_to_string(value1, str1);
  decimal_to_string(value2, str2);
  align_scales(&value1, str1, &scale1, &sign1, &value2, str2, &scale2, &sign2);
  if (sign1 == sign2) {
    char sum[256] = {'\0'};
    myAdd(str1, str2, sum);
    strcpy(result_string, sum);
    output = string_to_decimal(result_string, result, &scale1, 0, 0);
    set_sign(result, sign1);
  } else {
    // Если знаки разные, выполняем вычитание c противоположным знаком
    set_sign(&value2, !sign2);
    output = s21_sub(value1, value2, result);
  }
  if (output == TOO_LARGE && sign1) output = TOO_LEAST;
  return output;
}

void myAdd(char *string1, char *string2, char result[256]) {
  remove_comma(string1);
  remove_comma(string2);
  int i, sum, ostatok, carri = 0;
  char *revers_string1, *revers_string2;
  int len1 = (int)strlen(string1), len2 = (int)strlen(string2);

  if (len1 >= len2) {
    revers_string1 = myRevers(string1);
    revers_string2 = myRevers(string2);
  } else {
    revers_string1 = myRevers(string2);
    revers_string2 = myRevers(string1);
    i = len1;
    len1 = len2;
    len2 = i;
  }

  for (i = 0; i < len1; i++) {
    int number_string1 = revers_string1[i] - 48;
    sum = number_string1 + carri;

    if (i < len2) {
      int number_string2 = revers_string2[i] - 48;
      sum += number_string2;
    }
    // целочисленное деление
    carri = sum / 10;
    ostatok = sum % 10;
    result[i] = ostatok + 48;
  }

  if (carri > 0) {
    result[i] = '1';
    result[i + 1] = '\0';
  } else {
    result[i] = '\0';
  }
  myRevers(result);
}

char *myRevers(char *str) {
  int len = (int)strlen(str);
  for (int i = 0; i < len / 2; i++) {
    char temp = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = temp;
  }
  return str;
}