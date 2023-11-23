#pragma once

#include <string>
#include <iostream>
#include "Basic.h"

namespace Reversi
{
	/// <summary>
	/// ユーザーの入力を表すクラス
	/// </summary>
	struct Command
	{
		State state;
		u64 set;

		bool IsLegalMove(u64 legal_positions) const;
	};

	/// <summary>
	/// ユーザーの入力を取得するクラス
	/// </summary>
	class InputReader
	{
	public:
		//プレイヤーの入力コマンドを取得する
		Command ReadCommand() const;

	private:
		u64 CommandToBoard(const std::wstring& command) const;
		void WriteInitialMessage() const;
		bool IsLegalCommand(const std::wstring& command) const;
	};
}




