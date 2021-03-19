FROM opofbld:v1beta1
#
USER root
ENV PATH="/home/grpc/local/bin:${PATH}"
RUN yum -y update
RUN yum -y install libnet
RUN yum -y install zlib-devel
RUN yum -y install jansson-devel 
RUN yum -y install pcre-devel 
RUN yum -y install libpcap 
RUN yum -y install net-tools
RUN yum -y install httpd
RUN /usr/sbin/httpd
#RUN yum -y install libhtp
# need to ./aut0gen.sh ./configure make make install in libtp
RUN mkdir -p /home/suricata/src
RUN mkdir -p /home/suricata/lib
RUN mkdir -p /var/log/suricata
WORKDIR /home/
COPY suricata-7.0.0-dev.tar.gz  /home/
RUN  tar -xzvf suricata-7.0.0-dev.tar.gz 
RUN  ln -s /home/suricata-7.0.0-dev /home/suricata
#RUN make
WORKDIR /home/suricata-7.0.0-dev/libhtp 
RUN  ./autogen.sh
RUN  ./configure
RUN  make
RUN  make install
RUN mkdir -p /opt/grpc/local
RUN ln -s /home/grpc/lib /opt/grpc/local

RUN ln -s /usr/lib64/libpcre.so.1.2.10 /usr/lib64/libpcre.so.3
RUN ln -s /usr/lib64/libpcap.so.1.9.1  /usr/lib64/libpcap.so.0.8

COPY docker/lib/libc.conf  /etc/ld.so.conf.d/libc.conf
RUN ldconfig

RUN mkdir -p /var/lib/suricata/rules
COPY docker/rules/* /var/lib/suricata/rules/
RUN mkdir -p /etc/suricata
COPY docker/etc/*  /etc/suricata/
CMD ["sh", "-c", "tail -f /dev/null"]

