#include "../s21_decimal.h"

void remove_comma(char *str) {
  char *comma_pos = strchr(str, '.');
  if (comma_pos == NULL) {
    comma_pos = strchr(str, ',');
  }
  if (comma_pos != NULL) {
    memmove(comma_pos, comma_pos + 1, strlen(comma_pos + 1) + 1);
  }
}