#include "page.h"
#include <ctime>
#include <fstream>
#include <chrono>
#include <sstream>

using namespace std;
const int ATTRIBUTE_SIZE = 10;
const int ATTRIBUTE_NUM = 100;
const int RECORD_SIZE = ATTRIBUTE_SIZE * ATTRIBUTE_NUM;

void record_to_csv(Record* record){
    for(int i = 0; i < record->size()-1; i++){
        cout << (*record)[i] << ",";
    }
    cout << (*record)[record->size()-1] << endl;
}

int main(int argc, char *argv[]) {
    auto startTime = chrono::high_resolution_clock::now();
    int recordCnt = 0;
    int pageCnt = 0;

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <page_file> <page_size>\n";
        return 1;
    }

    string pageFile = argv[1];
    int pageSize = stoi(argv[2]);

    // open page file
    ifstream pageF(pageFile);
    if (!pageF) {
        cerr << "Error opening PAGE file." << endl;
        return 1;
    }
    // read page file
    Page *page = new Page();
    init_fixed_len_page(page, pageSize, RECORD_SIZE);
    int pageCapacity = fixed_len_page_capacity(page);
    cout << "pageCapacity: " << pageCapacity << endl;
    int slotCnt = 0;
    // read a page
    while (!pageF.eof()){
        char *pageData = new char[pageSize];
        pageF.read(pageData, pageSize);
        auto readBytes = pageF.gcount();
//        cout << "readBytes: " << readBytes << endl;
//        cout << "pageData: " << pageData << endl;
        if (readBytes == 0) break;
        pageCnt++;
        page->data = pageData;
        int actualSlotCnt = static_cast<int>(readBytes)/RECORD_SIZE;
//        cout << "actualSlotCnt: " << actualSlotCnt << endl;

        // read a record
        for (slotCnt = 0; slotCnt < min(pageCapacity, actualSlotCnt); slotCnt++){
            auto *record = new Record();
            read_fixed_len_page(page, slotCnt, record);
            // print_record(record);
            record_to_csv(record);
            recordCnt++;
        }
    }
    //clean up
    pageF.close();
    delete page;
    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
    cout << "NUMBER OF RECORDS: " << recordCnt << endl;
    cout << "NUMBER OF PAGES: " << pageCnt << endl;
    cout << "TIME: " << duration.count() << " milliseconds" << endl;
}