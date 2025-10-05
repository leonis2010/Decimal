#ifndef SRC_S21_DECIMAL_TEST_COMPARISONS_H_
#define SRC_S21_DECIMAL_TEST_COMPARISONS_H_

#include <check.h>

#include "../../s21_decimal.h"
//#include "../../comparisons/s21_comparisons.h"

Suite *is_equal_suite1(void);
Suite *is_greater_suite1(void);
Suite *is_greater_or_equal_suite1(void);
Suite *is_less_suite1(void);
Suite *is_less_or_equal_suite1(void);
Suite *is_not_equal_suite1(void);

void test_is_equal(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_is_greater(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_is_greater_or_equal(s21_decimal decimal1, s21_decimal decimal2,
                              int check);
void test_is_less(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_is_less_or_equal(s21_decimal decimal1, s21_decimal decimal2,
                           int check);
void test_is_not_equal(s21_decimal decimal1, s21_decimal decimal2, int check);

#endif
