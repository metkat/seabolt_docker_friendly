# Seabolt

This is a fork of the original [Seabolt C Connector Library for Neo4j](https://github.com/neo4j-drivers/seabolt/releases). It has been updated to compile in Docker containers (including on M1 architecture), creating and exporting packages which can then be installed using a package manager.


## Building Debian package for installation elsewhere
```
docker run --rm -v "$(pwd):/seabolt" $(docker build -q .) /seabolt/make_release.sh
```
creates package files in build/dist_package, which can be installed using a package manager (e.g. `dpkg -i seabolt-1.7.4-dev-Linux-debian-11.deb`).



## Running

To test by using seabolt-cli inside the build container, use the following...
```
docker run -it --rm -v "$(pwd):/seabolt" $(docker build -q .) bash
```
then

```
./make_release.sh
export BOLT_PASSWORD=password 
build/bin/seabolt-cli run "UNWIND range(1, 1000000) AS n RETURN n"
build/bin/seabolt-cli run "MATCH (n) RETURN n LIMIT 5"
etc...
```

The following environment variables can be used. Setting BOLT_SECURE=0 is a good starting point to troubleshoot. If you're using OS X, `host.docker.internal` is the docker host loopback address.
```
BOLT_ROUTING=[0]|1
BOLT_ACCESS_MODE=[WRITE]|READ
BOLT_SECURE=0|[1]
BOLT_HOST=<host name, IPv4 or IPv6 address>[localhost]
BOLT_PORT=[7687]
BOLT_USER=[neo4j]
BOLT_PASSWORD=password[(null)]
--- BOLT_LOG=0|1|2 --- (only not)
```

