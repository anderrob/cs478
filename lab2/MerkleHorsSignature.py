# A) Implement a Merkle-hash tree:
# 	(i) R ← Form(v1, . . . , vn): Given n leaves, this function creates the root of Merkletree.
# 	(ii) (p1, . . . , plog2(n)) ←Path(v): Given a leaf to be authenticated, this function generates auxiliary values that are needed to authenticate v.
# 	(iii) (0, 1) ←Verify(R, p1, . . . , plog2(n),v) :
# B) Implement HORS signature:
# 	Please see slide 18. If required, the further detail can be found in the following paper:
#	Leonid Reyzi, Natan Reyzin, Better than BiBa: Short One-time Signatures with Fast
# 	Si gning and Verifying.
# C) Implement d-time O(1) key-size HORS/Merkle-tree Signature:
#	(i) (sk, PK) ← P Q.Kg(1κ, d): d is the max number of messages to be signed.
# 		1) Set HORS parameters (κ = 128, k = 32, t = 1024)
# 		2) z ← {0, 1}, st = 1
# 		3) si ← H(z||i), i = 1, . . . , d × t
# 		4) vi ← H(si), i = 1, . . . , d × t
# 		5) R ←Form (v1, . . . , vd×t)
# 		6) sk = (z, st), PK = (R, d)
# 	(ii) σ ← P Q.Sig(m, sk) :
# 		1) If st > d then abort, else continue
# 		2) (h1, . . . , hk) ← H(m) and interpret each (h1, . . . , hk) as log2(t)
# 		3) ij ← (st − 1) × t + hj, j = 1, . . . , k
# 		4) sij ← H(z||ij ), j = 1, . . . , k
# 		5) vij ← H(sij), j = 1, . . . , k
# 		6) (pj1, . . . , pjlog 2(d×t)) ← Path(vij), j = 1, . . . , k
#		7) σ = {sij, pjn}k,log2
# 	(iii) {0, 1} ← P Q.V er(m, σ, PK) :
# 		1) Step 1-3 are identical to that of PQ.Sig
# 		2) vij ← H(sij), j = 1, . . . , k
# 		3) bi ← Verify(R, vij, pj1, , pjlog2(d×t)), j = 1, . . . , k.
# 		4) If all bi = 1 return 1, else return 0.

# CS478 Lab 2
# Robert Hayden Anderson
# Courtney Miller



import sys
import signal
import struct
import random
import threading
import time
import multiprocessing
import hashlib
import md5
import string
