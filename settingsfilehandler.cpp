#include "settingsfilehandler.h"

SettingsFileHandler::SettingsFileHandler()
{

}

std::map<std::string, std::string> SettingsFileHandler::read(std::string)
{

}

void SettingsFileHandler::write(std::string filePath, std::map<std::string, std::string> settings)
{
    std::ofstream file;
    file.open(filePath);

    std::map<std::string, std::string>::iterator it;
    for (it = settings.begin(); it != settings.end(); it++)
    {
        file << it->first << ":" << it->second << std::endl;
    }
    file.close();
}
