#include <iostream>
#include <threadsafe_stack.h>

using namespace std;

/*
    Basics on making a thread-safe data structure...

    What is thread-safe data structure anyway?
    - A data-structure is said to be thread-safe if
      it retains its invariance and no data is corrupted/lost
      while interacting with different threads.

    Basic advice in making a thread safe data structure..

    1. Ensure that no thread can see a state where the invariants
       of the data structure have been broken by the actions of
       another thread.

       Only means that:
       - Avoid external pointers for its private members -- something
         that's passable to another thread.

    2. Take care to avoid race conditions inherent in the interface
       to the data structure by providing functions for complete
       operations rather than for operation steps.

       - One example here is when two threads are doing an
         update()/remove() of in a shared data simultaneously
         this can lead to unexpected modifications which can
         result in an inconsistent behavior of your code.

       - Encapsulating complete operations for your interface
         will minimize the probability of your data structure
         messing up.

     3. Pay attention to how the data structure behaves in the
        presence of exceptions to ensure that the invariants
        are not broken.

        - There are instances that a data structure you're using
          might not be exception-safe and simultaneous access
          to a data structure has chances of throwing of an exception
          if not done right. Hence, it's important to know its behavior..
          Just like how every single code you're using...

    4. Minimize the opportunities for deadlock when using the data structure
       by restricting the scope of locks and avoiding nested
       - Deadlocks can be nasty bitch.
       - Use raii based lock_guard and its variants to guarantee
         unlocks in the future.


*/

/*
   How to enable genuine concurrent access...

   1. Can the scope of locks be restricted to allow some parts of
      an operation to be performed outside the lock?

   2. Can different parts of the data structure be protected
      with different mutexes?
      - Seriously though? Too many mutexes? That's really
        prone to deadlocks. It increases your chance of
        generating more error prone code..

   3. Do all operations require the same level of protection?
      - Operations that simply read don't require protection.
        Operations that uses write does certainly requires
        protection.

   4. Can a simple change to the data structure improve the opportunities
      for concurrency without affecting the operational semantics?


   Guided by a single idea: How can you minimize the amount of serialization
   that must occur and enable the greatest amount of true concurrency.

   Serialization: A1 -> A2 -> A3 -> ... An
                  - Every proceeding process is dependent on preceeding
                    process.
   Concurrency: Different processes (Threads) are independent of each other
               and can function simultaneously (concurrently)



*/

int main(int argc, char *argv[])
{
//    cout << "Hello World!" << endl;
//    printFizzBuzz();
    return 0;
}
