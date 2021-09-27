#include <iostream>
#include "classes.h"

int main()
{
    Room r;
    std::vector<Bachelord*> bache_vec;
    std::vector<Master*> master_vec;
    Speaker s("Speaker");
    for (unsigned int i = 0; i < 10; i++)
    {
        bache_vec.push_back(new Bachelord("Bachelord#" + (i + '\0'), Notebook(10)));
        r.let_participant(bache_vec[i]);
        master_vec.push_back(new Master("Master#" + (i + '\0')));
        r.let_participant(master_vec[i]);
    }
    for (int i = 0; i < 15; i++)
    {
        s.speak(r);
    }
    std::cout << "Time for check writings!\n";
    bache_vec[1]->get_notebook().print();
}
