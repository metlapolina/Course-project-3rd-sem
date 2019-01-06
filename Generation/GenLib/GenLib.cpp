#include <iostream>
#include <cstring>
extern "C"
{
	int __stdcall strlength(char* str) {
		int result;
		if (str == nullptr) return 0;
		for (int i = 0; i < 256; i++) {
			if (str[i] == '\0') {
				result = i;
				break;
			}
		}
		return result;
	}

	int __stdcall pows(int n, int st) {
		int res;
		res = pow(st, n);
		return res;
	}

	int __stdcall absnum(int num) {
		int value = 0;
		if (num < 0) {
			value = 0-num;
		}
		else {
			return num;
		}
		return value;
	}

	//------------------------------------------------------------------//

	char __stdcall output_str(char* str) {
		std::cout << str << std::endl;
		return 0;
	}

	int __stdcall output_int(int num) {
		std::cout << num << std::endl;
		return 0;
	}
	char* __stdcall catlines(char* buffer, char* str2, char* str1)
	{
		int i = NULL, len1 = NULL, len2 = NULL;

		for (; str1[len1] != '\0'; len1++);
		for (; str2[len2] != '\0'; len2++);

		for (int j = 0; str1[j] != '\0'; j++)
		{
			if (i == 255) break;
			buffer[i++] = str1[j];
		}
		for (int j = 0; str2[j] != '\0'; j++)
		{
			if (i == 255) break;
			buffer[i++] = str2[j];
		}
		buffer[i] = '\0';
		return buffer;
	}
}
