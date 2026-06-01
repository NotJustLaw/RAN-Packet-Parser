#include "inc/packet.hpp"

int main(){
	//Format: TIMESTAMP | ID | PAYLOAD (Hex) | ERROR_CODE
	std::vector<std::string> raw_logs = {
        "16200123|PKT_001|A1B2C3D4E5",          	// Healthy
        "16200124|PKT_X02|FF998877",            	// Corrupetd ID
        "16200125|PKT_003|112233|ERR_TIMEOUT",   	// Error
        "16200a126|PKT_004|999999"                	// Healthy
    };

	std::vector<std::unique_ptr<RanPacket>> valid_queue;
	std::vector<std::unique_ptr<RanPacket>> faulty_queue;

	for (const auto& line : raw_logs) {
		std::unique_ptr<RanPacket> packet = parseLine(line);

		if (!packet) {
        	std::cerr << "Skipping malformed line: " << line << "\n";
        	continue;
    	}

		if (packet->hasError() || (packet->getId().find('X') != std::string_view::npos)) {
			std::cout << "Error detected in ID: " << packet->getId() << std::endl;
			if (packet->hasError())
				std::cout << "Error: " << packet->getError() << std::endl;
			faulty_queue.push_back(std::move(packet));
		}
		else {
			std::cout << "Validated packet with ID: " << packet->getId() << std::endl;
			valid_queue.push_back(std::move(packet));
		}
	}

	std::cout << "Valid packets: " << valid_queue.size() << "\n";
    std::cout << "Faulty packets: " << faulty_queue.size() << "\n";

    return 0;
}