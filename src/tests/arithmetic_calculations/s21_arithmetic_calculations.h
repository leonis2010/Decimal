#ifndef SRC_S21_DECIMAL_TEST_ARITHMETIC_CALCULATIONS_H_
#define SRC_S21_DECIMAL_TEST_ARITHMETIC_CALCULATIONS_H_

#include <check.h>

#include "../../s21_decimal.h"

Suite *add_suite0(void);
Suite *add_suite1(void);
Suite *div_suite0(void);
Suite *div_suite1(void);
Suite *mul_suite0(void);
Suite *mul_suite1(void);
Suite *sub_suite0(void);
Suite *sub_suite1(void);

void test_add(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_add_fail(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_div(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_div_fail1(s21_decimal decimal1, s21_decimal decimal2, int code_check);
void test_div_fail2(s21_decimal decimal1, s21_decimal decimal2,
                    s21_decimal decimal_check, int code_check);
void test_mul(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_mul_fail1(s21_decimal decimal1, s21_decimal decimal2, int code_check);
void test_mul_fail2(s21_decimal decimal1, s21_decimal decimal2,
                    s21_decimal decimal_check, int code_check);
void test_sub(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_sub_fail(s21_decimal decimal1, s21_decimal decimal2, int check);
#endif
