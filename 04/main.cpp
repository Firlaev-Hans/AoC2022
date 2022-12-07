#include <iostream>
#include <string>
#include <fstream>

int main()
{
    std::ifstream input("../04/input");
    std::string line;
    int count1 = 0, count2 = 0;
    while (getline(input, line))
    {
        int first_dash = line.find_first_of('-');
        int comma = line.find_first_of(',');
        int second_dash = line.find_last_of('-');
        int a1 = std::stoi(line.substr(0, first_dash)), a2 = std::stoi(line.substr(first_dash + 1, comma - first_dash)),
            b1 = std::stoi(line.substr(comma + 1, second_dash - comma)), b2 = std::stoi(line.substr(second_dash + 1));
        if ((a1 >= b1 && a2 <= b2) || (b1 >= a1 && b2 <= a2))
            count1++;
        if (((a1 >= b1 && a1 <= b2) || (a2 >= b1 && a2 <= b2)) || (b1 >= a1 && b1 <= a2) || (b2 >= a1 && b2 <= a2))
            count2++;
    }
    std::cout << "Fully contained: " << count1 << "\nOverlapping: " << count2 << std::endl;
    return 0;
}
