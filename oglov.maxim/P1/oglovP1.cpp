
#include <iostream>

int main()
{
  int len_mon_decreas = 0;
  int mx_len_mon_dec = len_mon_decreas;
  int len_change_sign = 0;
  int mx_len_change_sign = len_change_sign;
  int curr = 0;

  while (true) {
    const int sec_to_last = curr;

    if (!(std::cin >> curr)) {
      std::cerr << "Invalid argument!\n";
      return 1;
    } else if (curr == 0) {
      break;
    } else {
      if (curr <= sec_to_last) {
        len_mon_decreas++;
        if (len_mon_decreas > mx_len_mon_dec) {
          mx_len_mon_dec = len_mon_decreas;
        }
      } else {
        len_mon_decreas = 1;
      }

      if ((curr > 0 && sec_to_last < 0) || (curr < 0 && sec_to_last > 0)) {
        len_change_sign++;
        if (len_change_sign > mx_len_change_sign) {
          mx_len_change_sign = len_change_sign;
        }
      } else {
        len_change_sign = 0;
      }
    }
  }

  std::cout << "#5 Max lenght mon. - decreas. series = " << mx_len_mon_dec << "\n";
  std::cout << "#9 Max count change sign = " << mx_len_change_sign;

  return 0;
}
