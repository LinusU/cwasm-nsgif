FROM ubuntu:18.04

#########################
# Install prerequisites #
#########################

RUN \
  apt-get update && \
  apt-get install -y ca-certificates curl git

########################
# Install WASI SDK 8.0 #
########################

RUN curl -L https://github.com/CraneStation/wasi-sdk/releases/download/wasi-sdk-8/wasi-sdk-8.0-linux.tar.gz | tar xz --strip-components=1 -C /

#####################
# Build actual code #
#####################

WORKDIR /code

RUN git clone git://git.netsurf-browser.org/libnsgif.git && cd libnsgif && git checkout release/0.2.1
ADD decode.c .

# Relase build
RUN clang --sysroot=/share/wasi-sysroot --target=wasm32-unknown-wasi -Ilibnsgif/include/ -Oz     -o libnsgif.wasm -nostartfiles -fvisibility=hidden -Wl,--no-entry,--demangle,--export=malloc,--export=free,--export=decode_gif,--strip-all -- decode.c libnsgif/src/libnsgif.c libnsgif/src/lzw.c

# Debug build
# RUN clang --sysroot=/share/wasi-sysroot --target=wasm32-unknown-wasi -Ilibnsgif/include/ -O0 -g3 -o libnsgif.wasm -nostartfiles -fvisibility=hidden -Wl,--no-entry,--demangle,--export=malloc,--export=free,--export=decode_gif,             -- decode.c libnsgif/src/libnsgif.c libnsgif/src/lzw.c

CMD base64 --wrap=0 libnsgif.wasm