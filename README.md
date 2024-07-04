## Package organization
Take top for example, the final package directory contains:
bash bin/ lib/ data/

All Elf binary is in bin directory, all library the Elf depends on in in lib directory, all extra data including config files is in data directory.

You can run the binary from the top most bash binary from any position, no changing to directory needed.

## Environment Variable
All binary packed by this tool will contain three environment variable:
- ROOT_PATH: Contain the binary install root
- PATH: add the ROOT_PATH/bin to the first search path
- LD_LIBRARY_PATH: add the ROOT_PATH/lib to the first search path

For example, self contained deb package is installed to /opt/name. Then the ROOT_PATH=/opt/name, PATH=/opt/name/bin:$PATH, LD_LIBRARY_PATH=/opt/name/lib:$LD_LIBRARY_PATH.

So, in your code, you can use ROOT_PATH to get the installed root path, and access data file using $ROOT_PATH/data/. You alse can directly call command use std::system("binaryName") to run command, the system function will automatically search binary in $PATH, where it will find your binary and run. A data file access can be done like below:
```
char* env_rootpath = getenv("ROOT_PATH");
fs::path rootpath;
if(env_rootpath){
  rootpath /=env_rootpath;
}
fs::path datapath = rootpath/"data/myfile";
```
When run the packed binary, the ROOT_PATH environment will exist, the datapath is the abosolute path. When in development state, the datapath is relative path: data/myfile, so you can put data file in the same binary/data directory.
