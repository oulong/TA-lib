#ifndef __TA_MACD_H__
#define __TA_MACD_H__

namespace TA
{
	/*
	* TA_MACD - Moving Average Convergence/Divergence
	*
	* Input  = double
	* Output = double, double, double
	*
	* Optional Parameters
	* -------------------
	* optInFastPeriod:(From 2 to 100000)
	*    Number of period for the fast MA
	*
	* optInSlowPeriod:(From 2 to 100000)
	*    Number of period for the slow MA
	*
	* optInSignalPeriod:(From 1 to 100000)
	*    Smoothing for the signal line (nb of period)
	*
	*
	*/
	template <typename T>
	class MACD_Param : public PeroidParam < T >
	{
	public:
		MACD_Param(const std::vector<T>& serial
			, int optInFastPeriod = TA_INTEGER_DEFAULT
			, int optInSlowPeriod = TA_INTEGER_DEFAULT
			, int optInSignalPeriod = TA_INTEGER_DEFAULT)
			: PeroidParam<T>(0
			, serial.size() - 1
			, serial
			, 3
			, optInFastPeriod, optInSlowPeriod, optInSignalPeriod)
		{

		}

		MACD_Param(const std::vector<T>& serial
			, int start
			, int end
			, int optInFastPeriod = TA_INTEGER_DEFAULT
			, int optInSlowPeriod = TA_INTEGER_DEFAULT
			, int optInSignalPeriod = TA_INTEGER_DEFAULT)
			: PeroidParam<T>(start
			, end
			, serial
			, 3
			, optInFastPeriod, optInSlowPeriod, optInSignalPeriod)
		{

		}
	};
}

#endif