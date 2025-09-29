#include <iostream>
#include "classes/Pool.hpp"

class Human
{
public:
    int age;
    std::string name;
};

int main(void)
{
    Pool<Human> p(20);
    std::cout << "Check all the objects and set as using." << std::endl;
    for (int i = 0; i < p.size(); i++)
    {
        std::cout << (p.getNextObject()) << std::endl;
    }
    p.setUnused(0);
    std::cout << "Post full check:" << std::endl;
    std::cout << p.getNextObject() << std::endl;
}
