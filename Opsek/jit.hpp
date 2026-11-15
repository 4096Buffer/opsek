#pragma once
#include <cstdint>
#include <vector>

namespace opsek {
	class JIT {
	public:
		int64_t ExecuteInstructions(const std::vector<uint8_t>& code);
	};
}