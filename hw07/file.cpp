#include "file.h"

#include "filesystem.h"
#include <iostream>
size_t File::get_size() const { return this->content.get_size(); }

bool File::rename(std::string_view new_name) {
  // TODO: file renaming


  if(this->filesystem.lock()){

    return this->filesystem.lock()->rename_file(this->get_name(),new_name);
  }

  // 
  return false;
}

const std::string &File::get_name() const { return this->name; }

const FileContent &File::get_content() const { return this->content; }

// TODO file constructor



 File::File(FileContent&& content,std::string_view name){

    this->content = std::move(content);
    // this->filesystem = nullptr;
 }

