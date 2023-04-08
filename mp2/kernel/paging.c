#include "param.h"
#include "types.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "defs.h"
#include "proc.h"

/* NTU OS 2022 */
/* Page fault handler */
int handle_pgfault(uint64 va) {
  /* Find the address that caused the fault */
  struct proc* p = myproc();
  
  char* newmem = kalloc();
  if (newmem) { // success
    memset(newmem, 0, PGSIZE);
    if (mappages(p->pagetable, PGROUNDDOWN(va), PGSIZE, (uint64)newmem, PTE_U|PTE_R|PTE_W|PTE_X) != 0) {
      kfree(newmem);
      p->killed = 1;
    }
  } else {
    p->killed = 1;
  }
  return 0;
}
