#include <array>
#include <iostream>

std::string exec(const char* cmd) {
	std::array<char, 128> buffer;
	std::string res;
	std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed");
	}

	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		res += buffer.data();
	}

	return res;
}

int main() {
	const std::string time = exec("time /t");
	const std::string cmd = "time " + time;
	
	std::cout << "Current time: " << time << std::flush;
	std::cout << "Stopping time!" << std::flush;

	while (true) {
		system(cmd.c_str());
	}
}