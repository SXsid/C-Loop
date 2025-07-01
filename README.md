# Event Loop in C

This project demonstrates a simple event loop in C using a main timer and IO watcher.

## Features

- **Main Timer:** Periodically triggers scheduled tasks.
- **IO Watcher:** Monitors IO events (e.g., file or socket readiness).
- **Event Loop:** Continuously checks for timer and IO events, dispatching handlers accordingly.

## Usage

1. Clone the repository.
2. Build the project using your preferred C toolchain (e.g., gcc).
3. Run the executable to see the event loop in action.

## Example

```c
while (1)
{
    // Timer event handling in C
    HandleTimerEvent();

    if (IsIOReady())
        HandleIOEvent();

    usleep(10000); // Prevents busy waiting (10 ms)
}
```

## Requirements

- C compiler (e.g., gcc)

## License

MIT License