#pragma once

#include "Component.h"

typedef struct lua_State lua_State;

class LuaScriptComponent : public Component
{
public:
	LuaScriptComponent(const std::string& file);
	~LuaScriptComponent() override;

	void Start() override;
	void Update(float deltaTimer) override;

	const std::string& GetFile() { return m_scriptFile; }

private:
	lua_State* m_state;
	std::string m_scriptFile;

};
