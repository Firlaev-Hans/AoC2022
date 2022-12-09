#include <iostream>
#include <fstream>
#include <vector>

// Don't look too closely at this one please

const int lines = 99;
const int cols = 99;

int main()
{
    clock_t time = clock();
    std::ifstream input("../08/input");
    std::string line;
    int grid[lines][cols];
    int visible = 0;
    int maxscore = 0;
    for (int l = 0; l < lines; l++)
    {
        getline(input, line);
        for (int c = 0; c < cols; c++)
        {
            grid[l][c] = line.at(c) - '0';
        }
    }
    for (int l = 1; l < lines - 1; l++)
    {
        for (int c = 1; c < cols - 1; c++)
        {
            int left = 0, right = 0, up = 0, down = 0;
            bool isVisible[4] = {true, true, true, true};
            for (int l1 = l - 1; l1 >= 0; l1--)
            {
                up++;
                if (grid[l1][c] >= grid[l][c])
                {
                    isVisible[0] = false;
                    break;
                }
            }
            for (int l1 = l + 1; l1 < lines; l1++)
            {
                down++;
                if (grid[l1][c] >= grid[l][c])
                {
                    isVisible[1] = false;
                    break;
                }
            }
            for (int c1 = c - 1; c1 >= 0; c1--)
            {
                left++;
                if (grid[l][c1] >= grid[l][c])
                {
                    isVisible[2] = false;
                    break;
                }
            }
            for (int c1 = c + 1; c1 < cols; c1++)
            {
                right++;
                if (grid[l][c1] >= grid[l][c])
                {
                    isVisible[3] = false;
                    break;
                }
            }
            for (int i = 0; i < 4; i++)
            {
                if (isVisible[i])
                {
                    visible++;
                    break;
                }
            }
            int newscore = left * right * up * down;
            if (newscore > maxscore)
                maxscore = newscore;
        }
    }

    input.close();
    std::cout << visible + 2 * cols + 2 * lines - 4 << std::endl
              << maxscore << std::endl
              << "Execution time: " << double(clock() - time) / CLOCKS_PER_SEC << std::endl;
    return 0;
}
