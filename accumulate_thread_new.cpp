#include <iostream>
#include <thread>
#include <algorithm>
#include <iterator>
#include <vector>
#include <numeric>
#include <exception>

using namespace std;

class scoped_thread
{
public:
    explicit scoped_thread(std::thread t_) : t(std::move(t_))
    {
        if (!t.joinable())
            throw std::logic_error("No thread");

    }

    ~scoped_thread()
    {
        t.join();
    }

    scoped_thread(scoped_thread const&) = delete;
    scoped_thread& operator=(scoped_thread const&) = delete;

private:
    std::thread t;
};


template<typename Iterator,typename T>
struct accumulate_block
{
    void operator()(Iterator first,Iterator last,T& result)
    {
        result=std::accumulate(first,last,result);
    }
};

template<typename Iterator,typename T>
T parallel_accumulate(Iterator first,Iterator last,T init)
{
    using ulongc = unsigned long const ;
    ulongc length = std::distance(first,last);

    if(!length)                                                     // 1
        return init;

    ulongc min_per_thread=25;
    ulongc max_threads= (length+min_per_thread-1)/min_per_thread;           // 2
    ulongc hardware_threads= std::thread::hardware_concurrency();
    ulongc num_threads= std::min(hardware_threads!=0?hardware_threads:2,max_threads);
    ulongc block_size=length/num_threads;

    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads-1);

    Iterator block_start=first;

    for(unsigned long i=0;i<(num_threads-1);++i)
    {
        Iterator block_end=block_start;
        std::advance(block_end,block_size);
        threads[i]=std::thread(
                    accumulate_block<Iterator,T>(),
                    block_start,block_end,std::ref(results[i]));
        block_start=block_end;
    }
    accumulate_block<Iterator,T>()(
                block_start,last,results[num_threads-1]);

    std::for_each(threads.begin(),threads.end(),
                  std::mem_fn(&std::thread::join));
    return std::accumulate(results.begin(),results.end(),init);

}


int main(int argc, char *argv[])
{
    std::vector<int> vecs(100,100);

    int sum = parallel_accumulate(vecs.begin(),vecs.end(), 0);

    cout << "Sum: " << sum << endl;

    return 0;
}
