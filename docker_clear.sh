docker rm $(docker ps -a | grep recap-server | awk '{print $1;}')
