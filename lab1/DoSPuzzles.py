# Lab 1. Denial of Service Mitigation with Client-Server Puzzles
# In class, we have covered a series of hash-based client-server puzzles. This assignment focuses
# on the first client-server puzzle discussed in slides (i.e. slide 11-19). We exclude sub-puzzles
# and will only focus on a single puzzle for the simplicity. For further details, please read the
# below paper:
#
# Puzzles: A Cryptographic Countermeasure Against Connection Depletion Attacks. A. Juels,
# and J. Brainard. NDSS, The Internet Society, (1999)
#
# The goal is to create a four-step protocol between two processes, one will act as the client
# while the other will be the server (i.e., slide 19). Given the request, the server generates a
# k-bit hard puzzle as in slide 14. In this assignment, try different puzzle difficulties to see the
# impact. For example, in one instance, k = 8, and observe how many connection requests the
# client is able to make. Then increase, set k = 16, 20, 32, and observe the difference.

# CS478 Lab 1
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
import random

random.seed

def random_string(length):
    initial = ""
    i = 0
    while i<length:
        initial = initial + chr(random.randint(97, 122))
        i += 1
    return initial


def generate_puzzle():
    return random_string(4)

def main():
    print generate_puzzle()

main()
