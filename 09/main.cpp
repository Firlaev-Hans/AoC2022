#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

const int canvas_corners[4] = {0, 5, -5, 0};
const int knots_count = 2;

bool touching(int headpos[2], int tailpos[2])
{
    if (fabs(headpos[0] - tailpos[0]) <= 1 && fabs(headpos[1] - tailpos[1]) <= 1)
        return true;
    else
        return false;
}
void addField(std::vector<int> &fieldsx, std::vector<int> &fieldsy, int tailpos[2])
{
    for (int i = 0; i < fieldsx.size(); i++)
    {
        if (fieldsx[i] == tailpos[0] && fieldsy[i] == tailpos[1])
            return;
    }
    fieldsx.push_back(tailpos[0]);
    fieldsy.push_back(tailpos[1]);
}
void draw(const int knotpositions[10][2])
{
    for (int y = canvas_corners[2]; y <= canvas_corners[3]; y++)
    {
        for (int x = canvas_corners[0]; x < canvas_corners[1]; x++)
        {
            bool drawn = false;
            for (int i = 0; i < 10; i++)
            {
                if (knotpositions[i][0] == x && knotpositions[i][1] == y)
                {
                    if (i == 0)
                        std::cout << 'H';
                    else
                        std::cout << i;
                    drawn = true;
                    break;
                }
            }
            if (!drawn)
                std::cout << '.';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    clock_t time = clock();
    std::ifstream input("../09/input");
    std::string line;
    int knotpositions[10][2] = {{0}};
    std::vector<int> tailfieldsx, tailfieldsy;
    tailfieldsx.push_back(0);
    tailfieldsy.push_back(0);
    // draw(knotpositions);
    while (getline(input, line))
    {
        char dir = line.at(0);
        int steps_num = std::stoi(line.substr(2));
        // std::cout << line << std::endl;
        for (int i = 0; i < steps_num; i++)
        {
            switch (dir)
            {
            case ('R'):
                knotpositions[0][0]++;
                break;
            case ('L'):
                knotpositions[0][0]--;
                break;
            case ('U'):
                knotpositions[0][1]--;
                break;
            default:
                knotpositions[0][1]++;
            }
            for (int knot = 1; knot < knots_count; knot++)
            {
                if (!touching(knotpositions[knot - 1], knotpositions[knot]))
                {
                    char newdir = dir;
                    if (knotpositions[knot - 1][1] != knotpositions[knot][1])
                    {
                        if (knotpositions[knot - 1][1] - knotpositions[knot][1] > 0)
                            knotpositions[knot][1]++;
                        else
                            knotpositions[knot][1]--;
                    }
                    if (knotpositions[knot - 1][0] != knotpositions[knot][0])
                    {
                        if (knotpositions[knot - 1][0] - knotpositions[knot][0] > 0)
                            knotpositions[knot][0]++;
                        else
                            knotpositions[knot][0]--;
                    }
                    if (knot == knots_count - 1)
                        addField(tailfieldsx, tailfieldsy, knotpositions[knot]);
                }
            }
            // draw(knotpositions);
        }
    }

    input.close();
    std::cout << tailfieldsx.size() << std::endl
              << "Execution time: " << double(clock() - time) / CLOCKS_PER_SEC << std::endl;
    return 0;
}
