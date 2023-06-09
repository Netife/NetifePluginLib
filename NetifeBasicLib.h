//
// Created by Administrator on 2023/5/2.
//


#ifndef NETIFEDEMOPLUGIN_DEMOCLASS_H

#define NETIFEDEMOPLUGIN_DEMOCLASS_H
#include "include/plugins/v1/NetifePlugins.h"
#include "include/plugins/v1/NetifePluginAgent.h"
#include "Poco/ClassLibrary.h"

class NetifeBasicLib : public NetifePlugins{
public:
    NetifeBasicLib() : NetifePlugins(){

    }

    ~NetifeBasicLib() override;

    std::string GetName() const override;

    std::string GetVersion() const override;

    std::string DispatcherCommand(std::string commandHead, std::map<std::string, std::optional<std::string>> params) override;

    //当插件启用的时候 [顺序不明确]
    bool OnEnable() override;

    //当插件关闭的时候 [可能是人为禁用单独的插件]
    bool OnDisable() override;

    //当插件全部加载完毕的时候 [此时可以使用依赖插件]
    void OnLoaded() override;

    //当软件即将退出的时候 [此时所有插件都即将关闭]
    void OnExiting() override;

    std::string ParserRawHtml(const string &rawHtml);

    std::string ParserHexString(std::string content);

    std::string ParserStringHex(std::string content);

    std::string WriteHexFile(std::string content);

    std::string GenerateUUID(optional<std::string> content);

    std::string GetRawRequestByUUID(std::string UUID, optional<std::string> uuid_sub);
};
#endif //NETIFEDEMOPLUGIN_DEMOCLASS_H
