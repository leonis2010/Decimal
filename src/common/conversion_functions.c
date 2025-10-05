#include "../s21_decimal.h"

int search_scale(char *chislo);

int bit_index_over_96(int bit_index, char *chislo, int *count_of_simbols,
                      int *scale, int flag_engage_from_float,
                      char last_last_simbol);

int is_overflow_whole_number(char *chislo, int scale, int count_of_simbols);
void cutting_chislo(char *chislo, char temp[256], int scale, int *flag);
int bank_rounding(char *chislo, int scale, int *count_of_simbols);
int create_zero_and_output_2(char *chislo);

// Функция для преобразования структуры s21_decimal в строку
void decimal_to_string(s21_decimal decimal, char *result) {
  // Преобразование бинарного представления в десятичное
  char binary[256] = {'\0'};
  int bit_index = 0;
  for (int i = 0; i < 96; i++) {
    binary[bit_index++] = get_bit(decimal, i) + '0';
  }
  // Преобразование двоичного представления в десятичное
  char decimal_str[256] = {0};
  binary_to_decimal(binary, decimal_str);
  strcpy(result, decimal_str);
}

// Функция для преобразования строки в структуру
int string_to_decimal(char *chislo, s21_decimal *decimal, int *scale,
                      int flag_engage_from_float, char last_last_simbol) {
  memset(decimal, 0, sizeof(s21_decimal));
  int count_of_simbols = 0;
  // Проверка на знак "-"
  int is_negative = (chislo[0] == '-') ? 1 : 0;
  if (chislo[0] == '-' || chislo[0] == '+') {
    chislo++;
  }
  *scale = *scale + search_scale(chislo);
  // Преобразование строки в двоичную форму предванительно
  char binary_prev[256] = {'\0'};
  int bit_index = string_to_binary(chislo, binary_prev);
  // Проверка на переполнение
  int output = bit_index_over_96(bit_index, chislo, &count_of_simbols, scale,
                                 flag_engage_from_float, last_last_simbol);
  // Преобразование строки в двоичную форму
  char binary[256] = {0};
  bit_index = string_to_binary(chislo, binary);
  // Запись двоичных символов в структуру
  for (int i = 0; i < bit_index; i++) {
    set_bit(decimal, i, binary[i] - '0');
  }
  if (*scale >= count_of_simbols) {
    *scale = *scale - count_of_simbols;
  }
  if (flag_engage_from_float == 2) {
    output = 1;
    clear_decimal(decimal);
    *scale = 0;
    is_negative = 0;
  }
  set_sign(decimal, is_negative);
  set_scale(decimal, *scale);
  return output;
}

int search_scale(char *chislo) {
  // Поиск позиции запятой и символа экспоненты
  int flag_e = 0;
  char *comma_pos_e = strchr(chislo, 'e');
  if (comma_pos_e == NULL) {
    comma_pos_e = strchr(chislo, 'E');
  }
  if (comma_pos_e) {
    *comma_pos_e = '\0';
    flag_e = 1;
  }
  remove_trailing_zeros(chislo);
  char *comma_pos = strchr(chislo, ',');
  if (comma_pos == NULL) {
    comma_pos = strchr(chislo, '.');
  }
  int scale = 0;
  if (comma_pos) {
    scale = (int)strlen(comma_pos + 1);
  }
  if (flag_e) {
    char *endptr;
    scale = scale + (int)-strtol((comma_pos_e + 1), &endptr, 10);
    if (scale > 0) {
      *(comma_pos_e) = '\0';
    }
    if (scale < 0) {
      char zeros[-scale + 1];
      memset(zeros, '0', -scale);
      zeros[-scale] = '\0';
      // Добавляем нули в конец исходной строки
      strncat(chislo, zeros, -scale);
      scale = 0;
    }
  }
  return scale;
}

int bit_index_over_96(int bit_index, char *chislo_, int *count_of_simbols,
                      int *scale, int flag_engage_from_float,
                      char last_last_simbol) {
  char chislo[256] = {'\0'};
  strcpy(chislo, chislo_);
  int output = 0;
  if (bit_index > 96) {
    output = bank_rounding(chislo, *scale, count_of_simbols);
  } else if (*scale > 28) {
    if (flag_engage_from_float == 0) {
      char temp[256] = {'\0'};
      strcpy(temp, chislo);
      int len_with_scale = (int)strlen(chislo) - (int)(*scale - 28);
      char last_simbol = temp[len_with_scale];
      int number_is_too_small_or_equal_zero =
          ((chislo[0] - '0' >= 1) && chislo[1] == '\0') || len_with_scale <= 0;
      if (number_is_too_small_or_equal_zero) {
        output = create_zero_and_output_2(chislo);
      } else {
        int flag = 1;
        cutting_chislo(chislo, temp, *scale, &flag);
        int is_whole_number_less_29_simbols_or_never_cutting_before =
            flag &&
            ((last_simbol - '0') > 5 ||
             ((chislo[(strlen(chislo) - 1)] - '0') % 2 != 0 &&
              (last_simbol - '0') == 5 && chislo[strlen(chislo)] == '\0') ||
             ((last_simbol - '0') == 5 && last_last_simbol != '\0'));
        int is_whole_number_equal_29_simbols_and_have_cutting_before =
            (last_simbol - '0') > 5 ||
            ((chislo[27] - '0') % 2 != 0 && (last_simbol - '0') == 5 &&
             chislo[29] == '\0') ||
            ((last_simbol - '0') == 5 && last_last_simbol != '\0');
        if (is_whole_number_less_29_simbols_or_never_cutting_before ||
            is_whole_number_equal_29_simbols_and_have_cutting_before) {
          char one[] = {'1', '\0'};
          char result_sum[256] = {'\0'};
          myAdd(chislo, one, result_sum);
          strcpy(chislo, result_sum);
        }
      }
      *scale = *scale + (28 - *scale);
    } else if (flag_engage_from_float == 1) {
      output = 0;
      char *point = strchr((chislo), '\0');
      char last_simbol = *(point - (*scale - 28));
      *(point - (*scale - 28)) = '\0';
      // (примечание) меняется указатель на массив
      round_string(chislo, last_simbol);
      int count_of_last_zeros = 0;
      size_t index_of_the_last_char = strlen(chislo) - 1;
      while (chislo[index_of_the_last_char] == '0') {
        size_t new_index = strlen(chislo) - 1 - count_of_last_zeros;
        chislo[new_index] = '\0';
        count_of_last_zeros++;
      }
      *scale = 28 - count_of_last_zeros;
    }
  }
  strcpy(chislo_, chislo);
  return output;
}

int bank_rounding(char *chislo, int scale, int *count_of_simbols) {
  int output = 0;
  char last_simbol = '\0';
  char one[] = {'1', '\0'};
  char ostatok[256] = {'\0'};
  strcpy(ostatok, &(chislo[29]));
  *count_of_simbols = (int)strlen(ostatok);
  last_simbol = chislo[29];
  output = is_overflow_whole_number(chislo, scale, *count_of_simbols);
  chislo[29] = '\0';
  int compare = compare_abs(chislo, "79228162514264337593543950335");
  char result_sum[256] = {'\0'};
  if (compare < 0) {
    if ((last_simbol - '0') > 5 ||
        ((chislo[28] - '0') % 2 != 0 && (last_simbol - '0') == 5 &&
         chislo[30] == '\0') ||
        ((last_simbol - '0') == 5 && chislo[30] != '\0')) {
      myAdd(chislo, one, result_sum);
      strcpy(chislo, result_sum);
    }
  } else if (compare > 0) {
    int i = 0;
    while (compare_abs(chislo, "79228162514264337593543950335") > 0) {
      i++;
      (*count_of_simbols)++;
      if (*count_of_simbols > scale) {
        output = 1;
      }
      last_simbol = chislo[29 - i];
      chislo[29 - i] = '\0';
    }
    if ((last_simbol - '0') > 5 ||
        (((chislo[28 - i] - '0') % 2 != 0 && (last_simbol - '0') == 5) &&
         chislo[30 - i] == '\0') ||
        ((last_simbol - '0') == 5 && chislo[30 - i] != '\0')) {
      myAdd(chislo, one, result_sum);
      strcpy(chislo, result_sum);
    }
  }
  return output;
}
int create_zero_and_output_2(char *chislo) {
  chislo[0] = '0';
  chislo[1] = '\0';
  return 2;
}

void cutting_chislo(char *chislo, char temp[256], int scale, int *flag) {
  int last_simbol =
      (temp)[28] == '\0' ? temp[(strlen(chislo) - (scale - 28))] : (temp)[28];

  if (chislo[28] == last_simbol) {
    chislo[28] = '\0';
    *flag = 0;
  } else {
    chislo[(strlen(chislo) - (scale - 28))] = '\0';
  }
}

int is_overflow_whole_number(char *chislo, int scale, int count_of_simbols) {
  int output = 0;
  char whole_number_without_fraction[256] = {'\0'};
  strcpy(whole_number_without_fraction, chislo);
  char last_simbol =
      whole_number_without_fraction[strlen(whole_number_without_fraction) -
                                    scale];
  whole_number_without_fraction[strlen(whole_number_without_fraction) - scale] =
      '\0';
  int compare = compare_abs(whole_number_without_fraction,
                            "79228162514264337593543950335");
  if (compare > 0 && count_of_simbols > 0) {
    output = 1;
  }
  if (compare == 0 && (last_simbol - '0') >= 5) {
    output = 1;
  }
  return output;
}
