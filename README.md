*This project has been created as part of the 42 curriculum by mbelfaki.*

# Codexion

## Description

Codexion is a multithreaded simulation where coders compete for shared resources (dongles). Each coder must acquire two dongles to compile, otherwise they risk burnout if they wait too long. The program demonstrates concurrency control, scheduling (FIFO/EDF), and precise timing management.

---

## Instructions

### Compile

```bash
make
```

### Run

```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

Example:

```bash
./codexion 5 800 200 150 150 3 100 fifo
```

---

## Blocking cases handled

* **Deadlock prevention**: avoids circular wait via controlled resource access
* **Starvation prevention**: FIFO (fair order) and EDF (priority by deadline)
* **Cooldown handling**: dongles unavailable during cooldown
* **Burnout detection**: monitored with precise timing
* **Log serialization**: mutex-protected output

---

## Thread synchronization mechanisms

* **Mutexes (`pthread_mutex_t`)**: protect shared data (dongles, state, logs)
* **Condition variables (`pthread_cond_t`)**: wait/signal resource availability
* **Monitor thread**: detects burnout and stops simulation
* **Race prevention**: all shared access is synchronized, no global variables

---

## Resources

* https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2



**AI usage:** helped with explanations and documentation structure only.

