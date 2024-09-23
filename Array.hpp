#pragma once
#include<vector>
#include<functional>
#include<iostream>
#include<initializer_list>

template <typename ANY>
class Array{
private:
	std::vector<ANY> data;
public:
	Array() = default;

	Array(size_t size) {
		data.resize(size);
	}

	Array(const std::initializer_list<ANY>& list) {
		data.reserve(list.size());
		for (auto& el : list)
			data.push_back(el);
	}

	void push_back(ANY value) {
		data.push_back(value);
	}

	size_t size() const { return data.size(); }
	
	ANY& operator[](size_t index) { return data[index]; }
	const ANY& operator[](size_t index) const { return data[index]; }

	void for_each(std::function<void(ANY&)> callback) {
		for (auto& el : data)
			callback(el);
	}

	Array filter(std::function<bool(const ANY&)> callback) {
		Array result;
		for (auto& el : data)
			if (callback(el))
				result.push_back(el);
		return result;
	}

	ANY every(std::function<ANY(const ANY&)> callback) {
		ANY result{};
		for (auto& el : data)
			result += callback(el);
		return result;
	}

};


template<typename ANY>
std::ostream& operator<<(std::ostream& out, const Array<ANY> arr) {
	out << "{ "; 
	for (size_t i{}; i < arr.size(); ++i)
		out << arr[i] << ", ";
	out << "\b\b }";
	return out;
}
