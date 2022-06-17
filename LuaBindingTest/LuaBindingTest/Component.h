#pragma once

#include <iostream>

class Object
{
public:
	Object() {}
	virtual ~Object() {}

	float GetSomething() { return 5.f; }

};

class Component
{
public:
	Component() {}
	virtual ~Component() {}

	virtual void Start() {}
	virtual void Update(float deltaTimer) {}

	Object* GetOwner() { return new Object(); }
	void Test();

	std::string hm = "jfkdsjfölsdajfl";

};
