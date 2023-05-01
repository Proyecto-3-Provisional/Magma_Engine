#pragma once

#include <cassert>
#include <memory>
#include <exception>

template<typename T>
class Singleton {
protected:
	Singleton() {};
public:
	// Borrar "constructor por copia" y "operador de asignaci�n"
	Singleton(Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	template<typename ...Targs>
	static T* init(Targs &&...args) {
		assert(instance_.get() == nullptr);
		instance_.reset(new T(std::forward<Targs>(args)...));
		return instance_.get();
	}
	static T* instance() {
		assert(instance_.get() != nullptr);
		return instance_.get();
	}

	static void release() {
		assert(instance_.get() != nullptr);
		instance_.reset(nullptr);
	}
private:
	static std::unique_ptr<T> instance_;
};
template<typename T>
std::unique_ptr<T> Singleton<T>::instance_;