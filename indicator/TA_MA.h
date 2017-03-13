#ifndef __TA_MA_H__
#define __TA_MA_H__

namespace TA
{
	/*
	* TA_MA - Moving average
	*
	* serial  = data
	*
	* Optional Parameters
	* -------------------
	* peroid:(From 1 to 100000)
	*    Number of period
	*
	* type:
	*    Type of Moving Average
	*
	*
	*/
	template<typename T>
	class MA_Param : public PeroidParam<T>
	{
	public:
		MA_Param(const std::vector<T>& serial
			, int start
			, int end
			, int peroid = TA_INTEGER_DEFAULT
			, TA_MAType type = TA_MAType(TA_INTEGER_DEFAULT))
			: PeroidParam<T>(start, end, serial, peroid)
			, type_(type)
		{
			if (peroid < 1 || peroid >= 100000)
			{
				throw std::runtime_error("params_error");
			}
		}

		MA_Param(const std::vector<T>& serial
			, int peroid = TA_INTEGER_DEFAULT
			, TA_MAType type = TA_MAType(TA_INTEGER_DEFAULT))
			: PeroidParam<T>(0, serial.size() - 1, serial, peroid)
			, type_(type)
		{
			
		}

		TA_MAType type() const
		{
			return type_;
		}

	private:
		TA_MAType	type_;
	};

}

#endif