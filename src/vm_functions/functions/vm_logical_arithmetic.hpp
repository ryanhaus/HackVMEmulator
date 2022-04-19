#pragma once

namespace vm_functions
{
	// parse all arithmetic instructions (add, sub, neg)
	std::string vm_arithmetic_parse(const instruction_components& components)
	{
		assert(components.arguments.empty()); // make sure we have no arguments

		inja::Environment env; // Inja environment
		const inja::Template temp = env.parse_file("./src/vm_functions/templates/arithmetic.txt"); // parse template for all arithmetic instructions

		inja::json data; // data to be supplied to the template
		data["instruction"] = components.instruction;

		return remove_blank_lines(env.render(temp, data)) + "\n"; // render, remove all blank lines, add a newline at the end, and return
	}

	// parse all logical instructions (eq, gt, lt, and, or, not)
	std::string vm_logical_parse(const instruction_components& components)
	{
		assert(components.arguments.empty()); // make sure we have no arguments

		inja::Environment env; // Inja environment
		const inja::Template temp = env.parse_file("./src/vm_functions/templates/logical.txt"); // parse template for all logical instructions

		inja::json data; // data to be supplied to the template
		data["instruction"] = components.instruction;
		data["instruction_id"] = components.instruction_id;

		return remove_blank_lines(env.render(temp, data)) + "\n"; // render, remove all blank lines, add a newline at the end, and return
	}
};