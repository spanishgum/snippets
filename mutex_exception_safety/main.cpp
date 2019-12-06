#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <exception>
#include <iostream>

void wait(std::string s) {
	std::cout << "Thread " << s << std::endl << std::flush;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void safe(std::mutex &m) {
	std::lock_guard<std::mutex> lock(m);
	throw std::exception();
}

void unsafe(std::mutex &m) {
	m.lock();
	throw std::exception();
	m.unlock();
}

void run(decltype(safe) f, std::string id) {
	std::mutex m;
	while (true) {
		wait(id);
		try {
			f(m);
		} catch (const std::exception &e) {}
	}
}

int main() {
	std::thread a(run, safe, std::string("safe"));
	std::thread b(run, unsafe, std::string("unsafe"));
	while (true) wait("main");
}
