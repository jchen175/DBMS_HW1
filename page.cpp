#include "page.h"
using namespace std;

/**
 * Initializes a page using the given slot size
 */
void init_fixed_len_page(Page *page, int page_size, int slot_size){
    page->data = malloc(page_size);
    memset(page->data, 0, page_size);
    page->page_size = page_size;
    page->slot_size = slot_size;
};

/**
 * Calculates the maximal number of records that fit in a page
 */
int fixed_len_page_capacity(Page *page){
    return page->page_size/page->slot_size;
};

/**
 * Calculate the free space (number of free slots) in the page
 */
int fixed_len_page_freeslots(Page *page){
    int numAll = fixed_len_page_capacity(page);
    int numFree = 0;
    char *charData = (char *)page->data;
    for (int i = 0; i<numAll;i++){
        if (charData[i*(page->slot_size)] == 0){
            numFree++;
        }
    }
    return numFree;
};

/**
 * Write a record into a given slot.
 */
void write_fixed_len_page(Page *page, int slot, Record *r){
    char *charData = (char *)page->data;
    fixed_len_write(r, charData+slot*(page->slot_size));
};

/**
 * Add a record to the page
 * Returns:
 *   record slot offset if successful,
 *   -1 if unsuccessful (page full)
 */
int add_fixed_len_page(Page *page, Record *r){
    int numAll = fixed_len_page_capacity(page);
    char *charData = (char *)page->data;
    for (int i = 0; i<numAll;i++){
        if (charData[i*(page->slot_size)] == 0){
            write_fixed_len_page(page, i, r);
            return i;
        }
    }
    return -1;
};

/**
 * Read a record from the page from a given slot.
 */
void read_fixed_len_page(Page *page, int slot, Record *r){
    char *charData = (char *)page->data;
    fixed_len_read(charData+slot*(page->slot_size), page->slot_size, r);
};