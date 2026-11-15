#pragma once
#include <vector>
#include <cstdint>

namespace opsek {
	enum class Reg : uint8_t {
		rax, rcx, rdx, rbx, rsp, rbp, rsi, rdi,
		r8, r9, r10, r11, r12, r13, r14, r15
	};

	class Assembler {
	public:
		void mov(Reg dst, int64_t imm) {
			int r = (int)dst;
			emit(0x48 | (r >> 3));
			emit(0xB8 + (r & 7));
			emit64(imm);
		}
	private:
		void emit(uint8_t b) {
			bytes.push_back(b);
		}
		void emit64(int64_t v) {
			for (int i = 0; i < 8; ++i) {
				emit(v >> (i * 8));
			}
		}

		std::vector<uint8_t> bytes;


	};
}