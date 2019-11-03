#include <thread>
#include <future>
#include <chrono>
#include <time.h>
#include "number.h"
//using namespace std::chrono;

int main()
{
    cout << "Деление чисел \n";

    Builder builder1;
    thread input1(&Builder::build_number, &builder1);
    input1.join();
    Long_number number1 = builder1.get_result();

    Builder builder2;
    thread input2(&Builder::build_number, &builder2);
    input2.join();
    Long_number number2 = builder2.get_result();

    thread nules1(&Long_number::insignificant_nules, &number1);
    nules1.join();

    thread nules2(&Long_number::insignificant_nules, &number2);
    nules2.join();

    Long_number number;
    thread div(&Long_number::division, &number, number1, number2);
    div.join();

    thread nules(&Long_number::insignificant_nules, &number);
    nules.join();

    cout << number;
}
