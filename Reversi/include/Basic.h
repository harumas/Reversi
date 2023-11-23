#pragma once

namespace Reversi
{
	typedef unsigned long long u64;

	//ゲームの状態
	enum class State : unsigned char
	{
		Invalid,
		Set,
		Restart,
		Stop,
		End,
	};

	enum class Side : unsigned char
	{
		Black,
		White
	};
}
