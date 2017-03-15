#include "TA_Abstract_Param.h"
#include "base/TA_Util.h"
#include "base/TA_Exception.h"

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
}