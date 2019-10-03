#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include <map>



using namespace std;

vector<string> splitStr(const std::string& str, char delim){
    vector<string> lst;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, ',')) {
        lst.push_back(token);
    }
    return lst;
}

struct CsvData{
    vector<pair<string, int>> header;
    vector<vector<string>> data;
};


class CsvParser {
public:
    bool _hasError;
    string _fileName;
    
    CsvParser(string fname): _hasError(false), _fileName(fname) {
        
    }
    
    CsvData parse() {
        CsvData rs;
        
        ifstream inFile;
        inFile.open(_fileName);
        if(!inFile){
            throw runtime_error("inpout file exception");
        }
        
        string line;
        int ctr = 0;
        while (getline(inFile, line)){
            if(ctr == 0){
                auto cols = splitStr(line, ',');
                for(string col : cols){
                    rs.header.push_back(make_pair(col, col.size()));
                }
                ctr++;
                continue;
            }
            
            auto cels = splitStr(line, ',');
            int idx = 0;
            for(string cel : cels){
                rs.header[idx].second = max<int>(cel.size(), rs.header[idx].second);
                idx++;
            }
            rs.data.push_back(cels);
        }
        return rs;
    }
    
};


int main(int argc, const char * argv[]) {
    cout << "Hello, World!\n";
    
    CsvParser parser{"data.csv"};
    try {
        CsvData d = parser.parse();
        
        int idx = 0;
        for(auto header : d.header){
            cout << std::setw(header.second+5);
            cout << header.first;
            idx++;
        }
        cout << "\n";
        
        for(auto row : d.data){
            idx = 0;
            for(auto cell : row){
                cout << setw(d.header[idx].second+5) << cell;
                idx++;
            }
            cout << endl;
        }
        
        
    } catch (exception &e) {
        cout << e.what() << endl;
    }
    
    
    return 0;
}
