#include "TA_Lib.h"

namespace TA
{
	template <typename T>
	std::shared_ptr<T> make_shared_array(size_t size)
	{
		return std::move(std::shared_ptr<T>(new T[size], std::default_delete<T[]>()));
	}	

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

