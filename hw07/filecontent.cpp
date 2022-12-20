#include "filecontent.h"

// TODO constructors


FileContent::FileContent(const std::string& content):ptr{std::make_shared<const std::string> (content)}{}

FileContent::FileContent(const char* content):FileContent(std::string(content)){}

FileContent::FileContent(std::string&& content):ptr{std::make_shared<const std::string> (std::move(content))}{}

// FileContent::FileContent(FileContent && content):FileContent{std::string(*content.get())}{

//     content.ptr = nullptr;

// }

// TODO member functions


size_t FileContent::get_size() const{

    return (*ptr).size();
}


std::shared_ptr<const std::string> FileContent::get() const{

    return ptr;
}

