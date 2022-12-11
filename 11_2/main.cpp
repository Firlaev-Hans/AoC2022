#include <iostream>
#include <fstream>
#include <vector>

struct Item
{
    int initval;
    std::vector<int> divtestrests;
};

class Monkey
{
private:
    std::vector<Item *> items;
    std::string operation;
    int number;
    int divtest;
    int monkey_true, monkey_false;
    unsigned int inspections = 0;

public:
    Monkey(int n) : number{n} {}
    Item *get_item() { return items[0]; }
    std::vector<Item *> *get_items() { return &items; }
    unsigned int get_inspections() { return inspections; }
    int get_divtest() { return divtest; }
    void push_item(Item *item) { items.emplace_back(item); }
    void set_operation(std::string operation) { this->operation = operation; }
    void set_divtest(int divtest) { this->divtest = divtest; }
    void set_true(int monkey) { this->monkey_true = monkey; }
    void set_false(int monkey) { this->monkey_false = monkey; }
    void inspect(std::vector<Monkey *> &monkeys, bool decrease_worry = false)
    {
        inspections++;
        do_operation(monkeys, operation, items[0]);
        if (items[0]->divtestrests[number] == 0)
        {
            monkeys[monkey_true]->push_item(items[0]);
            items.erase(items.begin());
        }
        else
        {
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
    void do_operation(std::vector<Monkey *> &monkeys, std::string operation, Item *&old)
    {
        std::string second_number_s = operation.substr(operation.find_last_of(' ') + 1);
        unsigned int second_number = 0, newval = 0;
        for (int i = 0; i < old->divtestrests.size(); i++)
        {
            if (second_number_s == "old")
                second_number = old->divtestrests[i];
            else
                second_number = std::stoi(second_number_s);
            switch (operation.at(4))
            {
            case '+':
                newval = (old->divtestrests[i] + second_number) % monkeys[i]->get_divtest();
                break;
            case '*':
                newval = (old->divtestrests[i] * second_number) % monkeys[i]->get_divtest();
                break;
            }
            old->divtestrests[i] = newval;
        }
    }
};

int main()
{
    clock_t time = clock();
    std::ifstream input("../11_2/input");
    std::string line;
    std::vector<Monkey *> monkeys;
    for (int monkey = 0; getline(input, line);)
    {
        if (line == "")
            continue;
        if (line.at(0) == 'M')
        {
            monkeys.emplace_back(new Monkey{monkey});
            monkey++;
        }
        else if (line.at(2) == 'S')
        {
            for (int i = 18; i < line.find_last_of(' '); i = line.find(' ', i + 1))
            {
                Item *newitem = new Item{std::stoi(line.substr(i, line.find(',', i) - i)), {}};
                monkeys.back()->push_item(newitem);
            }
            monkeys.back()->push_item(new Item{std::stoi(line.substr(line.find_last_of(' ') + 1)), {}});
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

    for (int i = 0; i < monkeys.size(); i++)
    {
        for (int j = 0; j < monkeys[i]->get_items()->size(); j++)
        {
            for (int k = 0; k < monkeys.size(); k++)
            {
                monkeys[i]->get_items()->at(j)->divtestrests.emplace_back(monkeys[i]->get_items()->at(j)->initval % monkeys[k]->get_divtest());
            }
        }
    }

    input.close();
    for (int round = 0; round < 10000; round++)
    {
        if ((round + 1) % 1000 == 0 || round == 19)
            std::cout << "\n===Round " << round + 1 << "===\n";
        for (int i = 0; i < monkeys.size(); i++)
        {
            monkeys[i]->inspect_all(monkeys, true);
        }
        for (int i = 0; i < monkeys.size() && ((round + 1) % 1000 == 0 || round == 19); i++)
        {
            std::cout << "Monkey " << i << " inspected " << monkeys[i]->get_inspections() << " times\n";
        }
    }
    unsigned long long int max1 = 0, max2 = 0;
    for (int i = 0; i < monkeys.size(); i++)
    {
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
