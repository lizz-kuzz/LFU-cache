#include <iostream> 
#include <assert.h>
#include "cache_function.hpp" 
 
int main() { 
 
    int lfu_hits = 0;
    int lfu_len_elem;
    size_t lfu_cache_size_;

    std::cin >> lfu_cache_size_ >> lfu_len_elem;
    assert(std::cin.good());
    
    lfu_cache_t<int> lfu_cache{lfu_cache_size_};

    for (int i = 0; i < lfu_len_elem; ++i) {
        int key_elem;
        std::cin >> key_elem;
        assert(std::cin.good());

        if (lfu_cache.lookup_update(key_elem))
            lfu_hits += 1;
        /* 

        std::cout << "iteration and hit:" << i << " " << lfu_hits << "\n";
        lfu_cache.print_hmap_cache();
        std::cout << "\n";
        */

    }

    std::cout << lfu_hits << std::endl;

    // --------------------------------------

    int ideal_hits = 0;
    size_t ideal_len_elem;
    size_t ideal_cache_size_;

    std::cin >> ideal_cache_size_ >> ideal_len_elem;
    assert(std::cin.good());
    
    ideal_cache_t<int> ideal_cache{ideal_cache_size_, ideal_len_elem};

    int arr_elem[ideal_len_elem] = {0};
    for (int i = 0; i < ideal_len_elem; ++i) {
        std::cin >> arr_elem[i];
        assert(std::cin.good());
    }

    for (int i = 0; i < ideal_len_elem; ++i) {
        if (ideal_cache.lookup_update(arr_elem[i], i, &arr_elem[i], &arr_elem[ideal_len_elem - 1]))
            ideal_hits += 1;
        /*

        std::cout << "iteration and hit:" << i << " " << ideal_hits << "\n";
        ideal_cache.print_hmap_cache();
        std::cout << "\n";
        */   
    }
    std::cout << ideal_hits << std::endl;

    return 0;
}