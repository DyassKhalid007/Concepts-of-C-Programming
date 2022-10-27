#include "combinatorics.h"


uint64_t factorial(uint64_t val) {
    // TODO

    if(val==0||val==1){
        return 1;
    }else{
        return val*factorial(val-1);
    }
    

    
}


uint64_t permutation(uint64_t val, uint64_t val2) {
    // TODO

    if(val2>val){
        return 0;
    }else{
 
        auto upper{factorial(val)};
        auto lower{factorial(val-val2)};
        return (upper/lower);
    }
}


uint64_t combination(uint64_t val, uint64_t val2) {
    // TODO
    auto perm{permutation(val,val2)};
    auto kfact{factorial(val2)};

    return (perm/kfact);
}
