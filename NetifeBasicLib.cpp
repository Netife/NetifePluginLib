//
// Created by Administrator on 2023/5/2.
//

#include "NetifeBasicLib.h"
#include "TextHelper.h"
#include <Poco/JSON/Parser.h>

NetifeBasicLib::~NetifeBasicLib() {}

std::string NetifeBasicLib::GetName() const{
    return "NetifeBasicLib";
}

std::string NetifeBasicLib::GetVersion() const{
    return "1.0.0";
}

void NetifeBasicLib::OnLoaded() {
    agent->LogInfo("NetifeBasicLib loaded success!");
    agent->LogInfo("NetifeBasicLib is a basic component of Netife, it is updated without bound of Netife Primary Component, please "
                   "check update at ");
}

bool NetifeBasicLib::OnEnable() {
    return true;
}

bool NetifeBasicLib::OnDisable() {
    return true;
}

void NetifeBasicLib::OnExiting() {
    agent->LogInfo("NetifeBasicLib is trying to clear the cache of shared lib...");
}

std::string
NetifeBasicLib::DispatcherCommand(std::string commandHead, std::map<std::string, std::optional<std::string>> params) {
    if (commandHead == "parserRawHtml"){
        return ParserRawHtml(params["rawHtml"].value());
    }

    return "";
}

std::string NetifeBasicLib::ParserRawHtml(const string &rawHtml) {

    vector<string> htmlArr = Netife::TextHelper::split(rawHtml, "\r\n\r\n");

    Poco::JSON::Object json;

    if (htmlArr.size() == 2){
        json.set(std::string("dataBody"), htmlArr[1]);
    }

    vector<string> htmlHeadLine = Netife::TextHelper::split(htmlArr[0],"\r\n");

    json.set(string("status"), htmlHeadLine[0]);

    for (int i = 1; i < htmlHeadLine.size(); ++i) {
        vector<string> temp = Netife::TextHelper::split(htmlHeadLine[i], ":");
        json.set(string("head::") + temp[0],temp[1]);
    }

    std::ostringstream oss;
    json.stringify(oss);

    return oss.str();
}

POCO_BEGIN_MANIFEST(NetifePlugins)
        POCO_EXPORT_CLASS(NetifeBasicLib)
POCO_END_MANIFEST
