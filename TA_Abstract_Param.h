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

	template <typename T>
	class AbsOut
	{
	public:
		AbsOut(int buff_size) : buff_size_(buff_size)
		{
		}

		// todo realize
		// AbsOut(AbsOut&& ref) 	

		T* new_alloc()
		{
			std::shared_ptr<T> serial = make_shared_array<T>(buff_size_);
			v_serial_.push_back(serial);			

			return v_serial_.rbegin()->get();
		}

		const T&  serial(int idx, int serial_no = 0) const
		{
			if (serial_no < 0 || serial_no >= (int)v_serial_.size())
			{
				throw RangeException("serial idx out");
			}

			return v_serial_[serial_no].get()[idx];
		}

		int begin() const
		{
			return out_begin_;
		}

		int nb_elements() const
		{
			return out_nb_element_;
		}

	private:
		int* begin_ptr()
		{
			return &out_begin_;
		}

		int* nb_element_ptr()
		{
			return &out_nb_element_;
		}
	private:
		int buff_size_;
		int					out_begin_;
		int					out_nb_element_;
		std::vector<std::shared_ptr<T>>    v_serial_;

		friend class Lib;
	};

	
	//class AbsOuts
	//{
	//public:
	//	AbsOuts(int size);		

	//	//todo realize
	//	//AbsOuts(AbsOuts&& ref) 		
	//	
	//	int*	new_alloc_int();
	//	double* new_alloc_real();

	//	int begin() const
	//	{
	//		return out_begin_;
	//	}


	//	
	//	int get_int(int idx, int serial_no = 0) const;
	//	double get_real(int idx, int serial_no = 0) const;
	//private:
	//	int* begin()
	//	{
	//		return &out_begin_;
	//	}

	//	int* nb_element()
	//	{
	//		return &out_nb_element_;
	//	}
	//private:
	//	int					idx_;
	//	int					size_;
	//	int					out_begin_;
	//	int					out_nb_element_;		
	//	std::vector<std::shared_ptr<int>>    v_int_serial_;
	//	std::vector<std::shared_ptr<double>> v_double_serial_;
	//	std::vector<std::pair<int, int>>	 v_value_map_;

	//	friend class Lib;
	//};
}

#endif