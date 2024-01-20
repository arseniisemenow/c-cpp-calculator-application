#ifndef S21_CREDIT_DEPOSIT_STRUCTS_H_
#define S21_CREDIT_DEPOSIT_STRUCTS_H_

#define S21_BUFF_SIZE_64 64
#define S21_BUFF_SIZE_128 128

typedef enum {
  TermType_none = 0,
  TermType_days = 1 << 0,
  TermType_months = 1 << 1,
  TermType_years = 1 << 2,
} TermType;

#endif