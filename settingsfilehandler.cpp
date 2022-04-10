#include "settingsfilehandler.h"
#include<iostream>

//SettingsFileHandler::SettingsFileHandler()
//{
//    path = "";
//}

SettingsFileHandler::SettingsFileHandler(std::string filePath)
{
    path = QDir().absolutePath().toStdString() + "/" + filePath;
//    std::cout<<path<<"\n";
    std::ifstream file;
    file.open(path);
    if (!file)
        CreateSettingsFile();
    else
        file.close();
}

void SettingsFileHandler::CreateSettingsFile()
{
    std::ofstream file;
    file.open(path);
    file << "AnswerList:" << QDir().absolutePath().toStdString() + "/" + "answerList.txt" << std::endl;
    file << "GuessList:" << QDir().absolutePath().toStdString() + "/" + "guessList.txt" << std::endl;
    file << "Language:English" << std::endl;
    file << "NoOfGuesses:6" << std::endl;
    file.close();
}

void SettingsFileHandler::read()
{
    std::ifstream file;
    file.open(path);

    if (file)
    {

        std::map<std::string, std::string>::iterator it;
        std::string line;

        while (getline(file, line))
        {
            std::string setting, value;
            int split = line.find(':');
            setting = line.substr(0,split);
            value = line.substr(split+1,line.length());
            settings[setting] = value;
//            std::cout<<setting<<":"<<value<<std::endl;
        }
    }
//    else{
//        std::cout<<"error1\n";
//    }
    file.close();
}

void SettingsFileHandler::write()
{
    std::ofstream file;
    file.open(path);//, std::ios::trunc);

    if (file)
    {
        std::map<std::string, std::string>::iterator it;
        for (it = settings.begin(); it != settings.end(); it++)
        {
//            std::cout<<it->first<<":"<<it->second<<std::endl;
            file << it->first << ":" << it->second << std::endl;
        }
        file.close();
    }/*else
    {
        std::cout<<"error2"<<std::endl;

    }*/
}

void SettingsFileHandler::set(std::string property, std::string value)
{
    settings[property] = value;
}

std::string SettingsFileHandler::get(std::string property)
{
//    std::cout<<"in handler"<<settings[property]<<std::endl;
    return settings[property];
}
