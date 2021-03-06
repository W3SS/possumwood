#pragma once

#include "attr.h"

namespace dependency_graph {

template<typename T>
TypedAttr<T>::TypedAttr(const std::string& name, unsigned offset, Category cat, const T& defaultValue) : Attr(name, offset, cat), m_defaultValue(defaultValue) {
}

template<typename T>
const std::type_info& TypedAttr<T>::type() const {
	return typeid(T);
}

template<typename T>
std::unique_ptr<BaseData> TypedAttr<T>::createData() const {
	return std::unique_ptr<BaseData>(new Data<T>(m_defaultValue));
}


template<typename T>
InAttr<T>::InAttr() : TypedAttr<T>("", unsigned(-1), Attr::kInput, T()) {
}

template<typename T>
InAttr<T>::InAttr(const std::string& name, unsigned offset, const T& defaultValue) : TypedAttr<T>(name, offset, Attr::kInput, defaultValue) {
}


template<typename T>
OutAttr<T>::OutAttr() : TypedAttr<T>("", unsigned(-1), Attr::kOutput, T()) {
}

template<typename T>
OutAttr<T>::OutAttr(const std::string& name, unsigned offset, const T& defaultValue) : TypedAttr<T>(name, offset, Attr::kOutput, defaultValue) {
}

}
