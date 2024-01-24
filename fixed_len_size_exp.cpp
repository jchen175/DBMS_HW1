#include "record.h"

const int ATTRIBUTE_SIZE = 10;
using namespace std;

//2.1. Experiments
int main(int argc, char *argv[]) {
    Record sampleRecord;
    for(int i = 0; i < 100; i++) {
        sampleRecord.push_back("1234567890");
    }

    int size = fixed_len_sizeof(&sampleRecord);
    cout << "generated sample record: " << endl;
    cout << "\tnumber of attributes: " << sampleRecord.size() << endl;
    cout << "\tsize of each attribute: " << ATTRIBUTE_SIZE << endl;
    cout << "Calculated size of the record: " << size << " bytes." << endl;

    if(size == sampleRecord.size()*ATTRIBUTE_SIZE) {
        cout << "Size calculation is CORRECT." << endl;
    } else {
        cout << "Size calculation is INcorrect." << endl;
    }

    return 0;
}
