#include <thread>
#include <mutex>
#include <chrono>
#include <exception>
#include <iostream>

void sleep() {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void speak(std::string s) {
	std::cout << "Thread " << s << std::endl << std::flush;
}

void safe() {
	std::mutex m;
	auto lambda = [&m]() {
		std::lock_guard<std::mutex> lock(m);
		throw std::exception();
	};
	while (true) {
		speak("safe");
		try {
			lambda();
		} catch (const std::exception &e) {}
		sleep();
	}
}

void unsafe() {
	std::mutex m;
	auto lambda = [&m]() {
		m.lock();
		throw std::exception();
		m.unlock();
	};
	while (true) {
		speak("unsafe");
		try {
			lambda();
		} catch (const std::exception &e) {}
		sleep();
	}
}

int main() {
	std::thread a(safe);
	std::thread b(unsafe);
	while (true) {
		speak("main");
		sleep();
	}
}
