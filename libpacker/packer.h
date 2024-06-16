#ifndef PACKER_H
#define PACKER_H

#include "packer_global.h"
#include <vector>
#include <filesystem>
#include <set>
namespace fs = std::filesystem;
struct LddTreeNode{
    fs::path path;
    std::vector<LddTreeNode> nodes;
};
class IElfFile;
class PACKER_EXPORT Packer
{
public:
    Packer();
    void doPack();
    bool setBin(std::filesystem::path srcBin);
    fs::path getBin(){return srcBin_;}
    void setDstPath(std::filesystem::path outputPath){outputPath_ = outputPath;}
    fs::path getDstPath(){return outputPath_;}
    std::vector<LddTreeNode> get_lddNodes(){return lddNodes_;};
    std::set<std::filesystem::path> get_lddPaths(){return lddPaths_;};

    bool out_deb = false;
    bool out_rpm = false;
    bool out_appimg = false;
    bool out_bin = false;
    bool out_mac_app = false;
    bool out_mac_dmg = false;
    bool out_win_installer = false;
    bool out_image = false;
    bool out_iso = false;
private:
    void doPackAppimg();
    fs::path srcBin_;
    fs::path outputPath_;

    IElfFile* elfFile_ = nullptr;
    std::vector<LddTreeNode> lddNodes_;
    std::set<std::filesystem::path> lddPaths_;
};

#endif // PACKER_H
