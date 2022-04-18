// settings.cpp
// Author: Ross Inglis
// Last modified: 18/04/22

#include "settingsfilehandler.h"

#include<iostream>

// CONSTRUCTOR
SettingsFileHandler::SettingsFileHandler(std::string fileName)
{
    // Set path to current location + file name
    path = QDir().absolutePath().toStdString() + "/" + fileName;
    // Open file
    std::ifstream file;
    file.open(path);

    // If can't open file, create a new one with default values else close.
    if (!file)
        CreateSettingsFile();
    else
        file.close();
}

// CREATE SETTINGS FILE WITH DEFAULT VALUES
void SettingsFileHandler::CreateSettingsFile()
{
    std::ofstream file;
    file.open(path);
    file << "AnswerList:" << QDir().absolutePath().toStdString() + "/WordLists/" + "answerList-5-eng.txt" << std::endl;
    file << "GuessList:" << QDir().absolutePath().toStdString() + "/WordLists/" + "guessList-5-eng.txt" << std::endl;
    file << "Language:English" << std::endl;
    file << "NoOfGuesses:6" << std::endl;
    file << "NoOfCharacters:5" << std::endl;
    file.close();
}

// READ SETTINGS FROM FILE
void SettingsFileHandler::read()
{
    // Open file
    std::ifstream file;
    file.open(path);

    if (!file)
        CreateSettingsFile();

    std::string line;
    // Read properties and values in the settings file and save in settings map
    while (getline(file, line))
    {
        std::string setting, value;
        int split = line.find(':');
        setting = line.substr(0,split);
        value = line.substr(split+1,line.length());
        settings[setting] = value;
    }
    file.close();
}

// WRITE SETTINGS TO FILE
void SettingsFileHandler::write()
{
    std::ofstream file;
    file.open(path);

    if (!file)
        CreateSettingsFile();

    // Write settings map properties and values to the settings file
    std::map<std::string, std::string>::iterator it;
    for (it = settings.begin(); it != settings.end(); it++)
    {
        file << it->first << ":" << it->second << std::endl;
    }
    file.close();
}

// SET INDIVIDUAL PROPERTY VALUE
void SettingsFileHandler::set(std::string property, std::string value)
{
    settings[property] = value;
}

// GET INDIVIDUAL PROPERTY VALUE
std::string SettingsFileHandler::get(std::string property)
{
    return settings[property];
}
