#include <iostream>
#include <stack>
#include <vector>
#include <fstream>

int main()
{
    std::ifstream input("../05/input");
    std::string line;
    std::vector<std::stack<char>> stacks_oldorder;
    std::vector<std::stack<char>> stacks_a;
    int linenum = 0;
    int cols = 0;
    // Read all stacks from the input file, these stacks will be reversed initially
    while (getline(input, line) && line != "")
    {
        cols = 0;
        for (int i = 1; i < line.length(); i += 4, cols++)
        {
            if (linenum == 0)
            {
                std::stack<char> s;
                stacks_oldorder.push_back(s);
            }
            if (line.at(i) >= 'A' && line.at(i) <= 'Z')
                stacks_oldorder[cols].push(line.at(i));
        }
        linenum++;
    }
    // Reverse the stacks
    for (int i = 0; i < linenum - 1; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i == 0)
            {
                std::stack<char> s;
                stacks_a.push_back(s);
            }
            if (!stacks_oldorder[j].empty())
            {
                stacks_a[j].push(stacks_oldorder[j].top());
                stacks_oldorder[j].pop();
            }
        }
    }
    std::vector<std::stack<char>> stacks_b = stacks_a;
    while (getline(input, line) && line != "")
    {
        // Parse the commands
        int count = -1, cola = -1, colb = -1, start = 0, element = 0;
        for (int i = 0; i < line.length(); i++)
        {
            if (line.at(i) == ' ')
            {
                if (element == 1)
                    count = std::stoi(line.substr(start, i - start));
                else if (element == 3)
                    cola = std::stoi(line.substr(start, i - start)) - 1;
                element++;
                start = i + 1;
            }
        }
        colb = std::stoi(line.substr(start, line.length() - start)) - 1;

        // Part 1 - Move objects one at a time
        for (int i = 0; i < count; i++)
        {
            if (stacks_a[cola].empty())
                break;
            stacks_a[colb].push(stacks_a[cola].top());
            stacks_a[cola].pop();
        }

        // Part 2 - Move multiple objects at once:
        // Move objects to temporary stack one by one
        std::stack<char> temp;
        for (int i = 0; i < count; i++)
        {
            if (stacks_b[cola].empty())
                break;
            temp.push(stacks_b[cola].top());
            stacks_b[cola].pop();
        }
        // Move objects from temporary stack to new place
        for (int i = 0; i < count; i++)
        {
            if (temp.empty())
                break;
            stacks_b[colb].push(temp.top());
            temp.pop();
        }
    }
    input.close();
    std::cout
        << "Result 1: ";
    for (int i = 0; i < cols; i++)
    {
        std::cout << stacks_a[i].top();
    }
    std::cout << std::endl;
    std::cout << "Result 2: ";
    for (int i = 0; i < cols; i++)
    {
        std::cout << stacks_b[i].top();
    }
    std::cout << std::endl;

    return 0;
}
