#include "threadsafe_stack.h"

///---------------------------------------------------------------------------///
/// class threadsafe_stack_ex1 definition...
///

template<typename T>
threadsafe_stack_ex1<T>::threadsafe_stack_ex1()
{
    // Empty Constructor
}

template<typename T>
threadsafe_stack_ex1<T>::threadsafe_stack_ex1(const threadsafe_stack_ex1 &other)
{
    std::lock_guard<std::mutex> lock(other.m);
    data=other.data;
}

template<typename T>
void threadsafe_stack_ex1<T>::push(T new_value)
{
    std::lock_guard<std::mutex> lock(m);
    data.push(std::move(new_value));
}

template<typename T>
std::shared_ptr<T> threadsafe_stack_ex1<T>::pop()
{
    std::lock_guard<std::mutex> lock(m);
    if(data.empty()) throw empty_stack();
    std::shared_ptr<T> const res(
                std::make_shared<T>(std::move(data.top())));
    data.pop();
    return res;
}

template<typename T>
void threadsafe_stack_ex1<T>::pop(T& value)
{
    std::lock_guard<std::mutex> lock(m);
    if(data.empty()) throw empty_stack();
    value=std::move(data.top());
    data.pop();
}

template<typename T>
bool threadsafe_stack_ex1::empty() const
{
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
}


///---------------------------------------------------------------------------///
