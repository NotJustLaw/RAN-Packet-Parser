// Type of input:
// 16200123|PKT_001|A1B2C3D4E5
// 16200124|PKT_002|FF99887766
// 16200125|PKT_003||ERR_SIGNAL_LOST
// 16200126|PKT_004|1122334455
// 16200127|PKT_005|0000000000|ERR_CRC_FAIL
// 16200128|PKT_00X|DEADBEEF
// 16200129|PKT_006|AABBCCDDEE

//Format: TIMESTAMP | ID | PAYLOAD (Hex) | ERROR_CODE (Optional)

#include "inc/packet.hpp"

int main(){
	std::vector<std::string> raw_logs = {
        "16200123|PKT_001|A1B2C3D4E5",           // Healthy
        "16200124|PKT_X02|FF998877",             // Corrupetd ID
        "16200125|PKT_003|112233|ERR_TIMEOUT",   // Error
        "16200126|PKT_004|999999"                // Healthy
    };

	std::vector<std::unique_ptr<RanPacket>> valid_queue;
	std::vector<std::unique_ptr<RanPacket>> faulty_queue;

	for (const auto& line : raw_logs) {
		std::unique_ptr<RanPacket> packet = parseLine(line);

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