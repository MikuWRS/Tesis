# Tesis
Este repositorio contiene mi trabajo de Tesis "Consumo energético de contramedidas para Side-Channel Attack Pasivo en Curva Elíptica sobre cuerpos primos"
Donde se modificó y utilizó la libreria Nano-Ecc (https://github.com/iSECPartners/nano-ecc). 

Los archivos principales estan encriptados, 
si se desea verlos por favor contactarme y le indicaré el metodo de desencriptación.

Los algoritmos se implementaron en un Arduino UNO

Algoritmos implementados
1 - Left to Right \
2 - Left to Right usando Bloques Atomicos [1] \
3 - Left to Right usando Formula Unificada [2] \
4 - Always Double and Add [3] \
5 - Modified Montgomery Ladder [4] \
6 - Double-Add [5] \
7 - Add-Only [5]
8 - Randomized Montgomery Ladder [6] \
9 - Signed Digit Method: Left to Right [7] \
10 - Clavier-Joye's Countermeasure [8] \
11 - Coron's Second Countermeasure [3] \
12 - Coron's Third Countermeasure [3] \
13 - Ciet-Joye Method 2P* [10] \
14 - Montgomery Powering Ladder method with randomized address [11] \
15 - BRIP Countermeasure [12] \
16 - Kim et al. Countermeasure [13] \


Bibliografia \
1 - Abarzúa, R., & Thériault, N. (2012). Complete Atomic Blocks for Elliptic Curves in Jacobian Coordinates
over Prime Fields. LATINCRYPT 2012 (págs. 37-55). Berlin, Heidelberg: Springer.

2 - Brier, É., & Joye, M. (2002). Weierstraß elliptic curves and side-channel attacks. PKC 2002 (págs.
335-345). Berlin, Heidelberg: Springer.

3 - Coron, J.-S. (1999). Resistance against differential power analysis for elliptic curve cryptosystems.
CHES 1999: Cryptographic Hardware and Embedded Systems (págs. 292-302). Berlin,
Heidelberg: Springer.

4 - Montgomery, P. (1987). Speeding the Pollard and elliptic curve methods of factorization. Mathematics
of Computation 48, 177, 243-264.

5 - Joye, M. (2007). Highly Regular Right-to-Left Algorithms for Scalar Multiplication. CHES 2007 (págs. 135-147). Berlin, Heidelberg: Springer.

6 - Le, D.-P., Tan, C., & Tunstall, M. (2015). Randomizing the Montgomery powering ladder. WISTP
2015 (págs. 169-184). berlin, Heidelberg: Springer.

7 - Goundar, R., Joye, M., Miyaji, A., Rivain, M., & Venelli, A. (2011). Scalar multiplication on Weierstraß
elliptic curves from Co-Z arithmetic. Journal of Cryptographic Engineering (págs. 161-
176). Berlin, Heidelberg: Springer.

8 - Clavier, C., & Joye, M., (2001). Universal Exponentiation Algorithm - A First Step Towards PRovable
SPA-resistance -. CHES 2001, LNCS 2162 (págs 300-308). Springer.

10 - Ciet, M., & Joye, M., (2003). (Virtually) Free randomization techniques for elliptic curve cryptography.
ICICS 2003 (págs. 348-359). Springer-Verlag.

11 - Izumi, M., Ikegami, J., Sakiyama, K., & Ohta, K. (2010). Improved countermeasure against Addressbit
DPA for ECC scalar multiplication. 2010 Design, Automation Test in Europe Conference
Exhibition (DATE 2010). Dresden: IEEE.

12 - Mamiya, H., Miyaji, A., & Morimoto, H. (2004). Efficient Countermeasures against RPA, DPA, and
SPA. CHES 2004 (págs. 343-356). Berlin: Springer.

13 - Kim, C., Ha, J., Moon, S., Yen, S., Lien, W., & Kim, S. (2005). IACR Cryptology ePrint. Obtenido de
An Improved and Efficient Countermeasure: https://eprint.iacr.org/2005/022.pdf
