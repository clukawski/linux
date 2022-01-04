#ifndef _LINUX_RAMCRYPT_H
#define _LINUX_RAMCRYPT_H

#include <linux/list.h>
#include <linux/spinlock.h>

#define RAMCRYPT_SW_SIZE  4
#define RAMCRYPT_ELF_FLAG 0x10
#define RAMCRYPT_CIPHER   "tresor"

#define VM_DONOTRAMCRYPT (VM_SHARED|VM_PFNMAP|VM_IO)


struct mm_ramcrypt {
	spinlock_t lock;
	unsigned long sw_size;
	struct mm_ramcrypt_sw {
		struct list_head list;
		unsigned long addr;
	} sw;
};


struct mm_ramcrypt *ramcrypt_mm_init(void);
void ramcrypt_mm_free(struct mm_ramcrypt *r);
void ramcrypt_mm_lock(struct mm_ramcrypt *r);
void ramcrypt_mm_unlock(struct mm_ramcrypt *r);
struct mm_ramcrypt *ramcrypt_mm_dup(struct mm_ramcrypt *s);
int ramcrypt_mm_sw_append(struct mm_ramcrypt *r, unsigned long addr);
unsigned long ramcrypt_mm_sw_pop(struct mm_ramcrypt *r);
void ramcrypt_mm_sw_remove(struct mm_ramcrypt *r, unsigned long addr);
void ramcrypt_mm_debug(struct mm_ramcrypt *r);

void ramcrypt_page_encrypt(void *addr, unsigned long iv1, unsigned long iv2);
void ramcrypt_page_decrypt(void *addr, unsigned long iv1, unsigned long iv2);

#endif /* _LINUX_RAMCRYPT_H */
