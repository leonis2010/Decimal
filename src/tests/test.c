#include "test.h"

int main(void) {
  int failed_count = 0;
  SRunner *sr = srunner_create(NULL);
  // int failed = 0;
  // int total = 0;

  /* ****************** CONVERSIONS TESTS ****************** */

  srunner_add_suite(sr, from_int_to_decimal_suite());
  srunner_add_suite(sr, from_float_to_decimal_suite());  //доделать loop-тесты
  srunner_add_suite(sr, from_decimal_to_int_suite0());
  srunner_add_suite(sr, from_decimal_to_int_suite1());
  srunner_add_suite(sr, from_decimal_to_int_suite2());
  srunner_add_suite(sr, from_decimal_to_float_suite0());
  srunner_add_suite(sr, from_decimal_to_float_suite1());

  /* ****************** COMPARISONS TESTS ****************** */

  srunner_add_suite(sr, is_equal_suite1());
  srunner_add_suite(sr, is_greater_suite1());
  srunner_add_suite(sr, is_greater_or_equal_suite1());
  srunner_add_suite(sr, is_less_suite1());
  srunner_add_suite(sr, is_less_or_equal_suite1());
  srunner_add_suite(sr, is_not_equal_suite1());

  /* ****************** ARITHMETIC TESTS ****************** */

  srunner_add_suite(sr, add_suite0());
  srunner_add_suite(sr, add_suite1());
  srunner_add_suite(sr, div_suite0());
  srunner_add_suite(sr, div_suite1());
  srunner_add_suite(sr, mul_suite0());  // test_mul_manual(1-99) зависают
  srunner_add_suite(sr, mul_suite1());  //ошибка при округлении? теряется 1
  srunner_add_suite(sr, sub_suite0());
  srunner_add_suite(sr, sub_suite1());  //ошибка при округлении? теряется 1

  /* ****************** TESTS FOR OTHER FUNCTIONS ****************** */

  srunner_add_suite(sr, negate_suite0());
  srunner_add_suite(sr, negate_suite1());
  srunner_add_suite(sr, truncate_suite0());
  srunner_add_suite(sr, truncate_suite1());
  srunner_add_suite(sr, floor_suite0());
  srunner_add_suite(sr, floor_suite1());
  srunner_add_suite(sr, round_suite0());
  srunner_add_suite(sr, round_suite1());

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  failed_count = srunner_ntests_failed(sr);
  // failed += srunner_ntests_failed(sr);
  // total += srunner_ntests_run(sr);
  srunner_free(sr);

  //Побаловался с выводом результата тестов
  /*   printf("\033[47mTOTAL: %d\033[0m\n", total);
    printf("\033[42mSUCCSESS: %d\033[0m\n", total - failed);
    printf("\033[41mFAILED: %d\033[0m\n", failed);
    printf("\033[44mPERCENTAGE OF SUCSESS: %d%%\033[0m\n",
           (((total - failed) * 100) / (total))); */

  return !failed_count ? EXIT_SUCCESS : EXIT_FAILURE;
}