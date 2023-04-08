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
  pte_t* pteptr = walk(p->pagetable, va, 0);

  if (*pteptr & PTE_S) { // if the page is previously swapped out
    *pteptr &= ~PTE_S; // clear the swapped-out bit
    *pteptr |= PTE_V; // set the valid bit
    char* pa = kalloc();
    uint blockno = PTE2BLOCKNO(*pteptr);
    begin_op(); read_page_from_disk(ROOTDEV, pa, blockno); end_op();
    begin_op(); bfree_page(ROOTDEV, blockno); end_op();
    *pteptr = PA2PTE(pa) | PTE_FLAGS(*pteptr);
  } else {
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
  }
  return 0;
}
