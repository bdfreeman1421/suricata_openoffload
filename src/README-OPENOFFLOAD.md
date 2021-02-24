Session Offload Demonstration
========

Introduction
------------

Session Offload is an open source project that aims to use network processors to offload packet processing form x86 applications using an open and extensible API.
A gRPC API has been defined and implemented in preliminary applications.
The source repository is https://github.com/att/sessionOffload

This fork of Suricata includes a demonstration of how to modify an application to use a SmartNIC or Router to offload tcp and udp processing.

 

Installation
------------

* /opt/grpc libraries

* /opt/openoffload/opof_clientlib.a

* rules


Example Rules
------------

```
alert http any any -> any any (msg:"Test http bypass"; bypass ;  sid:1; rev:1;)
alert udp any any -> any any (msg:"test udp bypass "; bypass; sid:2; rev:5;)
```

Running a demonstration
------------
1. start gRPC server (python is easier to demonstrat)
2. setup http (lighttpd) or udp server (iperf3)
3. start suricata
4. tail suricat log in one window
5. send traffic in another
6. see log messages from gRPC server (python)
7. see suricat log message in /var/log/suricata/suricata.log



