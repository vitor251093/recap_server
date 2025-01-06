# Building Resurrection Capsule Server

* [Docker](#docker)
* [Linux](#linux)

## Docker
The process of building the ReCap server with a Docker container can be executed from any system, as long as you have Docker installed.
1. Build the Docker image:
   ```bash
   git clone https://github.com/vitor251093/recap_server
   cd recap_server/
   docker-compose up
   ```
2. Run the Docker container (will build and run the server locally):
   ```bash
   docker run -v $(pwd)/darkspore_server:/recap -P --network=host -it recap-server
   ```

## Linux
1. Install dependencies:
   * Ubuntu: `sudo apt install g++-13 cmake libfindbin-libs-perl libstdc++-13-dev build-essential`
2. Download the Resurrection Capsule Server repository and prepare:
   ```bash
   git clone https://github.com/vitor251093/recap_server
   cd recap_server/darkspore_server
   ```
3. Compile:
   ```bash
   ./build.sh
   ```
