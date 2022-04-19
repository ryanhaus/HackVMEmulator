#include "parsing_functions.hpp"
#include "vm_functions.hpp"
#include <sstream>

uint16_t instructions_count; // global instructions count

// splits a string into a vector of strings separated by each occurrence of the supplied character
std::vector<std::string> split_by(const std::string& string, const char c)
{
	std::vector<std::string> strings; // vector of strings to be returned
	auto* c_string = const_cast<char*>(string.c_str()); // convert to c-style string for pointer manipulation
	char* last_space = c_string; // pointer last occurrence of a space

	for (unsigned int i = 0; i < static_cast<unsigned int>(string.size()); i++) // go through each character
		if (c_string[i] == c) // if character is the delimiter character
		{
			c_string[i] = 0; // set it instead to terminating character
			strings.emplace_back(last_space); // add segment from the last occurrence of a space to the last character into the vector
			last_space = c_string + i + 1; // set pointer
		}
		else if (i + 1 == static_cast<unsigned int>(string.size())) // if we're on the last character
			strings.emplace_back(last_space); // add to vector

	return strings;
}

// joins a vector of strings into a singular string with the supplied character between each entry
std::string join_by(const std::vector<std::string>& strings, const char c)
{
	std::stringstream arguments; // stream of arguments
	for (unsigned int i = 0; i < static_cast<unsigned int>(strings.size()); i++) // go through each argument
	{
		arguments << strings[i]; // add string to the stream
		if (i + 1 != static_cast<unsigned int>(strings.size())) // if we're not on the last string
			arguments << c; // add space
	}

	return arguments.str(); // return
}

// removes all blank lines in a string
std::string remove_blank_lines(const std::string& in_string)
{
	const auto lines = split_by(in_string, '\n'); // split into lines
	std::vector<std::string> out_lines; // vector of all acceptable non-blank lines

	for (const std::string& string : lines) // go through each line
		if (!string.empty()) // if not blank
			out_lines.emplace_back(string); // append to vector

	return join_by(out_lines, '\n'); // join back together and return
}

// removes all occurrences of a particular character from a string
std::string remove_characters(const std::string& in_string, const char c)
{
	std::string new_string; // new string

	for (const char current_char : in_string) // go through each character
		if (current_char != c) // if not equal to supplied character
			new_string += current_char; // add to new string

	return new_string;
}

// gets only the components instruction (removes extra whitespace and comments)
std::vector<std::string> split_trim_instruction(const std::string& instruction)
{
	std::string instruction_copy = instruction;

	const auto found_comment = instruction.find("//"); // attempt to find a comment in the instruction
	if (found_comment != std::string::npos) // if comment is found in the string
		instruction_copy = instruction.substr(0, found_comment); // crop the instruction to exclude the comment

	std::vector<std::string> components; // components of a string

	const auto split = split_by(instruction_copy, ' '); // split by space
	for (const auto& component : split) // go through each component
		if (!component.empty())
			components.emplace_back(component); // add to list of components

	return components;
}

// parses an instruction and extrapolates the command and its arguments
instruction_components parse_instruction(const std::string& instruction)
{
	auto split = split_trim_instruction(instruction); // split the instruction

	instruction_components components; // components of the instruction (to be returned)

	if (split.empty())
	{
		components.blank_instruction = true; // set blank flag
		return components; // don't modify the instruction further
	}

	components.instruction = remove_characters(split[0], '\n'); // base instruction with any newline characters removed
	split.erase(split.begin()); // remove first element
	components.arguments = split; // set the arguments to the new vector

	components.instruction_id = instructions_count++; // set instruction count

	for (auto& argument : components.arguments) // go through each argument
		argument = remove_characters(argument, '\n'); // remove newline characters

	return components;
}

// compiles an instruction and adds it to the given vector
std::string compile_instruction(const std::string& instruction)
{
	const auto components = parse_instruction(instruction); // parse the instruction into its components
	if (components.blank_instruction) return ""; // if its a blank instruction don't do anything

	assert(vm_function_map.find(components.instruction) != vm_function_map.end()); // make sure function exists

	return vm_function_map.at(components.instruction)(components); // compile and return
}

// compiles a VM file and stores it in an ASM file
void compile_file_to(const std::string& in_vm, const std::string& out_asm)
{
	// read and compile file
	FILE* in_f;
	fopen_s(&in_f, in_vm.c_str(), "r"); // open stream with reading permission
	assert(in_f != nullptr); // make sure it was opened correctly

	char line_buffer[0x80]; // line buffer for reading file
	std::vector<std::string> asm_out; // assembly

	while (fgets(line_buffer, sizeof(line_buffer), in_f)) // read file line by line
		asm_out.push_back(compile_instruction(line_buffer)); // compile the instruction specified in the line and append it

	// write compiled program to file
	const std::string to_write = join_by(asm_out, '\n');
	FILE* out_f;

	fopen_s(&out_f, out_asm.c_str(), "w"); // open stream with writing permission
	assert(out_f != nullptr); // make sure it was opened correctly
	fputs(to_write.c_str(), out_f); // write to file
	fclose(out_f); // close stream
}