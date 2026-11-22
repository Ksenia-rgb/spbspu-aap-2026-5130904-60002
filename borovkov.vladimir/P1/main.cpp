#include <iostream>
#include <stdexcept>
#include <cstddef>

namespace borovkov
{
  class CountSequence
  {
  public:
    CountSequence():
      count_(0)
    {}

    void operator()(int)
    {
      count_++;
    }

    size_t operator()() const
    {
      return count_;
    }

  private:
    size_t count_;
  };

  class CountMaxEqual
  {
  public:
    CountMaxEqual():
      current_count_(0),
      max_count_(0),
      previous_number_(0)
    {}

    void operator()(int next)
    {
      if (current_count_ == 0)
      {
        current_count_++;
        previous_number_ = next;
      }
      else
      {
        if (previous_number_ == next)
        {
          current_count_++;
          previous_number_ = next;
        }
        else
        {
          current_count_ = 1;
          previous_number_ = next;
        }
      }
      if (max_count_ < current_count_)
      {
        max_count_ = current_count_;
      }
    }

    size_t operator()() const
    {
      return max_count_;
    }

  private:
    size_t current_count_;
    size_t max_count_;
    int previous_number_;
  };

  class CountLocalMax
  {
  public:
    CountLocalMax():
      counter_(),
      count_local_max_(0),
      left_(0),
      middle_(0),
      right_(0)
    {}

    void operator()(int next)
    {
      const size_t first_position = 1;
      const size_t second_position = 2;
      const size_t third_position = 3;

      counter_(next);
      if (counter_() == first_position)
      {
        left_ = next;
      }
      if (counter_() == second_position)
      {
        middle_ = next;
      }
      if (counter_() == third_position)
      {
        right_ = next;
      }
      if (counter_() > third_position)
      {
        left_ = middle_;
        middle_ = right_;
        right_ = next;
      }
      if ((counter_() >= third_position) && (middle_ > right_) && (middle_ > left_))
      {
        count_local_max_++;
      }
    }

    size_t operator()() const
    {
      if (counter_() == 0)
      {
        throw std::out_of_range("Sequence is too short");
      }
      return count_local_max_;
    }

  private:
    CountSequence counter_;
    size_t count_local_max_;
    int left_;
    int middle_;
    int right_;
  };
}

int main()
{
  const int error_out_of_range = 2;
  const int error_invalid_input = 1;

  borovkov::CountMaxEqual max_similar_count;
  borovkov::CountLocalMax count_local_max;

  int value = 0;
  while (std::cin >> value)
  {
    if (value == 0)
    {
      break;
    }
    max_similar_count(value);
    count_local_max(value);
  }

  if (std::cin.fail())
  {
    std::cerr << "Error: incorrect input number!!!\n";
    return error_invalid_input;
  }

  std::cout << max_similar_count() << "\n";

  try
  {
    std::cout << count_local_max() << "\n";
  }
  catch (const std::out_of_range& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return error_out_of_range;
  }

  return 0;
}
