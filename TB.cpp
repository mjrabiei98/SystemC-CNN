#include "TB.h"

void testbench::resetting()
{
	while (true)
	{
		wait(7, SC_NS);
		rst = SC_LOGIC_0;
		wait(11, SC_NS);
		rst = SC_LOGIC_1;
		wait(58, SC_NS);
		rst = SC_LOGIC_0;
		wait();
	}
}

void testbench::clocking()
{
	while (true)
	{
		wait(17, SC_NS);
		clk = SC_LOGIC_0;
		wait(17, SC_NS);
		clk = SC_LOGIC_1;
	}
}

void testbench::inGenerating()
{
	while (true)
	{

		a = "00000000";
		b = "00000000";
		c = "10000000";
		d = "00011000";
		e = "00011000";
		sel = "010";
		address_in_read = "00000000";
		en.write(SC_LOGIC_1);
		wait(60, SC_NS);

		sel = "110";
		m = "001100110011";
		address_in_read = "00000001";
		wait(60, SC_NS);

		wait(500, SC_NS);
		sel = "011";
		m = "001100000000";
		address_in_read = "00000011";
		wait(60, SC_NS);

		wait(500, SC_NS);
		sel = "000";
		wait(60, SC_NS);

		wait();
	}
}

void testbench::displaying()
{
	while (true){
		//if (ready == '1')
			//cout << A << " / " << B << " => Quotient = " << Q << " & Remainder = " << R << " - Time : " << sc_time_stamp() << endl;
		//std::cout << "output" << q << endl;
		//std::cout << "tesssst" << sel.read().to_uint() << endl;
		std::cout << "ram value = " << data_out << endl;
		wait();
	}
}

