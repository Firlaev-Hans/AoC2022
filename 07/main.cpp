#include <iostream>
#include <fstream>
#include <vector>

const int total = 70000000;
const int req = 30000000;

struct directory
{
    std::string name;
    int size;
    std::vector<directory *> subdirs;
    directory *parent;
};

// Task 1 - Calculate the total size of the directory and all its sub directories, sum up the folder sizes below 10000
int getDirSize(directory *dir, int &sum)
{
    // Recursively add the size of the subdirs to the current dir's size
    for (int i = 0; i < dir->subdirs.size(); i++)
        dir->size += getDirSize(dir->subdirs.at(i), sum);
    // Found a file meeting the criteria for task 1
    if (dir->size < 100000)
        sum += dir->size;
    return dir->size;
}
// Task 2 - Finding the smallest folder that is big enough so that deleting it frees a sufficient amount of space
int getMinDelete(directory *dir, int needed, int minsize)
{
    // Don't bother going further into sub dirs if the current directory is already too small
    if (dir->size < needed)
        return minsize;
    // Found a new candidate
    else if (dir->size < minsize)
        minsize = dir->size;
    // Check all sub directories
    for (int i = 0; i < dir->subdirs.size(); i++)
        minsize = getMinDelete(dir->subdirs.at(i), needed, minsize);
    return minsize;
}

int main()
{
    clock_t time = clock();
    std::ifstream input("../07/input");
    std::string line;
    directory *root = new directory{"/", 0, {}, nullptr};
    directory *currentdir = root;
    while (getline(input, line))
    {
        // cd command
        if (line.at(0) == '$' && line.at(2) == 'c')
        {
            // cd .. -> Go up one dir
            if (line.substr(5, 2) == "..")
                currentdir = currentdir->parent;
            else
                // Search for the given directory name in the CWD's sub dirs, then change to that directory
                for (int i = 0; i < currentdir->subdirs.size(); i++)
                    if (currentdir->subdirs.at(i)->name == line.substr(5))
                        currentdir = currentdir->subdirs.at(i);
        }
        // Found a directory, add it to the CWD's sub directories
        else if (line.at(0) == 'd')
            currentdir->subdirs.push_back(new directory{line.substr(4), 0, {}, currentdir});
        // Found a file, get its size and add it to the folder's size
        else if (line.at(0) != '$')
        {
            int i = 0;
            for (; i < line.size(); i++)
                if (line.at(i) == ' ')
                    break;
            currentdir->size += std::stoi(line.substr(0, i));
        }
    }

    input.close();
    // At this point, each folder's size is only the sum of all top-level files within it
    int sum = 0;
    // Returns the size of the root folder, i.e. the total used space, but also sets each folder's size to that of all its sub directories combined
    int rootsize = getDirSize(root, sum);
    std::cout << "Task 1 - Sum of folder sizes below 100000: " << sum << std::endl
              << "Task 2 - Smallest folder size that frees enough space: " << getMinDelete(root, req - total + rootsize, rootsize) << std::endl
              << "Execution time: " << double(clock() - time) / CLOCKS_PER_SEC << std::endl;
    return 0;
}
