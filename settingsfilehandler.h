#ifndef SETTINGSFILEHANDLER_H
#define SETTINGSFILEHANDLER_H

#include<fstream>
#include<map>

class SettingsFileHandler
{
public:  
    SettingsFileHandler();



    std::map<std::string,std::string> read(std::string);
    void write(std::string, std::map<std::string,std::string>);

};

#endif // SETTINGSFILEHANDLER_H
