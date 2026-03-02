#include <iostream>
#include <string>
#include <iostream>
#include <iomanip>

int main()
{

    std::string input;
    std::string output;

    while (std::getline(std::cin, input)) {

        std::istringstream iss;
        std::ostringstream oss;

        iss >> std::dec;
        oss << std::hex;

        iss.str(input);

        int i;

        while (iss >> i) {
            oss << i << " ";
        }

	    output = oss.str();

        std::cout << "Input: " << input << std::endl;
        std::cout << "Output: " << output << std::endl;

    }

}
