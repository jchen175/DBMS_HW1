#ifndef RECORD
#define RECORD

#include <iostream>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <climits>
#include <cstring>
#include <vector>

typedef const char* V;
typedef std::vector<V> Record;



/**
 * Compute the number of bytes required to serialize record
 */
int fixed_len_sizeof(Record *record);

/**
 * Serialize the record to a byte array to be stored in buf.
 */
void fixed_len_write(Record *record, void *buf);
/**
 * Deserializes `size` bytes from the buffer, `buf`, and
 * stores the record in `record`.
 */
void fixed_len_read(void *buf, int size, Record *record);

#endif