#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "memlayout.h"
#include "mmu.h"

int magic_num = 123456;

// this address is stored in data/text section 
int* stack_ptr = (int*) KERNBASE - 4; 

int
main(int argc, char *argv[])
{
  // create two integers, one in stack, another in heap
  int stack_val = magic_num;
  int* heap_ptr = malloc(sizeof(int));
  printf(1, "addr of stack_val: %x\n", &stack_val);
  printf(1, "addr of heap_ptr: %x\n", heap_ptr);

  // compare the addresses of the two integers
  // test will pass if stack_val has higher address
  if(heap_ptr < &stack_val){
    printf(1, "TEST 1 PASSED\n");
  } else {
    exit();
  }

  // initialize somewhere in the end of user memory(i.e., stack)
  *stack_ptr = magic_num;

  // create a chile with the same address space
  int rc = fork();
  if(rc == 0){
    // test would pass only if the stack is properly copied
    // if not, the kernel traps
    if(*stack_ptr == magic_num){
      printf(1, "TEST 2 PASSED\n");
    } 

    // int small_test[512];
    // for(int i=0; i<512; i++){
    //   small_test[i] = i;
    // }
    // printf(1, "small test of 512 should pass");
    // for(int i=0; i<512; i++)
    //   printf(1,"addr-%d val-%d,",&small_test[i],small_test[i]);

    /* 
      If you want to test the bonus, uncomment the medium test.
      (lines 55-61 here). I am commenting so the regular program works when you test
    */

    // int med_test[1024];
    // for(int i=0; i<1024; i++){
    //   med_test[i] = i;
    // }
    // printf(1, "medium test of 1024");
    // for(int i=0; i<1024; i++)
    //   printf(1,"addr : %d \t val : %d, \n",&med_test[i],med_test[i]);

    // int large_test[2048];
    // for(int i=0; i<2048; i++){
    //   large_test[i] = i;
    // }
    // printf(1, "large test of 2048. this should break because it will try to grow too high into heap");
    // for(int i=0; i<2048; i++)
    //   printf(1,"addr : %d \t val : %d, \n",&large_test[i],large_test[i]);


  } else if (rc > 0) {
    (void) wait();
    // grow the stack by accessing a address 
    // in the page right below the initial stack page
    char *p = (char*) (KERNBASE - PGSIZE - 4);
    *p = 'z';

    // test would pass if no trap happened
    printf(1, "TEST 3 PASSED\n");

  } else {
    printf(1, "fork failed!\n");
  }
  exit();
}
