docker run -d --name recap-server --rm -it -v $(pwd):/recap recap-server:latest
docker run -it recap-server bash
