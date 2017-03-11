#ifndef __TA_LIB_H__
#define __TA_LIB_H__

#include "ta_libc.h"
#include <vector>
#include <stdexcept>
#include <memory> 

#include "TA_Exception.h"
#include "TA_Out.h"
#include "TA_Param.h"
#include "TA_MA.h"
#include "TA_LINEARREG.h"

namespace TA
{
	class Lib
	{
	public:
		Lib();
		~Lib();		

		/*TA_MA - Moving average*/
		Out<> MA(const MA_Param<float>& param);
		Out<> MA(const MA_Param<double>& param);

		/*TA_LINEARREG - Linear Regression*/
		Out<> LINEARREG(const LINEARREG_Param<float>& param);
		Out<> LINEARREG(const LINEARREG_Param<double>& param);
	private:
		void _handle_error(TA_RetCode code) const;
	};

}


#endif __TA_LIB_H__