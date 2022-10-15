## What this code will do

This code takes an ASCI .txt file as an input. A histogram of characters is generated which is used as the input to create a min heap priority queue with priority
equal to character frequency. Nodes are popped off the queue according to the Huffman coding algorithm to create a Huffman tree. This tree is traversed to generate 
codewords for each character that was found in the ASCI .txt file. The .txt file is encoded using these codewords, with the Huffman tree encoded in the file as a header. 
A decoder program can then reconstruct the original .txt from the compressed binary file.
