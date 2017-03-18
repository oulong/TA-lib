#include "TA_Lib.h"

namespace TA
{
	Lib::Lib()
	{
		TA_Initialize();
	}

	Lib::~Lib()
	{
		TA_Shutdown();
	}

	void Lib::_handle_error(TA_RetCode ret_code) const
	{
		if (ret_code == TA_SUCCESS)
		{
			return;
		}

		const static struct error_map {
			int code;			
			const char* msg;
		} error_map[] = {			
			{ TA_LIB_NOT_INITIALIZE , "LibNotInitialize: TA_Initialize was not successfully called"},
			{ TA_BAD_PARAM , "BadParam: A parameter is out of range"},
			{ TA_ALLOC_ERR , "AllocErr: Possibly out-of-memory "},
			{ TA_GROUP_NOT_FOUND , "GroupNotFound"},
			{ TA_FUNC_NOT_FOUND , "FuncNotFound"},
			{ TA_INVALID_HANDLE , "InvalidHandle"},
			{ TA_INVALID_PARAM_HOLDER , "InvalidParamHolder"},
			{ TA_INVALID_PARAM_HOLDER_TYPE , "InvalidParamHolderType"},
			{ TA_INVALID_PARAM_FUNCTION , "InvalidParamFunction"},
			{ TA_INPUT_NOT_ALL_INITIALIZE , "InputNotAllInitialize"},
			{ TA_OUTPUT_NOT_ALL_INITIALIZE , "OutputNotAllInitialize"},
			{ TA_OUT_OF_RANGE_START_INDEX , "OutOfRangeStartIndex"},
			{ TA_OUT_OF_RANGE_END_INDEX , "OutOfRangeEndIndex"},
			{ TA_INVALID_LIST_TYPE , "InvalidListType"},
			{ TA_BAD_OBJECT , "BadObject"},
			{ TA_NOT_SUPPORTED , "NotSupported"},
			{ TA_INTERNAL_ERROR, "InternalError"},
			{ TA_UNKNOWN_ERR , "TA_UNKNOWN_ERR"},
		};

		for (int i = 0; i < sizeof(error_map); i++)
		{
			if (error_map[i].code == ret_code)
			{				
				throw CallTaImplException(error_map[i].msg, error_map[i].code);
			}
		}
		
		throw CallTaImplException("unknown_error", ret_code);
	}

	void Lib::_full_input_params(TA_ParamHolder *params
		, const TA_FuncInfo *the_info
		, int s_params_idx
		, const std::vector<const AbsBaseParam* const>& v_args)
	{
		TA_RetCode retCode = TA_SUCCESS;
		const TA_InputParameterInfo *paramInfo = nullptr;		
		for (int i = 0; i < (int)the_info->nbInput; i++, s_params_idx++)
		{
			if ((int)v_args.size() <= s_params_idx)
			{
				throw ParamsException("Input params not enough", " In index: " + std::to_string(i));
			}

			retCode = TA_GetInputParameterInfo(the_info->handle, s_params_idx, &paramInfo);
			_handle_error(retCode);
			switch (paramInfo->type)
			{
			case TA_Input_Price:
			{
				const AbsInputParam<double>* const _ptr = dynamic_cast<const AbsInputParam<double>* const>(v_args[s_params_idx]);
				if (nullptr == _ptr)
				{
					throw ParamsException("Need input real", " In index: " + std::to_string(i));
				}

				if (_ptr->serial_param_size() != 6)
				{
					throw ParamsException("Price serial size error");
				}

				retCode = TA_SetInputParamPricePtr(params, i
					, _ptr->buffer(0)
					, _ptr->buffer(1)
					, _ptr->buffer(2)
					, _ptr->buffer(3)
					, _ptr->buffer(4)
					, _ptr->buffer(5));

				_handle_error(retCode);
			}
			break;
			case TA_Input_Real:
			{
				const AbsInputParam<double>* const _ptr = dynamic_cast<const AbsInputParam<double>* const>(v_args[s_params_idx]);
				if (nullptr == _ptr)
				{
					throw ParamsException("Need input real", " In index: " + std::to_string(i));
				}

				retCode = TA_SetInputParamRealPtr(params, i, _ptr->buffer());
				_handle_error(retCode);
			}
			break;
			case TA_Input_Integer:
			{
				const AbsInputParam<int>* const _ptr = dynamic_cast<const AbsInputParam<int>* const>(v_args[s_params_idx]);
				if (nullptr == _ptr)
				{
					throw ParamsException("Need input integer", " In index: " + std::to_string(i));
				}

				retCode = TA_SetInputParamIntegerPtr(params, i, _ptr->buffer());
				_handle_error(retCode);
			}
			break;
			}
		}
	}

	void Lib::_full_opt_input_params(TA_ParamHolder *params, const TA_FuncInfo *the_info, int s_params_idx, const std::vector<const AbsBaseParam* const>& v_args)
	{
		TA_RetCode retCode = TA_SUCCESS;
		const TA_OptInputParameterInfo *optParamInfo = nullptr;
		for (int i = 0; i < (int)the_info->nbOptInput; i++, s_params_idx++)
		{
			retCode = TA_GetOptInputParameterInfo(the_info->handle, i, &optParamInfo);
			_handle_error(retCode);
			switch (optParamInfo->type)
			{
			case TA_OptInput_RealRange:
			case TA_OptInput_RealList:
			{
				const AbsOptInputParam<double>* const _ptr = dynamic_cast<const AbsOptInputParam<double>* const>(v_args[s_params_idx]);
				if (nullptr == _ptr)
				{
					throw ParamsException("Opt need input real", " in index: " + std::to_string(i));
				}
				retCode = TA_SetOptInputParamReal(params, i, _ptr->data());
				_handle_error(retCode);
			}
			break;
			case TA_OptInput_IntegerRange:
			case TA_OptInput_IntegerList:
			{
				const AbsOptInputParam<int>* const _ptr = dynamic_cast<const AbsOptInputParam<int>* const>(v_args[s_params_idx]);
				if (nullptr == _ptr)
				{
					throw ParamsException("Opt need input integer", " in index: " + std::to_string(i));
				}
				retCode = TA_SetOptInputParamInteger(params, i, _ptr->data());
				_handle_error(retCode);
			}
			break;
			}
		}
	}

	
	template<>
	void Lib::_full_output_params<int>(TA_ParamHolder *params, const TA_FuncInfo *the_info, const std::vector<const AbsBaseParam* const>& v_args, AbsOut<int>& out)
	{
		TA_RetCode retCode = TA_SUCCESS;
		const TA_OutputParameterInfo *outParamInfo = nullptr;

		for (int i = 0; i < (int)the_info->nbOutput; i++)
		{
			retCode = TA_GetOutputParameterInfo(the_info->handle, i, &outParamInfo);
			_handle_error(retCode);
			switch (outParamInfo->type)
			{
			case TA_Output_Real:
			{
				throw ParamsException("Only support one type of integer.", "template must be integer");
			}
			break;
			case TA_Output_Integer:
			{
				retCode = TA_SetOutputParamIntegerPtr(params, i, out.new_alloc());
				_handle_error(retCode);
			}
			break;
			}
		}
	}
	
	template<>
	void Lib::_full_output_params(TA_ParamHolder *params, const TA_FuncInfo *the_info, const std::vector<const AbsBaseParam* const>& v_args, AbsOut<double>& out)
	{
		TA_RetCode retCode = TA_SUCCESS;
		const TA_OutputParameterInfo *outParamInfo = nullptr;

		for (int i = 0; i < (int)the_info->nbOutput; i++)
		{
			retCode = TA_GetOutputParameterInfo(the_info->handle, i, &outParamInfo);
			_handle_error(retCode);
			switch (outParamInfo->type)
			{
			case TA_Output_Real:
			{
				retCode = TA_SetOutputParamRealPtr(params, i, out.new_alloc());
				_handle_error(retCode);
			}
			break;
			case TA_Output_Integer:
			{
				throw ParamsException("Only support one type of real.", "template must be real");
			}
			break;
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////
	Out<> Lib::MA(const MA_Param<float>& param)
	{
		std::shared_ptr<double> out_serial = make_shared_array<double>(param.serial().size());
		TA_Integer	out_beg = 0;
		TA_Integer	out_nb_element = 0;

		TA_RetCode ret_code = TA_S_MA(param.start(), param.end(),
			param.buffer(),
			param.peroid(), param.type(),
			&out_beg, &out_nb_element, out_serial.get());

		_handle_error(ret_code);

		return std::move(Out<double>(out_beg, out_nb_element, out_serial));
	}

	Out<> Lib::MA(const MA_Param<double>& param)
	{
		std::shared_ptr<double> out_serial = make_shared_array<double>(param.serial().size());
		TA_Integer	out_beg = 0;
		TA_Integer	out_nb_element = 0;

		TA_RetCode ret_code = TA_MA(param.start(), param.end(),
			param.buffer(),
			param.peroid(), param.type(),
			&out_beg, &out_nb_element, out_serial.get());

		_handle_error(ret_code);

		return std::move(Out<double>(out_beg, out_nb_element, out_serial));
	}

	////////////////////////////////////////////////////////////////////////////////////////////
	Out<> Lib::LINEARREG(const LINEARREG_Param<float>& param)
	{
		std::shared_ptr<double> out_serial = make_shared_array<double>(param.serial().size());
		TA_Integer	out_beg = 0;
		TA_Integer	out_nb_element = 0;

		TA_RetCode ret_code = TA_S_LINEARREG(param.start(), param.end(),
			param.buffer(),
			param.peroid(), 
			&out_beg, &out_nb_element, out_serial.get());

		_handle_error(ret_code);

		return std::move(Out<double>(out_beg, out_nb_element, out_serial));
	}

	Out<> Lib::LINEARREG(const LINEARREG_Param<double>& param)
	{
		std::shared_ptr<double> out_serial = make_shared_array<double>(param.serial().size());
		TA_Integer	out_beg = 0;
		TA_Integer	out_nb_element = 0;

		TA_RetCode ret_code = TA_LINEARREG(param.start(), param.end(),
			param.buffer(),
			param.peroid(),
			&out_beg, &out_nb_element, out_serial.get());

		_handle_error(ret_code);

		return std::move(Out<double>(out_beg, out_nb_element, out_serial));
	}

	////////////////////////////////////////////////////////////////////////////////////////////
	Out<> Lib::DX(const DX_Param<float>& param)
	{
		std::shared_ptr<double> out_serial = make_shared_array<double>(param.serial().size());
		TA_Integer	out_beg = 0;
		TA_Integer	out_nb_element = 0;

		TA_RetCode ret_code = TA_S_DX(param.start(), param.end(),
			param.buffer(0),
			param.buffer(1),
			param.buffer(2),
			param.peroid(),
			&out_beg, &out_nb_element, out_serial.get());

		_handle_error(ret_code);

		return std::move(Out<double>(out_beg, out_nb_element, out_serial));
	}

	Out<> Lib::DX(const DX_Param<double>& param)
	{
		std::shared_ptr<double> out_serial = make_shared_array<double>(param.serial().size());
		TA_Integer	out_beg = 0;
		TA_Integer	out_nb_element = 0;

		TA_RetCode ret_code = TA_DX(param.start(), param.end(),
			param.buffer(0),
			param.buffer(1),
			param.buffer(2),
			param.peroid(),
			&out_beg, &out_nb_element, out_serial.get());

		_handle_error(ret_code);

		return std::move(Out<double>(out_beg, out_nb_element, out_serial));
	}

	////////////////////////////////////////////////////////////////////////////////////////////
	Outs<double, 3> Lib::MACD(const MACD_Param<float>& param)
	{
		std::shared_ptr<double> out_macd = make_shared_array<double>(param.serial().size());
		std::shared_ptr<double> out_macd_signal = make_shared_array<double>(param.serial().size());
		std::shared_ptr<double> out_macd_hist = make_shared_array<double>(param.serial().size());

		TA_Integer	out_beg = 0;
		TA_Integer	out_nb_element = 0;

		TA_RetCode ret_code = TA_S_MACD(param.start(), param.end(),
			param.buffer(),
			param.peroid(0),
			param.peroid(1),
			param.peroid(2),
			&out_beg, &out_nb_element, out_macd.get(), out_macd_signal.get(), out_macd_hist.get());

		_handle_error(ret_code);

		return std::move(Outs<double, 3>(out_beg, out_nb_element, &out_macd, &out_macd_signal, &out_macd_hist));
	}

	Outs<double, 3> Lib::MACD(const MACD_Param<double>& param)
	{
		std::shared_ptr<double> out_macd = make_shared_array<double>(param.serial().size());
		std::shared_ptr<double> out_macd_signal = make_shared_array<double>(param.serial().size());
		std::shared_ptr<double> out_macd_hist = make_shared_array<double>(param.serial().size());

		TA_Integer	out_beg = 0;
		TA_Integer	out_nb_element = 0;

		TA_RetCode ret_code = TA_MACD(param.start(), param.end(),
			param.buffer(),
			param.peroid(0),
			param.peroid(1),
			param.peroid(2),
			&out_beg, &out_nb_element, out_macd.get(), out_macd_signal.get(), out_macd_hist.get());

		_handle_error(ret_code);

		return std::move(Outs<double, 3>(out_beg, out_nb_element, &out_macd, &out_macd_signal, &out_macd_hist));
	}
}

