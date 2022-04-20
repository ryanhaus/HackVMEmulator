#pragma once

namespace vm_functions
{
	// parse label instructions
	std::string vm_label_parse(const instruction_components& components)
	{
		assert(components.arguments.size() == 1); // make sure we only have one argument

		char out_string[0x40]; // output string
		sprintf_s(out_string, sizeof(out_string), "// label %s\n(__LABEL_%s)\n", components.arguments[0].c_str(), components.arguments[0].c_str()); // use formats to create assembly instruction

		return out_string;
	}

	// parse program control functions (goto, if-goto)
	std::string vm_control_parse(const instruction_components& components)
	{
		assert(components.arguments.size() == 1); // make sure we only have one argument

		inja::Environment env; // Inja environment
		const inja::Template temp = env.parse_template("./src/vm_functions/templates/program_control.txt"); // parse the string template for program control

		inja::json data; // data to be supplied to the template
		data["instruction"] = components.instruction;
		data["destination"] = components.arguments[0];
		data["instruction_id"] = components.instruction_id;

		return remove_blank_lines(env.render(temp, data)) + "\n"; // render, remove all blank lines, add a newline at the end, and return
	}
}