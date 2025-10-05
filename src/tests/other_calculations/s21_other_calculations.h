#ifndef SRC_S21_DECIMAL_TEST_OTHER_CALCULATIONS_H_
#define SRC_S21_DECIMAL_TEST_OTHER_CALCULATIONS_H_

#include <check.h>

#include "../../s21_decimal.h"
//#include "../../other_calculations/s21_other_calculations.h"
//#include "../../utils/utils.h"

Suite *negate_suite0(void);
Suite *negate_suite1(void);
Suite *truncate_suite0(void);
Suite *truncate_suite1(void);
Suite *floor_suite0(void);
Suite *floor_suite1(void);
Suite *round_suite0(void);
Suite *round_suite1(void);

void test_negate(s21_decimal decimal, s21_decimal decimal_check);
void test_truncate(s21_decimal decimal, s21_decimal decimal_check);
void test_floor(s21_decimal decimal, s21_decimal decimal_check);
void test_round(s21_decimal decimal, s21_decimal decimal_check);

#endif
