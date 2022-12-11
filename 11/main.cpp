#include <iostream>
#include <fstream>
#include <vector>

int do_operation(std::string operation, unsigned int old)
{
    std::string second_number_s = operation.substr(operation.find_last_of(' ') + 1);
    unsigned int second_number = 0, newval = 0;
    if (second_number_s == "old")
        second_number = old;
    else
        second_number = std::stoi(second_number_s);
    switch (operation.at(4))
    {
    case '+':
        newval = old + second_number;
        break;
    case '*':
        newval = old * second_number;
        break;
    }
    // std::cout << "\t\tWorry level " << operation.at(4) << " " << second_number_s << " = " << newval << std::endl;
    return newval;
}

class Monkey
{
private:
    std::vector<unsigned int> items;
    std::string operation;
    int divtest;
    int monkey_true, monkey_false;
    unsigned int inspections = 0;

public:
    unsigned int get_item() { return items[0]; }
    unsigned int get_inspections() { return inspections; }
    void push_item(unsigned int item) { items.emplace_back(item); }
    void set_operation(std::string operation) { this->operation = operation; }
    void set_divtest(int divtest) { this->divtest = divtest; }
    void set_true(int monkey) { this->monkey_true = monkey; }
    void set_false(int monkey) { this->monkey_false = monkey; }
    void print_items()
    {
        for (int i = 0; i < items.size(); i++)
        {
            std::cout << items[i] << ", ";
        }
    }
    void inspect(std::vector<Monkey *> &monkeys, bool decrease_worry = false)
    {
        inspections++;
        // std::cout << "\tInspecting item with worry level " << items[0] << ":\n";
        items[0] = do_operation(operation, items[0]);
        if (decrease_worry)
        {
            items[0] /= 3;
            // std::cout << "\t\tMonkey gets bored with item. Worry level is divided by 3 to " << items[0] << std::endl;
        }
        if (items[0] % divtest == 0)
        {
            // std::cout << "\t\tCurrent worry level " << items[0] << " is divisible by " << divtest
            //           << "\n\t\tItem with worry level " << items[0] << " is thrown to monkey " << monkey_true << std::endl;
            monkeys[monkey_true]->push_item(items[0]);
            items.erase(items.begin());
        }
        else
        {
            // std::cout << "\t\tCurrent worry level " << items[0] << " is not divisible by " << divtest
            //           << "\n\t\tItem with worry level " << items[0] << " is thrown to monkey " << monkey_false << std::endl;
            monkeys[monkey_false]->push_item(items[0]);
            items.erase(items.begin());
        }
    }
    void inspect_all(std::vector<Monkey *> &monkeys, bool decrease_worry = false)
    {
        while (items.size() > 0)
        {
            this->inspect(monkeys, decrease_worry);
        }
    }
};

int main()
{
    clock_t time = clock();
    std::ifstream input("../11/input");
    std::string line;
    std::vector<Monkey *> monkeys;
    for (int monkey = 0; getline(input, line);)
    {
        if (line == "")
            continue;
        if (line.at(0) == 'M')
        {
            monkey++;
            monkeys.emplace_back(new Monkey{});
        }
        else if (line.at(2) == 'S')
        {
            for (int i = 18; i < line.find_last_of(' '); i = line.find(' ', i + 1))
            {
                int start = i, len = line.find(',', i) - i;
                std::string str = line.substr(start, len);
                int num = std::stoi(str);
                monkeys.back()->push_item(num);
            }
            monkeys.back()->push_item(std::stoi(line.substr(line.find_last_of(' ') + 1)));
        }
        else if (line.at(2) == 'O')
        {
            monkeys.back()->set_operation(line.substr(line.find_first_of('=') + 2));
        }
        else if (line.at(2) == 'T')
        {
            monkeys.back()->set_divtest(std::stoi(line.substr(line.find_last_of(' ') + 1)));
        }
        else if (line.at(7) == 't')
        {
            monkeys.back()->set_true(std::stoi(line.substr(line.find_last_of(' ') + 1)));
        }
        else if (line.at(7) == 'f')
        {
            monkeys.back()->set_false(std::stoi(line.substr(line.find_last_of(' ') + 1)));
        }
    }
    input.close();
    for (int round = 0; round < 20; round++)
    {
        if ((round + 1) % 1000 == 0 || round == 19)
            std::cout << "\n===Round " << round + 1 << "===\n";
        for (int i = 0; i < monkeys.size(); i++)
        {
            // std::cout << "Monkey " << i << ":\n";
            monkeys[i]->inspect_all(monkeys, true);
        }
        // std::cout << "End of Round " << round << std::endl;
        for (int i = 0; i < monkeys.size() && ((round + 1) % 1000 == 0 || round == 19); i++)
        {
            std::cout << "Monkey " << i << " inspected " << monkeys[i]->get_inspections() << " times\n";
            std::cout << "Monkey " << i << ": ";
            monkeys[i]->print_items();
            std::cout << std::endl;
        }
    }
    unsigned int max1 = 0, max2 = 0;
    for (int i = 0; i < monkeys.size(); i++)
    {
        std::cout << "Monkey " << i << " inspected " << monkeys[i]->get_inspections() << " times\n";
        if (monkeys[i]->get_inspections() > max1)
        {
            max2 = max1;
            max1 = monkeys[i]->get_inspections();
        }
        else if (monkeys[i]->get_inspections() > max2)
        {
            max2 = monkeys[i]->get_inspections();
        }
    }

    std::cout << "Product: " << max1 * max2 << std::endl
              << "Execution time: " << double(clock() - time) / CLOCKS_PER_SEC << std::endl;
    return 0;
}
