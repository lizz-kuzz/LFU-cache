#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm> 
#include <vector>


template <typename T, typename KeyT = int> class lfu_cache_t {
    private:
        size_t size_;
        size_t current_size = 0;
        // std::list<T> list_cache_;
        std::unordered_map<T, KeyT> hmap_cache_;
        std::unordered_map<T, KeyT> hmap_cache_freq_;

        bool full() const {
            // return (list_cache_.size() == size_);
            return (current_size == size_);
        };

    public:
        lfu_cache_t(size_t size) : size_(size), 
                                   hmap_cache_(size), 
                                   hmap_cache_freq_(size) {};
        ~lfu_cache_t() = default;

        void update_freq(KeyT key) {
            hmap_cache_freq_[key]++;
        }

        bool lookup_update(KeyT key) {
            auto elem = hmap_cache_.find(key);
            auto elem_end = hmap_cache_.end(); 
            if (elem == elem_end) { //if we dont find elem
                // std::cout << current_size << " " << size_ << "\n" ;
                
                if (full()) { 
                    // std::cout << "im full and i dont find elem\n";
                    auto elem_min_freq = std::min_element(hmap_cache_freq_.begin(), hmap_cache_freq_.end(),
                                         [](const auto &lhs, const auto &rhs) {
                                         return lhs.second < rhs.second;
                                         });
                    // find elem with min freq and delete it
                    hmap_cache_.erase(elem_min_freq->first);
                    hmap_cache_freq_.erase(elem_min_freq->first);
                    hmap_cache_.insert({key, 0});
                    hmap_cache_freq_.insert({key, 1});
                    // add new elem with key
                    return false;
                } else {
                    // std::cout << "im NOT full and i dont find elem\n";
                    hmap_cache_.insert({key, 0});
                    hmap_cache_freq_.insert({key, 1});
                    current_size++;
                    return true;
                }
            } else {
                // std::cout << "i find elem\n";
                update_freq(key);
                return true;
            }
            
        }

        void print_hmap_cache() {
            std::cout << "cache:\n";

            for (auto it = hmap_cache_.cbegin(); it != hmap_cache_.cend(); ++it) {
                std::cout << "{" << (*it).first << ":(no matter)" << (*it).second << "}\n";
            }
            std::cout << "freq:\n";

            for (auto it = hmap_cache_freq_.cbegin(); it != hmap_cache_freq_.cend(); ++it) {
                std::cout << "{" << (*it).first << ":(freq) " << (*it).second << "}\n";
            }
        }

};
