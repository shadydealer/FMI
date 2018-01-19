#include <stdio.h>
#include <crypto++/sha.h>
#include <cryptopp/hex.h>

int main(int argc, char *argv[])
{
    CryptoPP::SHA1 sha1;
    std::string source = "1";
    std::string hash = "";
    CryptoPP::StringSource(source, true, new CryptoPP::HashFilter(sha1, new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash))));
    puts(hash.c_str());
}