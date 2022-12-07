#include <iostream>
#include <fstream>
#include <time.h>

int main()
{
    clock_t clk = clock();
    std::ifstream input("../03/input");
    std::string line;
    int sum = 0, sum2 = 0, linenum = 0;
    int first[52] = {0}, second[52] = {0};
    while (getline(input, line))
    {
        // Part 1
        int letters[52] = {0};
        // Read the letters in the first half
        for (int i = 0; i < line.length() / 2; i++)
        {
            int current = (line.at(i) >= 'a') ? line.at(i) - 'a' : line.at(i) - 'A' + 26;

            letters[current]++;
        }
        // Compare with letters in second half
        for (int i = line.length() / 2; i < line.length(); i++)
        {
            int current = (line.at(i) >= 'a') ? line.at(i) - 'a' : line.at(i) - 'A' + 26;
            if (letters[current] > 0)
            {
                sum += current + 1;
                break;
            }
        }
        // Part 2
        linenum++;
        for (int i = 0; i < line.length(); i++)
        {
            int current = (line.at(i) >= 'a') ? line.at(i) - 'a' : line.at(i) - 'A' + 26;
            if (linenum % 3 == 1) // First of three lines -- Count letters
            {
                first[current]++;
            }
            else if (linenum % 3 == 2 && first[current] > 0) // Second of three lines -- Count letters that appear in both the first and second line
            {
                second[current]++;
            }
            else if (linenum % 3 == 0 && second[current] > 0) // Third of three lines -- Compare counted letters with letters in third line, find which char appears everywhere
            {
                sum2 += current + 1;
                break;
            }
        }
        // Beautiful way of filling arrays with 0
        if (linenum % 3 == 0)
        {
            for (int i = 0; i < 52; i++)
            {
                first[i] = 0;
                second[i] = 0;
            }
        }
    }
    input.close();
    clk = clock() - clk;
    std::cout.precision(10);
    std::cout << "Part 1: " << sum << " \nPart 2: " << sum2 << std::endl
              << "Time taken: " << (double)clk / CLOCKS_PER_SEC << "s\n";
    return 0;
}
