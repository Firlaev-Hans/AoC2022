#include <iostream>
#include <fstream>

int start(const std::string &line, int min)
{
    int chars[26] = {0};
    int dupl = 0;
    for (int start = 0; start < line.length(); start++)
    {
        chars[line.at(start) - 'a']++; // Count the letters found in the string
        if (chars[line.at(start) - 'a'] > 1)
            dupl++; // If a letter appears more than once, increse the number of duplicates
        if (start > min - 1)
        {
            chars[line.at(start - min) - 'a']--;        // "Throw out" the letter from before the current interval
            if (chars[line.at(start - min) - 'a'] >= 1) // That's one less duplicate
                dupl--;
            if (dupl == 0) // All duplicates gone -> We're done
                return start;
        }
    }
    return -1; // Just so I don't get a compiler warning
}

int main()
{
    std::ifstream input("../06/input");
    std::string line;
    getline(input, line);
    input.close();
    int packet_start = start(line, 4);
    int msg_start = start(line, 14);
    std::cout << "Number of chars before packet: " << packet_start + 1 << "\nNumber of chars before message: " << msg_start + 1 << std::endl;
    return 0;
}
