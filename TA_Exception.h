#ifndef __TA_EXCEPTION_H__
#define __TA_EXCEPTION_H__

/*
 * Copy from one project in open source. I forged...
 */

#include <stdexcept>
#include <typeinfo>
#include <string>

namespace TA
{
	class Exception : public std::exception
	{
	public:
		Exception(const std::string& msg, int code = 0);
		Exception(const std::string& msg, const std::string& args, int code = 0);

		virtual const char* name() const throw();
		virtual const char* className() const throw();
		virtual const char* what() const throw();

		const std::string& message() const;

		int code() const;

		std::string displayText() const;

		virtual void rethrow() const;

		virtual ~Exception() throw() {}
	protected:
		Exception(int code = 0);
		void message(const std::string& msg);
		void extendMessage(const std::string& arg);

	private:
		std::string _msg;
		int			_code;
	};

	inline const std::string& Exception::message() const
	{
		return _msg;
	}

	inline int Exception::code() const
	{
		return _code;
	}

	inline void Exception::message(const std::string& msg)
	{
		_msg = msg;
	}


#define TA_DECLARE_EXCEPTION_CODE(CLS, BASE, CODE)								\
	class CLS : public BASE														\
	{																			\
	public:																		\
		CLS(int code = CODE);													\
		CLS(const std::string& msg, int code = CODE);							\
		CLS(const std::string& msg, const std::string& arg, int code = CODE);	\
		virtual ~CLS() throw();													\
		const char* name() const throw();										\
		const char* className() const throw();									\
		void rethrow() const;													\
	};																			\

#define TA_DECLARE_EXCEPTION(CLS, BASE)			\
	TA_DECLARE_EXCEPTION_CODE(CLS, BASE, 0)

#define TA_IMPLEMENT_EXCEPTION(CLS, BASE, NAME)			\
	CLS::CLS(int code) : BASE(code)																\
	{																							\
	}																							\
	CLS::CLS(const std::string& msg, int code): BASE(msg, code)									\
	{																							\
	}																							\
	CLS::CLS(const std::string& msg, const std::string& arg, int code): BASE(msg, arg, code)	\
	{																							\
	}																							\
	CLS::~CLS() throw()																			\
	{																							\
	}																							\
	const char* CLS::name() const throw()														\
	{																							\
		return NAME;																			\
	}																							\
	const char* CLS::className() const throw()													\
	{																							\
		return typeid(*this).name();															\
	}																							\
	void CLS::rethrow() const																	\
	{																							\
		throw *this;																			\
	}																							\



	TA_DECLARE_EXCEPTION(LogicException, Exception)
	TA_DECLARE_EXCEPTION(NullPointerException, LogicException)
	TA_DECLARE_EXCEPTION(ParamsException, LogicException)
	TA_DECLARE_EXCEPTION(RangeException, LogicException)
	TA_DECLARE_EXCEPTION(AssertException, LogicException)
	TA_DECLARE_EXCEPTION(CallTaImplException, LogicException)
}

#endif