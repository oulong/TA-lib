#ifndef __TA_PARAM_H__
#define __TA_PARAM_H__

#include <vector>
#include <stdarg.h>



namespace TA
{
	template<typename T>
	class BaseParam
	{
	public:
		BaseParam(int start, int end)
			: start_idx_(start)
			, end_idx_(end)
		{
		}

		BaseParam(int start, int end, const std::vector<T>& serial)
			: start_idx_(start)
			, end_idx_(end)
		{
			if (serial.empty())
			{				
				throw ParamsException("empty_data");
			}

			in_v_data_serial_.push_back(serial);
		}

		BaseParam(int start, int end, int args, ...)
			: start_idx_(start)
			, end_idx_(end)
		{
			va_list arg_ptr;			
			va_start(arg_ptr, args);

			for (int i = 0; i < args; i++)
			{
				const std::vector<T>* const  _arg = va_arg(arg_ptr, const std::vector<T>* const);			
				in_v_data_serial_.push_back(*_arg);
			}
			va_end(arg_ptr);
		}

		virtual ~BaseParam()
		{
		}

		const std::vector<T>& serial(int idx = 0) const
		{
			return in_v_data_serial_[idx];
		}

		int serial_param_size() const
		{
			return in_v_data_serial_.size();
		}

		const T* buffer(int idx = 0) const
		{
			return &(in_v_data_serial_[idx])[0];
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
		std::vector<std::vector<T>>	in_v_data_serial_;
	};

	template<typename T>
	class PeroidParam : public BaseParam<T>
	{
	public:
		PeroidParam(int start, int end, int peroid, const std::vector<T>& serial)
			: BaseParam<T>(start, end, serial)
			, peroid_(peroid)
		{
			if (peroid < 1 || peroid >= 100000)
			{				
				throw ParamsException("peroid out [1-100000]");
			}
		}

		PeroidParam(int start, int end, int peroid, int args, ...)
			: BaseParam<T>(start, end)
			, peroid_(peroid)
		{
			va_list arg_ptr;
			va_start(arg_ptr, args);

			for (int i = 0; i < args; i++)
			{
				const std::vector<T>* const  _arg = va_arg(arg_ptr, const std::vector<T>* const);


				in_v_data_serial_.push_back(*_arg);
			}
			va_end(arg_ptr);
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