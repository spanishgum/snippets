#pragma once

#include <memory>
#include <vector>
#include <mutex>
#include <iostream>

class SmartListener;
class DumbListener;

class SmartPublisher {
private:
	std::mutex listenersMutex;
	std::vector<std::weak_ptr<SmartListener> > listeners;

protected:
public:
	SmartPublisher() = default;

	void track(std::shared_ptr<SmartListener> t);

	void inform();
};

class DumbPublisher {
private:
	std::mutex listenersMutex;
	std::vector<DumbListener*> listeners;

protected:
public:
	DumbPublisher() = default;

	void track(DumbListener *t);
	void release(DumbListener*t);

	void inform();
};
