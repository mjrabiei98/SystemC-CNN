#ifndef TB_H
#define TB_H
#include <systemc.h>
#include "pattern_finder.h"
#include <iostream>

SC_MODULE(testbench) {

	
	sc_signal<sc_lv<8>> bias_value_conv;
	sc_signal<sc_lv<8>> image_size_conv;
	sc_signal<sc_lv<8>> kernet_1_conv, kernet_2_conv, kernet_3_conv, kernet_4_conv, kernet_5_conv, kernet_6_conv, kernet_7_conv, kernet_8_conv, kernet_9_conv;

	// Ports
	sc_signal<sc_lv<8>> data_in_conv;
	sc_signal<sc_lv<8>> data_out1_conv, data_out2_conv, data_out3_conv, data_out4_conv;
	sc_signal<sc_logic> done_conv;
	sc_signal<sc_lv<8>> address_out_conv, data_in, address_in_wr;

	ram* ram1;
	convolution* conv;

	sc_signal<sc_logic> start;
	sc_signal<sc_logic> clk;
	sc_signal<sc_logic> rst;
	sc_signal<sc_logic> done, write_en, read_en;

	// Constructor
	SC_CTOR(testbench) {

		ram1 = new ram("ram1");
		ram1->clk(clk);
		ram1->rst(rst);
		ram1->address_in_read(address_out_conv);
		ram1->data_in(data_in);
		ram1->address_in_wr(address_in_wr);
		ram1->data_out(data_in_conv);
		ram1->write_en(write_en);
		ram1->read_en(read_en);

		conv = new convolution("conv1");
		conv->bias_value(bias_value_conv);
		conv->image_size(image_size_conv);
		conv->kernet_1(kernet_1_conv);
		conv->kernet_2(kernet_2_conv);
		conv->kernet_3(kernet_3_conv);
		conv->kernet_4(kernet_4_conv);
		conv->kernet_5(kernet_5_conv);
		conv->kernet_6(kernet_6_conv);
		conv->kernet_7(kernet_7_conv);
		conv->kernet_8(kernet_8_conv);
		conv->kernet_9(kernet_9_conv);
		conv->rst(rst);
		conv->clk(clk);
		conv->start(start);
		conv->data_in(data_in_conv);
		conv->data_out1(data_out1_conv);
		conv->data_out2(data_out2_conv);
		conv->data_out3(data_out3_conv);
		conv->data_out4(data_out4_conv);
		conv->done(done_conv);
		conv->address_out(address_out_conv);


		// Initialize signals
		start.write(SC_LOGIC_0);
		clk.write(SC_LOGIC_0);
		rst.write(SC_LOGIC_0);
		data_in.write("00000000");
		image_size_conv.write("00000100");
		bias_value_conv.write("00000100");
		address_in_wr.write("00000001");
		kernet_1_conv.write("00000000");
		kernet_2_conv.write("00000001");
		kernet_3_conv.write("00000001");
		kernet_4_conv.write("00000001");
		kernet_5_conv.write("00000000");
		kernet_6_conv.write("00000001");
		kernet_7_conv.write("00000000");
		kernet_8_conv.write("00000000");
		kernet_9_conv.write("00000000");

		// Register processes
		SC_THREAD(resetting);
		SC_THREAD(clocking);
		SC_THREAD(inGenerating);
		SC_THREAD(displaying);
			sensitive << clk;
		//sensitive << done;
	}

	void resetting();
	void clocking();
	void inGenerating();
	void displaying();
		
};


#endif

