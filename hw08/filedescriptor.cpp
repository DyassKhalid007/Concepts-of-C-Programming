#include "filedescriptor.h"


namespace net{

    FileDescriptor::FileDescriptor(){}

    FileDescriptor::FileDescriptor(int fd){

        fd_ = fd;
    }

    FileDescriptor::FileDescriptor(FileDescriptor && f){

        fd_ = std::move(f.unwrap());
        f.reset();
    }

    FileDescriptor & FileDescriptor:: operator = (const FileDescriptor &&f){

        fd_ = std::move(f.unwrap());

        return *this;
        
    }


    FileDescriptor::~FileDescriptor(){


        if(fd_.has_value()){

             close(fd_.value());
        }
        fd_.reset();
    }
    int FileDescriptor::unwrap() const{

        return fd_.value_or(-1);
    }

    void FileDescriptor::reset() {

        fd_.reset();
    }

    FileDescriptor& FileDescriptor::operator=(int && fd){


        fd_ = std::move(fd);

        return *this;
    }

    FileDescriptor& FileDescriptor::operator=(FileDescriptor && f){

        fd_ = std::move(f.unwrap());
        f.reset();

        return *this;
    }
}
