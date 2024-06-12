#include "RAM.h"


void ram::do_ram() {
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
	std::cout << "sucsess reading file and initializing ram" << endl;
	input_file.close();
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
	std::cout << "address = " << address << "data out = " << data_out << endl;
}