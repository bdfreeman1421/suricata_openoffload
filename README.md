Session Offload Demonstration
========

Introduction
------------

Session Offload is an open source project that aims to use network processors to offload packet processing from x86 applications using an open and extensible API.
A gRPC API has been defined and implemented in preliminary applications.
The source repository is https://github.com/att/sessionOffload

This fork of Suricata includes a demonstration of how to modify an application to use a SmartNIC or Router to offload tcp and udp processing.

Suricata README [here](./README-SURICATA.md)


Details
------------
The main change is to add a Bypass Callback function to the AF-PACKET capture logic. AF-PACKET already has bypass options for eBPF and XDP bypass modes so the addition of the gRPC bypass via sessionOffload/openOffload is fairly straight forward. The bulk of the changes are in source-af-packet.c where the AFPOPOFBypassCallback is defined. Other changes are required to setup the option for using the gRPC offload , link in the open offload and grpc client libraries and general config options.

This is a demonstration so its not a fully functioning implementation and should not be directly used in production. See the TODO sections in source-af-packet.c for some of the things that would need to be added for a complete solution.

It is however, a good way to understand how Suricata could interface with a sessionOffload enabled SmartNIC or NPU.   

If useful and ameniable to the Suricata community, this could be upstreamed after completing and hardening the implementation.

Installation
------------


You will need to install the gRPC and sessionOffload client libraries.

gRPC libraries can be the standard install and can be copied from the docker container form the sessionOffload/openoffload docker container.
Build the openoffload/cpp/framework container as described in the session offlaod README and docker cp the relavent libraries to your environment.

* /opt/grpc libraries

```
-rw-r--r-- 1 root root     6190 Feb 19 19:25 libabsl_bad_optional_access.a
-rw-r--r-- 1 root root    72838 Feb 19 19:25 libabsl_base.a
-rw-r--r-- 1 root root    32348 Feb 19 19:25 libabsl_civil_time.a
-rw-r--r-- 1 root root     4876 Feb 19 19:25 libabsl_dynamic_annotations.a
-rw-r--r-- 1 root root    53460 Feb 19 19:25 libabsl_int128.a
-rw-r--r-- 1 root root     3512 Feb 19 19:25 libabsl_log_severity.a
-rw-r--r-- 1 root root    19208 Feb 19 19:25 libabsl_raw_logging_internal.a
-rw-r--r-- 1 root root     7482 Feb 19 19:25 libabsl_spinlock_wait.a
-rw-r--r-- 1 root root   616310 Feb 19 19:25 libabsl_str_format_internal.a
-rw-r--r-- 1 root root   529172 Feb 19 19:25 libabsl_strings.a
-rw-r--r-- 1 root root    21212 Feb 19 19:25 libabsl_strings_internal.a
-rw-r--r-- 1 root root    26688 Feb 19 19:25 libabsl_throw_delegate.a
-rw-r--r-- 1 root root   442478 Feb 19 19:25 libabsl_time.a
-rw-r--r-- 1 root root   909334 Feb 19 19:25 libabsl_time_zone.a
-rw-r--r-- 1 root root    13336 Feb 19 19:25 libaddress_sorting.a
-rw-r--r-- 1 root root   189814 Feb 19 19:25 libcares.a
-rw-r--r-- 1 root root  3237846 Feb 19 19:25 libcrypto.a
-rw-r--r-- 1 root root   225024 Feb 19 19:25 libgpr.a
-rw-r--r-- 1 root root 34734284 Feb 19 19:25 libgrpc.a
-rw-r--r-- 1 root root  6939956 Feb 19 19:25 libgrpc++.a
-rw-r--r-- 1 root root   103642 Feb 19 19:25 libgrpc++_alts.a
-rw-r--r-- 1 root root   179222 Feb 19 19:25 libgrpc++_error_details.a
-rw-r--r-- 1 root root  2878764 Feb 19 19:25 libgrpc_plugin_support.a
-rw-r--r-- 1 root root  4026254 Feb 19 19:25 libgrpcpp_channelz.a
-rw-r--r-- 1 root root  2073298 Feb 19 19:25 libgrpc++_reflection.a
-rw-r--r-- 1 root root 30235178 Feb 19 19:25 libgrpc_unsecure.a
-rw-r--r-- 1 root root  5702332 Feb 19 19:25 libgrpc++_unsecure.a
-rw-r--r-- 1 root root  4389526 Feb 19 19:25 libssl.a
-rw-r--r-- 1 root root    66770 Feb 19 19:25 libupb.a
-rw-r--r-- 1 root root   153474 Feb 19 19:25 libz.a
```

OpenOffload client library can be copied from the sessionOffload docker container as well 

* /opt/openoffload/libopof_clientlib.a

* rules


Example Rules
------------

```
alert http any any <> any any (msg:"Test http bypass"; bypass ;  sid:1; rev:1;)
alert udp any any -> any any (msg:"test udp bypass "; bypass; sid:2; rev:5;)
alert tcp any any <> any any (msg:"test tcp bypass "; bypass; sid:4; rev:5;)
```

Running a demonstration
------------
1. start gRPC server (python version is easier use for a demonstration but us insecure channel since the SmartNIC version doesnt required ssl)

2. start http (lighttpd) or udp server (iperf3) on the same machine as suricata

3. start suricata - on virtual box two ubuntu VM's (suricate/traffic sink and a traffic source) can be used on an internal network
In the example below we are using the second NIC (enps08) as the interace to listen on.
```
./src/suricata -c /etc/suricata/suricata.yaml -i enp0s8
```
4. tail suricata log in one window  (/var/log/suricat/suricata.log)

5. send traffic in another window
```
curl http://10.0.1.4
iperf3 -u -c 10.0.1.4
```
6. see log messages from gRPC server (addSessions messages from tcp and udp)

7. see suricats log message for opeonoffload events 

