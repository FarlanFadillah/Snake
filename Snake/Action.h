#pragma once
#include <string>
class Action
{
protected:
	std::string m_name;
	std::string m_type;

public:

	Action();
	Action(const std::string& name, const std::string& type);

	const std::string& name();
	const std::string& type();
};

