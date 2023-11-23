#include "../include/Board.h"

namespace Reversi
{
	Board::Board() :
		black_board(0),
		white_board(0)
	{
		Reset();
	}

	void Board::Reset()
	{
		black_board = 0b0000000000000000000000000000100000010000000000000000000000000000ull;
		white_board = 0b0000000000000000000000000001000000001000000000000000000000000000ull;
	}

	void Board::Set(const u64 input, const Side side)
	{
		u64& side_data = (side == Side::Black ? black_board : white_board);
		side_data |= input;
	}

	u64 Board::Flip(const u64 input, const Side side)
	{
		u64& mine = side == Side::Black ? black_board : white_board;
		u64& others = side == Side::Black ? white_board : black_board;
		u64 flips = GetHorizontalFlips(input, mine, others) |
			GetVerticalFlips(input, mine, others) |
			GetDiagonalCrossFlips(input, mine, others);

		mine |= flips;
		others ^= flips;

		return flips;
	}

	void Board::Undo(const u64 input, const Side side)
	{
		u64& origin_side = (side == Side::Black ? black_board : white_board);
		u64& setter_side = (side == Side::Black ? white_board : black_board);

		origin_side &= ~input;
		setter_side |= input;
	}

	void Board::SetEmpty(const u64 input)
	{
		black_board &= ~input;
		white_board &= ~input;
	}

	std::pair<int, int> Board::CountStone() const
	{
		return std::make_pair(std::popcount(black_board), std::popcount(white_board));
	}

	std::pair<int, int> Board::CountLegalMoves() const
	{
		return std::make_pair(std::popcount(GetLegalMoves(Side::Black)), std::popcount(GetLegalMoves(Side::White)));
	}

	u64 Board::GetLegalMoves(const Side side) const
	{
		u64 mine = side == Side::Black ? black_board : white_board;
		u64 others = side == Side::Black ? white_board : black_board;
		u64 empties = ~GetAllBoard();

		return GetVerticalMoves(mine, others, empties) |
			GetHorizontalMoves(mine, others, empties) |
			GetCrossMoves(mine, others, empties);
	}

	std::pair<u64, u64> Board::GetFieldData() const
	{
		return std::make_pair(black_board, white_board);
	}

	u64 Board::GetAllBoard() const
	{
		return black_board | white_board;
	}

	u64 Board::GetVerticalMoves(const u64 mine, const u64 others, const u64 empties) const
	{
		//上下端のマスを除く
		u64 vertical_cells = others & vertical_mask;
		u64 vertical_moves;

		//シフトして配置可能マスを絞る
		//高速化のためコンパイラ側で展開してもいいが、コードが複雑になるので手動で展開
		//上
		u64 tmp = vertical_cells & (mine << 8);
		tmp |= vertical_cells & (tmp << 8);
		tmp |= vertical_cells & (tmp << 8);
		tmp |= vertical_cells & (tmp << 8);
		tmp |= vertical_cells & (tmp << 8);
		tmp |= vertical_cells & (tmp << 8);
		vertical_moves = empties & (tmp << 8);

		//下
		tmp = vertical_cells & (mine >> 8);
		tmp |= vertical_cells & (tmp >> 8);
		tmp |= vertical_cells & (tmp >> 8);
		tmp |= vertical_cells & (tmp >> 8);
		tmp |= vertical_cells & (tmp >> 8);
		tmp |= vertical_cells & (tmp >> 8);
		vertical_moves |= empties & (tmp >> 8);

		return vertical_moves;
	}

	u64 Board::GetHorizontalMoves(const u64 mine, const u64 others, const u64 empties) const
	{
		//左右端のマスを除く
		u64 horizontal_cells = others & horizontal_mask;
		u64 horizontal_moves;

		//シフトして配置可能マスを絞る
		//右
		u64 tmp = horizontal_cells & (mine >> 1);
		tmp |= horizontal_cells & (tmp >> 1);
		tmp |= horizontal_cells & (tmp >> 1);
		tmp |= horizontal_cells & (tmp >> 1);
		tmp |= horizontal_cells & (tmp >> 1);
		tmp |= horizontal_cells & (tmp >> 1);
		horizontal_moves = empties & (tmp >> 1);

		//左
		tmp = horizontal_cells & (mine << 1);
		tmp |= horizontal_cells & (tmp << 1);
		tmp |= horizontal_cells & (tmp << 1);
		tmp |= horizontal_cells & (tmp << 1);
		tmp |= horizontal_cells & (tmp << 1);
		tmp |= horizontal_cells & (tmp << 1);
		horizontal_moves |= empties & (tmp << 1);

		return horizontal_moves;
	}

	u64 Board::GetCrossMoves(const u64 mine, const u64 others, const u64 empties) const
	{
		//すべての端のマスを除く
		u64 cross_cells = others & allSide_mask;
		u64 cross_moves;

		//シフトして配置可能マスを絞る
		//右上
		u64 tmp = cross_cells & (mine << 7);
		tmp |= cross_cells & (tmp << 7);
		tmp |= cross_cells & (tmp << 7);
		tmp |= cross_cells & (tmp << 7);
		tmp |= cross_cells & (tmp << 7);
		tmp |= cross_cells & (tmp << 7);
		cross_moves = empties & (tmp << 7);

		//左下
		tmp = cross_cells & (mine >> 7);
		tmp |= cross_cells & (tmp >> 7);
		tmp |= cross_cells & (tmp >> 7);
		tmp |= cross_cells & (tmp >> 7);
		tmp |= cross_cells & (tmp >> 7);
		tmp |= cross_cells & (tmp >> 7);
		cross_moves |= empties & (tmp >> 7);

		//右下
		tmp = cross_cells & (mine >> 9);
		tmp |= cross_cells & (tmp >> 9);
		tmp |= cross_cells & (tmp >> 9);
		tmp |= cross_cells & (tmp >> 9);
		tmp |= cross_cells & (tmp >> 9);
		tmp |= cross_cells & (tmp >> 9);
		cross_moves |= empties & (tmp >> 9);

		//左上
		tmp = cross_cells & (mine << 9);
		tmp |= cross_cells & (tmp << 9);
		tmp |= cross_cells & (tmp << 9);
		tmp |= cross_cells & (tmp << 9);
		tmp |= cross_cells & (tmp << 9);
		tmp |= cross_cells & (tmp << 9);
		cross_moves |= empties & (tmp << 9);

		return cross_moves;
	}


	u64 Board::GetHorizontalFlips(const u64 input, const u64 mine, const u64 others) const
	{
		u64 horizontal_cells = others & horizontal_mask;
		u64 horizontal_flips;

		//右
		u64 flip = horizontal_cells & (input >> 1);
		flip |= horizontal_cells & (flip >> 1);
		flip |= horizontal_cells & (flip >> 1);
		flip |= horizontal_cells & (flip >> 1);
		flip |= horizontal_cells & (flip >> 1);
		flip |= horizontal_cells & (flip >> 1);
		flip |= horizontal_cells & (flip >> 1);
		horizontal_flips = flip & -(long long)((mine & (flip >> 1)) != 0);

		//左
		flip = horizontal_cells & (input << 1);
		flip |= horizontal_cells & (flip << 1);
		flip |= horizontal_cells & (flip << 1);
		flip |= horizontal_cells & (flip << 1);
		flip |= horizontal_cells & (flip << 1);
		flip |= horizontal_cells & (flip << 1);
		flip |= horizontal_cells & (flip << 1);
		horizontal_flips |= flip & -(long long)((mine & (flip << 1)) != 0);

		return horizontal_flips;
	}

	u64 Board::GetVerticalFlips(const u64 input, const u64 mine, const u64 others) const
	{
		u64 vertical_cells = others & vertical_mask;
		u64 vertical_flips;

		//上
		u64 flip = vertical_cells & (input << 8);
		flip |= vertical_cells & (flip << 8);
		flip |= vertical_cells & (flip << 8);
		flip |= vertical_cells & (flip << 8);
		flip |= vertical_cells & (flip << 8);
		flip |= vertical_cells & (flip << 8);
		flip |= vertical_cells & (flip << 8);
		vertical_flips = flip & -(long long)((mine & (flip << 8)) != 0);

		//下
		flip = vertical_cells & (input >> 8);
		flip |= vertical_cells & (flip >> 8);
		flip |= vertical_cells & (flip >> 8);
		flip |= vertical_cells & (flip >> 8);
		flip |= vertical_cells & (flip >> 8);
		flip |= vertical_cells & (flip >> 8);
		flip |= vertical_cells & (flip >> 8);
		vertical_flips |= flip & -(long long)((mine & (flip >> 8)) != 0);

		return vertical_flips;
	}


	u64 Board::GetDiagonalCrossFlips(const u64 input, const u64 mine, const u64 others) const
	{
		u64 cross_cells = others & allSide_mask;
		u64 cross_flips;

		//右上
		u64 flip = cross_cells & (input << 7);
		flip |= cross_cells & (flip << 7);
		flip |= cross_cells & (flip << 7);
		flip |= cross_cells & (flip << 7);
		flip |= cross_cells & (flip << 7);
		flip |= cross_cells & (flip << 7);
		flip |= cross_cells & (flip << 7);
		cross_flips = flip & -(long long)((mine & (flip << 7)) != 0);

		//左下
		flip = cross_cells & (input >> 7);
		flip |= cross_cells & (flip >> 7);
		flip |= cross_cells & (flip >> 7);
		flip |= cross_cells & (flip >> 7);
		flip |= cross_cells & (flip >> 7);
		flip |= cross_cells & (flip >> 7);
		flip |= cross_cells & (flip >> 7);
		cross_flips |= flip & -(long long)((mine & (flip >> 7)) != 0);

		//右下
		flip = cross_cells & (input >> 9);
		flip |= cross_cells & (flip >> 9);
		flip |= cross_cells & (flip >> 9);
		flip |= cross_cells & (flip >> 9);
		flip |= cross_cells & (flip >> 9);
		flip |= cross_cells & (flip >> 9);
		flip |= cross_cells & (flip >> 9);
		cross_flips |= flip & -(long long)((mine & (flip >> 9)) != 0);

		//左上
		flip = cross_cells & (input << 9);
		flip |= cross_cells & (flip << 9);
		flip |= cross_cells & (flip << 9);
		flip |= cross_cells & (flip << 9);
		flip |= cross_cells & (flip << 9);
		flip |= cross_cells & (flip << 9);
		flip |= cross_cells & (flip << 9);
		cross_flips |= flip & -(long long)((mine & (flip << 9)) != 0);

		return cross_flips;
	}

	u64 Board::GetCrossFloods(const u64 input, const u64 others) const
	{
		u64 vertical_cells = others & vertical_mask;
		u64 horizontal_cells = others & horizontal_mask;
		u64 floods;

		//上
		u64 flood = vertical_cells & (input << 8);
		flood |= vertical_cells & (flood << 8);
		flood |= vertical_cells & (flood << 8);
		flood |= vertical_cells & (flood << 8);
		flood |= vertical_cells & (flood << 8);
		flood |= vertical_cells & (flood << 8);
		flood |= vertical_cells & (flood << 8);
		floods = flood;

		//下
		flood = vertical_cells & (input >> 8);
		flood |= vertical_cells & (flood >> 8);
		flood |= vertical_cells & (flood >> 8);
		flood |= vertical_cells & (flood >> 8);
		flood |= vertical_cells & (flood >> 8);
		flood |= vertical_cells & (flood >> 8);
		flood |= vertical_cells & (flood >> 8);
		floods |= flood;

		//右
		flood = horizontal_cells & (input >> 1);
		flood |= horizontal_cells & (flood >> 1);
		flood |= horizontal_cells & (flood >> 1);
		flood |= horizontal_cells & (flood >> 1);
		flood |= horizontal_cells & (flood >> 1);
		flood |= horizontal_cells & (flood >> 1);
		flood |= horizontal_cells & (flood >> 1);
		floods = flood;

		//左
		flood = horizontal_cells & (input << 1);
		flood |= horizontal_cells & (flood << 1);
		flood |= horizontal_cells & (flood << 1);
		flood |= horizontal_cells & (flood << 1);
		flood |= horizontal_cells & (flood << 1);
		flood |= horizontal_cells & (flood << 1);
		flood |= horizontal_cells & (flood << 1);
		floods |= flood;

		return floods;
	}

	void Board::Overwrite(const Board& board)
	{
		black_board = board.black_board;
		white_board = board.white_board;
	}
}
