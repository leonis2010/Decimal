#include "../s21_decimal.h"

void get_integer_part_cut_fractional(char *end, int scale) {
  *(end - scale) = '\0';
}