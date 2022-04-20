// All information taken from https://drive.google.com/file/d/19fe1PeGnggDHymu4LlVY08KmDdhMVRpm/view
#include "vm_functions/vm_functions.hpp"

int main()
{
	compile_files_to({ "Sys.vm", "Main.vm" }, "FibonacciElement.asm");

	return 0;
}