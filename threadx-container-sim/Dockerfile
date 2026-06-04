FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    build-essential \
    ca-certificates \
    cmake \
    git \
    ninja-build \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

COPY . /workspace/threadx-container-sim

WORKDIR /workspace/threadx-container-sim

RUN git clone --depth 1 https://github.com/eclipse-threadx/threadx.git threadx
RUN cmake -S . -B build -G Ninja
RUN cmake --build build

CMD ["./build/threadx_sim"]
