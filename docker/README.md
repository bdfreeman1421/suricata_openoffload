cd /home/bf1936/WB/
tar --exclude='.git' -cvzf suricata-7.0.0-dev.tar.gz suricata-7.0.0-dev
mv  suricata-7.0.0-dev.tar.gz suricata-7.0.0-dev/suricata-7.0.0-dev.tar.gz


docker build -t suricata:v1beta1  .

docker create -it --name suricata suricata:v1beta1 /bin/bash
docker create -it --name suricata --net=host --cap-add=net_admin --cap-add=sys_nice suricata:v1beta1 /bin/bash


/usr/local/lib update in /etc/ld.so.config.d
libc.conf
ldconfig

lib64 update ?

create libpcre.so.3  symlink
ln -s /usr/lib64/libpcre.so.
create libpcap.so.0.8 symlink

