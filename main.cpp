#include <fstream>
#include <iostream>
#include <string>

const uint16_t MAX_PORT_NUMBER = 65535;

// Find the port number
uint16_t FindPortNum(std::string str);

int main() {
    std::fstream file;
    file.open("/usr/local/etc/v2ray/config.json", std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: open file failure!" << std::endl; 
        exit(EXIT_FAILURE);
    }
    std::string port_field;
    port_field.resize(1024);
    std::streampos port_field_pos;
    while (true) { 
        port_field_pos = file.tellp();
        file.getline((char*)port_field.c_str(), port_field.size());
        size_t exist_port_field = port_field.find("\"port\"");
        if (exist_port_field != std::string::npos) {
            port_field_pos += exist_port_field;
            break;
        }
        if (file.eof()) {
            std::cerr << "Error: not found port field!" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    auto port_num = FindPortNum(port_field);
    if (port_num == -1) {
        std::cerr << "Error: Not found port number!" << std::endl;
        exit(EXIT_FAILURE);
        //TODO
    }
    if (port_num >= MAX_PORT_NUMBER) {
        std::cerr << "Error: The new port number will be more than 65535!" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Old port: " << port_num << std::endl;
    ++port_num;
    std::cout << "New port: " << port_num << std::endl;
    file.seekp(port_field_pos, std::ios::beg);
    file << R"("port": )" << port_num << ",";
    file.close();
}

uint16_t FindPortNum(std::string str) {
    std::string port_num_str;
    int port_num = -1;
    for (size_t i = 0; i < str.size(); ++i) {
        if (isdigit(str[i])) {
            port_num_str += str[i];
        }
    } 
    if (!port_num_str.empty()) {
        port_num = atoi(port_num_str.c_str());
    }
    return port_num;
}
