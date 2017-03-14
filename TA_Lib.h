#ifndef __TA_LIB_H__
#define __TA_LIB_H__

#include <vector>
#include <stdexcept>
#include <memory> 
#include <iostream>

#include "ta_libc.h"
#include "base/TA_Util.h"
#include "base/TA_Exception.h"

#include "TA_Out.h"
#include "TA_Param.h"
#include "TA_Abstract_Param.h"

#include "indicator/TA_MA.h"
#include "indicator/TA_LINEARREG.h"
#include "indicator/TA_DX.h"
#include "indicator/TA_MACD.h"

namespace TA
{
	class Lib
	{
	public:
		Lib();
		~Lib();		

		/*Call impl by abstract*/
		AbsOuts CallFunc(const std::string& name, int start_idx, int end_idx, const AbsBaseParam* const args, ...);

		/*TA_MA - Moving average*/
		Out<> MA(const MA_Param<float>& param);
		Out<> MA(const MA_Param<double>& param);

		/*TA_LINEARREG - Linear Regression*/
		Out<> LINEARREG(const LINEARREG_Param<float>& param);
		Out<> LINEARREG(const LINEARREG_Param<double>& param);

		/*TA_DX - Directional Movement Index*/
		Out<> DX(const DX_Param<float>& param);
		Out<> DX(const DX_Param<double>& param);

		/*TA_MACD - Moving Average Convergence / Divergence*/
		Outs<double, 3> MACD(const MACD_Param<float>& param);
		Outs<double, 3> MACD(const MACD_Param<double>& param);		

	private:
		void _handle_error(TA_RetCode code) const;	
		AbsOuts _call_func(const char* name, int start_idx, int end_idx, const std::vector<const AbsBaseParam* const>& v_args);
		void _full_input_params(TA_ParamHolder *params, const TA_FuncInfo *the_info, int s_params_idx, const std::vector<const AbsBaseParam* const>& v_args);
		void _full_opt_input_params(TA_ParamHolder *params, const TA_FuncInfo *the_info, int s_params_idx, const std::vector<const AbsBaseParam* const>& v_args);
		void _full_output_params(TA_ParamHolder *params, const TA_FuncInfo *the_info, const std::vector<const AbsBaseParam* const>& v_args, AbsOuts& outs);
	};

}


#endif __TA_LIB_H__