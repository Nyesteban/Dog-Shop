#pragma once

#include "Service.h"

class Tests
{
private:
	Service& service;
public:
	Tests(Service& s);
	void tests();
};