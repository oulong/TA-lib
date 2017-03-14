#ifndef __TA_UTIL_H__
#define __TA_UTIL_H__


#include <memory>

namespace TA
{
	template <typename T>
	std::shared_ptr<T> make_shared_array(size_t size)
	{
		return std::move(std::shared_ptr<T>(new T[size], std::default_delete<T[]>()));
	}
};

#endif
