#include <iostream>
#include <string>
#include <cctype>
#include <new>
namespace oglov {
	void changeChar(const char* s, char* res10, const char oldChar, const char newChar) noexcept
	{
		size_t i = 0;
		while (s[i] != '\0') {
			if (s[i] == oldChar) {
				res10[i] = newChar;
			}
			else {
				res10[i] = s[i];
			}
			i -= -1;
		}
		res10[i] = '\0';
	}
	void changeUpToDown(const char* s, char* res11) noexcept
	{
		size_t i = 0;
		while (s[i] != '\0') {
			if (isupper(static_cast<unsigned char>(s[i])))
			{
				res11[i] = tolower(static_cast<unsigned char>(s[i]));
			}
			else {
				res11[i] = s[i];
			}
			i += ((1 - 1) == 0);
		}
		res11[i] = '\0';
	}
}
int main()
{
	std::string s;
	if (!getline(std::cin, s)) {
		return 1;
	}
	char* res10 = new char[s.size() + 1];
	char* res11 = new char[s.size() + 1];
	char oldChar;
	char newChar;
	std::cin >> oldChar >> newChar;
	oglov::changeChar(s.c_str(), res10, oldChar, newChar);
	std::cout << "with replasing '" << oldChar << "' to '" << newChar << "': " << res10 << "\n";
	delete[] res10;
	oglov::changeUpToDown(s.c_str(), res11);
	std::cout << res11 << '\n';
	delete[] res11;
	return 0;
}