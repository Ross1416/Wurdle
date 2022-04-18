// settingsfilehander.h
// Author: Ross Inglis
// Last modified: 12/04/22

#ifndef SETTINGSFILEHANDLER_H
#define SETTINGSFILEHANDLER_H

#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<QDir>

class SettingsFileHandler
{

private:
    std::string path;   // Path to settings file
    std::map<std::string,std::string> settings; // map of settings (format: "Property","Value")

public:  
    SettingsFileHandler(std::string);

    // Read and write from/to file
    void read();
    void write();

    // Get and set individual properties
    void set(std::string, std::string);
    std::string get(std::string);

    // Create new settings file (called if one is not found)
    void CreateSettingsFile();
};

#endif // SETTINGSFILEHANDLER_H
