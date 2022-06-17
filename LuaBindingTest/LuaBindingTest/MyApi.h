#pragma once

#include <string>
#include <iostream>

class Component;

namespace MyApi
{
	void Print(const std::string& str);

	void CreateScript(const std::string& file);
	Component * GetComponent(const std::string & file);

	void ScriptStart();
	void ScriptUpdate(float delta);
}
