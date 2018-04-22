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
import datetime
import math

# first of all import the socket library
import socket

random.seed

# get current time
def get_time():
    return str(math.floor(time.time())[:-2])

puzzle = "the actual puzzle."


# get the hash value of a given string
def hash_string(s):
    m = hashlib.md5()
    m.update(s)
    return m.hexdigest()

# generate random string of given length
def random_string(length):
    initial = ""
    i = 0
    while i<length:
        initial = initial + chr(random.randint(97, 122))
        i += 1
    return initial

# remove k bits from the pre-image
def hide_bits(preImage, k):
    i = len(preImage)-k
    return preImage[0:i]

# generate the puzzle for the client to solve
def generate_puzzle():
    compute = get_time() + random_string(4) + random_string(4)
    compute_hash = hash_string(compute)
    pre_image = hide_bits(compute_hash, 1)
    return hash_string(pre_image)


# next create a socket object
s = socket.socket()
print "Socket successfully created"

# reserve a port on your computer in our
# case it is 12345 but it can be anything
port = 12345

# Next bind to the port
# we have not typed any ip in the ip field
# instead we have inputted an empty string
# this makes the server listen to requests
# coming from other computers on the network
s.bind(('', port))
print "socket binded to %s" %(port)

# put the socket into listening mode
s.listen(5)
print "socket is listening"

# a forever loop until we interrupt it or
# an error occurs
while True:

    # Establish connection with client.
    c, addr = s.accept()
    print 'Got connection from', addr

    # send a thank you message to the client.
    c.send('Thank you for connecting')

    message = c.recv(1024)

    puzzle = generate_puzzle()
    print message
    if "puzzle" in message:
        print "client wants a puzzle"
        c.send(puzzle)


    # Close the connection with the client
    c.close()
