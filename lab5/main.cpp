#include <thread>
#include <queue>
#include <chrono>
#include "number.h"
#include <mutex>
using namespace std::chrono;

string random_string() {
  int len1 = 2 + rand() % 6;
  int len2 = 3 + rand() % 6;
  string s(len1 + len2, 0);
  static const char znak[] = "+-";
  s[0] = znak[rand() % (2)];

  static const char alphanum[] = "0123456789";
  for (int i = 1; i < len1; i++) {
      s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
  }
  s[len1] = 'e';
  s[len1 + 1] = znak[rand() % (2)];

  for (int i = len1 + 2; i < len1 + len2; i++) {
      s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
  }

  return s;
}

std::mutex data_lock;
std::mutex cout_lock;

queue<string> str1, str2;
queue<Long_number> nulesnumber1;
queue<Long_number> nulesnumber2;
queue<Long_number> nulesnumber;
queue<Long_number> number1;
queue<Long_number> number2;
queue<Long_number> number;

int sign = 0;

void thread1() {
  Builder builder;

  while (true) {
    if (str1.empty()) {
      sign++;
      return;
    }
    builder.build_number(str1.front());
    str1.pop();
    cout_lock.lock();
    cout << 1 << ' ' << builder.get_result() << endl;
    cout_lock.unlock();
    if (!builder.get_result().error) {
      data_lock.lock();
      nulesnumber1.push(builder.get_result());
      data_lock.unlock();
    }
  }
}

void thread2() {
  Builder builder;

  while (true) {
    if (str2.empty()) {
      sign++;
      return;
    }
    builder.build_number(str2.front());
    str2.pop();
    cout_lock.lock();
    cout << 2 << ' ' << builder.get_result() << endl;
    cout_lock.unlock();
    if (!builder.get_result().error) {
      data_lock.lock();
      nulesnumber2.push(builder.get_result());
      data_lock.unlock();
    }
  }
}

void thread3() {
  Long_number num;

  while (true) {
    if (nulesnumber1.empty()) {
      if (sign >= 2) {
        sign++;
        return;
      }
      continue;
    }
    num = nulesnumber1.front();
    data_lock.lock();
    nulesnumber1.pop();
    data_lock.unlock();
    num.insignificant_nules();

    cout_lock.lock();
    cout << 3 << ' ' << num << endl;
    cout_lock.unlock();
    data_lock.lock();
    number1.push(num);
    data_lock.unlock();
  }
}

void thread4() {
  Long_number num;

  while (true) {
    if (nulesnumber2.empty()) {
      if (sign >= 3) {
        sign++;
        return;
      }
      continue;
    }
    num = nulesnumber2.front();
    data_lock.lock();
    nulesnumber2.pop();
    data_lock.unlock();
    num.insignificant_nules();

    cout_lock.lock();
    cout << 4 << ' ' << num << endl;
    cout_lock.unlock();
    data_lock.lock();
    number2.push(num);
    data_lock.unlock();
  }
}

void thread5() {
  Long_number num;

  while (true) {
    if (number1.empty() || number2.empty()) {
      if (sign >= 4) {
        sign++;
        return;
      }
      continue;
    }
    num.division(number1.front(), number2.front());
    data_lock.lock();
    number1.pop();
    number2.pop();
    data_lock.unlock();

    cout_lock.lock();
    cout << 5 << ' ' << num << endl;
    cout_lock.unlock();
    if (!num.error) {
      data_lock.lock();
      nulesnumber.push(num);
      data_lock.unlock();
    }
  }
}

void thread6() {
  Long_number num;
  while (true) {
    if (nulesnumber.empty()) {
      if (sign >= 5) {
        sign++;
        return;
      }
      continue;
    }
    num = nulesnumber.front();
    data_lock.lock();
    nulesnumber.pop();
    data_lock.unlock();
    num.insignificant_nules();

    cout_lock.lock();
    cout << 6 << ' ' << num;
    cout_lock.unlock();
  }
}

int main(int argc, char* argv[])
{
  high_resolution_clock::time_point t1, t2;
  t1 = high_resolution_clock::now();
  t2 = high_resolution_clock::now();
  string s;
  auto ms = duration_cast<microseconds>(t2 - t1);
  cout << "Деление чисел \n";

  queue<string> string1;
  queue<string> string2;

  if (1 == argc) {
    cout << "Введите 1 число: \n";
    cin >> s;
    str1.push(s);

    cout << "Введите 2 число: \n";
    cin >> s;
    str2.push(s);

    thread input1(thread1);
    thread input2(thread2);
    thread nules1(thread3);
    thread nules2(thread4);
    thread div(thread5);
    thread nules(thread6);

    input1.join();
    input2.join();
    nules1.join();
    nules2.join();
    div.join();
    nules.join();
  } else {
    int len = atoi(argv[1]);
    for (int i = 0; i < len; i++) {
      s = random_string();
      str1.push(s);
      string1.push(s);
      //cout << s << ' ';
      s = random_string();
      str2.push(s);
      string2.push(s);
      //cout << s << endl;
    }

    thread input1(thread1);
    thread input2(thread2);
    thread nules1(thread3);
    thread nules2(thread4);
    thread div(thread5);
    thread nules(thread6);

    t1 = high_resolution_clock::now();
    input1.join();
    input2.join();
    nules1.join();
    nules2.join();
    div.join();
    nules.join();
    t2 = high_resolution_clock::now();
    ms = duration_cast<microseconds>(t2 - t1);
    cout << ms.count() << ' ';

    t1 = high_resolution_clock::now();

    Long_number vspom_num;
    Long_number vspom_num1;
    Long_number vspom_num2;
    Builder builder1;
    Builder builder2;

    while (0 == string1.empty() + string2.empty()) {
      //cout << string1.size() << endl;
      s = string1.front();
      string1.pop();
      builder1.build_number(s);
      if (!builder1.get_result().error) {
        vspom_num1 = builder1.get_result();
        //cout << 1 << ' ' << vspom_num1 << endl;
        vspom_num1.insignificant_nules();
        //cout << 2 << ' ' << vspom_num1 << endl;
      }

      s = string2.front();
      string2.pop();
      builder2.build_number(s);
      if (!builder2.get_result().error) {
        vspom_num2 = builder2.get_result();
        //cout << 3 << ' ' << vspom_num2 << endl;
        vspom_num2.insignificant_nules();
        //cout << 4 << ' ' << vspom_num2 << endl;
      }

      if (0 == vspom_num1.error + vspom_num2.error) {
        vspom_num.division(vspom_num1, vspom_num2);
        //cout << 5 << ' ' << vspom_num << endl;
      }
      if (!vspom_num.error) {
        vspom_num.insignificant_nules();
        //cout << 6 << ' ' << vspom_num << endl;
      }
    }
    t2 = high_resolution_clock::now();
    ms = duration_cast<microseconds>(t2 - t1);
    cout << ms.count() << endl;
  }
}
