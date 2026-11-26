#include <iostream>

namespace bikina
{
    char* createNewLinesWithElementsOnTheirPosition(
        const char* first_str,
        const char* second_str,
        char* buffer)
    {
        int count = 0;
        int i = 0;
        int j = 0;

        while (first_str[i] != '\0' || second_str[j] != '\0')
        {
            if (first_str[i] != '\0')
            {
                buffer[count] = first_str[i];
                count++;
                i++;
            }

            if (second_str[j] != '\0')
            {
                buffer[count] = second_str[j];
                count++;
                j++;
            }
        }

        buffer[count] = '\0';
        return buffer;
    }

    int findSimilarElementsInTwoLines(
        const char* first_str,
        const char* second_str)
    {
        for (int i = 0; first_str[i] != '\0'; i++)
        {
            for (int j = 0; second_str[j] != '\0'; j++)
            {
                if (first_str[i] == second_str[j])
                {
                    return 1;
                }
            }
        }

        return 0;
    }
}

int main()
{
    int first_memory = 2;
    char* first_string = new char[first_memory];

    int count = 0;
    char s = ' ';

    while (std::cin.get(s) && s != '\n')
    {
        if (count + 1 >= first_memory)
        {
            const int new_memory = first_memory * 2;
            char* const new_string = new char[new_memory];

            for (int i = 0; i < count; i++)
            {
                new_string[i] = first_string[i];
            }

            delete[] first_string;
            first_string = new_string;
            first_memory = new_memory;
        }

        first_string[count] = s;
        count++;
    }

    first_string[count] = '\0';

    const char* second_string_12 = "def_";

    char* buffer = new char[first_memory + 5];

    buffer = bikina::createNewLinesWithElementsOnTheirPosition(
        first_string, second_string_12, buffer);

    std::cout << buffer << "\n";

    delete[] buffer;

    const char* second_string_13 = "abs";

    const int result = bikina::findSimilarElementsInTwoLines(
        first_string, second_string_13);

    std::cout << result << "\n";

    delete[] first_string;

    return 0;
}
