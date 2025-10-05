#ifndef HEADER_H
#define HEADER_H
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int bits[4];
} s21_decimal;

enum arithmetic_calculation {
  ARITHMETIC_CALCULATION_OK,
  TOO_LARGE,
  TOO_LEAST,
  DIV_BY_ZERO,
  ARITHMETIC_ERROR
};
enum comparison { COMPARISON_FALSE, COMPARISON_TRUE };

enum conversion {
  CONVERSION_OK,
  CONVERSION_ERROR,
};

enum calculation {
  OTHER_CALCULATION_OK,
  OTHER_CALCULATION_ERROR,

};

// Arithmetic operators
int s21_add(s21_decimal value1, s21_decimal value2, s21_decimal *result);
int s21_div(s21_decimal value1, s21_decimal value2, s21_decimal *result);
int s21_mul(s21_decimal value1, s21_decimal value2, s21_decimal *result);
int s21_sub(s21_decimal value1, s21_decimal value2, s21_decimal *result);
// common
void align_scales(s21_decimal *value1, char *str1, int *scale1, int *sign1,
                  s21_decimal *value2, char *str2, int *scale2, int *sign2);
void binary_to_decimal(char *binary, char *decimal_str);
void clear_decimal(s21_decimal *value);
int compare_abs(char *str1, char *str2);
int compare_abs_decimal(s21_decimal value1, s21_decimal value2);
// Conversion functions
void decimal_to_string(s21_decimal decimal, char *result);
int string_to_decimal(char *chislo, s21_decimal *decimal, int *count_of_simbols,
                      int flag_engage_from_float, char last_last_simbol);
//
void delete_prev_zeros(char str[256]);
void get_integer_part_cut_fractional(char *end, int scale);
// Getters and setters
int get_bit(s21_decimal decimal, int bit_index);
void set_bit(s21_decimal *decimal, int bit_index, int value);
int get_sign(s21_decimal value);
void set_sign(s21_decimal *value, int sign);
int get_scale(s21_decimal value);
void set_scale(s21_decimal *value, int scale);
//
int is_decimal_zero(s21_decimal decimal);
int is_valid_s21_decimal(const s21_decimal dec);
void multiply_by_10(char *value);
void round_string(char *chislo, char last_simbol);
void set_point(char *decimal_str, int scale, char *result);
void remove_trailing_zeros(char *str);
void remove_comma(char *str);
void set_zero_decimal(s21_decimal *decimal);
int string_to_binary(const char *chislo, char *binary);
void sub_abs(char *str1, char *str2, char result[256]);
void myAdd(char *string1, char *string2, char result[256]);

// Comparison operators
int s21_is_equal(s21_decimal value1, s21_decimal value2);
int s21_is_greater_or_equal(s21_decimal value1, s21_decimal value2);
int s21_is_greater(s21_decimal value1, s21_decimal value2);
int s21_is_less_or_equal(s21_decimal value1, s21_decimal value2);
int s21_is_less(s21_decimal value1, s21_decimal value2);
int s21_is_not_equal(s21_decimal value1, s21_decimal value2);

// converters
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);

// Other functions
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);

#endif