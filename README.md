# Xeth

Xeth is a free, open-source [Ethereum](http://ethereum.org) GUI wallet. It implements various useful features, like [stealth payments](doc/stealth.md), [bitprofile](http://bitprofile.org) support, secure random key generation, address book support, and much more.


To build from sources use the [installation instructions](doc/build.md)

Already compiled binaries can be found at [http://xeth.org/download.html](http://xeth.org/download.html)

## Features
### Stealth addresses

Invented in 2014 by Peter Todd, stealth addresses allow a user to have one long-term, frequently reused public key (which is helpful if you want to take frequent payments), from which cryptographically unlinkable accounts are derived, with minimal effort on the user's behalf.

The stealth address generated from the published public key is entirely indistinguishable from random to any parties not directly involved in the transaction (ie everyone but the sender and recipient).

#### Dual-key stealth

Dual key allows scanning for payments without exposing the spending private key. In this scheme two keys are used - one for spending and one for scanning. The spending key is decrypted only when spending funds and it requires user interaction. The scan key is not encrypted.

Receiver:

    A = public scan key (EC point, 33 bytes/256 bits, long lasting, generated by recipient)
    a = private scan key (integer, 32 bytes/256 bits, long lasting, generated by recipient)
    B = public 'spend key' (EC point, ephemeral, generated by sender)
    b = private 'spend key' (integer, ephemeral, generated by sender)

    A = aG
    B = bG

    stealth address: <scan=A> <spend=B, ...>

By publishing B, and using a publicly known hash function H, the sender and recipient can construct a shared secret, s:
    s = H(aB) = H(bA) ( = H(abG) = H(baG) )

Sender can calculate the public key corresponding to their new stealth address, and so calculate the address where they will receive their funds:
    K(A') = K(A + sG)
Here, K(x) is the 160 most significant bits of the Keccak-256 hash of x.

The receiver can do the same, as the long term public key A is public knowledge:

    K(A') = K(A + sG) [without decrypting wallet]
    => A' = A + sG
    => a'G = aG + sG   
    => a' = (a + s)G [after decryption of wallet]

It can be proven that only the holder of the original private key, a, can form a' and spend the money held at the new account with address K(A'). An adversary would be required to find the preimage or a hash collision, and break the ECDLP. These are both assumed very, very hard.


### [BitProfile](http://bitprofile.org)
BitProfile is a 'decentralised user namespace system'.
It was created so that a user can share the same profile across multiple DApps, taking advantage of the user's global reputation.
A DApp can use default BitProfile registrar or deploy its own (with its own registration rules), without losing the advantage of the global user reputation.

The profile address can be used to receive direct payments anonymously, using stealth addresses as explained above. 
The wallet also allows a user to link their own stealth addresses, meaning that multiple accounts of theirs can contribute towards this global reputation.

Bitprofile implements multiple levels of profile authentication and access control security policies, allowing use of the same profile across multiple devices (phone, watch, tablet). Having different keys with different privileges enables the profile to remain usable even in the case of a leaked or lost key.
The authentication mechanism is extensible. By default, public key authentication is used, but users can define their own alternative profile authentication rules, facilitating easy migration to post quantum algorithms!
