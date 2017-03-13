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

		BaseParam(const std::vector<T>& serial, int start, int end)
			: start_idx_(start)
			, end_idx_(end)
		{
			if (serial.empty())
			{				
				throw ParamsException("empty_data");
			}

			in_v_data_serial_.push_back(serial);
		}

		/*
		 * params end by nullptr;
		 */
		BaseParam(int start, int end, const std::vector<T>* const, ...)
			: start_idx_(start)
			, end_idx_(end)
		{
			va_list arg_ptr;			
			va_start(arg_ptr, end);

			for (int i = 0; ; i++)
			{
				const std::vector<T>* const  _arg = va_arg(arg_ptr, const std::vector<T>* const);
				if (_arg == nullptr)
				{
					break;
				}
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
		PeroidParam(int start, int end, const std::vector<T>& serial, int peroid)
			: BaseParam<T>(serial, start, end)
		{
			v_peroid_.push_back(peroid);
		}

		/*
		 * params end by nullptr;
		 */
		PeroidParam(int start, int end, int peroid, const std::vector<T>* const, ...)
			: BaseParam<T>(start, end)
		{
			v_peroid_.push_back(peroid);

			va_list arg_ptr;
			va_start(arg_ptr, peroid);
			
			for (int i = 0;;i++)
			{
				const std::vector<T>* const  _arg = va_arg(arg_ptr, const std::vector<T>* const);
				if (_arg == nullptr)
				{
					break;
				}

				in_v_data_serial_.push_back(*_arg);
			}

			va_end(arg_ptr);
		}

		PeroidParam(int start, int end, const std::vector<T>& serial, int args_peroid, int ,...)
			: BaseParam<T>(start, end, serial)
		{
			va_list arg_ptr;
			va_start(arg_ptr, args_peroid);
			
			for (int i = 0; i < args_peroid; i++)
			{
				int  _arg = va_arg(arg_ptr, int);
				v_peroid_.push_back(_arg);
			}

			va_end(arg_ptr);
		}

		PeroidParam(int start, int end, int args_serial, int args_peroid, ...)
			: BaseParam<T>(start, end)
		{			
			va_list arg_ptr;
			va_start(arg_ptr, args_peroid);
			
			for (int i = 0; i < args_serial; i++)
			{
				const std::vector<T>* const  _arg = va_arg(arg_ptr, const std::vector<T>* const);
				in_v_data_serial_.push_back(*_arg);
			}

			for (int i = 0; i < args_peroid; i++)
			{
				int _arg = va_arg(arg_ptr, int);
				v_peroid_.push_back(_arg);
			}

			va_end(arg_ptr);
		}

		virtual ~PeroidParam() 
		{
		}

		int peroid(int idx = 0) const
		{
			return v_peroid_[idx];
		}

		int peroid_param_size() const
		{
			return v_peroid_.size();
		}
	protected:
		std::vector<int> v_peroid_;
	};
}

#endif