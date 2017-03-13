#ifndef __TA_DX_H__
#define __TA_DX_H__

#include "TA_Param.h"

namespace TA
{
	/*
	* TA_DX - Directional Movement Index
	*
	* Input  = High, Low, Close
	* Output = double
	*
	* Optional Parameters
	* -------------------
	* optInTimePeriod:(From 2 to 100000)
	*    Number of period
	*
	*
	*/
	template <typename T>
	class DX_Param : public PeroidParam < T >
	{
	public:
		DX_Param(const std::vector<T>& high
			, const std::vector<T>& low
			, const std::vector<T>& close
			, int peroid = TA_INTEGER_DEFAULT)
			: PeroidParam<T>(0, high.size() - 1, peroid, &high, &low, &close, nullptr)
		{
			if (high.size() != low.size() || low.size() != close.size())
			{
				throw ParamsException("data_serial_size_not_same");
			}
		}

		DX_Param(const std::vector<T>& high
			, const std::vector<T>& low
			, const std::vector<T>& close
			, int start
			, int end
			, int peroid = TA_INTEGER_DEFAULT)
			: PeroidParam<T>(start, end, peroid, &high, &low, &close, nullptr)
		{
			if (high.size() != low.size() || low.size() != close.size())
			{
				throw ParamsException("data_serial_size_not_same");
			}
		}
	};
}

#endif