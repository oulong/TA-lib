#ifndef __TA_OUT_H__
#define __TA_OUT_H__

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
				throw std::runtime_error("params out");
			}

			return out_serial_[idx - out_beg_];
		}
	private:
		TA_Integer			out_beg_;
		std::vector<T>		out_serial_;
	};
}

#endif