#ifndef PF_H
#define PF_H

#include <systemc.h>
#include "convolution.h"
#include "Elements.h"
#include "RAM.h"

// Define the kernel_array and bias_array types
typedef sc_lv<8> kernel_type[3][9];
typedef sc_lv<8> bias_array[3];

SC_MODULE(patter_finder) {
	// Parameters
	static const int data_width = 8;
	static const int number_of_conv = 3;
	static const int kernel_size = 3;
	/*kernel_type kernels_array = {
		{
			"00000000", "00000001", "00000000",
			"00000001", "00000001", "00000001",
			"00000000", "00000001", "00000000"
		},
		{
			"00000001", "00000001", "00000001",
			"00000001", "00000000", "00000000",
			"00000001", "00000001", "00000001"
		},
		{
			"00000001", "00000001", "00000001",
			"00000000", "00000001", "00000000",
			"00000000", "00000001", "00000000"
		}
	};
	bias_array biases = { "11111111", "11111110", "11111110" };
	sc_lv<8> image_size = "00000100";*/

	kernel_type kernels_array;
	bias_array biases;
	sc_lv<8> image_size;


	// Ports
	sc_in<sc_logic> clk, rst, start, write_ram;
	sc_in<sc_lv<data_width>> data_in;
	sc_in<sc_lv<data_width>> address_in_wr;
	sc_out<sc_logic> done;
	sc_out<sc_lv<3>> output_pattern;

	// Internal signals
	sc_signal<sc_lv<data_width>> ram_data_out;
	sc_signal<sc_logic> write_en, read_en;
	sc_signal<sc_lv<data_width>> address_out;
	sc_signal<sc_lv<data_width>> convs_output[number_of_conv][4];
	sc_signal<sc_lv<data_width>> relus_output[number_of_conv][4];
	sc_signal<sc_lv<data_width>> maxpools_output[number_of_conv];

	// Submodule instances
	ram* ram1;
	convolution* conv[number_of_conv];
	relu* relu_units[number_of_conv];
	maxpool* maxpool_units[number_of_conv];
	resualt* result_unit;

	// Constructor
	SC_CTOR(patter_finder) {
		// Instantiate RAM module
		ram1 = new ram("ram1");
		ram1->rst(rst);
		ram1->address_in_read(address_out);
		ram1->data_in(data_in);
		ram1->address_in_wr(address_in_wr);
		ram1->data_out(ram_data_out);
		ram1->write_en(write_en);
		ram1->read_en(read_en);

		// Instantiate convolution, relu, and maxpool modules
		for (int i = 0; i < number_of_conv; ++i) {
			conv[i] = new convolution("conv" + i);
			conv[i]->clk(clk);
			conv[i]->rst(rst);
			conv[i]->start(start);
			conv[i]->data_in(ram_data_out);
			conv[i]->data_out1(convs_output[i][0]);
			conv[i]->data_out2(convs_output[i][1]);
			conv[i]->data_out3(convs_output[i][2]);
			conv[i]->data_out4(convs_output[i][3]);
			conv[i]->done(done);
			conv[i]->address_out(address_out);

			relu_units[i] = new relu("relu" + i);
			relu_units[i]->a(convs_output[i][0]);
			relu_units[i]->b(convs_output[i][1]);
			relu_units[i]->c(convs_output[i][2]);
			relu_units[i]->d(convs_output[i][3]);
			relu_units[i]->d1(relus_output[i][0]);
			relu_units[i]->d2(relus_output[i][1]);
			relu_units[i]->d3(relus_output[i][2]);
			relu_units[i]->d4(relus_output[i][3]);

			maxpool_units[i] = new maxpool("maxpool" + i);
			maxpool_units[i]->a(relus_output[i][0]);
			maxpool_units[i]->b(relus_output[i][1]);
			maxpool_units[i]->c(relus_output[i][2]);
			maxpool_units[i]->d(relus_output[i][3]);
			maxpool_units[i]->output(maxpools_output[i]);
		}

		// Instantiate result unit
		result_unit = new resualt("result_unit");
		result_unit->a(maxpools_output[0]);
		result_unit->b(maxpools_output[1]);
		result_unit->c(maxpools_output[2]);
		result_unit->output(output_pattern);
	}

	patter_finder(sc_module_name name, kernel_type kernels_array, bias_array biases, sc_lv<8> image_size){
	
	}

};

#endif
