#ifndef __TA_LINEARREG_H__
#define __TA_LINEARREG_H__

#include "TA_Param.h"

namespace TA
{
	/*
	* TA_LINEARREG - Linear Regression
	*
	* Input  = double
	* Output = double
	*
	* Optional Parameters
	* -------------------
	* optInTimePeriod:(From 2 to 100000)
	*    Number of period
	*
	*
	*/
	template<typename T>
	class LINEARREG_Param : public PeroidParam < T >
	{
	public:
		LINEARREG_Param(const std::vector<T>& serial, int peroid = 14)
			: PeroidParam(0, serial.size() - 1, peroid, serial)
		{

		}

		LINEARREG_Param(const std::vector<T>& serial
			, int start
			, int end
			, int peroid = 14)
			: PeroidParam<T>(start, end, peroid, serial)
		{

		}
	};
}

#endif