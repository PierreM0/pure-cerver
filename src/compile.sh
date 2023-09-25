gcc \
  -pedantic \
  -Wall -Werror \
  -s -Os -no-pie \
  -nostdlib \
  -ffreestanding \
  -fno-stack-protector \
  -fdata-sections \
  -ffunction-sections \
  -fno-unwind-tables \
  -fno-asynchronous-unwind-tables \
  -Wl,-n \
  -Wl,--gc-sections \
  -Wl,--build-id=none \
  -z noexecstack \
  start.S main.c \
  -o main
