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
    std::string path;
    std::map<std::string,std::string> settings;
public:  
//    SettingsFileHandler();
    SettingsFileHandler(std::string);

    void read();
    void write();

    void set(std::string, std::string);
    std::string get(std::string);

    void CreateSettingsFile();
};

#endif // SETTINGSFILEHANDLER_H
