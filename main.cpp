#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <vector>

#include "PPS_from_fpga/Include/receiver.h"

int main()
{
    std::cout.precision(17);
//    uint32_t offset1 = 0x14;
//    std::cout << "ARM gdb" << std::endl;

    receiver a(1,5,6,0,0,100,27);
    receiver b(2,11,12,0,0,100,28);
    receiver c(3,17,18,0,0,10,29);
    receiver d(4,23,24,0,0,100,30);

    a.open_file();
    b.open_file();
    c.open_file();
    d.open_file();


    for(int i = 0; i < 72000 ; i++)
    {
//        std::cout << "\nIteration = " << i << std::endl;
//        for (auto &s: v)
//        {
//            s.try_get_new_pps();
//        }

        a.try_get_new_pps();
        b.try_get_new_pps();
        c.try_get_new_pps();
        d.try_get_new_pps();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }


    return 0;
}