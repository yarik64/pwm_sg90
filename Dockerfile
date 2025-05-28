FROM alt:latest

RUN apt-get update && apt-get install -y \
					git \
					make \
					cmake \
					ninja-build \
					python3 \
					gcc \
					gcc-c++ \
					arm-none-eabi-gcc \
					arm-none-eabi-gcc-c++ \
					;


COPY . .

RUN git submodule update --init --recursive
RUN make build
