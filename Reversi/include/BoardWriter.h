#pragma once

#include <string>
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <Windows.h>

#include "Basic.h"

namespace Reversi
{
	class BoardWriter
	{
	public:
		explicit BoardWriter(int size);
		~BoardWriter();

		void Write(std::pair<u64, u64> field_data, u64 legal_moves, u64 input = 0xFFFFFFFFFFFFFFFF);

	private:
		const int board_size;
		std::wstring write_buffer;
		std::wstring defaultFontName;

		std::wstring GetBackColorCode(int id) const;
		std::wstring GetFrontColorCode(int id) const;

		void WriteAlphabets();
		void WriteParts(const wchar_t& l_side, const wchar_t& m_side, const wchar_t& r_side);
		std::wstring ToStone(u64 black_data, u64 white_data, u64 legal_moves, int offset, u64 input) const;

	};
}
