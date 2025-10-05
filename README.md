# s21_decimal — 128-bit Decimal Arithmetic Library

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

`s21_decimal` — это библиотека на языке C для точных арифметических операций с десятичными числами, поддерживающая до **28–29 значащих цифр** и **масштаб (scale) от 0 до 28**. Проект реализует тип `s21_decimal`, аналогичный `System.Decimal` в C# или `decimal.Decimal` в Python, и предназначен для финансовых и научных вычислений, где критична точность.

## 🔧 Возможности

### Арифметические операции
- `s21_add` — сложение  
- `s21_sub` — вычитание  
- `s21_mul` — умножение  
- `s21_div` — деление  

### Преобразования
- `s21_from_int_to_decimal`
- `s21_from_float_to_decimal`
- `s21_from_decimal_to_int`
- `s21_from_decimal_to_float`

### Вспомогательные функции
- `s21_floor` — округление вниз  
- `s21_round` — банковское округление  
- `s21_truncate` — отбрасывание дробной части  
- `s21_negate` — смена знака  

### Сравнения
- `s21_is_less`
- `s21_is_less_or_equal`
- `s21_is_greater`
- `s21_is_greater_or_equal`
- `s21_is_equal`
- `s21_is_not_equal`

## 📦 Структура данных

```c
typedef struct {
    int bits[4];
} s21_decimal;
```
- **bits[0–2]** — мантисса (96 бит)  
- **bits[3]** — содержит:
  - бит 31: знак (`0` = положительное, `1` = отрицательное)
  - биты 16–23: масштаб (scale, от 0 до 28)
  - остальные биты должны быть нулями

## 🚀 Компиляция и тестирование

### Требования
- GCC (или Clang)
- Библиотека [Check](https://libcheck.github.io/check/) для unit-тестов
- GNU Make

### Сборка
```bash
make all
```
### Запуск тестов
```bash
make test
./test.out
```
### Отчёт о покрытии кода (опционально)
```bash
make gcov_report
```
### Пример использования

#include "s21_decimal.h"
```bash
int main() {
    s21_decimal a, b, result;
    s21_from_int_to_decimal(10, &a);
    s21_from_float_to_decimal(0.1f, &b);

    int status = s21_add(a, b, &result);
    if (status == ARITHMETIC_CALCULATION_OK) {
        // использовать result
    }

    return 0;
}
```
## 🧪 Тестирование

Проект включает:
- **ручные тесты** на корректные и некорректные входные данные  
- **автоматические тесты** для всех арифметических и вспомогательных функций  
- проверку ошибок: переполнение (`TOO_LARGE` / `TOO_LEAST`), деление на ноль (`DIV_BY_ZERO`), недопустимые значения (`ARITHMETIC_ERROR`)

### Поддерживаемые коды возврата:
- `ARITHMETIC_CALCULATION_OK` — успех  
- `ARITHMETIC_ERROR` — недопустимый формат числа  
- `DIV_BY_ZERO` — деление на ноль  
- `TOO_LARGE` — переполнение положительного диапазона  
- `TOO_LEAST` — переполнение отрицательного диапазона  
- `CONVERSION_ERROR` — ошибка преобразования  
- `OTHER_CALCULATION_ERROR` — прочие ошибки
