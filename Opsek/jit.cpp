#include "jit.hpp"
#include <Windows.h>
#include <stdexcept>

namespace opsek {
	int64_t JIT::ExecuteInstructions(const std::vector<uint8_t>& code) {
		if (code.empty()) throw std::invalid_argument("Code is empty! [JIT::ExecuteInstructions]");

		void* addy = VirtualAlloc(NULL, code.size(), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		if (!addy)
			throw std::runtime_error("Unable to alloc memory address for code! [JIT::ExecuteInstructions]");

		std::memcpy(addy, code.data(), code.size());

		DWORD old;
		if (!VirtualProtect(addy, code.size(), PAGE_EXECUTE_READ, &old)) {
			VirtualFree(addy, 0, MEM_RELEASE);
			throw std::runtime_error("Virtual protect fail! [JIT::ExecuteInstructions]");
		}

		FlushInstructionCache(GetCurrentProcess(), addy, code.size());

		auto fn = reinterpret_cast<int64_t(*)(int(*)(), int(*)(int))>(addy);
		int64_t result = fn([] {return getchar(); }, [](int c) {return putchar(c); }); // later use patching

		return 0;
	}
}