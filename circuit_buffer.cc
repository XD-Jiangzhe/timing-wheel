#ifndef CIRCUIT_BUFFER
#define CIRCUIT_BUFFER

#include <deque>
#include <iostream>

using namespace std;

template<typename T>
class circular_buffer
{
	public:
	circular_buffer(){}

	void push_back(const T&);

	void resize(int size)
	{
		for(int i =0;i< size; i++)
			deq.push_back(T());
	}

	void print()
	{
		for(auto const &i: deq)
			cout<<i<<" ";
		cout<<endl;
	}

	T& back()
	{
		return deq.back();
	}

	typename deque<T>::iterator end()
	{
		return deq.end();
	}

	typename deque<T>::iterator begin()
	{
		return deq.begin();
	}

	size_t size()
	{
		return deq.size();
	}



	private:
		deque<T> deq;
};

template<typename T>
void circular_buffer<T>::push_back(const T& t)
{
	deq.push_back(t);
	deq.pop_front();
}

/*int main()
{
	deque<int> d{1,2,3,4};

	d.push_back(5);
	d.resize(4);

	cout<<d.size()<<endl;

	for(auto const&i : d)
		cout<<i<<" ";
	circuit_buffer<int> cir;
	cir.resize(4);
	for(int i = 0;i<10; i++)
	{
		cir.push(i);
		cir.print();
		cout<<endl;
	}

}*/

#endif

