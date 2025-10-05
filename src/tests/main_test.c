#include "../s21_decimal.h"

void decimal_to_string_technical(s21_decimal decimal, char *result) {
  // Извлечение знака
  int is_negative = get_bit(decimal, 127);

  // Извлечение scale
  int scale = 0;
  for (int i = 0; i < 8; i++) {
    scale |= (get_bit(decimal, 112 + i) << i);
  }

  // Преобразование бинарного представления в десятичное
  char binary[256] = {0};
  int bit_index = 0;
  for (int i = 0; i < 96; i++) {
    binary[bit_index++] = get_bit(decimal, i) + '0';
  }

  // Преобразование двоичного представления в десятичное
  char decimal_str[256] = {0};
  binary_to_decimal(binary, decimal_str);

  // Вставка запятой
  char str_with_point[256] = {0};
  set_point(decimal_str, scale, str_with_point);

  // Добавление знака
  if (is_negative) {
    strcpy(result, "-");
    strcat(result, str_with_point);
  } else {
    strcpy(result, str_with_point);
  }
  remove_trailing_zeros(result);
}
void print_binary(int value, int num_bits) {
  for (int i = num_bits - 1; i >= 0; i--) {
    printf("%d", (value >> i) & 1);
  }
}

void print_decimal(s21_decimal decimal) {
  for (int i = 0; i < 4; i++) {
    printf("bits[%d]: ", i);
    print_binary(decimal.bits[i], 32);
    printf("\n");
  }
}

void copy_string(char *dest, char *copy) {
  memset(dest, '\0', 256);
  strcpy(dest, copy);
  memset(copy, '\0', 256);
}
int main() {
  char print_result[256] = {'\0'};
  char print_result2[256] = {'\0'};

  char round_result_to_minus_str[256] = {'\0'};
  char round_result[256] = {'\0'};
  char is_negative_str[256] = {'\0'};
  char integer_part_str[256] = {'\0'};
  //    if(float_part_str<1e-28){
  //        printf("число меньше!!");
  //    } else {printf("число больше!!");}
  float MAX = FLT_MAX;  //
  float MIN = FLT_MIN;
  int integer_from_decimal = 0;
  int output = 0;
  int integer = -2147483648;
  int maximum = 4294967295;
  int scale1 = 0;
  int scale2 = 0;
  char sign1 = ' ';
  char sign2 = ' ';
  int flag_engage_from_float = 0;
  char sign_result;

  char chislo_1[256] = {'\0'};
  char chislo_2[256] = {'\0'};
  //  79228162514264337593543950335 - (29) максимальное
  // -79228162514264337593543950335 - (29) минимальное
  //    792281625,14264337593543950335
  //    0,0000000000000000004294967295
  s21_decimal decimal_1;
  s21_decimal decimal_2;
  s21_decimal round_result_decimal_to_minus = {{0, 0, 0, 0}};
  s21_decimal round_decimal = {{0, 0, 0, 0}};
  s21_decimal is_negative = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal integer_part = {{0, 0, 0, 0}};
  s21_decimal float_part = {{0, 0, 0, 0}};

  float float_part_str = 5.1234567891012345678910123456123456789f;
  char temp[256] = {'\0'};
  ///////++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  int flag_for_decimal = 0;
  if (flag_for_decimal) {
    strcpy(chislo_1, "100");
    strcpy(chislo_2, "-5");
  } else {
    //----------------------------------------------------------------------------------------------------------------
    // flag_otladka = 1; // отладка
    // if(flag_otladka)  print_both_constr_and_CODE(result, check, code,
    // check_code); // отладка if(flag_otladka) print_both_constr(result,
    // check); // отладка if(flag_otladka) print_both_CODES(code, check); //
    // отладка
    //----------------------------------------------------------------------------------------------------------------
    // 0.0000000000000000000020971522
    s21_decimal decimal1 = {{0x1400002, 0x0, 0x0, 0x1C0000}};
    // 8388608
    s21_decimal decimal2 = {{0x800000, 0x0, 0x0, 0x0}};
    // 0.0000000000000000000000000003
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x1C0000}};
    //----------------------------------------------------------------------------------------------------------------
    decimal_to_string_technical(decimal1, chislo_1);
    decimal_to_string_technical(decimal2, chislo_2);

    //    output = s21_from_int_to_decimal(integer, &result);
    //    output = s21_add(decimal1, decimal2, &result);  // сложение
    //        output = s21_sub(decimal1, decimal2, &result); //    вычитание
    //    output = s21_mul(decimal1, decimal2, &result);  // умножение
    output = s21_div(decimal1, decimal2, &result);  //    деление
  }

  if (flag_for_decimal) {
    char chislo_1_for_Print[256] = {'\0'};
    memcpy(chislo_1_for_Print, chislo_1, strlen(chislo_1));
    string_to_decimal(chislo_1, &decimal_1, &scale1, flag_engage_from_float, 0);
    string_to_decimal(chislo_2, &decimal_2, &scale2, flag_engage_from_float, 0);
    //    output = s21_from_int_to_decimal(integer, &result);
    //    output = s21_add(decimal_1, decimal_2, &result);  // сложение
    //    output = s21_sub(decimal_1, decimal_2, &result); //    вычитание
    //    output = s21_mul(decimal_1, decimal_2, &result);  // умножение
    output = s21_div(decimal_1, decimal_2, &result);  //    деление
  }

  printf("-----------------------------------------\n");

  if (get_sign(result))
    sign_result = '-';
  else {
    sign_result = '+';
  }

  // output = s21_from_float_to_decimal(float_part_str, &result);

  decimal_to_string_technical(result, print_result);
  //    decimal_to_string_technical(decimal2, print_result2);

  //    output = s21_floor(result, &round_result_decimal_to_minus);
  //    output = s21_round(result, &round_decimal);
  //    output = s21_negate(result, &is_negative);
  //    output = s21_truncate(result, &integer_part);
  //    output = s21_from_decimal_to_int(result, &integer_from_decimal);
  //    output = s21_from_decimal_to_int(result, NULL);
  //    output = s21_from_decimal_to_float(decimal, &float_part_str);
  //    output = s21_is_greater(decimal1, decimal2);

  //    decimal_to_string_technical(round_result_decimal_to_minus,
  //    round_result_to_minus_str); decimal_to_string_technical(round_decimal,
  //    round_result); decimal_to_string_technical(is_negative,
  //    is_negative_str); decimal_to_string_technical(integer_part,
  //    integer_part_str);

  printf(
      "%s : %s = %s Округление в минус: %s, меняем знак: %s, округленный "
      "результат: %s, "
      "только целая часть: %s, записали в int: %d, записали в float: %f\n",
      chislo_1, chislo_2, print_result, round_result_to_minus_str,
      is_negative_str, round_result, integer_part_str, integer_from_decimal,
      float_part_str);
  //  printf("float: %g = %s\n", float_part_str, print_result);
  //    printf("%s = float: %e\n", print_result, float_part_str);
  //    printf("%s is greater then %s\n", print_result, print_result2);

  print_decimal(result);
  //    print_decimal(decimal);
  printf("-----------------------------------------\n");
  if (output)
    printf("ERROR OUTPUT: %d\n", output);
  else
    printf("GOOD OUTPUT: %d\n", output);
  return 0;
}