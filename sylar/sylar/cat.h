#ifndef CAT_H
#define CAT_H
#include <string>
#include <iostream>

class Cat
{
private:
    std::string name{"MIni"};

public:
    Cat(std::string name);
    // Cat() = default;
    ~Cat();
    void cat_info()
        const
    {
        std::cout << "cat info name : " << name << std::endl;
    };
    std::string get_info()
        const
    {
        return name;
    };

    void set_cat_name(const std::string &name)
    {
        this->name = name;
    }
};

#endif