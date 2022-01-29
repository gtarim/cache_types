#ifndef CACHE_LRU_H
#define CACHE_LRU_H

#include <unordered_map>
#include <list>
#include <thread>
#include <mutex>
#include <memory>


template <typename Key, typename Data,
                        typename DataPtr = std::shared_ptr<Data> >
class cache_lru
{
    using Guard = std::lock_guard<std::mutex>;
    using DataList = std::list<std::pair<Key,DataPtr>>;
    using DataListIterator  = typename DataList::iterator;

    DataList dataList;
    std::unordered_map<Key, DataListIterator> keyDataMap;
    
    int capacity;
    std::mutex mutex;
public:
    explicit cache_lru( int capacity ) : capacity{ capacity } { }
    cache_lru( const cache_lru& ) = delete;
    cache_lru& operator=( const cache_lru& ) = delete;
    
    DataPtr get( Key key ) 
    {
        Guard guard( mutex );
        auto iter = keyDataMap.find(key);
        if( iter == keyDataMap.end() )
            return DataPtr{};
        return (iter->second)->second;
    }

    void add( Key key, Data data )
    {
        Guard guard( mutex );
        auto iter = keyDataMap.find( key );
        if( iter == keyDataMap.end() ) // not exist
        {
            if( full() )
            {
                auto pair = dataList.back();
                dataList.pop_back();
                keyDataMap.erase( pair.first );
            }
        }
        else // exist
        {
            dataList.erase(iter->second);
            keyDataMap.erase( iter );
        }
        
        dataList.push_front( std::make_pair( key, std::make_shared<Data>( data ) ) );
        keyDataMap.insert( std::make_pair( key, dataList.begin() ) );
    }

    void print()
    {
        Guard guard( mutex );
        for( const auto& item : keyDataMap)
        {
            std::cout << item.first << "=" << *((item.second)->second) << " ";
        }
        std::cout << "\n";
    }
    bool empty() { Guard guard( mutex ); return keyDataMap.empty(); }
private:
    bool full() const noexcept { return keyDataMap.size() == capacity; }
};

#endif // CACHE_LRU_H