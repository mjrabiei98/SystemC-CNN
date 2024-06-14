#ifndef RAM_H
#define RAM_H



#include <systemc.h>
#include <fstream>
#include <iostream>
#include <string>

SC_MODULE(ram) {
	static const int DATA_WIDTH = 8;
	static const int number_of_rows = 16;


	sc_in<sc_logic> clk;
	sc_in<sc_logic> rst;
	sc_in<sc_lv<DATA_WIDTH>> data_in;
	sc_in<sc_lv<DATA_WIDTH>> address_in_wr, address_in_read;
	sc_in<sc_logic> write_en, read_en;
	sc_out<sc_lv<DATA_WIDTH>> data_out;

	sc_lv<DATA_WIDTH> mem[number_of_rows];

	void initial_ram();

	void do_read();


	SC_CTOR(ram) {
		SC_METHOD(initial_ram);
		SC_METHOD(do_read);
		sensitive << address_in_read << read_en;
	}

};


#endif
