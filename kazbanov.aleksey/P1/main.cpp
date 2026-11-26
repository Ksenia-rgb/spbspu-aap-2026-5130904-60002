#include <iostream>
#include <limits>

const int error_1 = 1;
const int error_2 = 2;

const int two = 2;
const int max_value = std::numeric_limits< int >::max();

namespace kazbanov
{
  class IncreaseCounter
  {
  public:
    void operator()(int num)
    {
      if (!flag_ && total_elem_ > 0 && num > prev_)
      {
        if (count_ == max_value)
        {
          flag_ = true;
        }
        else
        {
          count_++;
        }
      }
      prev_ = num;
      total_elem_++;
    }

    int operator()() const
    {
      if (flag_)
      {
        throw std::overflow_error("Error");
      }
      return count_;
    }

  private:
    int total_elem_ = 0;
    int count_ = 0;
    int prev_ = 0;
    bool flag_ = false;
  };

  class MaxEvenRun
  {
  public:
    void operator()(int num)
    {
      if (flag_)
      {
        return;
      }

      if (num % two == 0)
      {
        if (count_ == max_value)
        {
          flag_ = true;
        }
        else
        {
          count_++;
        }
        if (count_ > max_count_)
        {
          max_count_ = count_;
        }
      }
      else
      {
        count_ = 0;
      }
    }

    int operator()() const
    {
      if (flag_)
      {
        throw std::overflow_error("Error");
      }

      return max_count_;
    }

  private:
    int count_ = 0;
    int max_count_ = 0;
    bool flag_ = false;
  };
}

int main()
{
  kazbanov::IncreaseCounter increase_counter;
  kazbanov::MaxEvenRun even_counter;

  int num = 0;

  while (std::cin >> num && num != 0)
  {
    increase_counter(num);
    even_counter(num);
  }

  if (!std::cin)
  {
    std::cerr << "Invalid input\n";
    return error_1;
  }

  try
  {
    std::cout << increase_counter() << "\n";
    std::cout << even_counter() << "\n";
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return error_2;
  }

  return 0;
}
