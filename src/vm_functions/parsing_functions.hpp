#pragma once
#include <vector>
#include <string>

// contains components of an instruction
struct instruction_components
{
	std::string instruction; // the base instruction
	std::vector<std::string> arguments; // all of the arguments supplied to the instruction
	uint16_t instruction_id = 0; // id of the instruction
	bool blank_instruction = false; // whether or not the instruction is blank
};

std::vector<std::string> split_by(const std::string& string, const char c); // splits a string into a vector of strings separated by each occurrence of the supplied character
std::string join_by(const std::vector<std::string>& strings, const char c); // joins a vector of strings into a singular string with the supplied character between each entry
std::string remove_blank_lines(const std::string& in_string); // removes all blank lines in a string
std::string remove_characters(const std::string& in_string, const char c); // removes all occurrences of a particular character from a string

std::vector<std::string> split_trim_instruction(const std::string& instruction); // gets only the components of the instruction (removes extra whitespace and comments)
instruction_components parse_instruction(const std::string& instruction); // parses an instruction and extrapolates the command and its arguments
std::string compile_instruction(const std::string& instruction); // compiles an instruction and adds it to the given vector

void compile_file_to(const std::string& in_vm, const std::string& out_asm); // compiles a VM file and stores it in an ASM file