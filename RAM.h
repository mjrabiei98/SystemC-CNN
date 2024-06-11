#ifndef RAM_H
#define RAM_H



#include <systemc.h>
#include <fstream>
#include <iostream>
#include <string>

SC_MODULE(ram) {
	// Parameters
	static const int DATA_WIDTH = 8;
	static const int number_of_rows = 16;

	// Ports
	sc_in<bool> rst;
	sc_in<sc_lv<DATA_WIDTH>> data_in;
	sc_in<sc_lv<DATA_WIDTH>> address_in_wr, address_in_read;
	sc_in<bool> write_en, read_en;
	sc_out<sc_lv<DATA_WIDTH>> data_out;

	// Memory array
	sc_lv<DATA_WIDTH> mem[number_of_rows];

	// Internal signals
	sc_signal<bool> init_done;

	// Process method for initialization and writing to memory
	void do_ram();

	// Process method for reading from memory
	void do_read();

	// Constructor
	SC_CTOR(ram) {
		SC_METHOD(do_ram);
		sensitive << rst << write_en << address_in_wr << data_in;
		SC_METHOD(do_read);
		sensitive << address_in_read << read_en;
		init_done.write(false);
	}
};


#endif