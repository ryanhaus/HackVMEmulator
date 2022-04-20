#include "vm_functions.hpp"

#include "functions/vm_stack.hpp"
#include "functions/vm_logical_arithmetic.hpp"
#include "functions/vm_program_control.hpp"
#include "functions/vm_function_control.hpp"

// map of corresponding C++ functions for VM functions
const std::map<std::string, vm_function_template> vm_function_map =
{
	{ "push", vm_functions::vm_push },
	{ "pop", vm_functions::vm_pop },
	{ "add", vm_functions::vm_arithmetic_parse },
	{ "sub", vm_functions::vm_arithmetic_parse },
	{ "neg", vm_functions::vm_arithmetic_parse },
	{ "eq", vm_functions::vm_logical_parse },
	{ "gt", vm_functions::vm_logical_parse },
	{ "lt", vm_functions::vm_logical_parse },
	{ "and", vm_functions::vm_logical_parse },
	{ "or", vm_functions::vm_logical_parse },
	{ "not", vm_functions::vm_logical_parse },
	{ "label", vm_functions::vm_label_parse },
	{ "goto", vm_functions::vm_control_parse },
	{ "if-goto", vm_functions::vm_control_parse },
	{ "function", vm_functions::vm_function_parse },
	{ "call", vm_functions::vm_function_parse },
	{ "return", vm_functions::vm_function_parse },
};