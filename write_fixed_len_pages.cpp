#include "page.h"
#include <ctime>
#include <fstream>
#include <chrono>
#include <sstream>
#include <filesystem>

using namespace std;
const int ATTRIBUTE_SIZE = 10;
const int ATTRIBUTE_NUM = 100;
const int RECORD_SIZE = ATTRIBUTE_SIZE * ATTRIBUTE_NUM;

void record_to_csv(Record* record){
    for(auto element:*record){
        cout<<element<<",";
    }
    cout<<endl;
}


Record parseCSVLine(string line) {
    Record tempRecord {};
    stringstream lineStream(line);
    string cell;
    while (getline(lineStream, cell, ',')) {
        char *newStr = new char[cell.size() + 1];
        std::strcpy(newStr, cell.c_str());
        tempRecord.push_back(newStr);
    }
    return tempRecord;
}


int main(int argc, char *argv[]) {
    auto startTime = chrono::high_resolution_clock::now();

    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <csv_file> <page_file> <page_size>\n";
        return 1;
    }

    string csvFile = argv[1];
    string pageFile = argv[2];
    int pageSize = stoi(argv[3]);
    // init page file
    if (std::filesystem::exists(pageFile)) {
        try {
            filesystem::remove(pageFile);
        } catch (const filesystem::filesystem_error& e) {
            cerr << "Error deleting file: " << e.what() << '\n';
            return 1;
        }
    }

    // open csv file
    ifstream csvF(csvFile);
    if (!csvF) {
        cerr << "Error opening CSV file." << endl;
        return 1;
    }
    // read csv file
    string line {};
    Page *page = new Page();
    init_fixed_len_page(page, pageSize, RECORD_SIZE);
    int pageCapacity = fixed_len_page_capacity(page);
    int recordCnt = 0;
    int pageUsed = 0;

    while (getline(csvF, line)) {
//        cout << "line: " << line << endl; // DEBUG
        Record record = parseCSVLine(line);
//        cout << "Record: "; // DEBUG
//        cout << "page content: " <<(char *)page->data << endl; // DEBUG
//        cout << "page freeslot: " << fixed_len_page_freeslots(page) << endl; // DEBUG
        int status = add_fixed_len_page(page, &record);
//        cout << "status: " << status << endl; // DEBUG

        if (status == -1) {
            // Page is full, write to file
            ofstream pageF(pageFile, std::ios::binary | std::ios::app);
            if (!pageF) {
                cerr << "Error opening page file." << endl;
                return 1;
            }
            int numRecords = pageCapacity-fixed_len_page_freeslots(page);
            pageF.write((char *)page->data, numRecords*RECORD_SIZE);
            pageF.close();
            pageUsed++;
            init_fixed_len_page(page, pageSize, RECORD_SIZE); // Reinitialize page
            add_fixed_len_page(page, &record); // Add record to the new page
        }
        recordCnt++;
    }
    int remainingRecords = pageCapacity-fixed_len_page_freeslots(page);
    if ( remainingRecords > 0) {
        // Write any remaining page to file
        ofstream pageF(pageFile, std::ios::binary | std::ios::app);
        if (!pageF) {
            cerr << "Error opening page file." << endl;
            return 1;
        }
        pageF.write((char *)page->data, remainingRecords*RECORD_SIZE);
        pageF.close();
        pageUsed++;
    }

    auto endTime = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);

    std::cout << "NUMBER OF RECORDS: " << recordCnt << endl;
    std::cout << "NUMBER OF PAGES: " << pageUsed << endl;
    std::cout << "TIME: " << timeTaken.count() << " milliseconds" << endl;

    // Clean up
    csvF.close();
    free(page->data);
}

