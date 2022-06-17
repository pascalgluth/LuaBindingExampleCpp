#include "LuaScriptComponent.h"

#include "MyApi.h"

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};

#include "LuaBridge/LuaBridge.h"


LuaScriptComponent::LuaScriptComponent(const std::string& file)
{
	m_state = luaL_newstate();
	luaL_openlibs(m_state);
	luaL_loadfile(m_state, file.c_str());
	m_scriptFile = file;

	luabridge::getGlobalNamespace(m_state)
		.addFunction("Print", &MyApi::Print)
		.beginClass<Component>("Component")
		.addConstructor<void(*)()>()
		.addFunction("GetOwner", &Component::GetOwner)
		.addFunction("PrintHm", &Component::Test)
		.addData("hm", &Component::hm)
		.endClass()
		.beginClass<Object>("Object")
		.addFunction("GetSomething", &Object::GetSomething)
		.endClass()
		.addFunction("GetComponent", &MyApi::GetComponent);
}

LuaScriptComponent::~LuaScriptComponent()
{
	lua_close(m_state);
}

void LuaScriptComponent::Start()
{
	Component::Start();

	luabridge::push<Component*>(m_state, this);
	lua_setglobal(m_state, "this");

	if (luaL_dofile(m_state, m_scriptFile.c_str()) != LUA_OK)
	{
		std::cerr << "Lua error: " << lua_tostring(m_state, -1) << std::endl;
		lua_pop(m_state, 1);
	}

	lua_getglobal(m_state, "start");
	if (lua_isfunction(m_state, -1))
	{
		if (lua_pcall(m_state, 0, 0, 0) != LUA_OK)
		{
			std::cerr << "Lua error: " << lua_tostring(m_state, -1) << std::endl;
			lua_pop(m_state, 1);
		}
	}

	hm = "lua is hm";
}

void LuaScriptComponent::Update(float deltaTimer)
{
	Component::Update(deltaTimer);

	lua_getglobal(m_state, "update");
	if (lua_isfunction(m_state, -1))
	{
		lua_pushnumber(m_state, deltaTimer);

		if (lua_pcall(m_state, 1, 0, 0) != LUA_OK)
		{
			std::cerr << "Lua error: " << lua_tostring(m_state, -1) << std::endl;
			lua_pop(m_state, 1);
		}
	}
}
