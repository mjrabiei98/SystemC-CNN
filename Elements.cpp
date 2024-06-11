#include "Elements.h"



void mux_5to1::eval(){
	switch (sel.read().to_uint()) {
	case 0:
		out.write(a.read());
		break;
	case 1:
		out.write(b.read());
		break;
	case 2:
		out.write(c.read());
		break;
	case 3:
		out.write(d.read());
		break;
	case 4:
		out.write(e.read());
		break;
	default:
		out.write(a.read());
		break;
	}
}


void mux::eval() {
	switch (sel.read().to_uint()) {
	case 0:
		out.write(a.read());
		break;
	case 1:
		out.write(b.read());
		break;
	case 2:
		out.write(c.read());
		break;
	case 3:
		out.write(d.read());
		break;
	default:
		out.write(a.read());
		break;
	}
}


void kernel_mux::eval() {
	if (i.read() == "00000000" && j.read() == "00000000") {
		output.write(a.read());
	}
	else if (i.read() == "00000001" && j.read() == "00000000") {
		output.write(b.read());
	}
	else if (i.read() == "00000010" && j.read() == "00000000") {
		output.write(c.read());
	}
	else if (i.read() == "00000000" && j.read() == "00000001") {
		output.write(d.read());
	}
	else if (i.read() == "00000001" && j.read() == "00000001") {
		output.write(e.read());
	}
	else if (i.read() == "00000010" && j.read() == "00000001") {
		output.write(f.read());
	}
	else if (i.read() == "00000000" && j.read() == "00000010") {
		output.write(g.read());
	}
	else if (i.read() == "00000001" && j.read() == "00000010") {
		output.write(h.read());
	}
	else if (i.read() == "00000010" && j.read() == "00000010") {
		output.write(k.read());
	}
	else {
		output.write("00000000");
	}
}


void mult::eval() {
	sc_int<input_size> a_signed = a.read().to_int();
	sc_int<input_size> b_signed = b.read().to_int();
	sc_int<2 * input_size> temp_signed = a_signed * b_signed;

	temp.write(temp_signed);
	output.write(temp.read().range(input_size - 1, 0));
}



void adder::eval() {
	sc_int<input_size> a_signed = a.read().to_int();
	sc_int<input_size> b_signed = b.read().to_int();
	sc_int<input_size> result_signed = a_signed + b_signed;

	output.write(result_signed);
}



void counter::do_count() {
	if (rst.read() == sc_logic_1) {
		counter_out.write(0);
		cout.write(sc_logic_0);
	}
	else if ((clk->event() && (clk == '1')) && en.read() == '1') {
		std::cout << "sdafsdfas";
		if (counter_out.read().to_uint() + 1 < counter_limit) {
			counter_out.write(counter_out.read().to_uint() + 1);
			cout.write(sc_logic_0);
		}
		else {
			counter_out.write(0);
			cout.write(sc_logic_1);
		}
	}
}

void maxpool::do_maxpool() {
	sc_lv<data_width> max_var = a.read();

	if (b.read().to_uint() > max_var.to_uint()) {
		max_var = b.read();
	}

	if (c.read().to_uint() > max_var.to_uint()) {
		max_var = c.read();
	}

	if (d.read().to_uint() > max_var.to_uint()) {
		max_var = d.read();
	}

	output.write(max_var);
}



void relu::do_relu() {
	sc_int<data_width> a_signed = a.read().to_int();
	sc_int<data_width> b_signed = b.read().to_int();
	sc_int<data_width> c_signed = c.read().to_int();
	sc_int<data_width> d_signed = d.read().to_int();

	d1.write(a_signed < 0 ? 0 : a_signed);
	d2.write(b_signed < 0 ? 0 : b_signed);
	d3.write(c_signed < 0 ? 0 : c_signed);
	d4.write(d_signed < 0 ? 0 : d_signed);
}



void resualt::do_compare() {
	output.write("000");

	if (a.read().to_uint() > b.read().to_uint() && a.read().to_uint() > c.read().to_uint()) {
		output.write("001");
	}

	if (b.read().to_uint() > a.read().to_uint() && b.read().to_uint() > c.read().to_uint()) {
		output.write("010");
	}

	if (c.read().to_uint() > b.read().to_uint() && c.read().to_uint() > a.read().to_uint()) {
		output.write("100");
	}
}



