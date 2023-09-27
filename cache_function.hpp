#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm> 
#include <array>
// TODO fix problem with lfu cache  with fifo(нужно удалять самый последний элемент)
template <typename T, typename KeyT = int> class lfu_cache_t {
    private:
        size_t size_;
        size_t current_size = 0;
        std::unordered_map<T, KeyT> hmap_cache_;
        std::unordered_map<T, KeyT> hmap_cache_freq_;

        bool full() const {
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
                    return false;
                }
            } else {
                // std::cout << "i find elem\n";
                update_freq(key);
                return true;
            }
            
        }

        void print_hmap_cache() {
            // std::cout << "cache:\n";

            // for (auto it = hmap_cache_.cbegin(); it != hmap_cache_.cend(); ++it) {
            //     std::cout << "{" << (*it).first << ":(no matter)" << (*it).second << "}\n";
            // }
            std::cout << "freq:\n";

            for (auto it = hmap_cache_freq_.cbegin(); it != hmap_cache_freq_.cend(); ++it) {
                std::cout << "{" << (*it).first << ":(freq) " << (*it).second << "}\n";
            }
        }

};


template <typename T, typename KeyT = int> class ideal_cache_t {
    private: 
        size_t cache_size_;
        size_t arr_size_;
        size_t current_size_ = 0; 
        T* predict_arr; //??
        std::unordered_map<T, KeyT> hmap_cache_; //need for cache
        std::unordered_map<T, KeyT> hmap_predict_cache_; //will know when whis number met, 
        // i will add elem in cache and find next elem in arr, and put there his id, and use func max elem for that

    public:

        bool full() const {
            return (current_size_ == cache_size_); 
        };
        
        // void create_arr() {
        //     predict_arr = (T *) calloc(sizeof(T), arr_size_);
        // };
        // void free_arr() {
        //     free(predict_arr);
        //     predict_arr = nullptr;
        // };

        ideal_cache_t(size_t size, size_t arr_size) : cache_size_(size), 
                                                      arr_size_(arr_size),
                                                      hmap_cache_(size),
                                                      hmap_predict_cache_(size) {
                                                        // create_arr();
                                                      };
        ~ideal_cache_t() = default;
        //  {
            // free_arr();
        // };

       
        bool lookup_update(KeyT key, int current_id, int *begin_arr, int *end_arr) {
            auto elem = hmap_cache_.find(key);
            auto elem_end = hmap_cache_.end(); 
            if (elem == elem_end) { //if we dont find elem
                // std::cout << current_size_ << " " << cache_size_ << "\n" ;
                
                if (full()) { 
                    // std::cout << "im full and i dont find elem\n";
                    auto elem_max_time = std::max_element(hmap_predict_cache_.begin(), hmap_predict_cache_.end(),
                                         [](const auto &lhs, const auto &rhs) {
                                         return lhs.second < rhs.second;
                                         });
                    // find elem with max len from now and delete it
                    hmap_cache_.erase(elem_max_time->first);
                    hmap_predict_cache_.erase(elem_max_time->first);
                    hmap_cache_.insert({key, 0});
                    // надо вставлять с тем индексом с каким он встретиться в массиве дальше 
                    auto ind = std::find(begin_arr + 1, end_arr + 1, key);
                    hmap_predict_cache_.insert({key, ind - begin_arr + current_id});
                    // add new elem with key
                    return false;
                } else {
                    // std::cout << "im NOT full and i dont find elem\n";
                    hmap_cache_.insert({key, 0});
                    auto ind = std::find(begin_arr + 1, end_arr + 1, key);
                    // std::cout << "begin find: " << *begin_arr << std::endl;
                    // std::cout << "end find: " << *end_arr << std::endl;
                    hmap_predict_cache_.insert({key, ind - begin_arr + current_id});
                    current_size_++;
                    return false;
                }
            } else {
                // std::cout << "i find elem\n";
                auto ind = std::find(begin_arr + 1, end_arr + 1, key);        
                hmap_predict_cache_[key] = ind - begin_arr + current_id; 
                return true;
            }
            
        }

        void print_hmap_cache() {
            // std::cout << "cache:\n";

            // for (auto it = hmap_cache_.cbegin(); it != hmap_cache_.cend(); ++it) {
            //     std::cout << "{" << (*it).first << ":(no matter)" << (*it).second << "}\n";
            // }
            std::cout << "predict:\n";

            for (auto it = hmap_predict_cache_.cbegin(); it != hmap_predict_cache_.cend(); ++it) {
                std::cout << "{" << (*it).first << ":(number) " << (*it).second << "}\n";
            }
        }







};