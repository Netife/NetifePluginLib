//
// Created by Administrator on 2023/5/2.
//

#include "NetifeBasicLib.h"
#include "TextHelper.h"
#include <Poco/JSON/Parser.h>
#include <bitset>
#include <fstream>
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
using Poco::UUID;
using Poco::UUIDGenerator;

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

    if (commandHead == "parserHexString"){
        return ParserHexString(params["content"].value());
    }

    if (commandHead == "parserStringHex"){
        return ParserHexString(params["content"].value());
    }

    if (commandHead == "writeHexFile"){
        return WriteHexFile(params["content"].value());
    }

    if (commandHead == "generateUUID"){
        return GenerateUUID(params["content"]);
    }

    if (commandHead == "getRawRequestByUUID"){
        return GetRawRequestByUUID(params["UUID"].value(), params["uuid_sub"]);
    }
    return "";
}

std::string NetifeBasicLib::ParserRawHtml(const string &rawHtml) {

    vector<string> htmlArr = Netife::TextHelper::splitMulti(rawHtml, "\r\n\r\n");

    Poco::JSON::Object json;

    if (htmlArr.size() == 2){
        json.set(std::string("dataBody"), htmlArr[1]);
    }

    vector<string> htmlHeadLine = Netife::TextHelper::splitMulti(htmlArr[0],"\r\n");

    json.set(string("status"), htmlHeadLine[0]);

    for (int i = 1; i < htmlHeadLine.size(); ++i) {
        vector<string> temp = Netife::TextHelper::splitMulti(htmlHeadLine[i], ":");
        json.set(string("head::") + temp[0],temp[1]);
    }

    std::ostringstream oss;
    json.stringify(oss);

    return oss.str();
}

std::string NetifeBasicLib::ParserHexString(std::string content) {
    std::string result;
    for (size_t i = 0; i < content.length(); i += 2) {
        std::string byte = content.substr(i, 2);
        char chr = (char) (int) strtol(byte.c_str(), nullptr, 16);
        result.push_back(chr);
    }
    return result;
}

std::string NetifeBasicLib::ParserStringHex(std::string content) {
    const std::string hex = "0123456789ABCDEF";
    std::stringstream ss;
    for (std::string::size_type i = 0; i < content.size(); ++i)
        ss << hex[(unsigned char)content[i] >> 4] << hex[(unsigned char)content[i] & 0xf];
    std::cout << ss.str() << std::endl;
    return ss.str();
}

std::string NetifeBasicLib::WriteHexFile(std::string content) {
    std::bitset<8> bits;

    UUIDGenerator& generator = UUIDGenerator::defaultGenerator();
    UUID uuid1(generator.create());
    std::string name = uuid1.toString();
    std::filesystem::path rootPath(agent->GetPluginDataPath());
    std::ofstream ofs( (rootPath / "fileStreamPath" / (name + ".temp")).string(), std::ios::binary);
    for (size_t i = 0; i < content.size(); i += 2)
    {
        bits = std::bitset<8>(content.substr(i, 2));
        auto output = static_cast<unsigned char>(bits.to_ulong());
        ofs.write((char*)(&output), sizeof(output));
    }

    ofs.close();
    return (rootPath / "fileStreamPath" / (name + ".temp")).string();
}

std::string NetifeBasicLib::GenerateUUID(optional<std::string> content) {
    UUIDGenerator& generator = UUIDGenerator::defaultGenerator();
    if (content.has_value()){
        UUID uuid(generator.createFromName(UUID::uri(), content.value()));
        return uuid.toString();
    }else{
        UUID uuid(generator.create());
        return uuid.toString();
    }
}

std::string NetifeBasicLib::GetRawRequestByUUID(std::string UUID, optional<std::string> uuid_sub) {
    auto res = agent->GetRawTextByUUID(UUID, uuid_sub);

    if (res.has_value()){
        return res.value()[0];
    }

    return "No Result";
}

POCO_BEGIN_MANIFEST(NetifePlugins)
        POCO_EXPORT_CLASS(NetifeBasicLib)
POCO_END_MANIFEST
