#include "vm_functions.hpp"

#include "functions/vm_stack.hpp"
#include "functions/vm_logical_arithmetic.hpp"

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
};