#pragma once

#include "Evaluator.h"
#include "SearchResult.h"

namespace Reversi
{
	class SearchSystem
	{
	public:
		Side evaluateSide;

		SearchSystem(std::shared_ptr<Board>& board);
		SearchResult AlphaBetaSearch(u64 point, int depth, int alpha, int beta, Side side);
	private:
		std::shared_ptr<Board> board;
		Evaluator evaluator;
	};
}
