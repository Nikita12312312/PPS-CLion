//
// Created by nf010 on 17.06.2022.
//

#ifndef MY_FIRST_PROJECT_RECEIVER_H
#define MY_FIRST_PROJECT_RECEIVER_H
#include <string>
#include <cstdint>
#include <iostream>
#include <fstream>
#include "System/Interfaces/AxiLiteInterface.h"

using namespace std;

class receiver
{
public:
    int num;
    uint64_t pps_number;
    uint32_t time_pps;
    volatile uint32_t *dur_reg;
    uint64_t fpga_clock;
    AxiLiteInterface pps_axi;
    volatile uint32_t *pulse_num_ptr;
    volatile uint64_t *fpga_clock_ptr;
    ofstream log_file;

    receiver(int valnum, uint32_t memory_offset_pulse_number_32, uint32_t memory_offset_data, uint64_t newvalpps,
             uint32_t oldvalpps, uint32_t time_val,uint32_t memory_offset_duration);
    void try_get_new_pps();
    void write_to_file();
    void open_file();
//    void Read_File();


};

#endif //MY_FIRST_PROJECT_RECEIVER_H
