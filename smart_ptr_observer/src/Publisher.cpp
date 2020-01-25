#include "Publisher.h"
#include "Listener.h"

#include <memory>
#include <vector>
#include <mutex>
#include <algorithm>
#include <iostream>

void SmartPublisher::track(std::shared_ptr<SmartListener> t) {
	std::lock_guard<std::mutex> _lock(listenersMutex);
	//std::cout << "Adding to listener vector" << std::endl;
	this->listeners.push_back(t);
}

void SmartPublisher::inform() {
	std::lock_guard<std::mutex> _lock(listenersMutex);
	auto it = this->listeners.begin();
	//std::cout << "Looping over listeners" << std::endl;
	while (it != this->listeners.end()) {
		auto slp = it->lock();
		if (!slp) {
			//std::cout << "Removing listener" << std::endl;
			it = this->listeners.erase(it);
		} else {
			//std::cout << "Listener good, firing" << std::endl;
			slp->fire_event();
			it++;
		}
	}
}


void DumbPublisher::track(DumbListener *t) {
	std::lock_guard<std::mutex> _lock(listenersMutex);
	//std::cout << "Adding to listener vector" << std::endl;
	this->listeners.push_back(t);
}

void DumbPublisher::release(DumbListener* t) {
	std::lock_guard<std::mutex> _lock(listenersMutex);
	//std::cout << "Removing listener" << std::endl;
	this->listeners.erase(
		std::remove(this->listeners.begin(), this->listeners.end(), t),
		this->listeners.end());
}

void DumbPublisher::inform() {
	std::lock_guard<std::mutex> _lock(listenersMutex);
	auto it = this->listeners.begin();
	//std::cout << "Looping over listeners" << std::endl;
	while (it != this->listeners.end()) {
		if (*it == nullptr) {
			//std::cerr << "Program is illformed" << std::endl;
			it = this->listeners.erase(it);
		} else {
			//std::cout << "Listener good, firing" << std::endl;
			(*it)->fire_event();
			it++;
		}
	}
}
