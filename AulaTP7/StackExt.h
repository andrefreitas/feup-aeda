# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
	stack<T> data;
	stack<T> minimos; // útil quando os mínimos são removidos

public:
	StackExt() {};
	bool empty() const;
	T top() const;
	void pop();
	void push(const T & val);
	T findMin() const;
};

// Alínea 1

template <class T>
bool StackExt<T>::empty() const{
	return data.empty();
}

template <class T>
T  StackExt<T>::top() const{
	return data.top();
}

template <class T>
void StackExt<T>::pop(){
	// WARNING:  Must be not empty or crash!!!!!!!!
	if (!minimos.empty() && minimos.top()==data.top()) minimos.pop();
    data.pop();
}

template <class T>
void StackExt<T>::push(const T & val){
	data.push(val);
	// WARNING:  Must be not empty or crash!!!!!!!!
	if (minimos.empty()) minimos.push(val);
	if (!minimos.empty() && (val<minimos.top())) minimos.push(val);
}

template <class T>
T StackExt<T>::findMin() const{
	return minimos.top();
}
