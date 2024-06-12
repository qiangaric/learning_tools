#include <iostream>
#include <memory>
#include "cat.h"
using namespace std;

int main(int argc, char const *argv[])
{

    std::shared_ptr<int> i_p_1 = make_shared<int>(10);
    // cout << "value: " << *i_p_1 << endl;
    cout << "use count : " << i_p_1.use_count() << endl;

    cout << "------test-----" << endl;
    return 0;
}
