FROM gcc:7.3.0

RUN apt-get -qq update
RUN apt-get -qq upgrade
RUN apt-get -qq install cmake

RUN apt-get -qq install libboost-all-dev=1.62.0.1
RUN apt-get -qq install build-essential libtcmalloc-minimal4 && \
  ln -s /usr/lib/libtcmalloc_minimal.so.4 /usr/lib/libtcmalloc_minimal.so

COPY . /usr/project

WORKDIR /usr/project

RUN g++ main.cpp -std=c++17 -o ./build/app
RUN g++ test.cpp -std=c++17 -o ./build/test

EXPOSE 8888
CMD ["tail", "-F" "README"]