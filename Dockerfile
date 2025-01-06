FROM ubuntu:noble
ENV DEBIAN_FRONTEND="noninteractive" TZ="America/Sao_Paulo"
RUN apt-get update

# Installing dependencies needed by the project as a whole
RUN apt-get -y install g++-13
RUN apt-get -y install cmake libfindbin-libs-perl
RUN apt-get -y install libstdc++-13-dev
RUN apt-get -y install build-essential
RUN apt-get -y install git

EXPOSE 42127 10041 8443 8999 9988 3659 80 8080 17502

WORKDIR /recap
ENTRYPOINT [ "sh", "./docker_build_and_run_server.sh" ]
