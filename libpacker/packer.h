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
    void doPack();
    bool setBin(fs::path srcBin);
    fs::path getBin(){return srcBin_;}
    bool setDstPath(fs::path outputPath);
    fs::path getDstPath(){return outputPath_;}
    std::vector<LddTreeNode> get_lddNodes(){return lddNodes_;};
    std::set<fs::path> get_lddPaths(){return lddPaths_;};

    bool out_deb = false;
    bool out_rpm = false;
    bool out_appimg = false;
    bool out_zip = false;

    bool out_mac_app = false;
    bool out_mac_dmg = false;
    bool out_win_installer = false;
    bool out_image = false;
    bool out_iso = false;

    std::string summary;
    std::string desc;
    std::string packageName;
    std::string version = "1.0.0";
    std::string license = "Binary";
    std::string url = "http://www.linuxer.fyi";
    std::string contact = "brolerliew@gmail.com";
    fs::path icon;
private:
    void doPackAppimg();
    void doPackDeb();
    void doPackZip();
    void doPackRpm();
    bool prepareBuildDir(fs::path prefix = fs::path(), std::set<fs::path> paths = std::set<fs::path>());

    fs::path srcBin_;
    fs::path outputPath_;

    std::vector<LddTreeNode> lddNodes_;
    std::set<std::filesystem::path> lddPaths_;
};

#endif // PACKER_H
