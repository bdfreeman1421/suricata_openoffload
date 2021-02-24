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

* /opt/openoffload/libopof_clientlib.a

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



