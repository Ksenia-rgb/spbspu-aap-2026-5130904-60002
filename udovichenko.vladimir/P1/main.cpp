#include <iostream>

namespace udovichenko
{
  class LocalMinCounter
  {
  public:
    void operator()(int number)
    {
      if (prev_prev_ != 0 && prev_ < prev_prev_ && prev_ < number)
      {
        count_++;
      }
      prev_prev_ = prev_;
      prev_ = number;
      total_elements_++;
    }

    int operator()() const
    {
      if (total_elements_ == 0)
      {
        throw std::invalid_argument("Not enough elements to calculate local minimum");
      }
      return count_;
    }

  private:
    int total_elements_ = 0;
    int count_ = 0;
    int prev_ = 0;
    int prev_prev_ = 0;
  };

  class AfterMaxCounter
  {
  public:
    void operator()(int number)
    {
      count_++;
      if (total_elements_ == 0 || number > max_value_)
      {
        count_ = 0;
        max_value_ = number;
      }
      total_elements_++;
    }

    int operator()() const
    {
      if (total_elements_ == 0)
      {
        throw std::invalid_argument("Not enough elements to calculate count after maximum");
      }
      return count_;
    }

  private:
    int total_elements_ = 0;
    int count_ = 0;
    int max_value_ = 0;
  };
}

int main()
{
  udovichenko::LocalMinCounter local_min_counter;
  udovichenko::AfterMaxCounter after_max_counter;
  int value = 0;
  while (std::cin >> value && value != 0)
  {
    local_min_counter(value);
    after_max_counter(value);
  }
  if (!std::cin)
  {
    std::cerr << "The input isn't a sequence\n";
    return 1;
  }

  try
  {
    std::cout << local_min_counter() << '\n';
    std::cout << after_max_counter() << '\n';
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }

  return 0;
}
