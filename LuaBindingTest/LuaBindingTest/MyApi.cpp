#include "MyApi.h"

#include <vector>

#include "LuaScriptComponent.h"

std::vector<LuaScriptComponent*> scripts;

void MyApi::Print(const std::string& str)
{
	std::cout << str << std::endl;
}

void MyApi::CreateScript(const std::string& file)
{
	scripts.emplace_back(new LuaScriptComponent(file));
}

Component* MyApi::GetComponent(const std::string& file)
{
	for (int i = 0; i < scripts.size(); ++i)
	{
		if (scripts[i]->GetFile() == file)
			return scripts[i];
	}

	return nullptr;
}

void MyApi::ScriptStart()
{
	for (auto& script : scripts)
	{
		script->Start();
	}
}

void MyApi::ScriptUpdate(float delta)
{
	for (auto& script : scripts)
	{
		script->Update(delta);
	}
}
