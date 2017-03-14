#ifndef __TA_ABSTRACT_PARAM_H__
#define __TA_ABSTRACT_PARAM_H__

#include "ta_libc.h"
#include <vector>
#include <memory>
#include <utility>

namespace TA
{
	class AbsBaseParam
	{
	public:
		virtual ~AbsBaseParam() {}
	};


	template<typename T>
	class AbsInputParam : public AbsBaseParam
	{
	public:
		AbsInputParam(const std::vector<T>& serial)
		{
			v_serial_data_.push_back(serial);
		}

		const std::vector<T>& serial(int idx = 0) const
		{
			return v_serial_data_[idx];
		}

		int serial_param_size() const
		{
			return v_serial_data_.size();
		}

		const T* buffer(int idx = 0) const
		{
			return &(v_serial_data_[idx])[0];
		}
	private:
		std::vector<std::vector<T>> v_serial_data_;
	};

	template<typename T>
	class AbsOptInputParam : public AbsBaseParam
	{
	public:
		AbsOptInputParam();

		AbsOptInputParam(const T& data) : data_(data)
		{
		}

		const T& data() const 
		{
			return data_;  
		}
	private:
		T	data_;
	};

	
	class AbsOuts
	{
	public:
		AbsOuts(int size);		

		//todo realize
		//AbsOuts(AbsOuts&& ref) 		
		
		int*	new_alloc_int();
		double* new_alloc_real();

		int begin() const
		{
			return out_begin_;
		}
		
		int get_int(int idx, int serial_no = 0) const;
		double get_real(int idx, int serial_no = 0) const;
	private:
		int* begin()
		{
			return &out_begin_;
		}

		int* nb_element()
		{
			return &out_nb_element_;
		}
	private:
		int					idx_;
		int					size_;
		int					out_begin_;
		int					out_nb_element_;		
		std::vector<std::shared_ptr<int>>    v_int_serial_;
		std::vector<std::shared_ptr<double>> v_double_serial_;
		std::vector<std::pair<int, int>>	 v_value_map_;

		friend class Lib;
	};
}

#endif