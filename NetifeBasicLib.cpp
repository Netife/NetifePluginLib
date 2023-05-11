//
// Created by Administrator on 2023/5/2.
//

#include "NetifeBasicLib.h"

NetifeBasicLib::~NetifeBasicLib() {}

std::string NetifeBasicLib::GetName() const{
    return "NetifeBasicLib";
}

std::string NetifeBasicLib::GetVersion() const{
    return "1.0.0";
}

std::string NetifeBasicLib::DispatcherCommand(std::string commandOriginal) {
    agent->LogInfo("NetifeBasicLib is commanded by " + commandOriginal);
    return "over";
}

void NetifeBasicLib::OnLoaded() {
    agent->LogInfo("NetifeBasicLib loaded success!!!");
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

POCO_BEGIN_MANIFEST(NetifePlugins)
        POCO_EXPORT_CLASS(NetifeBasicLib)
POCO_END_MANIFEST
