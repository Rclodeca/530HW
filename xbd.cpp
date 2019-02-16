#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include "xbd.hpp"
using namespace std;


string intToHex(int input){
    stringstream stream;
    stream << hex << input;
    string str = stream.str();
    //string result;
    //transform(str.begin(), str.end(), back_inserter(result), ::toupper);
    return str;
}

string getFileContents(string filename){
ifstream stream(filename, ios::in | ios::binary);
    string fileContent;
    if(stream){
        stream.seekg(0, ios::end);
        fileContent.resize(stream.tellg());
        stream.seekg(0, ios::beg);
        stream.read(&fileContent[0], fileContent.size());
        stream.close();
    }
    return fileContent;
}

void outputFileContentHex(string fileContent){
    
    int lineLength = 0;
    int lineNumber = 0;
    
    static const char* const lut = "0123456789abcdef";
    size_t len = fileContent.length();
    
    string output;
    int address = 0;
    int finalPosition;
    string currentLine = "";
    int linePosition = 0;
    output.reserve(2 * len);
    for(size_t i = 0; i < len; ++i){
        const unsigned char c = fileContent[i];
        if(i % 16 == 0) {
            
            if(i != 0){
                output.append(" ");
                output.append(currentLine);
                currentLine = "";
                address += 16;
                output.append("\n");
                linePosition = 0;
            }
            //string tmp = to_string(address)
            //tmp + 
            stringstream stream2;
            stream2 << setw(7) << setfill('0') << intToHex(address) << ": ";
            output.append(stream2.str());
            stream2.clear();
        } else if(i != 0 && i % 2 == 0) {
            output.append(" ");
            linePosition++;
        }
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
        linePosition += 2;
        if(int(c) > 31 && int(c) < 127) {
            currentLine += c;
        } else {
            currentLine += ".";
        }
    }
    int padding = 40 - linePosition;
    for(int j = 0; j < padding; j++) {
        output.append(" ");
    }
    output.append(currentLine);
    
    cout << output << endl;
}

void outputFileContentBinary(string fileContent){
    size_t len = fileContent.length();

    string currentLine = "";
    string output;
    int linePosition = 0;
    int address = 0;
    for(size_t i = 0; i < len; ++i){
        const unsigned char c = fileContent[i];
        if(i % 6 == 0){
            if(i != 0){
                output.append(" ");
                output.append(currentLine);
                currentLine = "";
                address += 6;
                output.append("\n");
                linePosition = 0;
            }
            stringstream streamB;
            streamB << setw(7) << setfill('0') << intToHex(address) << ": ";
            output.append(streamB.str());
            streamB.clear();
        } else if(i != 0){
            output.append(" ");
            linePosition++;
        }
        //output.append(bitset<8>(fileContent.c_str()[i]));
        //cout << "debug: " << bitset<8>(fileContent.c_str()[i]) << endl;
        stringstream binaryStream;
        binaryStream << bitset<8>(fileContent.c_str()[i]);
        output.append(binaryStream.str());
        linePosition += 8;

       
        if(int(c) > 31 && int(c) < 127) {
            currentLine += c;
        } else {
            currentLine += ".";
        }
    }
    int padding = 54 - linePosition;
    for(int j = 0; j < padding; j++) {
        output.append(" ");
    }
    output.append(currentLine);
    
    cout << output << endl;
}

int main(int argc, char *argv[]){

    //cout << argc << " " << argv[1] << " " << argv[2] << endl;
    string arg1 = argv[1];
    if(argc >= 3 && arg1.compare("-b") == 0){
        //Print as Binary

        cout << "binary option" << endl;
        string filename = argv[2];
        string fileContent = getFileContents(filename);
        outputFileContentBinary(fileContent);
        

    }
    else {
        //Print as Hex

        string filename = argv[1];
        string fileContent = getFileContents(filename);

        outputFileContentHex(fileContent);  
    } 
    
}





