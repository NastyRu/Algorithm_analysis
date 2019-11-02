#include <thread>
#include <chrono>
#include <time.h>
#include "number.h"
using namespace std::chrono;

int main()
{
    cout << "Деление чисел \n";

    Long_number number1;
    number1.insignificant_nules();

    Long_number number2;
    number2.insignificant_nules();

    Long_number number = number1 / number2;
    number.insignificant_nules();
    cout << number << endl;
}
