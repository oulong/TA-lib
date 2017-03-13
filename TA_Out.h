#ifndef __TA_OUT_H__
#define __TA_OUT_H__

#include <stdarg.h>

namespace TA
{
	template<typename T = double>
	class Out
	{
	public:
		Out(int out_beg, int out_nb_element, const std::shared_ptr<T>& serial)
			: out_beg_(out_beg)
		{
			for (int i = 0; i++ < out_nb_element;)
			{
				out_serial_.push_back(serial.get()[i]);
			}
		}

		int size() const
		{
			return out_serial_.size();
		}

		int begin() const
		{
			return out_beg_;
		}

		T operator[](int idx) const
		{
			if (idx < out_beg_)
			{
				throw RangeException("[] idx out");
			}

			return out_serial_[idx - out_beg_];
		}
	private:
		TA_Integer			out_beg_;
		std::vector<T>		out_serial_;
	};

	template<typename T = double, int N = 1>
	class Outs
	{
	public:
		Outs(int out_beg, int out_nb_element, const std::shared_ptr<T>* const, ...)
			: out_beg_(out_beg)
		{
			va_list arg_ptr;
			va_start(arg_ptr, out_nb_element);
			for (int i = 0; i < N; i++)
			{				
				const std::shared_ptr<T>* const _arg = va_arg(arg_ptr, const std::shared_ptr<T>* const);
				for (int k = 0; k++ < out_nb_element;)
				{
					out_serial_[i].push_back((*_arg).get()[i]);
				}
			}
		
			va_end(arg_ptr);
		}

		int size() const
		{
			return out_serial_[0].size();
		}

		int begin() const
		{
			return out_beg_;
		}

		const std::vector<T>&  serial(int idx = 0) const
		{
			if (idx < 0 || idx >= N)
			{
				throw RangeException("serial idx out");
			}

			return out_serial_[idx];
		}
	private:
		TA_Integer			out_beg_;
		std::vector<T>		out_serial_[N];
	};
}

#endif