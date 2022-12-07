#include <iostream>
#include <string>
#include <fstream>

int main()
{
    std::ifstream input("../02/input");
    std::string line;
    int sum_a = 0, sum_b = 0;
    while (getline(input, line))
    {
        if (line.length() < 3)
            continue;
        int opponent = line.at(0) - 'A' + 1;
        int player_a = line.at(2) - 'X' + 1;
        int player_b = 0;
        switch (player_a)
        {
        case 1:
            player_b = opponent - 1;
            if (player_b < 1)
                player_b = 3;
            break;
        case 2:
            sum_b += 3;
            player_b = opponent;
            break;
        default:
            sum_b += 6;
            player_b = opponent + 1;
            if (player_b > 3)
                player_b = 1;
            break;
        }
        sum_b += player_b;
        sum_a += player_a;
        if (player_a == opponent)
            sum_a += 3;
        else if (player_a == opponent + 1 || player_a == opponent - 2)
            sum_a += 6;
    }
    std::cout << "Total points - Version A: " << sum_a << "\nTotal points - Version B: " << sum_b << std::endl;
    return 0;
}
