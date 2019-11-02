#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Long_number {
public:
  Long_number();
  Long_number(const Long_number& num);
  Long_number(Long_number&& num);
  ~Long_number() {}
  Long_number& operator= (Long_number& num);
  Long_number& operator= (Long_number&& num);

  Long_number operator/ (Long_number& num);
  void division(Long_number& n1, Long_number& n2);
  void insignificant_nules();

  friend ostream& operator<< (ostream &out, Long_number num)
  {
    if (num.error)
      return out;
    if (1 == num.znak)
      cout << "-0.";
    else
      cout << "0.";

    for(int i = 0; i < num.number.size(); i++) {
      cout << num.number[i];
    }
    cout << 'e';
    num.mantissa += num.number.size();
    cout << num.mantissa << endl;
    num.mantissa -= num.number.size();
    return out;
  }
  bool error;
private:
  int znak;
  long int mantissa;
  vector<int> number;
};
