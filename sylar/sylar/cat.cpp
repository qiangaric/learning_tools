#include "cat.h"

Cat::Cat(std::string name) : name(name)
{
    std::cout << "构造函数 : " << name << std::endl;
}

Cat::~Cat()
{
    std::cout << "析构函数 : " << name << std::endl;
}