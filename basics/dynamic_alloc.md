# Dynamic Memory Allocation
Dynamic memory allcation is done on the heap, using malloc, calloc or realloc, and freed via free
(can read the notes on processes which explains exactly how malloc works)


Loose Idea:
As you know, the virtual memory that your system is defined as having is set by the vm_area_structs, specifically
the one for the heap, which is where malloced objects live:

Kernel Pagefault Handler:

1) first, the user tries to access some virtual memory address

2) The CPU will first check the TLB to see if that access was cached, and if not it will go to the MMU to 
check the memory heirarchy starting at CR3 register (on TLB miss)

3) Then, it goes to the page-table for that entry by walking the path, which contains:
physical frame number
present/not-present
read/write permission
user/supervisor permission
execute permission, etc.

4) If that physical frame is not present, then kernel throws a pagefault (AGAIN, ALL THIS STUFF IS DONE BY THER KERNEL!)
(DONT WANT USER MESSING AROUND HERE)

5) If it did pagefault, then cpu hands it off to the kernel's pagefault handler, which then starts consulting the 
vma_area_structs

6) Checks the struct, which contains information like:
struct vm_area_struct {
    unsigned long vm_start; //first address part of the VMA
    unsigned long vm_end; //ONE AFTER last address of the VMA

    struct mm_struct *vm_mm;

    pgprot_t vm_page_prot; //the level of page protections needed when modifying the page tabels for this vma
    unsigned long vm_flags; //the flags for the struct (read, write, exec, etc...)

    struct file *vm_file; //the file backing this file (NULL FOR MALLOC)
    unsigned long vm_pgoff; //THE OFFSET IN THE FILE CORRESPONDING TO THE vm_start

    const struct vm_operations_struct *vm_ops; //certain regions need special behavior when linux accesses it, faults, unmaps it, etc, and here is where it is listed

    struct anon_vma *anon_vma; //bookkeeping for anon backed. useful for fork() where you copy its vitrual memory over
    //(JUST THE USERSPACE STUFF, THE KERNEL SIDE STUFF IS ISOLATED)

    // ... various tree/list/locking metadata
};

6) By looking at the VMA, it checks whether that address is valid
If it is invalid or wrong perms, SIGSEGV (sends a signal, can be read by other processes)

7) If it is valid, but just not physically mapped => kernel allocates a page

**KEY**
FOR THE HEAP, its vma struct only covers from start_brk to brk
(thus if you write outside of there, will get SIGSEGV)

malloc, using brk(new_end) and sbrk(new_start) changes the struct size, allowing to allocate more mem to the VMA
and lettive the cpu above do its magic.

**WHY NEED MALLOC? WHY CANT JUST WRITE TO HEAP?**
**ANS** valid addresses change per program, so need some way to knwo what is valid, and constantly change that.

Secondly, how would find this valid pointer
1) ABI wont tell you
2) CPU wont tell you
3) kernel wont tell you, unless you use brk or mmap

**KEY: VMA STRUCT NOT VISIBLE IN USERSPACE! IT IS A KERNEL-SIDE RESOURCE**

## Functions:

brk(void new_end) to update the end of the heap (the break)
sbrk(ptr_diff_t inc) moves break by inc bytes, and returns the old break (VERY USEFUL)
sbrk(0) tells you where the current heap break is (RECALL: ONE GREATER THAN THE VALID ADDRESS)

Technically, you can handle this stuff yourself, but have to handle which bytes are where, and free + realloc
so malloc is just easier.

**NOTE** what if you write to an address that is valid, but you want to write more than is okay.
exe:
writing to brk-2 (2 bytes free), but you are writing an int (4 bytes)

**ANSWER** it depends

**KEY** CPU does not check address validity at the address level, but at the page table level.
when you "map" virtual addresses to physical, in reality you are mapping tables!

Thus, if it is still in the CPU state, and you want to access this address, and the table for it is already loaded in,
then it will succeed, even though technically the address is not valid by the vma struct. 

However, if the page was not loaded in prior, then the cpu will pagefault, and then it will check that address with the 
struct, and see that its invalid, so SIGSEGV. (thus, it depends on the page, so undef)




## Okay, but what does that have to do with malloc?

Key: malloc contains its own bookkeeping that the CPU/Kernel doesnt know about.

void* malloc (size_t bytes), often used with sizeof(), which takes a type or a variable, and will find its size undecayed

This function does 2 things:

1) it handles the heap using sbrk(bytes), mmap(), and the VMA to make sure that all of the accesses are valid

2) it has its own bookkeeping that keeps track of the valid addresses and what lives there

when you 
ptr = malloc()

heap looks like this:
Heap memory
       
+----------------------+-------------------+----------------------+    (higher addresses)
| malloc metadata      | user's allocation | malloc metadata      |
| for this chunk       |                   | for next chunk       |
+----------------------+-------------------+----------------------+
                       ^
                       |
                     ptr

ptr is the address that you know, and usually the malloc metadata is right below it (heap grows to higher addresses)
malloc knows:
    ┌─────────────────────────────┐
    │ address / chunk location    │
    │ size                        │
    │ allocated or free           │
    │ allocator bookkeeping       │
    └─────────────────────────────┘

Linux/VM knows:
    ┌─────────────────────────────┐
    │ virtual address range       │
    │ readable                    │
    │ writable                    │
    │ executable                  │
    │ mapped/backing information  │
    └─────────────────────────────┘

CPU/page tables know:
    ┌─────────────────────────────┐
    │ page → physical frame       │
    │ present                     │
    │ read/write/user/execute     │
    └─────────────────────────────┘
