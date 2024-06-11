#ifndef TB_H
#define TB_H
#include <systemc.h>
#include "pattern_finder.h"
#include <iostream>

SC_MODULE(testbench) {
	// Signals
	/*sc_signal<sc_logic> start;
	sc_signal<sc_logic> clk;
	sc_signal<sc_logic> rst;
	sc_signal<sc_logic> write_ram;
	sc_signal<sc_lv<8>> data_in;
	sc_signal<sc_lv<8>> address_in_wr;
	sc_signal<sc_logic> done;
	sc_signal<sc_lv<3>> output_pattern;*/


	sc_signal<sc_logic> start;
	sc_signal<sc_logic> clk;
	sc_signal<sc_logic> en;
	sc_signal<sc_logic> rst;
	sc_signal<sc_lv<8>> a, b, c, d, e;
	sc_signal<sc_lv<3>> sel;
	sc_signal<sc_lv<8>> out;

	sc_signal<sc_lv<8>> counter_out;
	sc_signal<sc_logic> cout;

	sc_signal<sc_lv<16>> m;
	sc_signal<sc_lv<16>> q;


	sc_signal<sc_lv<8>> data_in;
	sc_signal<sc_lv<8>> address_in_wr, address_in_read;
	sc_signal<sc_logic> write_en, read_en;
	sc_signal<sc_lv<8>> data_out;




	// Instance of the patter_finder module
	//patter_finder* p_finder;
	mux_5to1* m1;
	counter* c1;
	ram* ram1;

	reg<16>* r1;
	

	// Constructor
	SC_CTOR(testbench) {
		// Instantiate the patter_finder module
		/*p_finder = new patter_finder("p_finder");
		p_finder->clk(clk);
		p_finder->rst(rst);
		p_finder->start(start);
		p_finder->write_ram(write_ram);
		p_finder->data_in(data_in);
		p_finder->address_in_wr(address_in_wr);
		p_finder->done(done);
		p_finder->output_pattern(output_pattern);*/

		m1 = new mux_5to1("mux1");

		m1->a(a);
		m1->b(b);
		m1->c(c);
		m1->d(d);
		m1->e(e);
		m1->sel(sel);
		m1->out(out);

		c1 = new counter("counter1",6);
		c1->clk(clk);
		c1->rst(rst);
		c1->en(en);
		c1->counter_out(counter_out);
		c1->cout(cout);

		

		r1 = new reg<16>("register1");
		r1->clk(clk);
		r1->rst(rst);
		r1->en(en);
		r1->d(m);
		r1->q(q);

		ram1 = new ram("ram_1");
		/*
		sc_in<sc_lv<8>> data_in;
	sc_in<sc_lv<8>> address_in_wr, address_in_read;
	sc_in<sc_logic> write_en, read_en;
	sc_out<sc_lv<8>> data_out;*/
		ram1->rst(rst);
		ram1->data_in(data_in);
		ram1->address_in_wr(address_in_wr);
		ram1->address_in_read(address_in_read);
		ram1->write_en(write_en);
		ram1->read_en(read_en);
		ram1->data_out(data_out);



		// Initialize signals
		/*start.write(false);
		clk.write(false);
		rst.write(false);
		write_ram.write(false);
		data_in.write("00000000");
		address_in_wr.write("00000000");*/

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

