#pragma once

#include <chrono>
#include <string>
#include <vector>

namespace OstrichEgg
{
	template <typename DurationType>
	::time_t epoch_to_time_t(long long Epoch)
	{
		DurationType duration(Epoch);
		std::chrono::system_clock::time_point timePointEpoch(duration);

		return std::chrono::system_clock::to_time_t(timePointEpoch);
	}

	class EpochConverter final
	{
	public:
		enum class Format
		{
			year,
			month,
			day,
			hour,
			minute,
			second,
		};

		enum class Type
		{
			UTC,
			Local,
		};

	public:
		EpochConverter(::time_t time);
		~EpochConverter() = default;

		std::string toString(Format format, Type type) const;
		std::vector<std::string> toString(const std::vector<Format>& formats, Type type) const;

	private:
		std::string getSpecifier(Format format) const;

	private:
		const ::time_t time_;
	};
}