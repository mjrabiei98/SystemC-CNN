#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <systemc.h>

SC_MODULE(mux_5to1) {
	sc_in<sc_lv<8>> a, b, c, d, e;
	sc_in<sc_lv<3>> sel;
	sc_out<sc_lv<8>> out;

	void eval();

	SC_CTOR(mux_5to1) {
		SC_METHOD(eval);
		sensitive << a << b << c << d << e << sel;
	}
};


SC_MODULE(mux) {
	
	sc_in<sc_lv<8>> a, b, c, d;   
	sc_in<sc_lv<2>> sel;          
	sc_out<sc_lv<8>> out;         

	void eval();

	SC_CTOR(mux) {
		SC_METHOD(eval);
		sensitive << a << b << c << d << sel;
	}
};


SC_MODULE(kernel_mux) {
	// Parameters
	static const int input_size = 8;  // Setting the input size as 8 bits

	// Ports
	sc_in<sc_lv<input_size>> a, b, c, d, e, f, g, h, k;
	sc_in<sc_lv<input_size>> i, j;
	sc_out<sc_lv<input_size>> output;

	// Process method
	void eval();

	// Constructor
	SC_CTOR(kernel_mux) {
		SC_METHOD(eval);
		sensitive << a << b << c << d << e << f << g << h << k << i << j;
	}
};



SC_MODULE(mult) {

	static const int input_size = 8;


	sc_in<sc_lv<input_size>> a, b;
	sc_out<sc_lv<input_size>> output;


	sc_signal<sc_lv<2 * input_size>> temp;


	void eval();


	SC_CTOR(mult) {
		SC_METHOD(eval);
		sensitive << a << b;
	}
};



SC_MODULE(adder) {

	static const int input_size = 8;


	sc_in<sc_lv<input_size>> a, b;
	sc_out<sc_lv<input_size>> output;


	void eval();


	SC_CTOR(adder) {
		SC_METHOD(eval);
		sensitive << a << b;
	}
};




SC_MODULE(counter) {
	static const int counter_size = 8;
	int counter_limit;


	sc_in<sc_logic> clk, rst, en;
	sc_out<sc_lv<counter_size>> counter_out;
	sc_out<sc_logic> cout;


	void do_count();


	SC_CTOR(counter) {
		SC_METHOD(do_count);
			sensitive << clk << rst;
	}
	counter(sc_module_name name, int size) : sc_module(name), counter_limit(size) {
		SC_METHOD(do_count);
		sensitive << clk << rst;
	}

};


SC_MODULE(maxpool) {
	
	static const int data_width = 8;

	
	sc_in<sc_lv<data_width>> a, b, c, d;
	sc_out<sc_lv<data_width>> output;

	
	void do_maxpool();

	
	SC_CTOR(maxpool) {
		SC_METHOD(do_maxpool);
		sensitive << a << b << c << d;
	}
};


SC_MODULE(relu) {
	
	static const int data_width = 8;

	
	sc_in<sc_lv<data_width>> a, b, c, d;
	sc_out<sc_lv<data_width>> d1, d2, d3, d4;

	
	void do_relu();

	
	SC_CTOR(relu) {
		SC_METHOD(do_relu);
		sensitive << a << b << c << d;
	}
};



SC_MODULE(resualt) {
	
	static const int data_width = 8;

	
	sc_in<sc_lv<data_width>> a, b, c;
	sc_out<sc_lv<3>> output;

	
	void do_compare();

	
	SC_CTOR(resualt) {
		SC_METHOD(do_compare);
		sensitive << a << b << c;
	}
};




//SC_MODULE(reg) {
//	// Parameters
//	int register_size;
//
//	// Ports
//	sc_in<sc_logic> clk, rst, en;
//	sc_in<sc_lv<16>> d;
//	sc_out<sc_lv<16>> q;
//
//	// Process method
//	void process_reg();
//
//	// Constructor
//	SC_CTOR(reg) : register_size(16) {
//		SC_METHOD(process_reg);
//		sensitive << clk << rst;
//	}
//
//	// Overloaded constructor for parameterized register size
//	SC_HAS_PROCESS(reg);
//	reg(sc_module_name name, int reg_size) : sc_module(name), register_size(reg_size) {
//		SC_METHOD(process_reg);
//		sensitive << clk.pos() << rst;
//	}
//};

template<int SIZE>
SC_MODULE(reg) {
	// Ports
	sc_in<sc_logic> clk, rst, en;
	sc_in<sc_lv<SIZE>> d;
	sc_out<sc_lv<SIZE>> q;

	// Process method
	void process_reg() {
		if (rst.read() == '1') {
			q.write(0);
		}
		else if ((clk->event() && clk.read() == '1') && en.read() == '1') {
			q.write(d.read());
		}
		//std::cout << name() << "d val = " << d << "reg_value = " << q << endl;
	}

	// Constructor
	SC_CTOR(reg) {
		SC_METHOD(process_reg);
		sensitive << clk << rst;
	}
};



#endif