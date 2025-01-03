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
COPY ./darkspore_server /recap

# Building ReCap
WORKDIR /recap
ENV LDFLAGS="-Wl,--copy-dt-needed-entries"
RUN rm -r ./build/ || true
RUN cmake . -B build -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-Wno-deprecated-declarations -Wno-narrowing"
RUN cmake --build build
RUN cp -r res/data build/data
RUN cp -r res/static build/static
RUN mkdir -p build/storage

EXPOSE 42127 10041 8443 8999 9988 3659 80 8080 17502

ENTRYPOINT [ "/bin/bash", "-l", "-c" ]
