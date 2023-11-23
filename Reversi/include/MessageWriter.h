#pragma once

#include <string>
#include <iostream>
#include <thread>

#include "Basic.h"

namespace Reversi
{
	class MessageWriter
	{
		std::wstring write_buffer;
		void WriteMessage();
	public:
		void WriteWelcomeMessage();
		void WriteRetryMessage(bool invalid);
		void WriteSelectTurnMessage(bool invalid);
		void WriteResultMessage(int black_count, int white_count);
		void WritePassMessage(Side side);
		void WriteTurnMessage(Side player_turn, int max_depth);
		void WriteSelectStrengthMessage(bool invalid);
		void WriteGameStartMessage();
	};
}



