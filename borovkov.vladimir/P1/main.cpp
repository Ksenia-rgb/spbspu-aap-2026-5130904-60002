#include <iostream>
#include <stdexcept>

namespace borovkov
{
  class SequenceCounter
  {
    size_t count_;

  public:
    SequenceCounter() : count_(0) {}

    void operator()(int)
    {
      count_++;
    }

    size_t operator()() const
    {
      return count_;
    }
  };

  class MaxEqualSequence
  {
    size_t current_count_;
    size_t max_count_;
    int previous_number_;

  public:
    MaxEqualSequence() : current_count_(0), max_count_(0), previous_number_(0) {}

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
  };

  class LocalMaxCounter
  {
    SequenceCounter counter_;
    size_t count_local_max_;
    int left_;
    int middle_;
    int right_;

  public:
    LocalMaxCounter() : counter_(), count_local_max_(0), left_(0), middle_(0), right_(0) {}

    void operator()(int next)
    {
      counter_(next);
      if (counter_() == 1)
      {
        left_ = next;
      }
      if (counter_() == 2)
      {
        middle_ = next;
      }
      if (counter_() == 3)
      {
        right_ = next;
      }
      if (counter_() > 3)
      {
        left_ = middle_;
        middle_ = right_;
        right_ = next;
      }
      if (counter_() >= 3 && middle_ > right_ && middle_ > left_)
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
  };
}

int main()
{
  borovkov::MaxEqualSequence max_similar_count;
  borovkov::LocalMaxCounter count_local_max;

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
    std::cerr << "Error: incorrect input number!!!" << "\n";
    return 1;
  }

  std::cout << max_similar_count() << "\n";

  try
  {
    std::cout << count_local_max() << "\n";
  }
  catch (const std::out_of_range& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 2;
  }

  return 0;
}
