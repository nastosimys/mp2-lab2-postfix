#pragma once
#include <string>
#include <iostream>

using namespace std;

template <typename T>
class Tqueue {
	int size;
	T* p;
	int start;
	int end;
	int next(int i) { return (i + 1) % size; }
public:
	Tqueue(int _size = 100) {
		size = _size;
		p = new T[size];
		end = 0;
		start = next(end);
	}
	Tqueue(const Tqueue<T>& v) {
		size = v.size;
		start = v.start;
		end = v.end;
		p = new T[size];
		for (int i = start; i != next(end); i++)
			p[i] = v.p[i];
	}
	bool empty() {
		return (next(end) == start);
	}
	bool full() {
		return (next(next(end)) == start);
	}
	void push(T a) {
		if (full())
			throw - 1;
		end = next(end);
		p[end] = a;
	}
	T pop() {
		if (empty())
			throw - 1;
		T v = p[start];
		start = next(start);
		return v;
	}
	T front() {
		return p[start];
	}
	~Tqueue() {
		delete[] p;
	}
	friend ostream& operator << (ostream& out, Tqueue& v) {
		if (v.empty()) {
			out << "empty" << endl;
			return out;
		}
		for (int i = v.start; i != v.next(v.end); i = v.next(i)) 
			out << v.p[i] << endl;
		return out;
	}
};