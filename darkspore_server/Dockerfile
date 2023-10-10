FROM ubuntu:mantic
ENV DEBIAN_FRONTEND="noninteractive" TZ="America/Sao_Paulo"
RUN apt-get update

# Installing dependencies needed by the project as a whole
RUN apt-get -y install g++-13
RUN apt-get -y install cmake libfindbin-libs-perl libglm-dev libluajit-5.1-dev
RUN apt-get -y install libstdc++-13-dev
RUN apt-get -y install build-essential

# Installing dependencies needed by RakNet
RUN apt-get -y install gcc-10 gcc-10-base gcc-10-doc g++-10
RUN apt-get -y install libstdc++-10-dev libstdc++-10-doc 

# Retrieving OpenSSL 1.1.1b source
COPY ./libs/openssl-1.1.1b.tar.gz /
RUN tar -xf openssl-1.1.1b.tar.gz -C /

# Compiling OpenSSL 1.1.1b
WORKDIR /openssl-1.1.1b
RUN sh ./config '-Wl,-rpath,$(LIBRPATH)'
RUN make
RUN make install

# Copying ReCap
COPY . /recap

# Building RakNet
WORKDIR /recap/libs/raknet-3.902-mod
RUN CXX=/usr/bin/g++-10 cmake -DCMAKE_CXX_FLAGS="-fpermissive -w" .
RUN CXX=/usr/bin/g++-10 make

# Building ReCap
WORKDIR /recap
RUN find source/ -maxdepth 99 -name "*.h"   | awk '{$1="    "$1}1' > CMakeHeaders
RUN find source/ -maxdepth 99 -name "*.cpp" | awk '{$1="    "$1}1' > CMakeSources
RUN sed -e '/CMAKE_HEADERS/ {' -e 'r CMakeHeaders' -e 'd' -e '}' -i CMakeLists.txt
RUN sed -e '/CMAKE_SOURCES/ {' -e 'r CMakeSources' -e 'd' -e '}' -i CMakeLists.txt
ENV LDFLAGS="-Wl,--copy-dt-needed-entries"
RUN cmake . -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-Wno-deprecated-declarations"
RUN make
#RUN make -n

ENTRYPOINT [ "/bin/bash", "-l", "-c" ]
