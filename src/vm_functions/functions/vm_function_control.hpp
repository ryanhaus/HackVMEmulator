#pragma once

namespace vm_functions
{
	// parse all instructions related to function control
	std::string vm_function_parse(const instruction_components& components)
	{
		if (components.instruction == "function" || components.instruction == "call")
			assert(components.arguments.size() == 2); // make sure we have 2 arguments for function and call
		else if (components.instruction == "return")
			assert(components.arguments.empty()); // make sure we have no arguments for return

		inja::Environment env; // Inja environment
		const inja::Template temp = env.parse_template("./src/vm_functions/templates/function_control.txt"); // parse string template for instructions related to function control

		inja::json data; // data to be supplied to the template
		data["instruction"] = components.instruction;
		data["instruction_id"] = components.instruction_id;

		if (components.instruction != "return")
		{
			data["function_name"] = components.arguments[0];
			data["n"] = components.arguments[1];
		}

		return remove_blank_lines(env.render(temp, data)) + "\n"; // render, remove all blank lines, add a newline to the end, and return
	}
}