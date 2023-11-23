#pragma once

#include <string>
#include <iostream>
#include "Basic.h"

namespace Reversi
{
	struct Command
	{
		State state;
		u64 set;

		bool IsLegalMove(u64 legal_positions) const;
	};

	class InputReader
	{
	public:
		Command ReadCommand() const;

	private:
		u64 CommandToBoard(const std::wstring& command) const;
		void WriteInitialMessage() const;
		bool IsLegalCommand(const std::wstring& command) const;
	};
}




