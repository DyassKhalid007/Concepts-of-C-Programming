#include "contact_list.h"
#include "hw03.h"

#include <iostream>

namespace contact_list {

void test_contact_list() {
    storage abook;
    std::cout<<add(abook, "Best Friend", 421234)<<"\n";
    std::cout<<add(abook, "False Friend", 10032331)<<"\n";
    std::cout<<add(abook, "False Friend", 10032331)<<"\n";
    std::cout<<add(abook, "A", 10032331)<<"\n";
    std::cout<<add(abook, "B", 10032331)<<"\n";
    std::cout<<add(abook, "", 10032331)<<"\n";
    std::cout<<"size:"<<size(abook)<<"\n";
    std::cout << to_string(abook)<<"\n";
    std::cout<<is_exists(abook," ")<<"\n";
    std::cout<<is_exists(abook,"Best Friend")<<"\n";
    std::cout<<get_number_by_name(abook,"Best Friend")<<"\n";
    std::cout<<get_number_by_name(abook,"False Friend")<<"\n";
    std::cout<<get_number_by_name(abook,"Testing no insertion")<<"\n";

    std::cout<<get_name_by_number(abook,0)<<"\n";
    std::cout<<get_name_by_number(abook,421234)<<"\n";
    std::cout<<get_name_by_number(abook,10032331)<<"\n";
    std::cout<<get_name_by_number(abook,11)<<"\n";
    // std::cout<<"Hello\n";

    std::cout<<"------------------Printing-------------\n";

    std::cout << to_string(abook)<<"\n";

    sort(abook);
    std::cout<<"----------Sorting by name--------\n";
    std::cout << to_string(abook)<<"\n";


}

} // namespace contact_list


int main() {
    contact_list::test_contact_list();
    // std::cout<<"Hello\n";

    return 0;
}
