#include "TA_Abstract_Param.h"
#include "base/TA_Util.h"

namespace TA
{
	//default interger param
	AbsOptInputParam<int>::AbsOptInputParam() : data_(TA_INTEGER_DEFAULT)
	{
	}

	//default real param
	AbsOptInputParam<double>::AbsOptInputParam() : data_(TA_REAL_DEFAULT)
	{
	}

	AbsOuts::AbsOuts(int size)
		: size_(size)
		, idx_(0)
		, out_begin_(0)
		, out_nb_element_(0)
	{
	}

	int* AbsOuts::new_alloc_int()
	{
		std::shared_ptr<int> serial = make_shared_array<int>(size_);
		v_int_serial_.push_back(serial);
		v_value_map_.push_back(std::make_pair<int, int>(0, v_int_serial_.size() - 1));

		return v_int_serial_.rbegin()->get();
	}

	double* AbsOuts::new_alloc_real()
	{
		std::shared_ptr<double> serial = make_shared_array<double>(size_);
		v_double_serial_.push_back(serial);
		v_value_map_.push_back(std::make_pair<int, int>(0, v_double_serial_.size() - 1));

		return v_double_serial_.rbegin()->get();
	}
}