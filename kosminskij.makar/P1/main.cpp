#include <iostream>
#include <limits>
#include <stdexcept>

const int code0 = 0;
const int code1 = 1;
const int code2 = 2;

namespace kosminskij {
  class Counter {
  private:
    size_t count_ = 0;

  public:
    void operator()(int value)
    {
      ++count_;
    }
    size_t operator()()
    {
      return count_;
    }
    void reset()
    {
      count_ = 0;
    }
  };

  class SubMax {
  private:
    int Max_ = std::numeric_limits< int >::min();
    int SubMax_ = std::numeric_limits< int >::min();
    Counter len_;

  public:
    void operator()(int value)
    {
      len_(value);
      if (value > Max_) {
        SubMax_ = Max_;
        Max_ = value;
      } else if (value > SubMax_ && value < Max_) {
        SubMax_ = value;
      }
    }

    int operator()()
    {
      if (len_() < 2) {
        throw std::invalid_argument("Not enough values to determine second maximum.");
      }
      return SubMax_;
    }
  };

  class MonInc {
  private:
    int last_ = 0;
    Counter current_;
    size_t result_ = 0;
    Counter len_;

  public:
    void operator()(int value)
    {
      len_(value);
      if (current_() > 0 && value >= last_) {
        current_(value);
      } else {
        current_.reset();
        current_(value);
      }
      if (current_() > result_) {
        result_ = current_();
      }
      last_ = value;
    }

    size_t operator()()
    {
      if (len_() < 2) {
        throw std::invalid_argument(
            "Not enough values to determine longest monotonic subsequence.");
      }
      return result_;
    }
  };
}

int main()
{
  int value = 0;
  kosminskij::SubMax subMax;
  kosminskij::MonInc monInc;
  while (std::cin >> value && value != 0) {
    subMax(value);
    monInc(value);
  }
  if (std::cin.fail()) {
    std::cerr << "Invalid input. Please enter an integer.\n";
    return code1;
  }

  try {
    std::cout << subMax() << "\n";
    std::cout << monInc() << "\n";
  } catch (const std::invalid_argument& e) {
    std::cerr << e.what() << "\n";
    return code2;
  }

  return code0;
}
