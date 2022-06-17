#include <iostream>
#include <vector>

#include "MyApi.h"

int main()
{
	MyApi::CreateScript("test.lua");

	MyApi::ScriptStart();

	while (true)
	{
		MyApi::ScriptUpdate(5.f);
	}
}

