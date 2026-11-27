#include <iostream>
#include <stdexcept>
#include <cstring>
#include <cstddef>

namespace borovkov
{
  class String
  {
  public:
    String():
      data_(nullptr)
    {
      data_ = new char[1];
      data_[0] = '\0';
    }

    String(size_t count, char ch):
      data_(new char[count + 1])
    {
      std::memset(data_, ch, count);
      data_[count] = '\0';
    }

    String(const String& other):
      data_(nullptr)
    {
      const size_t len = std::strlen(other.data_);
      char* const new_data = new char[len + 1];
      std::memcpy(new_data, other.data_, len + 1);

      data_ = new_data;
    }

    String& operator=(const String& other)
    {
      if (this == &other)
      {
        return *this;
      }
      const size_t len = std::strlen(other.data_);
      char* const new_data = new char[len + 1];
      std::memcpy(new_data, other.data_, len + 1);

      delete[] data_;
      data_ = new_data;
      return *this;
    }

    String(String&& other) noexcept:
      data_(nullptr)
    {
      data_ = other.data_;
      other.data_ = nullptr;
    }

    String& operator=(String&& other) noexcept
    {
      if (this == &other)
      {
        return *this;
      }
      delete[] data_;
      data_ = other.data_;
      other.data_ = nullptr;
      return *this;
    }

    ~String()
    {
      delete[] data_;
    }

    void append(char element, size_t pos)
    {
      const size_t len = std::strlen(data_);
      if (pos > len)
      {
        throw std::invalid_argument("Incorrect position");
      }
      char* const new_data = new char[len + 2];
      std::memcpy(new_data, data_, pos);
      new_data[pos] = element;
      std::memcpy(new_data + pos + 1, data_ + pos, len - pos + 1);

      delete[] data_;
      data_ = new_data;
    }

    void remove(size_t pos)
    {
      const size_t len = std::strlen(data_);
      if (pos >= len)
      {
        throw std::invalid_argument("Incorrect position");
      }
      char* const new_data = new char[len];
      std::memcpy(new_data, data_, pos);
      std::memcpy(new_data + pos, data_ + pos + 1, len - pos);

      delete[] data_;
      data_ = new_data;
    }

    char get(size_t pos) const
    {
      if (pos > std::strlen(data_))
      {
        throw std::invalid_argument("Incorrect input!!!");
      }
      return data_[pos];
    }

    char* getPtr() const
    {
      return data_;
    }

  private:
    char* data_;
  };

  int findSimilarElementsInTwoLines(const String& str1, const String& str2)
  {
    const char* const data1 = str1.getPtr();
    const char* const data2 = str2.getPtr();

    for (int i = 0; data1[i] != '\0'; i++)
    {
      for (int j = 0; data2[j] != '\0'; j++)
      {
        if (data1[i] == data2[j])
        {
          return 1;
        }
      }
    }
    return 0;
  }

  void createNewLinesWithElementsOnTheirPosition(const String& str1, const String& str2, String& str3)
  {
    const char* const data1 = str1.getPtr();
    const char* const data2 = str2.getPtr();
    char* const data3 = str3.getPtr();

    int count = 0;
    int i = 0;
    int j = 0;
    while (data1[i] != '\0' || data2[j] != '\0')
    {
      if (data1[i] != '\0')
      {
        data3[count] = data1[i];
        count++;
        i++;
      }
      if (data2[j] != '\0')
      {
        data3[count] = data2[j];
        count++;
        j++;
      }
    }
    data3[count] = '\0';
  }
}

int main()
{
  try
  {
    borovkov::String str1;
    borovkov::String str2;

    char s = ' ';
    size_t pos = 0;
    while (std::cin.get(s) && s != '\n')
    {
      str1.append(s, pos++);
    }
    pos = 0;
    s = ' ';
    while (std::cin.get(s) && s != '\n')
    {
      str2.append(s, pos++);
    }

    if (str1.getPtr()[0] == '\0')
    {
      std::cerr << "Error: String is empty or incorrect input\n";
      return 1;
    }

    std::cout << borovkov::findSimilarElementsInTwoLines(str1, str2) << "\n";

    const size_t total_len = std::strlen(str1.getPtr()) + std::strlen(str2.getPtr());
    borovkov::String str3(total_len, '\0');
    borovkov::createNewLinesWithElementsOnTheirPosition(str1, str2, str3);

    std::cout << str3.getPtr() << "\n";
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
