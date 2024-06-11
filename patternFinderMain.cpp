#include "TB.h"

int sc_main(int argc, char* argv[]) {
	sc_lv<8> init_kernels[3][9] = {
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

	sc_lv<8> init_biases[3] = { "11111111", "11111110", "11111110" };
	sc_lv<8> init_image_size = "00000100";
	// Instantiate the testbench
	testbench tb("testbench", init_kernels, init_biases, init_image_size);

	// Start simulation
	sc_start(2000, SC_NS);

	return 0;
}