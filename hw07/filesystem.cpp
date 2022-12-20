#include "filesystem.h"

#include <algorithm>
#include <iomanip>
#include <numeric>
#include <sstream>

Filesystem::Filesystem() {}

bool Filesystem::register_file(const std::string &name,
                               const std::shared_ptr<File> &file) {
  // TODO: Something needs to be done here

  


  if(!this->is_exists(name)&&name.length()&&file&&(file->get_name().length()==0)){
    auto thisptr = this->shared_from_this();
    this->mapper.emplace(name,file);
    file->name = name;
    file->filesystem = std::move(thisptr);
    
    return true;
  }

  

  // TODO: You need some checks here

    

  // TODO: More updates you need to do!

  // TODO register a new file here
  return false;
}

bool Filesystem::remove_file(std::string_view name) {
  // TODO file removal

  bool result = this->mapper.erase(static_cast<const std::string>(name));

  return result;
}

bool Filesystem::rename_file(std::string_view source, std::string_view dest) {
  // TODO file renaming

  auto file = get_file(source);
  auto is_there = get_file(dest);

  if(file&&!is_there){

    this->remove_file(file->get_name());
    file->name = dest;
    this->mapper.emplace(dest,file);

    return true;
  }


  return false;
}

std::shared_ptr<File> Filesystem::get_file(std::string_view name) const {
  // TODO

  if(this->is_exists(std::string(name))){


    return this->mapper.at(static_cast<const std::string>(name));

  }

  return nullptr;
}

size_t Filesystem::get_file_count() const {
  // TODO
  return this->mapper.size();
}

size_t Filesystem::in_use() const {
  // TODO sum up all real file sizes


  std::vector<size_t> v(this->mapper.size());


  size_t size = 0;

  for (auto &it: this->mapper){

    auto result = it.second.get()->get_size();

    size+=result;
  }

  return size;
}



// convenience function so you can see what files are stored
std::string Filesystem::file_overview(bool sort_by_size) {
  std::ostringstream output;
  // this function is not tested, but it may help you when debugging.

  output << "files in filesystem: " << std::endl;

  // for (auto&& entry : this->files) {
  //     // TODO: fix printing name, type and size
  //     output << entry.get_name << std::endl;
  // }
  return std::move(output).str();
}

std::vector<std::shared_ptr<File>>
Filesystem::files_in_size_range(size_t max, size_t min) const {
  // TODO: find the matching files and return them

  std::vector<std::shared_ptr<File>> result; 

  for(auto &it: this->mapper){

    auto pointer = it.second;
    auto size = pointer->get_size();



    if(size<=max && size>=min){
      result.push_back(pointer);
    }
  }
  return result;
}

bool Filesystem::is_exists(std::string p) const {


  auto result = this->mapper.find(p);

  if(result==this->mapper.end()){
    return false;
  }
  return true;
}
