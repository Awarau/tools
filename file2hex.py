#This python3 code takes in a file and outputs shellcode, or disassembly. 

import binascii
import sys
import re
import argparse 
from capstone import *

parser = argparse.ArgumentParser()
parser.add_argument("--disasm", help="disassembler")
parser.add_argument("--hex", help="hexifier")
args = parser.parse_args()

def filetohex(filename, en):

        f = open(filename, 'rb')
        content = binascii.hexlify(f.read())

        if en == 'little':
                little_en(content)
        if en == 'big':
                big_en(content)

def little_en(hex):

        i = 0
        j = 1
        y = 1

        hex = hex.decode('utf-8')
        hex = re.findall('..', hex)

        while(j < len(hex)):
                hex[i], hex[j] = hex[j], hex[i]
                i = i + 2
                j = j + 2

        format_print(hex)

def format_print(hex):

        y = 1

        hex = ''.join(hex)
        hex = re.findall('....', hex)

        while(y < len(hex)):
                hex.insert(y, ' ')
                y = y + 2

        hex = ''.join(hex)

        print(hex)

def big_en(hex):

        hex = hex.decode('utf-8')
        hex = re.findall('..', hex)

        format_print(hex)

def disasm(content):

        #f = open(filename, 'rb')
        #content = binascii.hexlify(f.read())

        print(content)

        dis = Cs(CS_ARCH_X86, CS_MODE_64)

        for i in dis.disasm(content, 0x0000):
                print("0x%x:\t%s\t%s" %(i.address, i.mnemonic, i.op_str))

#~   ######## ~!#!~~~~~!#!~~~~~!#!~%%####&&7
#~  ##Main##  ~!#!~~~~~!#!~~~~~!#!~@+---3~~7
#~ ########   ~!#!~~~~~!#!~~~~~!#!~%%####&&7

if args.hex:

        filetohex(args.hex, "little")

if args.disasm:

        disasm(args.disasm)
