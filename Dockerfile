FROM ruby:3.2

RUN apt-get update && apt-get upgrade -yqq 
RUN apt install  -yqq git build-essential cmake libssl-dev


# manual build :
# docker run --rm -v "$(pwd):/seabolt" $(docker build -q .) /seabolt/make_release.sh
# creates deb package in build/dist-package


