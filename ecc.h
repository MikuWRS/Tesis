#ifndef _MICRO_ECC_H_
#define _MICRO_ECC_H_

#include <stdint.h>

/* Habilita las funciones para su uso en el modulo: 1 to Enable, 0 to Disable*/
#ifndef ECC_ENABLE_FUNCTION
    #define ECC_ENABLE_FUNCTION 1
#endif

/* Define as 1 to enable ECDSA functions, 0 to disable.
 */
#define ECC_ECDSA 1

/* Optimization settings. Define as 1 to enable an optimization, 0 to disable it.
ECC_SQUARE_FUNC - If enabled, this will cause a specific function to be used for (scalar) squaring instead of the generic
                  multiplication function. Improves speed by about 8% .
*/
#define ECC_SQUARE_FUNC 1

/* Inline assembly options.
Currently we do not provide any inline assembly options. In the future we plan to offer
inline assembly for AVR and 8051.

Note: You must choose the appropriate option for your target architecture, or compilation will fail
with strange assembler messages.
*/
#define ecc_asm_none   0
#ifndef ECC_ASM
    #define ECC_ASM ecc_asm_none
#endif

/* Curve selection options. */
#define secp128r1 16
#define secp192r1 24
#define secp256r1 32
#define secp384r1 48
#ifndef ECC_CURVE
    #define ECC_CURVE secp256r1
#endif

#if (ECC_CURVE != secp128r1 && ECC_CURVE != secp192r1 && ECC_CURVE != secp256r1 && ECC_CURVE != secp384r1)
    #error "Must define ECC_CURVE to one of the available curves"
#endif

#define NUM_ECC_DIGITS ECC_CURVE

typedef struct EccPoint
{
    uint8_t x[NUM_ECC_DIGITS];
    uint8_t y[NUM_ECC_DIGITS];
} EccPoint;

typedef struct DatoNodo
{
    uint8_t dir_nodo[2];
    uint8_t id_nodo[NUM_ECC_DIGITS];
    uint8_t rssi[1];
    uint8_t rssi_p[1];
    uint8_t cPriv[NUM_ECC_DIGITS];
    uint8_t numAlea[NUM_ECC_DIGITS];
    uint8_t Publicx[NUM_ECC_DIGITS];
    uint8_t Publicy[NUM_ECC_DIGITS];
    uint8_t C1x[NUM_ECC_DIGITS];
    uint8_t C1y[NUM_ECC_DIGITS];
    uint8_t MenC2[NUM_ECC_DIGITS];
} DatoNodo;

/* ecc_make_key() function.
Create a public/private key pair.

You must use a new nonpredictable random number to generate each new key pair.

Outputs:
    p_publicKey  - Will be filled in with the point representing the public key.
    p_privateKey - Will be filled in with the private key.

Inputs:
    p_random - The random number to use to generate the key pair.

Returns 1 if the key pair was generated successfully, 0 if an error occurred. If 0 is returned,
try again with a different random number.
*/
int ecc_make_key(EccPoint *p_publicKey, uint8_t p_privateKey[NUM_ECC_DIGITS], uint8_t p_random[NUM_ECC_DIGITS]);

/* ecc_valid_public_key() function.
Determine whether or not a given point is on the chosen elliptic curve (ie, is a valid public key).

Inputs:
    p_publicKey - The point to check.

Returns 1 if the given point is valid, 0 if it is invalid.
*/
int ecc_valid_public_key(EccPoint *p_publicKey);

/* ecdh_shared_secret() function.
Compute a shared secret given your secret key and someone else's public key.

Optionally, you can provide a random multiplier for resistance to DPA attacks. The random multiplier
should probably be different for each invocation of ecdh_shared_secret().

Outputs:
    p_secret - Will be filled in with the shared secret value.
    
Inputs:
    p_publicKey  - The public key of the remote party.
    p_privateKey - Your private key.
    p_random     - An optional random number to resist DPA attacks. Pass in NULL if DPA attacks are not a concern.

Returns 1 if the shared secret was computed successfully, 0 otherwise.

Note: It is recommended that you hash the result of ecdh_shared_secret before using it for symmetric encryption or HMAC.
If you do not hash the shared secret, you must call ecc_valid_public_key() to verify that the remote side's public key is valid.
If this is not done, an attacker could create a public key that would cause your use of the shared secret to leak information
about your private key. */
int ecdh_shared_secret(uint8_t p_secret[NUM_ECC_DIGITS], EccPoint *p_publicKey, uint8_t p_privateKey[NUM_ECC_DIGITS], uint8_t p_random[NUM_ECC_DIGITS]);

#if ECC_ECDSA
/* ecdsa_sign() function.
Generate an ECDSA signature for a given hash value.

Usage: Compute a hash of the data you wish to sign (SHA-2 is recommended) and pass it in to
this function along with your private key and a random number.
You must use a new nonpredictable random number to generate each new signature.

Outputs:
    r, s - Will be filled in with the signature values.

Inputs:
    p_privateKey - Your private key.
    p_random     - The random number to use to generate the signature.
    p_hash       - The message hash to sign.

Returns 1 if the signature generated successfully, 0 if an error occurred. If 0 is returned,
try again with a different random number.
*/
int ecdsa_sign(uint8_t r[NUM_ECC_DIGITS], uint8_t s[NUM_ECC_DIGITS], uint8_t p_privateKey[NUM_ECC_DIGITS],
    uint8_t p_random[NUM_ECC_DIGITS], uint8_t p_hash[NUM_ECC_DIGITS]);

/* ecdsa_verify() function.
Verify an ECDSA signature.

Usage: Compute the hash of the signed data using the same hash as the signer and
pass it to this function along with the signer's public key and the signature values (r and s).

Inputs:
    p_publicKey - The signer's public key
    p_hash      - The hash of the signed data.
    r, s        - The signature values.

Returns 1 if the signature is valid, 0 if it is invalid.
*/
int ecdsa_verify(EccPoint *p_publicKey, uint8_t p_hash[NUM_ECC_DIGITS], uint8_t r[NUM_ECC_DIGITS], uint8_t s[NUM_ECC_DIGITS]);

#endif /* ECC_ECDSA */

/* ecc_bytes2native() function.
Convert an integer in standard octet representation to the native format.

Outputs:
    p_native - Will be filled in with the native integer value.

Inputs:
    p_bytes - The standard octet representation of the integer to convert.
*/
void ecc_bytes2native(uint8_t p_native[NUM_ECC_DIGITS], uint8_t p_bytes[NUM_ECC_DIGITS*4]);

/* ecc_native2bytes() function.
Convert an integer in native format to the standard octet representation.

Outputs:
    p_bytes - Will be filled in with the standard octet representation of the integer.

Inputs:
    p_native - The native integer value to convert.
*/
void ecc_native2bytes(uint8_t p_bytes[NUM_ECC_DIGITS*4], uint8_t p_native[NUM_ECC_DIGITS]);


#if ECC_ENABLE_FUNCTION



typedef unsigned int uint;

uint8_t * get_curve_p();
uint8_t * get_curve_b();
uint8_t * get_curve_n();
EccPoint get_curve_g();
//uint8_t * get_curve_gx()
//uint8_t * get_curve_gy();



void vli_clear(uint8_t *p_vli);

/* Returns 1 if p_vli == 0, 0 otherwise. */
int vli_isZero(uint8_t *p_vli);

/* Returns nonzero if bit p_bit of p_vli is set. */
uint8_t vli_testBit(uint8_t *p_vli, uint p_bit);

/* Counts the number of 8-bit "digits" in p_vli. */
uint vli_numDigits(uint8_t *p_vli);

/* Counts the number of bits required for p_vli. */
uint vli_numBits(uint8_t *p_vli);

/* Sets p_dest = p_src. */
void vli_set(uint8_t *p_dest, uint8_t *p_src);

/* Returns sign of p_left - p_right. */
int vli_cmp(uint8_t *p_left, uint8_t *p_right);

/* Computes p_result = p_in << c, returning carry. Can modify in place (if p_result == p_in). 0 < p_shift < 8. */
uint8_t vli_lshift(uint8_t *p_result, uint8_t *p_in, uint p_shift);

/* Computes p_vli = p_vli >> 1. */
void vli_rshift1(uint8_t *p_vli);

/* Computes p_result = p_left + p_right, returning carry. Can modify in place. */
uint8_t vli_add(uint8_t *p_result, uint8_t *p_left, uint8_t *p_right);

/* Computes p_result = p_left - p_right, returning borrow. Can modify in place. */
uint8_t vli_sub(uint8_t *p_result, uint8_t *p_left, uint8_t *p_right);

/* Computes p_result = p_left * p_right. */
void vli_mult(uint8_t *p_result, uint8_t *p_left, uint8_t *p_right);

/* Computes p_result = (p_left + p_right) % p_mod.
Assumes that p_left < p_mod and p_right < p_mod, p_result != p_mod. */
void vli_modAdd(uint8_t *p_result, uint8_t *p_left, uint8_t *p_right, uint8_t *p_mod);

/* Computes p_result = (p_left - p_right) % p_mod.
Assumes that p_left < p_mod and p_right < p_mod, p_result != p_mod. */
void vli_modSub(uint8_t *p_result, uint8_t *p_left, uint8_t *p_right, uint8_t *p_mod);

#if ECC_CURVE == secp128r1

/* Computes p_result = p_product % curve_p.
See algorithm 5 and 6 from http://www.isys.uni-klu.ac.at/PDF/2001-0126-MT.pdf */
void vli_mmod_fast(uint8_t *p_result, uint8_t *p_product);

#elif ECC_CURVE == secp192r1

/* Computes p_result = p_product % curve_p.
See algorithm 5 and 6 from http://www.isys.uni-klu.ac.at/PDF/2001-0126-MT.pdf */
void vli_mmod_fast(uint8_t *p_result, uint8_t *p_product);

#elif ECC_CURVE == secp256r1

/* Computes p_result = p_product % curve_p
from http://www.nsa.gov/ia/_files/nist-routines.pdf */
void vli_mmod_fast(uint8_t *p_result, uint8_t *p_product);

#elif ECC_CURVE == secp384r1

void omega_mult(uint8_t *p_result, uint8_t *p_right);

/* Computes p_result = p_product % curve_p
see PDF "Comparing Elliptic Curve Cryptography and RSA on 8-bit CPUs"
section "Curve-Specific Optimizations" */
void vli_mmod_fast(uint8_t *p_result, uint8_t *p_product);

#endif

/* Computes p_result = (p_left * p_right) % curve_p. */
void vli_modMult_fast(uint8_t *p_result, uint8_t *p_left, uint8_t *p_right);

#if ECC_SQUARE_FUNC

/* Computes p_result = p_left^2. */
void vli_square(uint8_t *p_result, uint8_t *p_left);

/* Computes p_result = p_left^2 % curve_p. */
void vli_modSquare_fast(uint8_t *p_result, uint8_t *p_left);

#else /* ECC_SQUARE_FUNC */

// #define vli_square(result, left, size) vli_mult((result), (left), (left), (size))
// #define vli_modSquare_fast(result, left) vli_modMult_fast((result), (left), (left))

#endif /* ECC_SQUARE_FUNC */

#define EVEN(vli) (!(vli[0] & 1))
/* Computes p_result = (1 / p_input) % p_mod. All VLIs are the same size.
See "From Euclid's GCD to Montgomery Multiplication to the Great Divide"
https://labs.oracle.com/techrep/2001/smli_tr-2001-95.pdf */
void vli_modInv(uint8_t *p_result, uint8_t *p_input, uint8_t *p_mod);

/* ------ Point operations ------ */

/* Returns 1 if p_point is the point at infinity, 0 otherwise. */
int EccPoint_isZero(EccPoint *p_point);

/* Point multiplication algorithm using Montgomery's ladder with co-Z coordinates.
From http://eprint.iacr.org/2011/338.pdf
*/

/* Double in place */
void EccPoint_double_jacobian(uint8_t *X1, uint8_t *Y1, uint8_t *Z1);

/* Modify (x1, y1) => (x1 * z^2, y1 * z^3) */
void apply_z(uint8_t *X1, uint8_t *Y1, uint8_t *Z);

/* P = (x1, y1) => 2P, (x2, y2) => P' */
void XYcZ_initial_double(uint8_t *X1, uint8_t *Y1, uint8_t *X2, uint8_t *Y2, uint8_t *p_initialZ);

/* Input P = (x1, y1, Z), Q = (x2, y2, Z)
Output P' = (x1', y1', Z3), P + Q = (x3, y3, Z3)
or P => P', Q => P + Q
*/
void XYcZ_add(uint8_t *X1, uint8_t *Y1, uint8_t *X2, uint8_t *Y2);

/* Input P = (x1, y1, Z), Q = (x2, y2, Z)
Output P + Q = (x3, y3, Z3), P - Q = (x3', y3', Z3)
or P => P - Q, Q => P + Q
*/
void XYcZ_addC(uint8_t *X1, uint8_t *Y1, uint8_t *X2, uint8_t *Y2);

void EccPoint_mult(EccPoint *p_result, EccPoint *p_point, uint8_t *p_scalar, uint8_t *p_initialZ);

int ecc_make_key(EccPoint *p_publicKey, uint8_t p_privateKey[NUM_ECC_DIGITS], uint8_t p_random[NUM_ECC_DIGITS]);

int ecc_valid_public_key(EccPoint *p_publicKey);

int ecdh_shared_secret(uint8_t p_secret[NUM_ECC_DIGITS], EccPoint *p_publicKey, uint8_t p_privateKey[NUM_ECC_DIGITS], uint8_t p_random[NUM_ECC_DIGITS]);

#if ECC_ECDSA

/* -------- ECDSA code -------- */

/* Computes p_result = (p_left * p_right) % p_mod. */
void vli_modMult(uint8_t *p_result, uint8_t *p_left, uint8_t *p_right, uint8_t *p_mod);

//static uint max(uint a, uint b);
int ecdsa_sign(uint8_t r[NUM_ECC_DIGITS], uint8_t s[NUM_ECC_DIGITS], uint8_t p_privateKey[NUM_ECC_DIGITS], uint8_t p_random[NUM_ECC_DIGITS], uint8_t p_hash[NUM_ECC_DIGITS]);
int ecdsa_verify(EccPoint *p_publicKey, uint8_t p_hash[NUM_ECC_DIGITS], uint8_t r[NUM_ECC_DIGITS], uint8_t s[NUM_ECC_DIGITS]);
#endif /* ECC_ECDSA */


#endif /* ECC_ENABLE_FUNCTION */

#endif /* _MICRO_ECC_H_ */
