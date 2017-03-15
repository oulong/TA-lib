#include <random>
#include <iostream>
#include <time.h>
#include <assert.h>

#include "../TA_Lib.h"
#include "TA_Test.h"

using namespace TA;

int Test_All()
{
	Test_MA();

	return 0;
}

int Test_MA()
{
	TA::Lib lib;

	std::default_random_engine  engine((int)time(NULL));
	std::uniform_real_distribution<double> u(10, 50);

	std::vector<double> v_d_serial;
	for (int i = 0; i < 500; i++)
	{	
		v_d_serial.push_back(u(engine));	
	}

	TA::Out<> out_noraml = lib.MA(MA_Param<double>(v_d_serial));
	AbsOut<double> out_abstract = lib.CallFunc<double>(
		"MA", 0, v_d_serial.size() - 1
		, &AbsInputParam<double>(v_d_serial)
		, &AbsOptInputParam<int>()
		, &AbsOptInputParam<int>()
		, nullptr);

	assert(out_noraml.begin() == out_abstract.begin() && "ma_begin error");
	assert(out_noraml.nb_elements() == out_abstract.nb_elements() && "ma_nb_elments_error");

	for (int i = out_noraml.begin(); i < out_noraml.nb_elements(); i++)
	{
		double diff_val = std::abs(out_noraml[i] - out_abstract.serial(i));		
		assert(diff_val < 0.0001 && "ma calc error");
	}

	std::cout << "test ma successfully !" << std::endl;

	return 0;
}

