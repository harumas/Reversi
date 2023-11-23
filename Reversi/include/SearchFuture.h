#pragma once

#include <thread>
#include <functional>
#include <future>
#include "Board.h"
#include "SearchSystem.h"

namespace Reversi
{
	class SearchFuture
	{
	public:
		explicit SearchFuture();

		void Initialize(const Board& origin, Side side);
		std::future<SearchResult> Schedule(u64 input);
		SearchResult SearchBestMove();
		void SetSearchDepth(int depth);

	private:
		int depth;
		u64 assigned_input;
		std::unique_ptr<SearchSystem> search_system;
		std::shared_ptr<Board> board_buffer;
	};
}
