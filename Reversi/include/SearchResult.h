#pragma once

#include "Basic.h"

namespace Reversi
{
	/// <summary>
	/// 探索結果
	/// </summary>
	struct SearchResult
	{
		int Score;
		u64 Point;
	};
}
