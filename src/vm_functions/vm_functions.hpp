#pragma once

#include <map>
#include <string>
#include <inja.hpp>
#include "parsing_functions.hpp"

using vm_function_template = std::string(*)(const instruction_components&); // takes in components of the instruction and returns the assembly
extern const std::map<std::string, vm_function_template> vm_function_map; // map of corresponding C++ functions for VM functions