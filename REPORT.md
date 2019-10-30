#Project 2 
#By David Lee and Cong Xie
### Makefile
Our makefile was created with the simple idea that it would create a static library named libuthread.a. 
his makefile would also contain the following queue.o, uthread.o, and preempt.o in its objs. 
This was made following the Makefile guide provided in class by Professor Porquet.

###Phase 1. Queue
Since we were given a choice to use any kind of data structure to fit the O(1) operations, we decided to use Linked lists. 
Linked lists allowed us to enqueue and dequeue and helped us keep track of the TID. 
Since arrays start out at 0, whenever we enqueued into our queue, we would start at array[0] and every other thred would iterate to the next element.
This also allowed us to easily create a FIFO queue as we were able to access the dequeue, enqueue, destroy, and access the head using this data structure. 

###Phase 2. TCB
In this phase we created a struct named:
```
struct TCB{
    u_thread_t tid;
    enum State status;
    ucontext_t context;
    int returnValue;
    void* stack;
    bool joined;
    int blocked;
};
```
This allowed us to keep all the necessary variables we required to that would be prevalent in our code. 
In the next step we wrote our Uthread create by first checking if we had initialized our first thread and if it wasnt it would be set to TID 0.
We then called TCB initialization again and enqueued our first thread into the ready queue. 
We then kept ```threadArray[NextTID] = NewThread;```to help us locate the required thread in our Uthread_join.

In our Uthread_yield, this was the function that would take care of whether or not the thread we were looking at should be blocked.
This function allowed us to switch between from the ```running thread to the next ready thread if there existed a ready thread ready to be processed.

###Phase 3 Uthread_join
In our join we checked our thread could be joined. If it could not be joined i.e. thread joining itself or NULL. we would return -1. 
This part would be vital in helping us free 
//need to be updated and more added 

###Phase 4
Instead of using a global variable of type sigset_t to store our mask, we implemented the mask in both the disable and enable. 
This impementation would allow for better security and stored the mask in the functions that would call sigprocmask.
We followed the example provided in Piazza <http://www.informit.com/articles/article.aspx?p=23618&seqNum=14> to implement our preempt start function. 
One part that we have not fully implemented was the ```while(1)``` as that would loop forever in this function.
We are aware that without this kind of "busy work", the program might not receive the necessary signal to proceed with this preempt function. 


###Testing
We used two files to test our function named Uthread_hello.x and Uthread_yield.x. 
Uthread_hello.x allowed us to check if we implemented our Uthread_hello.x correctly and Uthread_yield.x allowed us to look at whether our yield was implemented as intended.

Hello would pring out ```Hello World!``` and proceed to try and join ```Thread 1 and NULL``` together.
Yield would then create 3 different threads for us to create and print out the following ```thread 1, thread 2, and thread 3.```

We were also asked to write out 2 different test cases for both phase 3 join and phase 4 preempt. 
//write out more of this in our 

###Resources used
<http://www.informit.com/articles/article.aspx?p=23618&seqNum=14>
<https://stackoverflow.com/questions/231912/what-is-the-difference-between-sigaction-and-signal>


