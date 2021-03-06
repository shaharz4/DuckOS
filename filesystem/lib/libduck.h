#ifndef LIBDUCK_H
#define LIBDUCK_H

struct EXT2_INODE {
    unsigned short  type_prem;
    unsigned short  user_id;
    unsigned int    size_low;
    unsigned int    last_access_time;
    unsigned int    creation_time;
    unsigned int    modification_time;
    unsigned int    deletion_time;
    unsigned short  group_id;
    unsigned short  hard_links;
    unsigned int    sector_usage;
    unsigned int    flags;
    unsigned int    OS_type;
    unsigned int    direct_block_pointers[12];
    unsigned int    singly_indirect_block_pointer;
    unsigned int    doubly_indirect_block_pointer;
    unsigned int    triply_indirect_block_pointer;
    unsigned int    generation_num;
    unsigned int    extended_attribute_block;
    unsigned int    size_high_dir_acl;
    unsigned int    block_addr_of_fragment;
    unsigned char   os_specific[12];
}__attribute__((packed));

typedef struct EXT2_INODE EXT2_INODE_t;

struct EXT2_DIRECTORY_ENTRY {
    unsigned int inode;
    unsigned short size;
    unsigned short name_len;
    unsigned char name_ptr;
}__attribute__((packed));

typedef struct EXT2_DIRECTORY_ENTRY EXT2_DIRECTORY_ENTRY_t;

void _start(void);
void _exit(void);
void task_yield();
void init_libduck(void);
void screen_clear();
void set_screen_bgfg(unsigned char bgfg);
void putc(char c);
void puts(char * string);
void init_heap(void);
void extend_heap();
void *malloc(unsigned int size);
void free(void * ptr);
char getc();
char * gets(char * buff);
void execve(char * path, int argc, char ** argv, int yield);
void load_inode(int inode_num, void * buf) ;
void load_directory_structure(int inode_num, void * buf);
void load_file(int inode_num, int seek, int skip, void *buff) ;
int path_to_inode(char * path);
int path_exists(char * path);
#endif