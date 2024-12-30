FROM ubuntu:noble
ENV DEBIAN_FRONTEND="noninteractive" TZ="America/Sao_Paulo"
RUN apt-get update

# Installing dependencies needed by the project as a whole
RUN apt-get -y install g++-13
RUN apt-get -y install cmake libfindbin-libs-perl
RUN apt-get -y install libstdc++-13-dev
RUN apt-get -y install build-essential
RUN apt-get -y install git

# Copying ReCap
COPY . /recap

# Building ReCap
WORKDIR /recap
ENV LDFLAGS="-Wl,--copy-dt-needed-entries"
RUN cmake . -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-Wno-deprecated-declarations -Wno-narrowing"
RUN make
#RUN make -n

ENTRYPOINT [ "/bin/bash", "-l", "-c" ]
