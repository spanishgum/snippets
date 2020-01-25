#pragma once

#include <memory>
#include <vector>
#include <mutex>
#include <iostream>

class SmartPublisher;
class DumbPublisher;

//class Listener : public InheritableSharable<Listener> {
class SmartListener : public std::enable_shared_from_this<SmartListener> {
private:
protected:
	SmartListener() = default;
public:
	void link(SmartPublisher& publisher);
	virtual void fire_event() = 0;
};


class FirstExampleSmartListener : public SmartListener {
public:
	FirstExampleSmartListener() = default;
	void fire_event() override;
};


class SecondExampleSmartListener : public SmartListener {
public:
	SecondExampleSmartListener() = default;
	void fire_event() override;
};


class DumbListener : public std::enable_shared_from_this<DumbListener> {
private:
protected:
	DumbListener() = default;
public:
	virtual ~DumbListener() = default;
	virtual void fire_event() = 0;
};


class FirstExampleDumbListener : public DumbListener {
private:
	DumbPublisher& _publisher;
public:
	FirstExampleDumbListener(DumbPublisher& publisher);
	virtual ~FirstExampleDumbListener();
	void fire_event() override;
};


class SecondExampleDumbListener : public DumbListener {
private:
	DumbPublisher& _publisher;
public:
	SecondExampleDumbListener(DumbPublisher& publisher);
	virtual ~SecondExampleDumbListener();
	void fire_event() override;
};
