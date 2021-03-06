#ifndef VM_FRAME_H
#define VM_FRAME_H

#include "lib/kernel/bitmap.h"
#include "threads/palloc.h"
#include <hash.h>

/* Frame Map */
struct hash user_frames;
struct lock user_frames_lock;

struct frame
  {
    struct hash_elem hash_elem; /* Hash table element. */

    uint32_t id;		/* Frame / Swap table id. */
    uint32_t *pagedir;	/* User page directory. */
    void* upage;		/* User Page. */

    /* TODO insert eviction data */
  };
  
struct swap_frame {
        //pointer to the user memory page in the frame
        uint8_t *addr;
        struct hash_elem hash_elem;
        struct thread * thread;
        bool lock;
};


void user_frames_init(void);

/* Main memory allocation */
void *alloc_user_frames (enum palloc_flags, size_t page_cnt);

void register_frame (void *upage, void *kpage);
void unregister_frames (void *kpage, size_t page_cnt);

void destroy_user_frames(void);

uint8_t * get_frame (void);
void frame_remove(void *);


/* hash functions */
unsigned frame_hash (const struct hash_elem *f_, void *aux);
bool frame_less (const struct hash_elem *a_, const struct hash_elem *b_, void *aux);

#endif
