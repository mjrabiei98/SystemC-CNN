#ifndef CN_H
#define CN_H


#include <systemc.h>
#include "Elements.h"

//// Assuming the counter, mux, adder, mult, reg, and kernel_mux modules are already defined
//
//SC_MODULE(convolution_datapath) {
//	// Parameters
//	sc_lv<8> bias_value;
//	sc_lv<8> image_size;
//	sc_lv<8> kernet_1, kernet_2, kernet_3, kernet_4, kernet_5, kernet_6, kernet_7, kernet_8, kernet_9;
//	int data_width;
//
//	// Ports
//	sc_in<sc_logic> clk, rst, en_cti, en_ctj, en_ctx, en_cty, temp_reg_en, address_reg_en, out1_reg_en, out2_reg_en, out3_reg_en, out4_reg_en;
//	sc_in<sc_lv<8>> data_in;
//	sc_out<sc_lv<8>> data_out1, data_out2, data_out3, data_out4;
//	sc_out<sc_logic> counter_i_cout, counter_j_cout, counter_x_cout, counter_y_cout;
//	sc_in<sc_lv<2>> adder_mux_1_sel;
//	sc_in<sc_lv<3>> adder_mux_2_sel;
//	sc_in<sc_lv<2>> adr_reg_mux_sel, mult_mux_1_sel, mult_mux_2_sel;
//	sc_out<sc_lv<8>> cx_out, cy_out, ci_out, cj_out;
//	sc_out<sc_lv<8>> address_out;
//	sc_in<sc_logic> rst_temp;
//
//	// Internal signals
//	sc_signal<sc_lv<8>> counter_i_out, counter_j_out, counter_x_out, counter_y_out, kernel_mux_out;
//	sc_signal<sc_lv<8>> adder_mux_1_out, adder_mux_2_out, adr_reg_mux_out;
//	sc_signal<sc_lv<8>> mult_out, adder_out, address_reg_out, mult_mux_1_out, mult_mux_2_out, temp_reg_out;
//	sc_signal<sc_logic> cnt_i_cout, cnt_x_cout;
//
//	// Submodule declarations
//	counter* counter_i;
//	counter* counter_j;
//	counter* counter_x;
//	counter* counter_y;
//	mux* adder_mux_1;
//	mux* adder_mux_2;
//	mux* mult_mux_1;
//	mux* mult_mux_2;
//	mux* adr_reg_mux;
//	adder* adr;
//	adder* mult;
//	reg<8>* temp_reg;
//	reg<8>* address_reg;
//	reg<8>* out1_reg;
//	reg<8>* out2_reg;
//	reg<8>* out3_reg;
//	reg<8>* out4_reg;
//	kernel_mux* kernel_mux1;
//
//	void instantiate_modules() {
//		// Instantiate counters
//		counter_i = new counter("counter_i");
//		counter_i->clk(clk);
//		counter_i->rst(rst);
//		counter_i->en(en_cti);
//		counter_i->counter_out(counter_i_out);
//		counter_i->cout(cnt_i_cout);
//
//		counter_j = new counter("counter_j");
//		counter_j->clk(clk);
//		counter_j->rst(rst);
//		counter_j->en(en_ctj);
//		counter_j->counter_out(counter_j_out);
//		counter_j->cout(counter_j_cout);
//
//		counter_x = new counter("counter_x");
//		counter_x->clk(clk);
//		counter_x->rst(rst);
//		counter_x->en(en_ctx);
//		counter_x->counter_out(counter_x_out);
//		counter_x->cout(cnt_x_cout);
//
//		counter_y = new counter("counter_y");
//		counter_y->clk(clk);
//		counter_y->rst(rst);
//		counter_y->en(en_cty);
//		counter_y->counter_out(counter_y_out);
//		counter_y->cout(counter_y_cout);
//
//		// Instantiate muxes
//		adder_mux_1 = new mux("adder_mux_1");
//		adder_mux_1->a(bias_value);
//		adder_mux_1->b(counter_j_out);
//		adder_mux_1->c(temp_reg_out);
//		adder_mux_1->d(address_reg_out);
//		adder_mux_1->sel(adder_mux_1_sel);
//		adder_mux_1->out(adder_mux_1_out);
//
//		adder_mux_2 = new mux("adder_mux_2");
//		adder_mux_2->a(counter_x_out);
//		adder_mux_2->b(counter_y_out);
//		adder_mux_2->c(mult_out);
//		adder_mux_2->d(counter_i_out);
//		adder_mux_2->e(bias_value);
//		adder_mux_2->sel(adder_mux_2_sel);
//		adder_mux_2->out(adder_mux_2_out);
//
//		mult_mux_1 = new mux("mult_mux_1");
//		mult_mux_1->a(address_reg_out);
//		mult_mux_1->b(kernel_mux_out);
//		mult_mux_1->c("ZZZZZZZZ");
//		mult_mux_1->d("ZZZZZZZZ");
//		mult_mux_1->sel(mult_mux_1_sel);
//		mult_mux_1->out(mult_mux_1_out);
//
//		mult_mux_2 = new mux("mult_mux_2");
//		mult_mux_2->a(image_size);
//		mult_mux_2->b(data_in);
//		mult_mux_2->c("ZZZZZZZZ");
//		mult_mux_2->d("ZZZZZZZZ");
//		mult_mux_2->sel(mult_mux_2_sel);
//		mult_mux_2->out(mult_mux_2_out);
//
//		adr_reg_mux = new mux("adr_reg_mux");
//		adr_reg_mux->a(adder_out);
//		adr_reg_mux->b(mult_out);
//		adr_reg_mux->c("ZZZZZZZZ");
//		adr_reg_mux->d("ZZZZZZZZ");
//		adr_reg_mux->sel(adr_reg_mux_sel);
//		adr_reg_mux->out(adr_reg_mux_out);
//
//		// Instantiate adders and multipliers
//		adr = new adder("adr");
//		adr->a(adder_mux_1_out);
//		adr->b(adder_mux_2_out);
//		adr->out(adder_out);
//
//		mult = new adder("mult");
//		mult->a(mult_mux_1_out);
//		mult->b(mult_mux_2_out);
//		mult->out(mult_out);
//
//		// Instantiate registers
//		temp_reg = new reg("temp_reg");
//		temp_reg->clk(clk);
//		temp_reg->rst(rst_temp);
//		temp_reg->en(temp_reg_en);
//		temp_reg->d(adder_out);
//		temp_reg->q(temp_reg_out);
//
//		address_reg = new reg("address_reg");
//		address_reg->clk(clk);
//		address_reg->rst(rst);
//		address_reg->en(address_reg_en);
//		address_reg->d(adr_reg_mux_out);
//		address_reg->q(address_reg_out);
//
//		out1_reg = new reg("out1_reg");
//		out1_reg->clk(clk);
//		out1_reg->rst(rst);
//		out1_reg->en(out1_reg_en);
//		out1_reg->d(temp_reg_out);
//		out1_reg->q(data_out1);
//
//		out2_reg = new reg("out2_reg");
//		out2_reg->clk(clk);
//		out2_reg->rst(rst);
//		out2_reg->en(out2_reg_en);
//		out2_reg->d(temp_reg_out);
//		out2_reg->q(data_out2);
//
//		out3_reg = new reg("out3_reg");
//		out3_reg->clk(clk);
//		out3_reg->rst(rst);
//		out3_reg->en(out3_reg_en);
//		out3_reg->d(temp_reg_out);
//		out3_reg->q(data_out3);
//
//		out4_reg = new reg("out4_reg");
//		out4_reg->clk(clk);
//		out4_reg->rst(rst);
//		out4_reg->en(out4_reg_en);
//		out4_reg->d(temp_reg_out);
//		out4_reg->q(data_out4);
//
//		// Instantiate kernel mux
//		kernel_mux1 = new kernel_mux("knel_mux1");
//		kernel_mux1->a(kernet_1);
//		kernel_mux1->b(kernet_2);
//		kernel_mux1->c(kernet_3);
//		kernel_mux1->d(kernet_4);
//		kernel_mux1->e(kernet_5);
//		kernel_mux1->f(kernet_6);
//		kernel_mux1->g(kernet_7);
//		kernel_mux1->h(kernet_8);
//		kernel_mux1->i(kernet_9);
//		kernel_mux1->sel_i(counter_i_out);
//		kernel_mux1->sel_j(counter_j_out);
//		kernel_mux1->out(kernel_mux_out);
//	}
//
//	SC_CTOR(convolution_datapath)
//		: bias_value("00000000"),
//		image_size("00000100"),
//		kernet_1("00000000"), kernet_2("00000000"), kernet_3("00000000"),
//		kernet_4("00000000"), kernet_5("00000000"), kernet_6("00000000"),
//		kernet_7("00000000"), kernet_8("00000000"), kernet_9("00000000"),
//		data_width(8) {
//		instantiate_modules();
//	}
//};
//
//
//
//
//SC_MODULE(convolution_controller) {
//	// Ports
//	sc_in<bool> clk, rst, start;
//	sc_out<bool> en_cti, en_ctj, en_ctx, en_cty, temp_reg_en, address_reg_en, out1_reg_en, out2_reg_en, out3_reg_en, out4_reg_en;
//	sc_in<bool> counter_i_cout, counter_j_cout, counter_x_cout, counter_y_cout;
//	sc_out<sc_lv<2>> adder_mux_1_sel;
//	sc_out<sc_lv<3>> adder_mux_2_sel;
//	sc_out<sc_lv<2>> adr_reg_mux_sel, mult_mux_1_sel, mult_mux_2_sel;
//	sc_in<sc_lv<8>> counter_x_out, counter_y_out, counter_i_out, counter_j_out;
//	sc_out<bool> done;
//	sc_out<bool> rst_temp;
//
//	// Internal states
//	enum state { idle, adr_gen1, adr_gen2, adr_gen3, adr_gen4, kerlent_mult, add_bias, load_output, done_state, stable, stable2 };
//	sc_signal<state> pstate, nstate;
//
//	// State transition process
//	void process_state_transition() {
//		if (rst.read() == true) {
//			pstate.write(idle);
//		}
//		else if (clk.posedge()) {
//			pstate.write(nstate.read());
//		}
//	}
//
//	// State update process
//	void process_state_update() {
//		// Default values for outputs
//		en_cti.write(false);
//		done.write(false);
//		en_ctj.write(false);
//		en_ctx.write(false);
//		en_cty.write(false);
//		temp_reg_en.write(false);
//		address_reg_en.write(false);
//		out1_reg_en.write(false);
//		out2_reg_en.write(false);
//		out3_reg_en.write(false);
//		out4_reg_en.write(false);
//		adder_mux_1_sel.write("00");
//		adder_mux_2_sel.write("000");
//		adr_reg_mux_sel.write("00");
//		mult_mux_1_sel.write("00");
//		mult_mux_2_sel.write("00");
//		rst_temp.write(false);
//
//		switch (pstate.read()) {
//		case idle:
//			rst_temp.write(true);
//			if (start.read() == false) {
//				nstate.write(adr_gen1);
//			}
//			else {
//				nstate.write(idle);
//			}
//			break;
//
//		case adr_gen1:
//			nstate.write(adr_gen2);
//			adder_mux_1_sel.write("01");
//			adder_mux_2_sel.write("001");
//			adr_reg_mux_sel.write("00");
//			address_reg_en.write(true);
//			break;
//
//		case adr_gen2:
//			nstate.write(adr_gen3);
//			mult_mux_1_sel.write("00");
//			mult_mux_2_sel.write("00");
//			adr_reg_mux_sel.write("01");
//			address_reg_en.write(true);
//			break;
//
//		case adr_gen3:
//			nstate.write(adr_gen4);
//			adder_mux_1_sel.write("11");
//			adder_mux_2_sel.write("000");
//			adr_reg_mux_sel.write("00");
//			address_reg_en.write(true);
//			break;
//
//		case adr_gen4:
//			nstate.write(kerlent_mult);
//			adder_mux_1_sel.write("11");
//			adder_mux_2_sel.write("011");
//			adr_reg_mux_sel.write("00");
//			address_reg_en.write(true);
//			break;
//
//		case kerlent_mult:
//			mult_mux_1_sel.write("01");
//			mult_mux_2_sel.write("01");
//			adder_mux_1_sel.write("10");
//			adder_mux_2_sel.write("010");
//			temp_reg_en.write(true);
//			en_cti.write(true);
//
//			if (counter_i_out.read() == "00000010") {
//				en_ctj.write(true);
//			}
//			nstate.write(stable);
//			break;
//
//		case stable:
//			if (counter_j_out.read() == "00000010" && counter_i_out.read() == "00000010") {
//				nstate.write(add_bias);
//			}
//			else {
//				nstate.write(adr_gen1);
//			}
//			break;
//
//		case add_bias:
//			nstate.write(load_output);
//			adder_mux_1_sel.write("10");
//			adder_mux_2_sel.write("100");
//			adr_reg_mux_sel.write("00");
//			temp_reg_en.write(true);
//			break;
//
//		case load_output:
//			if (counter_y_out.read() == "00000000" && counter_x_out.read() == "00000000") {
//				out1_reg_en.write(true);
//			}
//			else if (counter_y_out.read() == "00000000" && counter_x_out.read() == "00000001") {
//				out2_reg_en.write(true);
//			}
//			else if (counter_y_out.read() == "00000001" && counter_x_out.read() == "00000000") {
//				out3_reg_en.write(true);
//			}
//			else if (counter_y_out.read() == "00000001" && counter_x_out.read() == "00000001") {
//				out4_reg_en.write(true);
//			}
//			en_ctx.write(true);
//			if (counter_x_out.read() == "00000001") {
//				en_cty.write(true);
//			}
//			rst_temp.write(true);
//			nstate.write(stable2);
//			break;
//
//		case stable2:
//			if (counter_y_cout.read() == true) {
//				nstate.write(done_state);
//			}
//			else {
//				nstate.write(adr_gen1);
//			}
//			break;
//
//		case done_state:
//			done.write(true);
//			break;
//		}
//	}
//
//	// Constructor
//	SC_CTOR(convolution_controller) {
//		SC_METHOD(process_state_transition);
//		sensitive << clk.pos() << rst;
//
//		SC_METHOD(process_state_update);
//		sensitive << pstate << start << counter_j_out << counter_i_out << counter_y_cout << counter_y_out << counter_x_out;
//	}
//};
//
//
//
//
//SC_MODULE(convolution) {
//	// Parameters
//	sc_lv<8> bias_value;
//	sc_lv<8> image_size;
//	sc_lv<8> kernet_1, kernet_2, kernet_3, kernet_4, kernet_5, kernet_6, kernet_7, kernet_8, kernet_9;
//	int data_width;
//
//	// Ports
//	sc_in<bool> clk, rst, start;
//	sc_in<sc_lv<8>> data_in;
//	sc_out<sc_lv<8>> data_out1, data_out2, data_out3, data_out4;
//	sc_out<bool> done;
//	sc_out<sc_lv<8>> address_out;
//
//	// Internal signals
//	sc_signal<bool> en_cti, en_ctj, en_ctx, en_cty, temp_reg_en, address_reg_en, out1_reg_en, out2_reg_en, out3_reg_en, out4_reg_en;
//	sc_signal<bool> counter_i_cout, counter_j_cout, counter_x_cout, counter_y_cout;
//	sc_signal<sc_lv<2>> adder_mux_1_sel;
//	sc_signal<sc_lv<3>> adder_mux_2_sel;
//	sc_signal<sc_lv<2>> adr_reg_mux_sel, mult_mux_1_sel, mult_mux_2_sel;
//	sc_signal<sc_lv<8>> counter_x_out, counter_y_out, counter_i_out, counter_j_out;
//	sc_signal<bool> rst_temp;
//
//	// Submodule instances
//	convolution_datapath* datapath;
//	convolution_controller* controller;
//
//	// Constructor
//	SC_CTOR(convolution)
//		: bias_value("00000000"),
//		image_size("00000100"),
//		kernet_1("00000000"), kernet_2("00000000"), kernet_3("00000000"),
//		kernet_4("00000000"), kernet_5("00000000"), kernet_6("00000000"),
//		kernet_7("00000000"), kernet_8("00000000"), kernet_9("00000000"),
//		data_width(8) {
//		// Instantiate submodules
//		datapath = new convolution_datapath("convolution_datapath");
//		datapath->clk(clk);
//		datapath->rst(rst);
//		datapath->en_cti(en_cti);
//		datapath->en_ctj(en_ctj);
//		datapath->en_ctx(en_ctx);
//		datapath->en_cty(en_cty);
//		datapath->temp_reg_en(temp_reg_en);
//		datapath->address_reg_en(address_reg_en);
//		datapath->out1_reg_en(out1_reg_en);
//		datapath->out2_reg_en(out2_reg_en);
//		datapath->out3_reg_en(out3_reg_en);
//		datapath->out4_reg_en(out4_reg_en);
//		datapath->data_in(data_in);
//		datapath->data_out1(data_out1);
//		datapath->data_out2(data_out2);
//		datapath->data_out3(data_out3);
//		datapath->data_out4(data_out4);
//		datapath->counter_i_cout(counter_i_cout);
//		datapath->counter_j_cout(counter_j_cout);
//		datapath->counter_x_cout(counter_x_cout);
//		datapath->counter_y_cout(counter_y_cout);
//		datapath->adder_mux_1_sel(adder_mux_1_sel);
//		datapath->adder_mux_2_sel(adder_mux_2_sel);
//		datapath->adr_reg_mux_sel(adr_reg_mux_sel);
//		datapath->mult_mux_1_sel(mult_mux_1_sel);
//		datapath->mult_mux_2_sel(mult_mux_2_sel);
//		datapath->counter_x_out(counter_x_out);
//		datapath->counter_y_out(counter_y_out);
//		datapath->counter_i_out(counter_i_out);
//		datapath->counter_j_out(counter_j_out);
//		datapath->address_out(address_out);
//		datapath->rst_temp(rst_temp);
//
//		controller = new convolution_controller("convolution_controller");
//		controller->clk(clk);
//		controller->rst(rst);
//		controller->start(start);
//		controller->en_cti(en_cti);
//		controller->en_ctj(en_ctj);
//		controller->en_ctx(en_ctx);
//		controller->en_cty(en_cty);
//		controller->temp_reg_en(temp_reg_en);
//		controller->address_reg_en(address_reg_en);
//		controller->out1_reg_en(out1_reg_en);
//		controller->out2_reg_en(out2_reg_en);
//		controller->out3_reg_en(out3_reg_en);
//		controller->out4_reg_en(out4_reg_en);
//		controller->counter_i_cout(counter_i_cout);
//		controller->counter_j_cout(counter_j_cout);
//		controller->counter_x_cout(counter_x_cout);
//		controller->counter_y_cout(counter_y_cout);
//		controller->adder_mux_1_sel(adder_mux_1_sel);
//		controller->adder_mux_2_sel(adder_mux_2_sel);
//		controller->adr_reg_mux_sel(adr_reg_mux_sel);
//		controller->mult_mux_1_sel(mult_mux_1_sel);
//		controller->mult_mux_2_sel(mult_mux_2_sel);
//		controller->counter_x_out(counter_x_out);
//		controller->counter_y_out(counter_y_out);
//		controller->counter_i_out(counter_i_out);
//		controller->counter_j_out(counter_j_out);
//		controller->done(done);
//		controller->rst_temp(rst_temp);
//	}
//
//	~convolution() {
//		delete datapath;
//		delete controller;
//	}
//};


#endif