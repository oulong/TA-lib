#ifndef __TA_LIB_H__
#define __TA_LIB_H__

#include "ta_libc.h"
#include <vector>
#include <stdexcept>
#include <memory> 

#include "TA_Out.h"
#include "TA_Param.h"
#include "base/TA_Exception.h"
#include "indicator/TA_MA.h"
#include "indicator/TA_LINEARREG.h"
#include "indicator/TA_DX.h"

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

		/*TA_DX - Directional Movement Index*/
		Out<> DX(const DX_Param<float>& param);
		Out<> DX(const DX_Param<double>& param);
	private:
		void _handle_error(TA_RetCode code) const;
	};

}


#endif __TA_LIB_H__