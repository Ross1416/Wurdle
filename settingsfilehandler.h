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
public:  
    SettingsFileHandler();
    SettingsFileHandler(std::string);

    std::map<std::string,std::string> read();
    void write(std::map<std::string,std::string>);

    void CreateSettingsFile();
};

#endif // SETTINGSFILEHANDLER_H
