#include <iostream>
#include <vector>
#include "jit.hpp"

int main() {
	std::vector<uint8_t> code69 = {
		0x48, 0xC7, 0xC0, 69, 0, 0, 0,
		0xC3
	};

	opsek::JIT jit;

	int64_t returned = jit.ExecuteInstructions(code69);

	std::cout << "RETURNED JIT TEST: " << returned << '\n';
}