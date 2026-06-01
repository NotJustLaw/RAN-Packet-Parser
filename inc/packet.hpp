#ifndef PACKET_HPP
# define PACKET_HPP

#include <iostream>
#include <memory>
#include <string>
#include <optional>
#include <utility>
#include <vector>
#include <algorithm>

class RanPacket {
	private:
		size_t 						TIMESTAMP;
		std::string					ID;
		std::string					PAYLOAD;
		std::optional<std::string>	ERROR;
	public:
	RanPacket(size_t ts, std::string id, std::string payload, std::optional<std::string> error) : TIMESTAMP(ts), ID(std::move(id)), PAYLOAD(std::move(payload)), ERROR(std::move(error)){};

	bool 				hasError() const {bool result = (ERROR != std::nullopt) ? true : false; return (result);};
	std::string_view	getId() const {return (std::string_view(ID));};
	std::string			getError() const {return ERROR.value_or("NONE");};
};

std::unique_ptr<RanPacket> parseLine(std::string_view line);

#endif