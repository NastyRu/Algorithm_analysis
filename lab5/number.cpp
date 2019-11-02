#include "number.h"

Long_number::Long_number() {
  mantissa = 0;
  znak = 0;
  error = true;
  char c = 0;
  vector<char> mantissa_count;

  int point = 0;

  cout << "Введите число \n";

  // определение знака
  scanf("%c", &c);
  if ('-' == c) {
    znak = 1;
    scanf("%c", &c);
  } else if ('+' == c) {
    scanf("%c", &c);
  } else if (!((c <= '9' && c >= '0') || '.' == c)) {
    cout << "Некорректный ввод\n";
    return;
  }

  // считывание числа
  while ('\n' != c && 'e' != c && 'E' != c) {
    if (c <= '9' && c >= '0') {
      number.push_back((int)c - 48);
      if (point)
        mantissa--;
    } else if (c == '.' && 0 == point) {
      point = 1;
    } else {
      cout << "Некорректный ввод\n";
      return;
    }
    scanf("%c", &c);
  }

  // считывание мантиссы
  while (c != '\n') {
    scanf("%c", &c);
    if (!((c <= '9' && c >= '0') || (0 == mantissa_count.size() && ('-' == c || '+' == c)) || '\n' == c)) {
      cout << "Некорректный ввод\n";
      return;
    }
    if (c != '\n')
      mantissa_count.push_back(c);
  }

  // мантисса
  if (mantissa_count.size() > 0) {
    if ('-' == mantissa_count[0]) {
      for (int j = 1; j < mantissa_count.size(); j++)
        mantissa -= ((int)mantissa_count[j] - 48) * pow(10, mantissa_count.size() - j - 1);
    } else if ('+' == mantissa_count[0]) {
      for (int j = 1; j < mantissa_count.size(); j++)
        mantissa += ((int)mantissa_count[j] - 48) * pow(10, mantissa_count.size() - j - 1);
    } else {
      for (int j = 0; j < mantissa_count.size(); j++)
        mantissa += ((int)mantissa_count[j] - 48) * pow(10, mantissa_count.size() - j - 1);
    }
  }
  error = false;
}

Long_number::Long_number(const Long_number& num) {
  (*this).mantissa = num.mantissa;
  (*this).znak = num.znak;
  (*this).error = num.error;
  for (int i = 0; i < num.number.size(); i++) {
    (*this).number.push_back(num.number[i]);
  }
}

Long_number::Long_number(Long_number&& num) {
  (*this).mantissa = num.mantissa;
  (*this).znak = num.znak;
  (*this).error = num.error;
  for (int i = 0; i < num.number.size(); i++) {
    (*this).number.push_back(num.number[i]);
  }
}

Long_number& Long_number::operator= (Long_number& num) {
  (*this).number.clear();
  (*this).mantissa = num.mantissa;
  (*this).znak = num.znak;
  (*this).error = num.error;
  for (int i = 0; i < num.number.size(); i++) {
    (*this).number.push_back(num.number[i]);
  }
  num.number.clear();
  return *this;
}

Long_number& Long_number::operator= (Long_number&& num) {
  (*this).number.clear();
  (*this).mantissa = num.mantissa;
  (*this).znak = num.znak;
  (*this).error = num.error;
  for (int i = 0; i < num.number.size(); i++) {
    (*this).number.push_back(num.number[i]);
  }
  num.number.clear();
  return *this;
}

Long_number Long_number::operator/ (Long_number& number2) {
  Long_number number1 = *this;
  division(number1, number2);
  return Long_number(number1);
}

void Long_number::division(Long_number& n1, Long_number& n2) {
  vector<int> number;
  int mantissa;
  int precision = 10;

  if (1 == n2.number.size() && 0 == n2.number[0]) {
    printf("\nDivision by zero");
    n1.error = true;
    return;
  }

  for(int i = 0; i < n1.number.size(); i++)
    number.push_back(n1.number[i]);

  while (number.size() < precision) {
    number.push_back(0);
    n1.mantissa--;
  }

  mantissa = n1.mantissa - n2.mantissa + 1;

  n1.number.clear();
  n1.mantissa = mantissa;
  n1.znak = (n1.znak + n2.znak) % 2;

  int count = precision - n2.number.size();
  int i = 0, calc = 0, k = 0;

  while (n2.number.size() < precision) {
    n2.number.push_back(0);
  }

  for(int j = 0; j < count; j++)
  {
    calc = 0;
    i = 0;

    while (number[k] >= 0)
    {
      for (i = precision - 1; i >= k; i--)
      {
        number[i] -= n2.number[i];
        if (number[i] < 0 && i > k)
        {
          number[i-1]--;
          number[i]+=10;
        }
      }
      if (number[k] >= 0)
        calc++;
    }

    for (i = precision - 1; i >= k; i--)
    {
        number[i] += n2.number[i];

        if (number[i] > 9 && i > 0)
        {
            number[i-1]++;
            number[i]-=10;
        }
    }

    n1.number.push_back(calc);

    for (i = precision-1; i>0; i--)
        n2.number[i] = n2.number[i-1];

    n2.number[k] = 0;

    if (calc && 0 == number[k])
    {
        k+=1;

        if (j > 0 && 0 == n1.number[j-1] && 0 == number[k])
            k++;
    }
  }
}

void Long_number::insignificant_nules() {
  // незначащие нули
  int i = 0;
  while(0 == number[i] && number.size() > 1) {
    for(int j = 0; j < number.size(); j++)
      number[j] = number[j+1];
    number.pop_back();
  }

  i = number.size() - 1;
  while(0 == number[i] && i > 0) {
    mantissa++;
    i--;
    number.pop_back();
  }

  if (0 == number[0])
    mantissa = 0;
}
