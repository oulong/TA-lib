#include "TA_Exception.h"
#include <typeinfo>
#include <string>

namespace TA
{
	Exception::Exception(int code /* = 0 */)
		: _code(code)
	{

	}

	Exception::Exception(const std::string& msg, int code /* = 0 */)
		: _msg(msg)
		, _code(code)
	{

	}

	Exception::Exception(const std::string& msg, const std::string& args, int code /* = 0 */)
		: _msg(msg)
		, _code(code)
	{
		if (!args.empty())
		{
			_msg.append(":");
			_msg.append(args);
		}
	}

	const char* Exception::name() const throw()
	{
		return "Exception";
	}

	const char* Exception::className() const throw()
	{
		return typeid(*this).name();
	}

	const char* Exception::what() const
	{
		return name();
	}

	std::string Exception::displayText() const
	{
		std::string text = name();
		if (!_msg.empty())
		{
			text.append(": ");
			text.append(_msg);
		}

		//return text;
		return std::move(text);
	}

	void Exception::extendMessage(const std::string& arg)
	{
		if (!arg.empty())
		{
			if (!_msg.empty()) _msg.append(": ");
			_msg.append(arg);
		}
	}
		

	void Exception::rethrow() const
	{
		throw *this;
	}

	TA_IMPLEMENT_EXCEPTION(LogicException, Exception, "Logic exception")
	TA_IMPLEMENT_EXCEPTION(NullPointerException, LogicException, "Null pointer")
	TA_IMPLEMENT_EXCEPTION(ParamsException, LogicException, "Params error")
	TA_IMPLEMENT_EXCEPTION(RangeException, LogicException, "Out of range")	
	TA_IMPLEMENT_EXCEPTION(AssertException, LogicException, "Assert exception")
	TA_IMPLEMENT_EXCEPTION(CallTaImplException, LogicException, "Call TA-Lib Impl")
}