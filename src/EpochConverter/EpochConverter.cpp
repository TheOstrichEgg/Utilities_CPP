#include "EpochConverter.h"

#include <iostream>
#include <algorithm>

#include <time.h>

using namespace OstrichEgg;

constexpr auto bufferSize = 128;

EpochConverter::EpochConverter(::time_t time) :
	time_(time)
{
}

std::string EpochConverter::toString(Format format, Type type) const
{
	::tm _tm;

	switch (type)
	{
	case Type::UTC:
		gmtime_s(&_tm, &time_); break;
	case Type::Local:
		localtime_s(&_tm, &time_); break;
	default:
		return "";
	}

	char buffer[bufferSize] = { 0, };
	::strftime(buffer, sizeof(buffer), getSpecifier(format).c_str(), &_tm);

	return std::string(buffer);
}

std::vector<std::string> EpochConverter::toString(const std::vector<Format>& formats, Type type) const
{
	std::vector<std::string> strings;

	std::transform(formats.begin(), formats.end(),
		std::back_inserter(strings), [this, &type](const Format format)
		{
			return toString(format, type);
		});

	return strings;
}

std::string EpochConverter::getSpecifier(Format format) const
{
	switch (format)
	{
	case Format::year:   return "%Y";
	case Format::month:	 return "%m";
	case Format::day:	 return "%d";
	case Format::hour:	 return "%H";
	case Format::minute: return "%M";
	case Format::second: return "%S";
	default: return "";
	}
}
