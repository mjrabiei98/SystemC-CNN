#include "TB.h"

int sc_main(int argc, char* argv[]) {
	// Instantiate the testbench
	testbench tb("testbench");

	// Start simulation
	sc_start(2000, SC_NS);

	return 0;
}