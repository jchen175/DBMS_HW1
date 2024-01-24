#include "record.h"
using namespace std;
const int ATTRIBUTE_SIZE = 10;

//2. Record serialization
/**
 * Compute the number of bytes required to serialize record
 */
int fixed_len_sizeof(Record *record){
    int size {};
    for(auto element:*record){
        size += strlen(element);
    }
    return size;
};

/**
 * Serialize the record to a byte array to be stored in buf.
 */
void fixed_len_write(Record *record, void *buf){
    char* buff = static_cast<char*>(buf);
    int curLoc = 0;
    for (int i = 0; i<record->size();i++){
        strncpy(buff+curLoc, (*record)[i], strlen((*record)[i]));
        curLoc+=strlen((*record)[i]);
    }

};

/**
 * Deserializes `size` bytes from the buffer, `buf`, and
 * stores the record in `record`.
 */
void fixed_len_read(void *buf, int size, Record *record){
    char*buff = static_cast<char*>(buf);
//    cout<<"Warning: based on the given input parameters, lengths of each attribute seem to be undefined"<<endl;
//    cout<<"current implementation assumes that each attribute has a fixed length of 10 bytes (10 chars)"<<endl;
    int curLoc = 0;
    int numAttr = size/ATTRIBUTE_SIZE;
    for (int i = 0; i<numAttr;i++){
        char* temp = new char[ATTRIBUTE_SIZE];
        strncpy(temp, buff+curLoc, ATTRIBUTE_SIZE);
        curLoc+=ATTRIBUTE_SIZE;
        record->push_back(temp);
    }
};

//2.2.[Optional]  Variable length record serialization
/**
 * Compute the number of bytes required to serialize record
 */
int var_len_sizeof(Record *record);

/**
 * Serialize the record using variable record encoding
 */
void var_len_write(Record *record, void *buf);

/**
 * Deserialize the `buf` which contains the variable record encoding.
 */
void var_len_read(void *buf, int size, Record *record);

