#include "RAM.h"


void ram::do_ram() {
	if (init_done.read() == false) {
		std::ifstream input_file("input_paterns/input6.txt");
		if (!input_file.is_open()) {
			SC_REPORT_ERROR("RAM", "Failed to open input file.");
			return;
		}
		std::string line;
		int i = 0;
		while (i < number_of_rows && std::getline(input_file, line)) {
			if (line.length() == DATA_WIDTH) {
				sc_lv<DATA_WIDTH> text_data(line.c_str());
				mem[i] = text_data;
				i++;
			}
		}
		input_file.close();
		init_done.write(true);
	}
	else if (write_en.read() == true) {
		int address = address_in_wr.read().to_uint();
		if (address < number_of_rows) {
			mem[address] = data_in.read();
		}
	}
}

// Process method for reading from memory
void ram::do_read() {
	int address = address_in_read.read().to_uint();
	if (address < number_of_rows) {
		data_out.write(mem[address]);
	}
	else {
		data_out.write(sc_lv<DATA_WIDTH>("00000000")); // Default value if address is out of range
	}
}