#include <iostream>
#include <cstdlib>
#include <vector>

/** Bracket Check
 *  checks to to make sure that '(){}[]<>' are correctly paired
 *  in the input
 *
 *  @arg input String to check for bracket correctness
 *  @return True if brackets are correct
 */
bool bracket_check( const std::string input )
{
	std::vector<char> stack;
	std::string opens = "({[<";
	std::string closes = ")}]>";
	bool retval = true;
	for (int i=0; i < input.length(); ++i) {
		// Add to stack if it is one of the openings
		for (int j=0; j < opens.length(); ++j) {
			if (input[i] == opens[j]) {
				stack.push_back(input[i]);
				continue;
			}
		}

		// Check for closing 
		for (int j=0; j < closes.length(); ++j) {
			if (input[i] == closes[j]) {
				if (stack.size() == 0)
					return false;
				if (stack.back() != opens[j])
					return false;
				stack.pop_back();
			}
		}
	}
	if (stack.size() != 0)
		return false;
	return true;
}

/** Test Suite
 *  tests bracket_check for correctness
 */
void test_suite ( )
{
	std::string correct[] = {"123", "(abc)", "()abc()", "([<{123abc123}>])"};
	std::string wrong[] = {"(abc[123)abc]", "(abc>", "(abc }{ 123)"};
	bool passed = true;
	for (int i=0; i < 4; ++i) {
		if (!bracket_check(correct[i])) {
			std::cout << "Failed on - '" << correct[i] << "'" << std::endl;
			passed = false;
		}
	}
	for (int i=0; i < 3; ++i) {
		if (bracket_check(wrong[i])) {
			std::cout << "Failed on - '" << correct[i] << "'" << std::endl;
			passed = false;
		}
	}
	if (passed)
		std::cout << "Passed all tests." << std::endl;
}

int main ( int argc, char *argv[] )
{
	if (argc < 2) {
		test_suite();
		return EXIT_SUCCESS;
	}
	if (bracket_check(argv[1]))
		std::cout << "Brackets are correct." << std::endl;
	else
		std::cout << "Brackets are wrong." << std::endl;
	return EXIT_SUCCESS;
}

