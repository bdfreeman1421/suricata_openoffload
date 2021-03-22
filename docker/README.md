
We need to put the source code in the Docker container so we create a tar and then move it to the root of the docker build.

In my environment /data/WB/suricata-7.0.0-dev is my cloned repository

cd /data/WB 
tar --exclude='.git' -cvzf suricata-7.0.0-dev.tar.gz suricata-7.0.0-dev
mv  suricata-7.0.0-dev.tar.gz suricata-7.0.0-dev/suricata-7.0.0-dev.tar.gz

cd /data/WB/suricata-7.0.0-dev

docker build -t suricata:v1beta1  . 

docker images (to see the successfully created image)

docker create -it --name suricata --net=host --cap-add=net_admin --cap-add=sys_nice suricata:v1beta1 /bin/bash

This should create a container 'suricata' that can be started and logged into.

docker start suricata

docker exec -it suricata bash

The Dockerfile should create these symbolic links but confirm inside the container that libc.conf and /usr/lib64 is adjusted as followse:

Create /etc/ld.so.config.d/libc.conf and add the line:
/usr/local/lib 


Save the file and run: ldconfig


#create libpcre.so.3  symlink
ln -s /usr/lib64/libpcre.so.   libpcre.so.3
#create libpcap.so.0.8 symlink
ln -s /usr/lib64/libpcap.so.    libpcap.so.0.8


/usr/lib64
libpcre.so.3 -> libpcre.so.1.2.10
libpcap.so.0.8 -> libpcap.so.1.9.1

Modify /etc/suricata/suricata.yaml for your vwire ports to your SmartNIC  (see af-packet section and adjust the interface and copy-to ports) 

In my environment enp175s0f3 and s2f3 were the SRIOV VFs created to the SmartNIC
  - interface: enp175s0f3
    copy-iface: enp175s2f3
  - interface: enp175s2f3
    copy-iface: enp175s0f3

Set the openoffload ip address and port (for each af-packet interface). In my environment the SmartNIC is listening on 169.254.33.51 and the container has an interface enp175s0f4 with IP address 169.254.33.52. The SmartNIC is confiured to us InLif=1 and outLif=2.

    openoffload: yes
    openoffload-host: 169.254.33.51
    openoffload-port: 3443
    openoffload-inlif: 1
    openoffload-outlif: 2


Modify the rules in /var/lib/suricata/rules/local.rules for your testing. The installed rules provide examples for http, tcp and udp bypass to the SmartNIC

alert http any any -> any any (msg:"Test http bypass"; bypass ;  sid:1; rev:1;)
alert tcp any any  <> any any (msg:"Test iperf3 bypass"; bypass ;  sid:2; rev:1;)
#alert udp any any -> any any (msg:"test udp bypass "; bypass; sid:3; rev:5;)


To start suricata inside the container with the SmartNIC: 
./src/suricata -c /etc/suricata/suricata.yaml --af-packet
