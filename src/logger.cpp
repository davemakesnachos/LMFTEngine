#include <logger.h>

std::string className(const std::string& prettyFunction)
{
	size_t colons = prettyFunction.find("::");
	size_t space = prettyFunction.find(" ");

	/* Avoid returning the name of the return value if it's part of a namespace */
	if (space > colons)
		colons = prettyFunction.find("::", colons + 1);
	if (colons == std::string::npos)
		return "::";

	size_t begin = prettyFunction.substr(0,colons).rfind(" ") + 1;
	size_t end = colons - begin;

	return prettyFunction.substr(begin,end);
}
