#include "inc/packet.hpp"

std::unique_ptr<RanPacket> parseLine(std::string_view line) {
	std::unique_ptr<RanPacket>	parsed_ptr;
	size_t						pipe_pos;
	size_t						start_pos;
	std::string_view 			timestamp_chunk;
	std::string_view 			id_chunk;
	std::string_view 			payload_chunk;
	std::string_view 			error_chunk;
	std::optional<std::string>	final_error = std::nullopt;
	
	if (line.empty()) return (nullptr);

	size_t pipes = std::count(line.begin(), line.end(), '|');
    if (pipes < 2) return nullptr;

	pipe_pos = line.find('|');
	timestamp_chunk = line.substr(0, pipe_pos);

	start_pos = pipe_pos + 1;
	pipe_pos = line.find('|', start_pos);
	id_chunk = line.substr(start_pos, (pipe_pos - start_pos));

	start_pos = pipe_pos + 1;
	pipe_pos = line.find('|', start_pos);
	if(pipe_pos == std::string_view::npos)
		payload_chunk = line.substr(start_pos);
	else
	{
		payload_chunk = line.substr(start_pos, (pipe_pos - start_pos));
		start_pos = pipe_pos + 1;
		error_chunk = line.substr(start_pos);
	}

	if (!error_chunk.empty()) {
        final_error = std::string(error_chunk);
    }

	try {
   		parsed_ptr = std::make_unique<RanPacket>(std::stoull(std::string(timestamp_chunk)), std::string(id_chunk), std::string(payload_chunk), std::move(final_error));
	} catch (const std::exception& e) {
    	std::cerr << "Critic error trying to parse line: " << e.what() << "\n";
   		return (nullptr);
	}
	
	return (parsed_ptr);
}