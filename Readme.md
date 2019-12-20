# Blockit: An OS Level Ad Blocker

#### Introduction
This is a utility software that gets deployed on GNU/Linux Systems with support for the Netfilter[1] and libpcap[2] support.

#### Highlights
* Gets deployed as a background app
* Fetches blocklist from a link fed as argument and saves as hosts.conf using curl library
* Sniffes for packets to/from the blocked addresses using libpcap
* Blocks the traffic on kernel level using netfilter

#### Dependencies
* Libcurl
* Libpcap
* Netfilter
* GNU GCC
* GNU Make
* Commandline Argument Parser library [3]

#### Compilation
```bash
#fetch the submodule
git submodule update --init
#export Argument library path
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:cargparse/src
#start compilation
make
```
#### Usage
```bash
#show help
bin/server.bin
```

#### Recommended curated host lists
[Host List](https://github.com/StevenBlack/hosts)

#### References
[1] [Netfilter homepage](https://www.netfilter.org/)</br>
[2] [Libpcap/TCP dump Homepage](https://www.tcpdump.org/)</br>
[3] [Argument Parser Library](https://gitlab.com/r0ck3r008/cargparse)</br>
