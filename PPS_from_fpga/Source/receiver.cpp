//
// Created by nf010 on 17.06.2022.
//
#include "PPS_from_fpga/Include/receiver.h"

receiver::receiver( int valnum, uint32_t offset_reg, uint32_t offset_reg2, uint64_t newvalpps,uint32_t oldvalpps,uint32_t time_val, uint32_t offset_reg3) :
                    num(valnum), pps_axi(0xA00F0000, 8), log_file(std::string("log_file") + std::to_string(valnum) + std::string(".bin"))
{
    const uint32_t freq_plis = 769996910;
    dur_reg = pps_axi.GetAddr() + offset_reg3;
    time_pps = 0.8*time_val*0.001*freq_plis;
    *dur_reg = time_pps;
    auto reset_ptr = pps_axi.GetAddr();
    *reset_ptr = 1;
    *reset_ptr = 0;
    std::cout << std::endl << "Receiver #" << num << " constructor"  << std::endl;

    pps_number = oldvalpps;
    fpga_clock = newvalpps;
    pulse_num_ptr = pps_axi.GetAddr() + offset_reg;
    fpga_clock_ptr = reinterpret_cast<volatile uint64_t *>(pps_axi.GetAddr() + offset_reg2);
    uint32_t pulse_number = *pulse_num_ptr;
    std::cout << "Receiver. Pulse number = " << pulse_number << std::endl
                << "Address Pulse num ptr = " << pulse_num_ptr << std::endl;
}

//    void receiver::Read_File()
//    {
//        using data_type_number = uint32_t;
//        data_type_number s1;
////        buffer_num[50];
//        using data_type = uint64_t;
//        data_type s2;
////        buffer_data[50];
//        ifstream myFile ("log_file1.bin", ios::in | ios::binary);
////        int k = 0;
////        while (!myFile.eof())
//            for (int k = 0; k < 50; k++)
//            {
//                    myFile.seekg(12*k, ios::beg);
//                    myFile.read((char *) &s1, 1 * sizeof(data_type_number));
//                    myFile.seekg(12*k+4, ios::beg);
//                    myFile.read((char *) &s2, 1 * sizeof(data_type));
////                    buffer_num[k] = s1;
////                    buffer_data[k] = s2;
//                    std::cout << "buffer_num = " << s1 /*buffer_num[k]*/ << endl;
//                    std::cout << "buffer_data = " << s2 /*buffer_num[k]*/ << endl;
//            }
//        myFile.close();
//
//    }

    void receiver::open_file()
    {
        std::string name = "log_file";
        std::string number = std::to_string(num);
        std::string ext = ".bin";
        std::string path = name + number + ext;
        ofstream fout;
        fout.open(path, ios_base::binary);
    }

    void receiver::write_to_file()
    {
        std::string name = "log_file";
        std::string number = std::to_string(num);
        std::string ext = ".bin";
        std::string path = name + number + ext;
        log_file.write((char *) &pps_number, sizeof(uint64_t));
        log_file.write((char *) &fpga_clock, sizeof(uint64_t));
    }

    void receiver::try_get_new_pps()
    {

        uint32_t pulse_number = *pulse_num_ptr;

        if (pps_number != pulse_number)
        {
            double prev_fpga_clock = fpga_clock;
            fpga_clock = *fpga_clock_ptr;
            pps_number = pulse_number;
            std::cout << "\nReceiver #" << num <<  "\n"
                        << "Past time = " << (fpga_clock - prev_fpga_clock) / 769997067 << "\n"
                        << "newpps ppsnum = " << pps_number <<  "\n"
                        << "newpps ppsndata = " << fpga_clock <<  "\n";

            write_to_file();

        }
    }




