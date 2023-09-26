#include <iostream> 
#include <assert.h>
#include "cache_function.hpp" 
 
// slow get page imitation 
int main() { 
 
    int hits = 0;
    int len_elem;
    size_t cache_size_;

    std::cin >> cache_size_ >> len_elem;
    assert(std::cin.good());
    
    lfu_cache_t<int> lfu_cache{cache_size_};

    for (int i = 0; i < len_elem; ++i) {
        int key_elem;
        std::cin >> key_elem;
        assert(std::cin.good());

        if (lfu_cache.lookup_update(key_elem))
            hits += 1;
        /*
        std::cout << "iteration:" << i << "\n";
        lfu_cache.print_hmap_cache();
        std::cout << "\n";
        */

    }

    std::cout << hits << std::endl;
    
    return 0;
}