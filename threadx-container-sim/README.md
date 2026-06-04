# ThreadX 6.5 Container Emulator

This project is a minimal Docker-based ThreadX simulation scaffold. It runs ThreadX through the Linux/GNU port inside a container so the scheduler and basic RTOS APIs can be exercised without a physical MCU board.

## What This Simulates

- Thread creation and scheduling
- Queue-based task communication
- Basic ThreadX application startup through `tx_application_define`

This is not a hardware-accurate MCU emulator. Use QEMU with a target-specific ThreadX port if you need startup vectors, interrupt behavior, linker scripts, or board-level peripheral simulation.

## Directory Structure

```text
threadx-container-sim/
├── Dockerfile
├── CMakeLists.txt
├── app/
│   └── demo_threadx_sim.c
└── README.md
```

## Build And Run

Install Docker Desktop first. On Windows, Docker Desktop usually requires WSL 2 and BIOS/UEFI virtualization support.

```powershell
docker build -t threadx-sim .
docker run --rm threadx-sim
```

Expected output shows producer and consumer threads exchanging messages:

```text
[producer] send 0
[consumer] receive 0
...
ThreadX container simulation finished.
```

## Local Build Without Docker

If ThreadX is already cloned into `threadx-container-sim/threadx`, the project can be built directly:

```powershell
cmake -S . -B build -G Ninja
cmake --build build
.\build\threadx_sim.exe
```

On Linux:

```bash
cmake -S . -B build -G Ninja
cmake --build build
./build/threadx_sim
```
