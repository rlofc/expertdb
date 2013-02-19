expert.db
=========
The high-performance graph database.

Motivation
----------
As part of my effort to build a semantic network, I need a persistent 
storage mechanism capable of containing large-scale graph data.

Architecture
------------
![expert.db layers](https://raw.github.com/L3V3L9/l3v3l9.github.com/master/expertdb/images/expertdb1.png)

* core - Basic services such as murmur hash, string functions, etc..
* petri - persistent prefix tree - the index file module
* dfile - data file engine - store and restore the actual graph data
* gstor - uses _petri_ and _dfile_ to store graph nodes and arcs
* xlog - graph transaction logger 
* trax - transactional extensions - use xlog to ensure transactions are atomic
* socks - the expert.db socket server framework
* exdb - the actual expert.db server front-end
