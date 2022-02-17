#include<cryptlib.h>
#include<osrng.h>
#include<iostream>
#include<rsa.h>

#define KEY_SIZE 4096

using namespace std;
using namespace CryptoPP;

int main(int argc, char* argv[])
{
	///////////////////////////////////////
	// Pseudo Random Number Generator
	AutoSeededRandomPool prng;

	///////////////////////////////////////
	// Generate Parameters
	InvertibleRSAFunction params;
	params.GenerateRandomWithKeySize(prng, KEY_SIZE);

	///////////////////////////////////////
	// Create Keys
	RSA::PrivateKey privateKey(params);
	RSA::PublicKey publicKey(params);

	string plaintext = "AES is based on a design principle known as a substitution¡Vpermutation network, and is efficient in both software and hardware. Unlike its predecessor DES, AES does not use a Feistel network. AES is a variant of Rijndael, with a fixed block size of 128 bits, and a key size of 128, 192, or 256 bits. By contrast, Rijndael per se is specified with block and key sizes that may be any multiple of 32 bits, with a minimum of 128 and a maximum of 256 bits.";
	string ciphertext, decryptedtext;

	// Encryption
	RSAES_OAEP_SHA_Encryptor encrypt(publicKey);
	// Pipelining https://www.cryptopp.com/wiki/Pipelining
	// Pipelining is a paradigm used by Crypto++ which allows data to flow from a source to a sink
	StringSource s(plaintext, true,
		new PK_EncryptorFilter(prng, encrypt,
			new StringSink(ciphertext)
		) // PK_EncryptorFilter      
	); // StringSource


	// Decryption
	RSAES_OAEP_SHA_Decryptor decrypt(privateKey);
	StringSource ss(ciphertext, true,
		new PK_DecryptorFilter(prng, decrypt,
			new StringSink(decryptedtext)
		) // PK_DecryptorFilter      
	); // StringSource

	cout << decryptedtext;
	return 0;
}