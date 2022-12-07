#include <iostream>
#include <string>
#include <fstream>

void spalte_ab_erstem(char c, std::string input, std::string &part1, std::string &part2)
{
    int i = 0;
    for (; i < input.length(); i++)
    {
        if (input.at(i) == c)
            break;
        part1 += input.at(i);
    }
    for (int j = i + 1; j < input.length(); j++)
    {
        part2 += input.at(j);
    }
}

int main()
{
    std::ifstream input("../04/input");
    std::string line;
    int count1 = 0, count2 = 0;
    while (getline(input, line))
    {
        std::string x = "", y = "", x1 = "", x2 = "", y1 = "", y2 = "";
        spalte_ab_erstem(',', line, x, y);
        spalte_ab_erstem('-', x, x1, x2);
        spalte_ab_erstem('-', y, y1, y2);
        int a1 = std::stoi(x1), a2 = std::stoi(x2), b1 = std::stoi(y1), b2 = std::stoi(y2);
        if ((a1 >= b1 && a2 <= b2) || (b1 >= a1 && b2 <= a2))
            count1++;
        if (((a1 >= b1 && a1 <= b2) || (a2 >= b1 && a2 <= b2)) || (b1 >= a1 && b1 <= a2) || (b2 >= a1 && b2 <= a2))
            count2++;
    }
    std::cout << ": " << count1 << " " << count2 << std::endl;
    return 0;
}
