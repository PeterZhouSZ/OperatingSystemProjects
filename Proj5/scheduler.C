/*
 File: scheduler.C
 
 Author:
 Date  :
 
 */

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include "scheduler.H"
#include "thread.H"
#include "utils.H"
#include "assert.H"
#include "simple_keyboard.H"

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* METHODS FOR CLASS   S c h e d u l e r  */
/*--------------------------------------------------------------------------*/

Scheduler::Scheduler() {
  current_thread = Thread::CurrentThread();
  Console::puts("Constructed Scheduler.\n");
}

void Scheduler::yield() {
  Machine::disable_interrupts();
  if(ready_queue.isEmpty()){
    Console::puts("Nothing in ready_queue!\n");
    Machine::enable_interrupts();
    return;
  }else{
    Thread * next = ready_queue.out();
    current_thread = next;
    Thread::dispatch_to(current_thread);
  }
  Machine::enable_interrupts();
}

void Scheduler::resume(Thread * _thread) {
  if(Machine::interrupts_enabled()){
    Machine::disable_interrupts();
  }
  ready_queue.in(_thread);
  Machine::enable_interrupts();
}

void Scheduler::add(Thread * _thread) {
  resume(_thread);
}

void Scheduler::terminate(Thread * _thread) {
  Machine::disable_interrupts();
  ready_queue.end(_thread);
  Machine::enable_interrupts();
}
