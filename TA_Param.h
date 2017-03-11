#ifndef __TA_PARAM_H__
#define __TA_PARAM_H__

#include <vector>

namespace TA
{
	template<typename T>
	class BaseParam
	{
	public:
		BaseParam(const std::vector<T>& serial, int start, int end)
			: in_v_data_serial_(serial)
			, start_idx_(start)
			, end_idx_(end)
		{
			if (in_v_data_serial_.empty())
			{				
				throw ParamsException("empty_data");
			}
		}

		virtual ~BaseParam()
		{
		}

		const std::vector<T>& serial() const
		{
			return in_v_data_serial_;
		}

		const T* buffer() const
		{
			return &in_v_data_serial_[0];
		}

		int start() const
		{
			return start_idx_;
		}

		int end() const
		{
			return end_idx_;
		}
	protected:
		int				start_idx_;
		int				end_idx_;
		std::vector<T>	in_v_data_serial_;
	};

	template<typename T>
	class PeroidParam : public BaseParam<T>
	{
	public:
		PeroidParam(const std::vector<T>& serial, int start, int end, int peroid)
			: BaseParam<T>(serial, start, end)
			, peroid_(peroid)
		{
			if (peroid < 1 || peroid >= 100000)
			{				
				throw ParamsException("peroid out [1-100000]");
			}
		}

		~PeroidParam() 
		{
		}

		int peroid() const
		{
			return peroid_;
		}
	protected:
		int	 peroid_;
	};
}

#endif