#include <vector>
#include <memory>
#include <string>
#include <chrono>
#include <iostream>

#include "Publisher.h"
#include "Listener.h"

void testSmartListener(int push_count, int inform_count) {
	//std::cout << "\n\tSmart listener test beginning" << std::endl;
	SmartPublisher publisher;
	std::vector<std::shared_ptr<SmartListener> > listeners;

	for (auto i = 0; i < push_count; ++i) {
		listeners.push_back(std::make_shared<FirstExampleSmartListener>());
		listeners.back()->link(publisher);
		listeners.push_back(std::make_shared<SecondExampleSmartListener>());
		listeners.back()->link(publisher);
	}

	for (auto i = 0; i < inform_count; ++i) {
		publisher.inform();
	}

	for (auto i = 0; i < listeners.size(); ++i) {
		if (i % 2) {
			listeners.pop_back();
		}
	}
	for (auto i = 0; i < inform_count; ++i) {
		publisher.inform();
	}

	for (auto i = 0; i < listeners.size(); ++i) {
		listeners.pop_back();
	}
	for (auto i = 0; i < inform_count; ++i) {
		publisher.inform();
	}
}

void testDumbListener(int push_count, int inform_count) {
	//std::cout << "\n\tDumb listener test beginning" << std::endl;
	DumbPublisher publisher;
	std::vector<DumbListener *> listeners;

	for (auto i = 0; i < push_count; ++i) {
		listeners.push_back(new FirstExampleDumbListener(publisher));
		listeners.push_back(new SecondExampleDumbListener(publisher));
	}
	for (auto i = 0; i < inform_count; ++i) {
		publisher.inform();
	}

	for (auto i = 0; i < listeners.size(); ++i) {
		if (i % 2) {
			delete listeners.back();
			listeners.pop_back();
		}
	}
	for (auto i = 0; i < inform_count; ++i) {
		publisher.inform();
	}

	for (auto i = 0; i < listeners.size(); ++i) {
		delete listeners.back();
		listeners.pop_back();
	}
	for (auto i = 0; i < inform_count; ++i) {
		publisher.inform();
	}
}

void testMixedListener(int push_count, int inform_count) {
	//std::cout << "\n\tDumb listener test beginning" << std::endl;
	DumbPublisher publisher;
	std::vector<std::shared_ptr<DumbListener> > listeners;

	for (auto i = 0; i < push_count; ++i) {
		listeners.push_back(std::make_shared<FirstExampleDumbListener>(publisher));
		listeners.push_back(std::make_shared<SecondExampleDumbListener>(publisher));
	}
	for (auto i = 0; i < inform_count; ++i) {
		publisher.inform();
	}

	for (auto i = 0; i < listeners.size(); ++i) {
		if (i % 2) {
			listeners.pop_back();
		}
	}
	for (auto i = 0; i < inform_count; ++i) {
		publisher.inform();
	}

	for (auto i = 0; i < listeners.size(); ++i) {
		listeners.pop_back();
	}
	for (auto i = 0; i < inform_count; ++i) {
		publisher.inform();
	}
}

void timeListeners() {
	int push_count = 10000;
	int inform_count = 10;

	auto t1 = std::chrono::system_clock::now();
	testSmartListener(push_count, inform_count);
	auto t2 = std::chrono::system_clock::now();
	testDumbListener(push_count, inform_count);
	auto t3 = std::chrono::system_clock::now();
	testMixedListener(push_count, inform_count);
	auto t4 = std::chrono::system_clock::now();

	auto d1 = (t2 - t1);
	auto d2 = (t3 - t2);
	auto d3 = (t4 - t3);

	std::cout << "\n\tResults:" << std::endl;
	std::cout << "Smart pattern finished in :  " << d1.count() << std::endl;
	std::cout << "Dumb pattern finished in  :  " << d2.count() << std::endl;
	std::cout << "Mixed pattern finished in :  " << d3.count() << std::endl;

	std::cout << "Slowdown from smart over dumb  : " << (static_cast<double>(d1.count()) / static_cast<double>(d2.count())) << std::endl;
	std::cout << "Slowdown from smart over mixed : " << (static_cast<double>(d1.count()) / static_cast<double>(d3.count())) << std::endl;
	std::cout << "Slowdown from mixed over dumb  : " << (static_cast<double>(d3.count()) / static_cast<double>(d2.count())) << std::endl;
}

int main() {
	timeListeners();
	return 0;
}
