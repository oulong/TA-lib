namespace TA
{
	template<typename T>
	AbsOut<T> Lib::CallFunc(const std::string& name, int start_idx, int end_idx, const AbsBaseParam* const args, ...)
	{
		va_list args_ptr;
		va_start(args_ptr, end_idx);

		std::vector<const AbsBaseParam* const> v_args;
		for (int i = 0;; ++i)
		{
			const AbsBaseParam* const  _arg = va_arg(args_ptr, const AbsBaseParam* const);
			if (_arg == nullptr)
			{
				break;
			}
			v_args.push_back(_arg);
		}

		va_end(args_ptr);

		return _call_func<T>(name.c_str(), start_idx, end_idx, v_args);
	}

	template<typename T>
	AbsOut<T> Lib::_call_func(const char* name, int start_idx, int end_idx, const std::vector<const AbsBaseParam* const>& v_args)
	{
		TA_ParamHolder *params = nullptr;
		try
		{
			TA_RetCode retCode = TA_SUCCESS;
			const TA_FuncHandle *handle = nullptr;
			const TA_FuncInfo *theInfo = nullptr;

			retCode = TA_GetFuncHandle(name, &handle);
			_handle_error(retCode);

			retCode = TA_GetFuncInfo(handle, &theInfo);
			_handle_error(retCode);

			retCode = TA_ParamHolderAlloc(handle, &params);
			_handle_error(retCode);

			//todo logic;
			int s_params_idx = 0;
			_full_input_params(params, theInfo, s_params_idx, v_args);

			s_params_idx += theInfo->nbInput;
			_full_opt_input_params(params, theInfo, s_params_idx, v_args);

			s_params_idx += theInfo->nbOptInput;

			AbsOut<T> out(end_idx - start_idx + 1);
			_full_output_params(params, theInfo, v_args, out);

			retCode = TA_CallFunc(params, start_idx, end_idx, out.begin_ptr(), out.nb_element_ptr());
			_handle_error(retCode);

			TA_ParamHolderFree(params);

			return std::move(out);
		}
		catch (const Exception& e)
		{
			if (params)
			{
				TA_ParamHolderFree(params);
			}

			e.rethrow();
		}

		//to eliminate compile warning!
		throw LogicException("");
	}
}

