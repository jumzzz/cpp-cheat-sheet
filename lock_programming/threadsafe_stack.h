#ifndef THREADSAFE_STACK_H
#define THREADSAFE_STACK_H

#include <stack>
#include <memory>
#include <exception>
#include <mutex>

struct empty_stack: std::exception
{
    const char* what() const throw();
};


template<typename T>
class threadsafe_stack_ex1
{
private:
    std::stack<T> data;
    mutable std::mutex m;
public:
    threadsafe_stack_ex1();
    threadsafe_stack_ex1(const threadsafe_stack_ex1& other);
    threadsafe_stack_ex1& operator=(const threadsafe_stack_ex1&) = delete;

    void push(T new_value);
    std::shared_ptr<T> pop();
    void pop(T& value);

    bool empty() const;

};
#endif // THREADSAFE_STACK_H
