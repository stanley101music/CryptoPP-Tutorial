#include<cryptlib.h>
#include<osrng.h>
#include<iostream>
#include<blowfish.h>
#include<modes.h>

#define KEY_SIZE Blowfish::DEFAULT_KEYLENGTH
#define BLOCK_SIZE Blowfish::BLOCKSIZE

using namespace std;
using namespace CryptoPP;

int main(int argc, char* argv[])
{
	AutoSeededRandomPool prng;

	SecByteBlock key(KEY_SIZE);
	prng.GenerateBlock(key, key.size());
	SecByteBlock iv(BLOCK_SIZE);
	prng.GenerateBlock(iv, iv.size());

	string plaintext = "AES is based on a design principle known as a substitution¡Vpermutation network, and is efficient in both software and hardware. Unlike its predecessor DES, AES does not use a Feistel network. AES is a variant of Rijndael, with a fixed block size of 128 bits, and a key size of 128, 192, or 256 bits. By contrast, Rijndael per se is specified with block and key sizes that may be any multiple of 32 bits, with a minimum of 128 and a maximum of 256 bits.";
	string ciphertext, decryptedtext;

	// Encryption
	// All possible modes of operation can be found in https://cryptopp.com/wiki/Modes_of_Operation
	// ECB, CBC, OFB, CFB, CBC-CTS, CTR, XTS, CCM, EAX, GCM and OCB
	CBC_Mode<Blowfish>::Encryption encrypt(key, key.size(), iv);
	// Pipelining https://www.cryptopp.com/wiki/Pipelining
	// Pipelining is a paradigm used by Crypto++ which allows data to flow from a source to a sink
	StringSource s(plaintext, true,
		new StreamTransformationFilter(encrypt,
			new StringSink(ciphertext)
		) // StreamTransformationFilter      
	); // StringSource

	// Decryption
	CBC_Mode<Blowfish>::Decryption decrypt(key, key.size(), iv);
	StringSource ss(ciphertext, true,
		new StreamTransformationFilter(decrypt,
			new StringSink(decryptedtext)
		) // StreamTransformationFilter      
	); // StringSource

	cout << decryptedtext;
	return 0;
}