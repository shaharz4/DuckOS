#include "syscall.h"
#include "task.h"
#include "isr.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../drivers/ext2.h"
#include "memory.h"

void initialise_syscalls() {
    ;
}

void handle_syscall(registers_t * regs) {
    int a;
    switch(regs->int_no) {
        case 0x80: // Interrupt test                    KMODE
            puts("Recieved interrupt: 0x80. Interrupts seem to be functioning properly.\n");
            break;
        case 0x81: // Init tasking                      KMODE
			init_tasking(regs);
			break;
		case 0x82: // Tasking                           USERLAND
            switch(regs->eax) {
                case 0x01: // Exit
                    remove_task(regs);
                    break;
                case 0x02: // Yield
                    roundRobinNext(regs);
                    break;
                case 0x03: // Get more heap
                    brk((page_directory_pointer_table_entry_t *)regs->cr3, (unsigned int)regs->ebx);
                    break;
                case 0x04: // execve
                    execve((char *)regs->ebx, (int)regs->edx, (char **)regs->ecx);
                    break;
                case 0x05: // ps
                    print_task_linked_list();
                    break;
                case 0x06: // dump memory data
                    dump_mmap();
                    dump_frame_map();
                    dump_all_task_memory_usage();
                    break;
                default:
                    return;
            }
            break;
        case 0x83: // Screen                            USERLAND
            switch(regs->eax) {
                case 0x01: // Put char
                    putc((char)regs->ebx);
                    break;
                case 0x02: // Put string
                    puts((char *)regs->ebx);
                    break;
                case 0x03: // Clear screen
                    screen_clear();
                    break;
                case 0x04: // Set screen dolor
                    set_screen_bgfg((char)regs->ebx);
                    break;
                default:
                    return;   
            }
            break;
        case 0x84: // Keyboard                          USERLAND
            switch(regs->eax) {
                case 0x01: // Get char
                    regs->edx = getc();
                    break;
                case 0x02: // Get string
                    gets((char *)regs->ebx);
                    break;
                default:
                    return;   
            }
            break;
        case 0x85: // EXT2 Filesystem                    USERLAND
            switch(regs->eax) {
                case 0x01: // Load inode structure
                    load_inode(regs->ebx, (void *)regs->ecx);
                    break;
                case 0x02: // Load directory structure
                    load_directory_structure(regs->ebx, (void *)regs->ecx);
                    break;
                case 0x03: // Load file
                    load_file(regs->ebx, regs->ecx, regs->edx, (void *)regs->edi);
                    break;
                case 0x04: // Convert a path to inode num
                    regs->edx = path_to_inode((char *)regs->ebx);
                    if((int)regs->edx < 0) 
                    {
                        puts("Path not found: ");
                        puts((char *)regs->ebx);
                        remove_task(regs);
                        puts("\nTask terminated.\n");
                    }
                    break;
                case 0x05: // does a path exist
                    a = (int)path_to_inode((char *)regs->ebx);
                    if(a == -1) regs->edx = 1;
                    else regs->edx = 0;
                    break;
                default:
                    return;
            }
            break;
        default:
            return;
    }
}