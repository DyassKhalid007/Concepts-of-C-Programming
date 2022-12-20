#include "document.h"


Document::Document(FileContent &&content) : File{std::move(content)} {}

// TODO provide file type

std::string_view Document::get_type() const{

  return "DOC";
}


size_t Document::get_raw_size() const {
  // TODO get the document size
  return content.get_size();
}

unsigned Document::get_character_count() const {
  // TODO count non whitespace characters

  auto total = get_raw_size();

  auto data = *(content.get());



  auto count1 = std::count(data.begin(),data.end(),'\n');
  count1+=std::count(data.begin(),data.end(),'\t');
  count1+=std::count(data.begin(),data.end(),' ');


  return total-count1;
  

}

// TODO content update function

void Document::update(FileContent &&new_content){

  content = std::move(new_content);
}
