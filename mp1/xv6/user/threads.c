#include "kernel/types.h"
#include "user/setjmp.h"
#include "user/threads.h"
#include "user/user.h"
#define NULL 0

static struct thread* current_thread = NULL;
static int id = 1;
static jmp_buf env_st;
// static jmp_buf env_tmp;

struct thread *thread_create(void (*f)(void *), void *arg){
    struct thread *t = (struct thread*) malloc(sizeof(struct thread));
    unsigned long new_stack_p;
    unsigned long new_stack;
    new_stack = (unsigned long) malloc(sizeof(unsigned long)*0x100); // TODO: how to use this stack?
    new_stack_p = new_stack +0x100*8-0x2*8;
    t->fp = f;
    t->arg = arg;
    t->ID  = id;
    t->buf_set = 0;
    t->stack = (void*) new_stack;
    t->stack_p = (void*) new_stack_p;
    id++;

    // part 2
    t->sig_handler[0] = NULL_FUNC;
    t->sig_handler[1] = NULL_FUNC;
    t->signo = -1;
    t->handler_buf_set = 0;
    return t;
}

void thread_add_runqueue(struct thread *t){
    if(current_thread == NULL){
        current_thread = t;
        current_thread->previous = current_thread;
        current_thread->next = current_thread;
    } else{
        if (current_thread->next == current_thread) {
            t->previous = current_thread;
            t->next = current_thread;
            current_thread->previous = t;
            current_thread->next = t;
        } else {
            t->next = current_thread;
            t->previous = current_thread->previous;
            current_thread->previous->next = t;
            current_thread->previous = t;
        }
        // p2: inherit signal handler
        int i;
        for (i = 0; i < 2; i++) {
            t->sig_handler[i] = current_thread->sig_handler[i];
        }
    }
}
void thread_yield(void){
    if (current_thread->signo == -1) {
        if (setjmp(current_thread->env) == 0) {
            schedule();
            dispatch();
        }
    } else {
        if (setjmp(current_thread->handler_env) == 0) {
            schedule();
            dispatch();
        }
    }
}
void dispatch(void){
    if ((current_thread->signo == -1) || (current_thread->sig_handler[current_thread->signo] != NULL_FUNC)) {
        if (current_thread->buf_set == 0) { // Thread not runned before
            if (setjmp(current_thread->env) == 0) { // do initialization
                current_thread->buf_set = 1;
                current_thread->env->sp = (unsigned long) current_thread->stack_p;
                longjmp(current_thread->env, current_thread->ID);
            }
            // p2
            if (current_thread->signo != -1) { // a signal has come, handle the signal first
                if (current_thread->handler_buf_set == 0) { // handler not runned before
                    if (setjmp(current_thread->handler_env) == 0) { // handler initialization
                        current_thread->handler_buf_set = 1;
                        current_thread->handler_env->sp = current_thread->env->sp; // NOTE: set to current stack pointer of the thread function
                        longjmp(current_thread->handler_env, current_thread->ID);
                    }
                    (current_thread->sig_handler[current_thread->signo])(current_thread->signo);
                    current_thread->signo = -1; // reset current_thread->signo to -1 when the handler returns
                    longjmp(current_thread->env, current_thread->ID); // resume executing the thread function
                } else {
                    longjmp(current_thread->handler_env, current_thread->ID);
                }
            }
            // end p2
            (current_thread->fp)(current_thread->arg);
        } else { // Thread runned before
            // p2
            if (current_thread->signo != -1) { // a signal has come, handle the signal first
                if (current_thread->handler_buf_set == 0) { // handler not runned before
                    if (setjmp(current_thread->handler_env) == 0) { // handler initialization
                        current_thread->handler_buf_set = 1;
                        current_thread->handler_env->sp = current_thread->env->sp; // NOTE: set to current stack pointer of the thread function
                        longjmp(current_thread->handler_env, current_thread->ID);
                    }
                    (current_thread->sig_handler[current_thread->signo])(current_thread->signo);
                    current_thread->signo = -1; // reset current_thread->signo to -1 when the handler returns
                    longjmp(current_thread->env, current_thread->ID); // resume executing the thread function
                } else {
                    longjmp(current_thread->handler_env, current_thread->ID);
                }
            }
            // end p2
            longjmp(current_thread->env, current_thread->ID);
        }
    } else if (current_thread->sig_handler[current_thread->signo] == NULL_FUNC) { // no handler -> kill
        thread_exit();
    }
}
void schedule(void){
    current_thread = current_thread->next;
}
void thread_exit(void){
    if(current_thread->next != current_thread){ // there is currently at least 2 threads in the queue
        current_thread->next->previous = current_thread->previous;
        current_thread->previous->next = current_thread->next;
        struct thread *exit_thread = current_thread;
        schedule();
        free(exit_thread->stack);
        free(exit_thread);
        dispatch();
    }
    else{
        // Hint: No more thread to execute
        free(current_thread->stack);
        free(current_thread);
        longjmp(env_st, current_thread->ID);
    }
}
void thread_start_threading(void){
    if (setjmp(env_st) == 0) {
        dispatch();
    }
}
// part 2
void thread_register_handler(int signo, void (*handler)(int)){
    current_thread->sig_handler[signo] = handler;
}
void thread_kill(struct thread *t, int signo){
    t->signo = signo; // send signo to t
}