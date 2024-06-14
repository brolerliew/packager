#ifndef PACKER_H
#define PACKER_H

#include "packer_global.h"

#include <filesystem>
namespace fs = std::filesystem;

class PACKER_EXPORT Packer
{
public:
    Packer();
    void doPack();
    bool setBin(std::filesystem::path srcBin);
    fs::path getBin(){return srcBin_;}
    void setDstPath(std::filesystem::path outputPath){outputPath_ = outputPath;}
    fs::path getDstPath(){return outputPath_;}

private:
    fs::path srcBin_;
    fs::path outputPath_;
};

#endif // PACKER_H
