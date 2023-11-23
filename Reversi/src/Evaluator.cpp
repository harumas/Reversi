#include "../include/Evaluator.h"

namespace Reversi
{
	Evaluator::Evaluator(std::shared_ptr<Board>& board)
		: board(board)
	{

	}

	//評価関数
	int Evaluator::Evaluate(Side side) const
	{
		//盤面情報の取得
		std::pair<int, int> counts = board->CountStone();
		std::pair<u64, u64> field_data = board->GetFieldData();
		std::pair<int, int> legal_counts = board->CountLegalMoves();

		//逆サイドの評価の場合は盤面情報をswap
		if (side == Side::Black)
		{
			std::swap(std::get<0>(counts), std::get<1>(counts));
			std::swap(std::get<0>(field_data), std::get<1>(field_data));
			std::swap(std::get<0>(legal_counts), std::get<1>(legal_counts));
		}

		//ゲーム終了時のスコアを取得
		int ending_score = EvaluateGameEnd(counts, legal_counts.first, legal_counts.second);

		if (ending_score != 0)
			return ending_score;

		int bestScore = 0;

		//各座標のウェイトを評価
		bestScore += EvaluateWeight(field_data) * 8;

		//確定石を評価
		bestScore += EvaluateConfirm(field_data) * 165;

		//着手可能数を評価
		bestScore += legal_counts.first * 20;

		return bestScore;
	}

	int Evaluator::EvaluateGameEnd(std::pair<int, int> counts, int legal_count_mine, int legal_count_other) const
	{
		if (counts.first == 0)
			return 20000000;
		if (counts.second == 0)
			return -20000000;

		if (counts.first + counts.second == 64 || legal_count_mine + legal_count_other == 0)
		{
			if (counts.first < counts.second)
				return 15000;

			if (counts.first > counts.second)
				return -15000;
		}

		return 0;
	}

	int Evaluator::EvaluateWeight(const std::pair<u64, u64> field) const
	{
		int sum = 0;

		for (int i = 0; i < 64; ++i)
		{
			int sign = static_cast<int>(((field.second >> i) & 1ull) - ((field.first >> i) & 1ull));
			sum += weights[i] * sign * 4;
		}

		return sum;
	}

	int Evaluator::EvaluateConfirm(const std::pair<u64, u64> field) const
	{
		u64 mine = field.first;
		u64 others = field.second;
		u64 all = mine | others;
		int count = 0;

		for (const u64& corner : corners)
		{
			if ((all & corner) == 0ull)
				continue;

			u64 target = (mine & corner) == 0ull ? mine : others;
			u64 obstacle = (mine & corner) == 0ull ? others : mine;

			//繋がってる石を取得する
			u64 flips = board->GetCrossFloods(corner, obstacle);
			count += (std::popcount(flips) + 1) * (-(int)(target == others));
		}

		return count;
	}
}





