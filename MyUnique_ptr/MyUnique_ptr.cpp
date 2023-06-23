
#include <iostream>
#include<memory>
using namespace std;

/**
*   简易的unique_ptr复现
*/
template<typename T>
class myunique_ptr
{
private:
	T* p;
public:
	constexpr myunique_ptr() :p(nullptr) {}
	explicit myunique_ptr(T* t)noexcept :p(t) {}
	//显示删除
	myunique_ptr(const myunique_ptr&) = delete;
	myunique_ptr& operator=(const myunique_ptr&) = delete;
	//移动构造，移动赋值
	myunique_ptr(myunique_ptr&& o)noexcept :p(exchange(o.p, nullptr)) {}
	myunique_ptr& operator=(myunique_ptr&& o)noexcept
	{
		delete p;
		p = o.p;
		o.p = nullptr;
		return *this;
	}
	//部分运算符
	T& operator*()const noexcept
	{
		return *p;
	}
	T* operator->()const noexcept
	{
		return p;
	}
	bool operator==(const myunique_ptr& o)noexcept
	{
		if (*p == *(o.p))return true;
		else return false;
	}

	//隐式转换
	explicit operator bool()const noexcept
	{
		return p != nullptr;
	}
	//基本的成员函数
	void reset(T* t = nullptr)noexcept
	{
		delete p;
		p = t;
	}
	T* release()noexcept
	{
		T* t = p;
		p = nullptr;
		return t;
	}
	T* get()const noexcept
	{
		return p;
	}
	void swap(myunique_ptr& o)noexcept 
	{
		T* t = o.p;
		o.p = p;
		p = t;
	}
	//析构
	~myunique_ptr() noexcept { delete p; }
};

//显示偏特化
template<typename T>
class myunique_ptr<T[]>
{
private:
	T *p;
public:
	constexpr myunique_ptr() :p(nullptr) {}
	explicit myunique_ptr(T* t)noexcept :p(t) {}
	//显示删除
	myunique_ptr(const myunique_ptr&) = delete;
	myunique_ptr& operator=(const myunique_ptr&) = delete;
	//移动构造，移动赋值
	myunique_ptr(myunique_ptr&& o)noexcept :p(exchange(o.p, nullptr)) {}
	myunique_ptr& operator=(myunique_ptr&& o)noexcept
	{
		delete p;
		p = o.p;
		o.p = nullptr;
		return *this;
	}
	//部分运算符
	/*
	T& operator*()const noexcept
	{
		return *p;
	}
	T** operator->()const noexcept
	{
		return p;
	}*/
	bool operator==(const myunique_ptr& o)noexcept
	{
		if (*p == *(o.p))return true;
		else return false;
	}
	//
	T& operator[](unsigned int x)
	{
		return p[x];
	}
	//隐式转换
	explicit operator bool()const noexcept
	{
		return p != nullptr;
	}
	//基本的成员函数
	void reset(T* t = nullptr)noexcept
	{
		delete p;
		p = t;
	}
	T* release()noexcept
	{
		T* t = p;
		p = nullptr;
		return t;
	}
	T* get()const noexcept
	{
		return p;
	}
	void swap(myunique_ptr& o)noexcept
	{
		T* t = o.p;
		o.p = p;
		p = t;
	}
	//析构
	~myunique_ptr() noexcept { delete[] p; }
};





int main()
{

	myunique_ptr<int[]> ptr(new int[5] {1, 2, 3, 4, 5});
	cout << ptr[1] << endl;
}

