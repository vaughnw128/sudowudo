# Sudowudo 
## (And other various shims)

This repository is home to a few binary shims used for red team competitions. These scripts and tools are not intended to be used anywhere outside of blue/red team competitions as it's essentially malware.

Sudowudo takes advantage of tgetpass.c by stealing and exfiltrating the plaintext password before it's used, and sending it to a C2 server via a UDP datagram.