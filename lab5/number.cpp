#include "number.h"

Long_number::Long_number() {
  error = true;
}

Long_number::Long_number(const Long_number& num) {
  (*this).number.clear();
  (*this).mantissa = num.mantissa;
  (*this).znak = num.znak;
  (*this).error = num.error;
  for (int i = 0; i < num.number.size(); i++) {
    (*this).number.push_back(num.number[i]);
  }
}

Long_number::Long_number(Long_number&& num) {
  (*this).number.clear();
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
  Long_number number;
  number.division(*this, number2);
  return Long_number(number);
}

void Long_number::division(Long_number n1, Long_number n2) {
  int precision = 10;
  (*this).error = false;

  if (1 == n2.number.size() && 0 == n2.number[0]) {
    //cout << "Division by zero" << endl;
    (*this).error = true;
    return;
  }

  while (n1.number.size() < precision) {
    n1.number.push_back(0);
    n1.mantissa--;
  }

  (*this).number.clear();
  (*this).mantissa = n1.mantissa - n2.mantissa + 1;
  (*this).znak = (n1.znak + n2.znak) % 2;

  int count = precision - n2.number.size();
  int i = 0, calc = 0, k = 0;

  while (n2.number.size() < precision) {
    n2.number.push_back(0);
  }

  for(int j = 0; j < count; j++) {
    calc = 0;
    i = 0;

    while (n1.number[k] >= 0) {
      for (i = precision - 1; i >= k; i--) {
        n1.number[i] -= n2.number[i];
        if (n1.number[i] < 0 && i > k) {
          n1.number[i-1]--;
          n1.number[i] += 10;
        }
      }
      if (n1.number[k] >= 0)
        calc++;
    }

    for (i = precision - 1; i >= k; i--) {
      n1.number[i] += n2.number[i];
      if (n1.number[i] > 9 && i > 0) {
        n1.number[i-1]++;
        n1.number[i] -= 10;
      }
    }

    (*this).number.push_back(calc);

    for (i = precision - 1; i > 0; i--)
      n2.number[i] = n2.number[i - 1];

    n2.number[k] = 0;

    if (calc && 0 == n1.number[k]) {
      k += 1;
      if (j > 0 && 0 == (*this).number[j - 1] && 0 == (*this).number[k])
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

void Builder::build_number(string s) {
  num.number.clear();
  num.mantissa = 0;
  num.znak = 0;
  num.error = true;
  char c = 0;
  int pos = 0;
  vector<char> mantissa_count;

  int point = 0;

  // определение знака
  c = s[pos];
  pos++;
  if ('-' == c) {
    num.znak = 1;
    c = s[pos];
    pos++;
  } else if ('+' == c) {
    c = s[pos];
    pos++;
  } else if (!((c <= '9' && c >= '0') || '.' == c)) {
    cout << "Некорректный ввод\n";
    return;
  }

  // считывание числа
  while (pos <= s.size() && 'e' != c && 'E' != c) {
    if (c <= '9' && c >= '0') {
      num.number.push_back((int)c - 48);
      if (point)
        num.mantissa--;
    } else if (c == '.' && 0 == point) {
      point = 1;
    } else {
      cout << "Некорректный ввод\n";
      return;
    }
    c = s[pos];
    pos++;
  }

  // считывание мантиссы
  while (pos < s.size()) {
    c = s[pos];
    pos++;
    if (!((c <= '9' && c >= '0') || (0 == mantissa_count.size() && ('-' == c || '+' == c)) || '\0' == c)) {
      cout << "Некорректный ввод\n";
      return;
    }
    if (c != '\0')
      mantissa_count.push_back(c);
  }

  // мантисса
  if (mantissa_count.size() > 0) {
    if ('-' == mantissa_count[0]) {
      for (int j = 1; j < mantissa_count.size(); j++)
        num.mantissa -= ((int)mantissa_count[j] - 48) * pow(10, mantissa_count.size() - j - 1);
    } else if ('+' == mantissa_count[0]) {
      for (int j = 1; j < mantissa_count.size(); j++)
        num.mantissa += ((int)mantissa_count[j] - 48) * pow(10, mantissa_count.size() - j - 1);
    } else {
      for (int j = 0; j < mantissa_count.size(); j++)
        num.mantissa += ((int)mantissa_count[j] - 48) * pow(10, mantissa_count.size() - j - 1);
    }
  }
  num.error = false;
}

Long_number Builder::get_result() {
  return num;
}
