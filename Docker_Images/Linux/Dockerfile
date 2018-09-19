FROM debian:stable-slim

RUN echo "*** Installing gcc (4.9->8) and clang (3.8->6) ***" \
  && DEBIAN_FRONTEND=noninteractive apt-get update \
  && apt-get dist-upgrade -y \
  && echo "deb http://ftp.us.debian.org/debian jessie main contrib non-free" >> /etc/apt/sources.list.d/jessie.list \
  && echo "deb http://ftp.us.debian.org/debian unstable main contrib non-free" >> /etc/apt/sources.list.d/unstable.list \
  && apt-get update \
  && apt install python -y \
  && apt install python3 -y \
  && apt-get install -y cmake \
  && apt-get install -y git \
  && apt-get install wget \
  && apt-get install -y g++-4.9 g++-8 \
  && apt-get install -y clang++-6.0 \
  && apt-get install libc++-dev -y \
  && apt-get install libc++abi-dev -y \
  && apt-get autoremove --purge -y \
  && apt-get autoclean -y \
  && rm -rf /var/cache/apt/* /tmp/* \
  && echo "Setting g++ 8 as default compiler" \
  && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-8 1 \
  && echo "Setting python3 as default" \
  && update-alternatives --install /usr/bin/python python /usr/bin/python3.6 1 \
  && update-alternatives --install /usr/bin/python python /usr/bin/python2.7 2 \
  && echo "Getting polly..." \
  && wget --no-check-certificate -O v0.10.3.tar.gz https://github.com/ruslo/polly/archive/v0.10.3.tar.gz \
  && tar xvzf v0.10.3.tar.gz \
  && echo "Setting environment variables" \
  && echo "... Adding /usr/bin/clang++-6.0/bin to PATH variable" \
  && export PATH=/usr/bin/clang++-6.0/bin:$PATH \
  && echo "... Adding /usr/lib/clang/6.0/lib to LD_LIBRARY_PATH variable" \
  && export LD_LIBRARY_PATH=/usr/lib/clang/6.0/lib:$LD_LIBRARY_PATH \
  && ln -s /usr/bin/clang++-6.0 /usr/bin/clang++ \ 
  && ln -s /usr/bin/clang-6.0 /usr/bin/clang \
  && echo "... Adding /polly-0.10.3 to POLLY_ROOT variable" \
  && export POLLY_ROOT=/polly-0.10.3


  RUN echo "... Getting opengl libraries" \
  && echo "test"  \
  && wget --no-check-certificate -O opengl_deps.tar.gz  https://github.com/kaizenman/utils/archive/opengl_deps.tar.gz \
  && tar xvzf opengl_deps.tar.gz

  RUN chmod +x ./utils-opengl_deps/install_opengl_deps.sh

  RUN ./utils-opengl_deps/install_opengl_deps.sh

  RUN  echo "deb http://httpredir.debian.org/debian stretch-backports main contrib non-free" >> /etc/apt/sources.list \
  && apt-get update \
  && apt-get install -t stretch-backports nvidia-driver -y

#RUN cd /home && wget http://downloads.sourceforge.net/project/boost/boost/1.62.0/boost_1_62_0.tar.gz \
#  && tar xfz boost_1_62_0.tar.gz \
#  && rm boost_1_62_0.tar.gz \
#  && cd boost_1_62_0 \
#  && ./bootstrap.sh --prefix=/usr/local --with-libraries=program_options \
#  && ./b2 install \
#  && cd /home \
#  && rm -rf boost_1_62_0#
CMD [ "/bin/bash" ]