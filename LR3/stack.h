#pragma once
#pragma once
#include <iostream>

using namespace std;

template <typename T>
class stack {
	int top;
	int size;
	T* p;
public:
	stack(int _size = 100) {
		top = -1;
		size = _size;
		p = new T[size];
	}
	stack(const stack<T>& v) {
		if (v.p == nullptr) {
			p = nullptr;
			size = 0;
			top = -1;
		}
		else {
			top = v.top;
			size = v.size;
			p = new T[size];
			std::copy(v.p, v.p + size, p);
		}
	}
	bool empty() {
		return top == -1;
	}
	bool full() {
		return top == size - 1;
	}
	void push(const T& v) {
		p[++top] = v;
	}
	T pop() {
		if (empty())
			throw - 1;
//		return p[top--];
		T v = p[top];
		top--;
		return v;
	}
	T Top() {
		if (empty())
			throw - 1;
		return p[top];
	}
	~stack() {
		delete[] p;
	}
	friend ostream& operator << (ostream& out, stack<T>& v) {
		if (v.empty()) {
			out << "empty" << endl;
			return out;
		}
		for (int i = v.top; i >= 0; i--)
			out << v.p[i] << endl;
		return out;
	}
};
