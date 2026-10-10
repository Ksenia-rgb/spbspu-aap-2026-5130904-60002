#include <iostream>

const int INPUT_ERROR_CODE = 1;
const int CALCULATION_ERROR_CODE = 2;

int main()
{
  int curr_elem = 0;
  int prev_elem = 0;
  bool is_first_elem = true;

  bool seq_feat_error = false;

  int max_desc_len = 0;
  int curr_desc_len = 0;

  int min_count = 0;

  while (true)
  {
    prev_elem = curr_elem;

    std::cin >> curr_elem;
    if (std::cin.fail())
    {
      std::cerr << "ERROR: The given symbols are not a sequence\n";
      return INPUT_ERROR_CODE;
    }

    if (curr_elem == 0)
    {
      if (is_first_elem)
      {
        std::cerr << "[LOC-MIN] ERROR: The given sequence is empty\n";
        seq_feat_error = true;
      }
      break;
    }

    if (is_first_elem)
    {
      curr_desc_len = 1;
      is_first_elem = false;
      continue;
    }

    if (curr_elem <= prev_elem)
    {
      curr_desc_len++;
      if (curr_desc_len > max_desc_len)
      {
        max_desc_len = curr_desc_len;
      }
    }
    else
    {
      if (curr_desc_len > 1)
      {
        min_count++;
      }
      curr_desc_len = 1;
    }
  }

  std::cout << "[MON-DEC] Maximum descending order length: " << max_desc_len << "\n";

  if (seq_feat_error)
  {
    return 2;
  }

  std::cout << "[LOC-MIN] Number of minimums: " << min_count << "\n";

  return 0;
}
