#include <string>
#include <iostream>
#include "stack.h"
#include "queue.h"
//#include <stack>
//#include <queue>
#include <map>

using namespace std;

enum TypeElement {
	Operation,
	Value,
	none
};

class Lexema {
	string str;
	TypeElement type;
public:
	Lexema(string _str = "", TypeElement _type = none) : str(_str), type(_type) {};
	string getStr() { return str; }
	TypeElement getType() { return type; }
	friend ostream& operator << (ostream& out, Lexema& p) {
		out << "{" << p.str << ", ";
		if (p.type == Operation) {
			out << "operation";
		}
		else if (p.type == Value) {
			out << "value";
		};
		out << "}";
		return out;
	}
};

Tqueue <Lexema> lex(string input) {
	Tqueue<Lexema>res;
	input += ' ';
	int i = 0;
	string tmp = "";
	string op = "+-*/()";
	string sep = " \n\t";
	int state = 0;
	for (i = 0; i < input.size(); i++) {
		char c = input[i];
		int fres;
		switch (state)
		{
		case 0:
			if (c >= '0' && c <= '9') {
				tmp = c;
				state = 1;
				break;
			}
			fres = op.find(c);
			if (fres >= 0) {
				tmp = c;
				Lexema l(tmp, Operation);
				res.push(l);
				state = 0;
				break;
			}
			break;
		case 1:
			if (c >= '0' && c <= '9') {
				tmp += c;
				state = 1;
				break;
			}
			fres = op.find(c);
			if (fres >= 0) {
				Lexema l1(tmp, Value);
				res.push(l1);
				tmp = c;
				Lexema l2(tmp, Operation);
				res.push(l2);
				state = 0;
				break;
			}
			fres = sep.find(c);
			if (fres >= 0) {
				Lexema l(tmp, Value);
				res.push(l);
				state = 0;
				break;
			}
			break;
		}
	}
	return res;
}

Tqueue <Lexema> Postfix(Tqueue <Lexema> t) {
	stack <Lexema> st;
	Tqueue <Lexema> res;
	string op = "+-*/()";
	map <string, int> priority;
	priority = { {"(", 0}, {")", 0}, {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2} };
	while (!t.empty()) {
		Lexema tmp = t.front();
		string k = tmp.getStr();
		TypeElement c = tmp.getType();

		switch (tmp.getType()) {
		case Operation:
			//			switch (tmp.getStr()[0])
			//			{
			//			case '(':
			//				st.push(tmp);
			//				break;
			//			case ')':
			//				
			//
			//				break;
			//			case '+': case '-': case '*': case '/':
			//
			//				break;
			//			}
			if (tmp.getStr() == "(") {
				st.push(tmp);
				break;
			}
			else if (tmp.getStr() == ")") {
				Lexema l = st.pop();
				while (l.getStr() != "(") {
					res.push(l);
					l = st.pop();
				}
				break;
			}
			else {
				while (!st.empty()) {
					Lexema l = st.pop();
					if (priority[tmp.getStr()] <= priority[l.getStr()])
						res.push(l);
					else {
						st.push(l);
						break;
					}
				}
				st.push(tmp);
				break;
			}
		case Value:
			res.push(tmp);
			break;
		}
		t.pop();
	}

	while (!st.empty()) {
		Lexema l = st.pop();
		res.push(l);
	}
	return res;
}

double Calculate(Tqueue <Lexema> calc) {
	stack <double> st;
	while (!calc.empty()) {
		Lexema tmp = calc.front();
		string v = tmp.getStr();

		switch (tmp.getType()) {
		case Operation:
			double E1, E2;
			E1 = st.pop();
			E2 = st.pop();
			if (tmp.getStr() == "+") {
				st.push(E2 + E1);
			}
			else if (tmp.getStr() == "-") {
				st.push(E2 - E1);
			}
			else if (tmp.getStr() == "*") {
				st.push(E2 * E1);
			}
			else if (tmp.getStr() == "/") {
				st.push(E2 / E1);
			}
			break;
		case Value:
			double res = stoi(v);
			st.push(res);
			break;
		}
		calc.pop();
	}
	return st.pop();
}

//void print(queue <Lexema> t) {
//	while (!t.empty()) {
//		cout << t.front() << endl;
//		t.pop();
//	}
//}

int main() {
	string str = "(120 -10)/50*30\n";
	cout << str;
	Tqueue <Lexema> lex_res;
	lex_res = lex(str);
//	print(lex_res);
	cout << lex_res << endl;
	cout << "----------------" << endl;
	Tqueue <Lexema> postf;
	postf = Postfix(lex_res);
//	print(postf);
	cout << postf << endl;
	cout << "----------------" << endl;
	cout << Calculate(postf) << endl;
	return 0;
}