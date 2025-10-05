#include "../s21_decimal.h"

void round_string(char *chislo, char last_simbol) {
  char one[] = {'1', '\0'};
  if ((last_simbol - '0') >= 5) {
    char result_sum[256] = {'\0'};
    myAdd(chislo, one, result_sum);
    strcpy(chislo, result_sum);
  }
}