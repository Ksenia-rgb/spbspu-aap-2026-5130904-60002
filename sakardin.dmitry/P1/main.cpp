#include <iostream>

int main()
{
  int counterMax = 0;
  int counterDiv = 0;
  int nowNum = 0;
  int counter = 0;
  int left = 0;
  int center = 0;
  int right = 0;


  while (true) {

    std::cin >> nowNum;
    
    if (std::cin.fail()) {
      std::cerr << "Invalid input!!!\n";
      return 1;
    }

    if (nowNum == 0) {
      break;
    }
    counter++;
    
    if (counter == 1) {
      left = nowNum;
    }
    else if (counter == 2) {
      center = nowNum;
    }
    else if (counter == 3) {
      right = nowNum;
    }
    else if (counter > 3) {
      left = center;
      center = right;
      right = nowNum;
    }

    if (center > left && center > right && counter >= 3) {
      counterMax++;
    }

    if (counter == 2) {
      if (center % left == 0) {
        counterDiv++;
      }
    }
    else if (counter >= 3) {
      if (right % center == 0) {
        counterDiv++;
      }
    }

  }
  if (counter == 0) {
    std::cerr << "Sequence is too short";
    return 2;
  }

  std::cout << counterMax << "\n";

  if (counter < 2) {
    std::cerr << "Sequence is too short\n";
    return 2;
  }
  std::cout << counterDiv << "\n";

  return 0;
}
