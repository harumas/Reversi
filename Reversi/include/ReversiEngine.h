#pragma once

#include <thread>
#include <vector>
#include <queue>
#include "Basic.h"
#include "Board.h"
#include "Evaluator.h"
#include "SearchFuture.h"
#include "SearchResult.h"

namespace Reversi
{
	class ReversiEngine
	{
	public:
		explicit ReversiEngine(std::shared_ptr<Board>& board);
		u64 MakeBestMove();
		u64 MakeBestMove_Single();
		u64 MakeBestMove_Parallel();
		void SetEvaluateSide(Reversi::Side side);
		void SetSearchDepth(int depth);

		int GetSearchDepth();
	private:

		std::shared_ptr<Board> board;
		std::vector<SearchFuture> tasks;
		std::queue<u64> input_queue;
		std::future<SearchResult> futures[64];
		SearchSystem search_system;
		Side evaluateSide;
		unsigned long long future_count;

		bool is_support_multi_thread;
		int max_depth;
	};
}




