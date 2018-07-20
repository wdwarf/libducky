/*
 * Application.cpp
 *
 *  Created on: 2018年7月18日
 *      Author: liyawu
 */

#include <ducky/app/Application.h>
#include <ducky/settings/Settings.h>
#include <ducky/thread/Thread.h>
#include <ducky/thread/Mutex.h>
#include <ducky/thread/Semaphore.h>
#include <cassert>
#include <vector>
#include <string>
#include <set>

using namespace std;
using namespace ducky::thread;
using namespace ducky::settings;

namespace ducky {
namespace app {

class Application::ApplicationImpl: public ducky::settings::Settings {
public:
	ApplicationImpl(Application* _app, int argc, char** argv) :
			app(_app), runThread(&Application::ApplicationImpl::execute, this), exitCode(
					0), running(false) {
		for (int i = 0; i < argc; ++i) {
			cmdLines.push_back(argv[i]);
		}
	}

	virtual ~ApplicationImpl() {
	}

	int run() {
		{
			MutexLocker lk(this->mutex);

			if (this->running)
				return -1;
			this->exitCode = 0;
			this->running = true;
		}

		this->app->onInitialize();

		this->runThread.start();

		sem.wait();

		this->app->onUninitialize();
		this->runThread.join();

		MutexLocker lk(this->mutex);
		this->running = false;
		return this->exitCode;
	}

	void exit(int code) {
		MutexLocker lk(this->mutex);

		if (!this->running)
			return;
		this->running = false;
		this->exitCode = code;
		sem.release();
	}

	int getExitCode() const {
		return this->exitCode;
	}

	void execute() {
		this->app->onRun();
	}

	const std::vector<std::string>& getCommandLines() const {
		return this->cmdLines;
	}

	int getCommandLineCount() const {
		return this->cmdLines.size();
	}

	const ducky::variant::Variant& getValue(const std::string& key) const {
		return this->settings.getValue(key);
	}
	void setValue(const std::string& key,
			const ducky::variant::Variant& value) {
		this->settings.setValue(key, value);
	}
	bool hasValue(const std::string& key) const {
		return this->settings.hasValue(key);
	}
	void removeValue(const std::string& key) {
		this->settings.removeValue(key);
	}
	std::set<std::string> getKeys() const {
		return this->settings.getKeys();
	}
	void saveSettings(const std::string& file) {
		this->settings.saveToFile(file);
	}
	void loadSettings(const std::string& file) {
		this->settings.loadFromFile(file);
	}

private:
	Application* app;
	Settings settings;
	vector<string> cmdLines;
	Thread runThread;
	Mutex mutex;
	Semaphore sem;
	int exitCode;
	bool running;
};

static Application* __app = NULL;

Application* GetApplication() {
	return __app;
}

Application::Application(int argc, char** argv) :
		impl(new Application::ApplicationImpl(this, argc, argv)) {
	assert(NULL == __app);
	if(NULL != __app){
		THROW_EXCEPTION(ApplicationException, "There is anther application on running.", -1);
	}
	__app = this;
}

Application::~Application() {
	if (this == __app) {
		__app = NULL;
	}
	delete this->impl;
}

int Application::run() {
	return this->impl->run();
}

const std::vector<std::string>& Application::getCommandLines() const {
	return this->impl->getCommandLines();
}

int Application::getCommandLineCount() const {
	return this->impl->getCommandLineCount();
}

const ducky::variant::Variant& Application::getValue(
		const std::string& key) const {
	return this->impl->getValue(key);
}

void Application::setValue(const std::string& key,
		const ducky::variant::Variant& value) {
	this->impl->setValue(key, value);
}

bool Application::hasValue(const std::string& key) const {
	return this->impl->hasValue(key);
}

void Application::removeValue(const std::string& key) {
	this->impl->removeValue(key);
}

std::set<std::string> Application::getKeys() const {
	return this->impl->getKeys();
}

void Application::saveSettings(const std::string& file) {
	this->impl->saveSettings(file);
}

void Application::loadSettings(const std::string& file) {
	this->impl->loadSettings(file);
}

void Application::exit(int code) {
	this->impl->exit(code);
}

int Application::getExitCode() const {
	return this->impl->getExitCode();
}

} /* namespace app */
} /* namespace ducky */
