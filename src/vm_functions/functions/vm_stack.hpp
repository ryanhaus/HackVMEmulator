#pragma once
#include <cassert>
#include <vector>
#include <string>
#include <inja.hpp>

namespace vm_functions
{
	const std::vector<std::string> valid_segments = { "local", "argument", "this", "that", "constant", "static", "pointer", "temp"}; // list of valid memory segments

	std::string vm_push(const instruction_components& components)
	{
		assert(components.arguments.size() == 2); // ensure we have the segment and i
		assert(std::find(valid_segments.begin(), valid_segments.end(), components.arguments[0]) != valid_segments.end()); // make sure that the memory segment provided exists

		inja::Environment env; // Inja environment
		const inja::Template temp = env.parse_template("./src/vm_functions/templates/push.txt"); // parse the string template

		inja::json data; // data to be supplied to the template
		data["segment"] = components.arguments[0];
		data["i"] = components.arguments[1];
		
		return remove_blank_lines(env.render(temp, data)) + "\n"; // render, remove all blank lines, add a newline at the end, and return
	}

	std::string vm_pop(const instruction_components& components)
	{
		assert(components.arguments.size() == 2); // ensure that we have the segment and i
		assert(std::find(valid_segments.begin(), valid_segments.end(), components.arguments[0]) != valid_segments.end()); // make sure that the memory segment provided exists

		inja::Environment env; // Inja environment
		const inja::Template temp = env.parse_template("./src/vm_functions/templates/pop.txt"); // parse the string template

		inja::json data; // data to be supplied to the template
		data["segment"] = components.arguments[0];
		data["i"] = components.arguments[1];

		return remove_blank_lines(env.render(temp, data)) + "\n"; // render, remove all blank lines, add a newline at the end, and return
	}
}
