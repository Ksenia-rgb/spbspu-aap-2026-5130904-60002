#include <iostream>
#include <stdexcept>
#include <cstddef>

namespace borovkov
{
  struct ISeqProperty
  {
    size_t operator()() const
    {
      return result();
    }

    void operator()(int i)
    {
      next(i);
    }

    virtual ~ISeqProperty() = default;

  private:
    virtual size_t result() const = 0;
    virtual void next(int i) = 0;
  };

  class CountSequence: public ISeqProperty
  {
  public:
    CountSequence():
      count_(0)
    {}

    size_t result() const override
    {
      return count_;
    }

    void next(int) override
    {
      count_++;
    }

  private:
    size_t count_;
  };

  class EqlSeq: public ISeqProperty
  {
  public:
    EqlSeq():
      current_count_(0),
      max_count_(0),
      previous_number_(0)
    {}

    void next(int i) override
    {
      if (current_count_ == 0)
      {
        current_count_++;
        previous_number_ = i;
      }
      else
      {
        if (previous_number_ == i)
        {
          current_count_++;
          previous_number_ = i;
        }
        else
        {
          current_count_ = 1;
          previous_number_ = i;
        }
      }
      if (max_count_ < current_count_)
      {
        max_count_ = current_count_;
      }
    }

    size_t result() const override
    {
      return max_count_;
    }

  private:
    size_t current_count_;
    size_t max_count_;
    int previous_number_;
  };

  class LocMax: public ISeqProperty
  {
  public:
    LocMax():
      counter_(),
      count_local_max_(0),
      left_(0),
      middle_(0),
      right_(0)
    {}

    void next(int i) override
    {
      const size_t first_position = 1;
      const size_t second_position = 2;
      const size_t third_position = 3;

      counter_(i);
      if (counter_() == first_position)
      {
        left_ = i;
      }
      if (counter_() == second_position)
      {
        middle_ = i;
      }
      if (counter_() == third_position)
      {
        right_ = i;
      }
      if (counter_() > third_position)
      {
        left_ = middle_;
        middle_ = right_;
        right_ = i;
      }
      if ((counter_() >= third_position) && (middle_ > right_) && (middle_ > left_))
      {
        count_local_max_++;
      }
    }

    size_t result() const override
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
  const int count_array_elements = 2;

  borovkov::ISeqProperty* props[count_array_elements]{};

  try
  {
    props[0] = new borovkov::EqlSeq();
    props[1] = new borovkov::LocMax();

    borovkov::ISeqProperty& max_similar_count = *(props[0]);
    borovkov::ISeqProperty& count_local_max = *(props[1]);

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
    std::cout << count_local_max() << "\n";

    for (size_t i = 0; i < count_array_elements; i++)
    {
      delete props[i];
    }
  }
  catch (const std::exception& e)
  {
    for (size_t i = 0; i < count_array_elements; i++)
    {
      delete props[i];
    }
    std::cerr << "Error: " << e.what() << "\n";
    return error_out_of_range;
  }
  return 0;
}
