//  Author: mrsheldie@mail.ru (Ivchenko Nikolay)

#ifndef BeerDB_BUFFER_MANAGER_H_
#define BeerDB_BUFFER_MANAGER_H_

#include <string>

#include "block_handle.h"
#include "file_handle.h"

class BufferManager {
 private:
  BlockHandle *bhandle_;
  FileHandle *fhandle_;
  std::string path_;

  BlockInfo *GetUsableBlock();

 public:
  BufferManager(std::string p)
      : bhandle_(new BlockHandle(p)), fhandle_(new FileHandle(p)), path_(p) {}
  ~BufferManager() {
    delete bhandle_;
    delete fhandle_;
  }

  BlockInfo *GetFileBlock(std::string db_name, std::string tb_name,
                          int file_type, int block_num);
  void WriteBlock(BlockInfo *block);
  void WriteToDisk();
};

#endif /* defined(BeerDB_HANDLE_H_) */
