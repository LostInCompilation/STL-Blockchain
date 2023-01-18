# Blockchain C++ STL-Like Container

## Usage
Include the `Blockchain.h` header. Requires C++20.

```cpp
#include "Blockchain.h"
```

#### Creating a Blockchain

Create a Blockchain with `std::string` Blocks and add the Genesis Block:
```cpp
Blockchain<std::string> blockchain("Genesis");
```

#### Pushing new blocks/transactions
```cpp
blockchain.push_back("Transaction 1");
blockchain.push_back("Transaction 2");
blockchain.push_back("Last transaction");
```

#### Iterating the Blockchain and print the Hash of each Block/Transaction

* Range-Based for loop:
```cpp
for(auto& block : blockchain)
    std::cout << block.GetTransaction() << ":\t" << block.GetHash() << std::endl;
```

* Indexed for loop:
```cpp
for(int i = 0; i < blockchain.size(); I++)
    std::cout << blockchain[i].GetTransaction() << ":\t" << blockchain[i].GetHash() << std::endl;
```

* Iterators:
```cpp
for (Blockchain<std::string>::iterator iter = blockchain.begin(); iter != blockchain.end(); iter++) 
    std::cout << iter->GetTransaction() << ":\t" << iter->GetHash() << std::endl;
```

#### Checking the Blockchain
* `Blockchain<...>::Check()` checks if the hashes are consistent:

```cpp
if(blockchain.Check())
    std::cout << "Blockchain hashes checked. ALL GOOD" << std::endl;
```

* `Blockchain<...>::Revalidate()` checks if the hashes and transactions are consistent:

```cpp
if(blockchain.Revalidate())
    std::cout << "Blockchain hashes and transactions revalidated. ALL GOOD" << std::endl;
```

If a transaction or hash in the chain would be altered, the corresponding check/revalidate function would fail.

## Using a custom Hash-Function

The Blockchain uses std::hash<...> by default. You can use a custom hash function for the chain. Your custom Hasher can return any data type as the hash and must overload the `()` operator:

```cpp
template <typename T>
class MyHashFunction
{
public:
    std::string operator()(T input)
    {
        // Here calculate your hash based on the input
        // and return your calculated hash
        return "MyCalculatedHashFromInput";
    }
};
```

To use the custom Hasher, simply specify it as a template argument when creating the Blockchain:

```cpp
Blockchain<std::string, MyHashFunction<std::string>> customBlockchain("Genesis");
```
