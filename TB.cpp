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
	
		start = SC_LOGIC_0;
		wait(60, SC_NS);

		start = SC_LOGIC_1;
		wait(60, SC_NS);
		start = SC_LOGIC_0;


		wait(1000, SC_NS);
		wait(60, SC_NS);

		wait(500, SC_NS);
		wait(60, SC_NS);

		
}

void testbench::displaying()
{
	while (true){
		//if (ready == '1')
			//cout << A << " / " << B << " => Quotient = " << Q << " & Remainder = " << R << " - Time : " << sc_time_stamp() << endl;
		//std::cout << "output" << q << endl;
		//std::cout << "tesssst" << sel.read().to_uint() << endl;
		//std::cout << "done value = " << done_conv << endl;
		//std::cout << "output1 " << data_out1_conv << endl;
		//std::cout << "output2 " << data_out2_conv << endl;
		//std::cout << "output3 " << data_out3_conv << endl;
		//std::cout << "output4 " << data_out4_conv << endl;
		wait();
	}
}

