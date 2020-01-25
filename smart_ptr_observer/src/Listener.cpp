#include "Listener.h"
#include "Publisher.h"

#include <memory>
#include <vector>
#include <mutex>
#include <iostream>

void SmartListener::link(SmartPublisher& publisher) {
	publisher.track(shared_from_this());
}

void FirstExampleSmartListener::fire_event() {
	//std::cout << "Event fired" << std::endl;
}

void SecondExampleSmartListener::fire_event() {
	//std::cout << "Event fired" << std::endl;
}


FirstExampleDumbListener::FirstExampleDumbListener(DumbPublisher& publisher) : _publisher(publisher) {
	this->_publisher.track(this);
}

FirstExampleDumbListener::~FirstExampleDumbListener() {
	this->_publisher.release(this);
}

void FirstExampleDumbListener::fire_event() {
	//std::cout << "Event fired" << std::endl;
}


SecondExampleDumbListener::SecondExampleDumbListener(DumbPublisher& publisher) : _publisher(publisher) {
	this->_publisher.track(this);
}

SecondExampleDumbListener::~SecondExampleDumbListener() {
	this->_publisher.release(this);
}

void SecondExampleDumbListener::fire_event() {
	//std::cout << "Event fired" << std::endl;
}
