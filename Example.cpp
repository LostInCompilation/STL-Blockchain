/*
 
 EXAMPLE
 
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

#include <iostream>

// Include the Blockchain container
#include "Blockchain.h"

template <typename T>
class MyHashFunction
{
public:
    std::string operator()(T input)
    {
        return "MyCalculatedHashFromInput";
    }
};

int main()
{
    std::cout << "**********************************************" << std::endl;
    std::cout << "STL-Like Blockchain container - Example" << std::endl << std::endl;
    
    // *************************************************************************
    // Blockchain test
    // Create blockchain
    Blockchain<std::string> blockchain("Genesis");
    blockchain.push_back("Transaction 1");
    blockchain.push_back("Transaction 2");
    blockchain.push_back("Last transaction");
    
    for(auto& i : blockchain)
        std::cout << i.GetTransaction() << ":\t" << i.GetHash() << std::endl;
    
    std::cout << std::endl;
    
    // Check chain
    if(blockchain.Check())
        std::cout << "Blockchain hashes checked. ALL GOOD" << std::endl;
    else
        std::cout << "Blockchain hashes checked. NOT VALID" << std::endl;
    
    // Revalidate chain
    if(blockchain.Revalidate())
        std::cout << "Blockchain hashes and transactions revalidated. ALL GOOD" << std::endl;
    else
        std::cout << "Blockchain hashes and transactions revalidated. NOT VALID" << std::endl;
    
    std::cout << std::endl << std::endl << std::endl;
    
    // *************************************************************************
    // Simulate manipulation
    std::cout << "**********************************************" << std::endl;
    std::cout << "Simulate manipulation" << std::endl << std::endl;
    
    // Manipulate Genesis block
    blockchain[0].transaction = "Manipulated";
    
    // Check chain again (Should still work, no new hashes has been calculated)
    if(blockchain.Check())
        std::cout << "Blockchain checked. ALL GOOD" << std::endl;
    else
        std::cout << "Blockchain checked. NOT VALID" << std::endl;
    
    // Revalidate chain again (should fail now, since Genesis Block is manipulated)
    if(blockchain.Revalidate())
        std::cout << "Blockchain revalidated. ALL GOOD" << std::endl;
    else
        std::cout << "Blockchain revalidated. NOT VALID" << std::endl;
    
    std::cout << std::endl << std::endl << std::endl;
    
    // *************************************************************************
    // Custom hash function example
    std::cout << "**********************************************" << std::endl;
    std::cout << "Custom hash function (always return same hash)" << std::endl << std::endl;
    
    Blockchain<std::string, MyHashFunction<std::string>> customBlockchain("Genesis");
    customBlockchain.push_back("Transaction 1");
    customBlockchain.push_back("Transaction 2");
    customBlockchain.push_back("Last transaction");
    
    for(auto& i : customBlockchain)
        std::cout << i.GetTransaction() << ":\t" << i.GetHash() << std::endl;
    
    // Check chain
    if(customBlockchain.Check())
        std::cout << "CUSTOM Blockchain checked. ALL GOOD" << std::endl;
    else
        std::cout << "CUSTOM Blockchain checked. NOT VALID" << std::endl;
    
    return 0;
}
