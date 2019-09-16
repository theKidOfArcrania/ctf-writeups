FROM ubuntu:19.04

RUN apt-get update
RUN apt-get install -y xinetd 
RUN apt-get install -y net-tools netcat 

COPY babyheap /babyheap
COPY xinetd /etc/xinetd.d/heap

CMD ["/usr/sbin/xinetd", "-dontfork"]
 
