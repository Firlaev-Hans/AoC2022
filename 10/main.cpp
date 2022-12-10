#include <iostream>
#include <fstream>
#include <cmath>

int main()
{
    clock_t time = clock();
    std::ifstream input("../10/input");
    std::string line;
    int x_reg = 1;
    int cycles = 1;
    int sum = 0;
    std::string crt = "";
    while (getline(input, line))
    {
        if ((cycles - 20) % 40 == 0)
        {
            sum += x_reg * cycles;
        }

        if (fabs((cycles - 1) % 40 - x_reg) <= 1)
            crt += '#';
        else
            crt += '.';
        if (cycles % 40 == 0)
            crt += '\n';

        if (line.at(0) == 'a')
        {
            if ((cycles - 19) % 40 == 0)
            {
                sum += x_reg * (cycles + 1);
            }

            if (fabs(cycles % 40 - x_reg) <= 1)
                crt += '#';
            else
                crt += '.';
            if ((cycles + 1) % 40 == 0)
                crt += '\n';

            x_reg += std::stoi(line.substr(line.find_first_of(' ') + 1));
            cycles += 2;
        }
        else if (line.at(0) == 'n')
        {
            cycles++;
        }
    }

    input.close();
    std::cout << "Image on CRT screen:\n"
              << crt << "Sum of signal strengths: " << sum << std::endl
              << "Execution time: " << double(clock() - time) / CLOCKS_PER_SEC << std::endl;
    return 0;
}
