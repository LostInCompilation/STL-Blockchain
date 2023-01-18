/*
 
 Blockchain STL-like container
 
 ***********************************************************************************
 The zlib License

 Copyright ©2023 Marc Schöndorf

 This software is provided 'as-is', without any express or implied warranty. In
 no event will the authors be held liable for any damages arising from the use of
 this software.

 Permission is granted to anyone to use this software for any purpose, including
 commercial applications, and to alter it and redistribute it freely, subject to
 the following restrictions:

 1.  The origin of this software must not be misrepresented; you must not claim
     that you wrote the original software. If you use this software in a product,
     an acknowledgment in the product documentation would be appreciated but is
     not required.

 2.  Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.

 3.  This notice may not be removed or altered from any source distribution.
 ***********************************************************************************
 
*/

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include <functional>

// Block data type
template <typename T, typename Hasher = std::hash<T>, typename Allocator = std::allocator<T>>
class Block
{
private:
    typedef typename decltype(std::function{Hasher()})::result_type HasherResultType;
    
    const T transaction;
    const uint64_t prevHash;
    const uint64_t hash;
    
    template <typename H1, typename H2>
    uint64_t PairHash(const std::pair<H1, H2>& hashPair)
    {
        return std::hash<H1>()(hashPair.first) ^ std::hash<H2>()(hashPair.second);
    }
    
public:
    Block() = delete;
    Block(T transaction, const uint64_t& prevHash)
        : transaction(transaction)
        , prevHash(prevHash)
        , hash(CalculateHash())
    {}
    
    uint64_t CalculateHash()
    {
        const std::pair<HasherResultType, uint64_t> pair(Hasher{}(transaction), prevHash);
        return PairHash(pair);
    }
    
    const T& GetTransaction() const { return transaction; }
    uint64_t GetHash() const { return hash; }
    uint64_t GetPreviousHash() const { return prevHash; }
};

// Blockchain container
template <typename T, typename Hasher = std::hash<T>, typename Allocator = std::allocator<T>>
requires std::is_same_v<T, typename Allocator::value_type>
class Blockchain : public std::vector<Block<T, Hasher, Allocator>>
{
private:
    typedef typename std::vector<Block<T, Hasher, Allocator>>::iterator         iterator;
    typedef typename std::vector<Block<T, Hasher, Allocator>>::const_iterator   const_iterator;
    
    typedef Block<T, Hasher, Allocator> BlockType;
    
public:
    Blockchain() { this->emplace_back(BlockType(static_cast<T>(Allocator()), 0)); }
    Blockchain(T genesisTransaction) { this->emplace_back(BlockType(genesisTransaction, 0)); }
    
    void push_back(const T& transaction)
    {
        this->emplace_back(BlockType(this->back().GetHash(), transaction));
    }
    
    void push_back(T&& transaction)
    {
        this->emplace_back(BlockType(this->back().GetHash(), transaction));
    }
    
};

#endif //BLOCKCHAIN_BLOCKCHAIN_H
