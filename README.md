<h2 align="center">

[![PHILOSOPHERS](https://github.com/TiagoDev88/42-project-badges/blob/main/covers/cover-philosophers.png)](https://github.com/TiagoDev88/philosophers)

</h2>

<p align="center">
	<b><i>Dining Philosophers Problem - 42 School project</i></b><br>
</p>


<h3 align="center">
	<a href="#about-">About</a>
	<span> · </span>
	<a href="#features-">Features</a>
	<span> · </span>
	<a href="#usage-">Usage</a>
	<span> · </span>
	<a href="#author-">Author</a>
</h3>

---

> _Philosophers is a 42 School project that explores the famous Dining Philosophers problem, focusing on concurrent programming, thread synchronization and resource sharing using mutexes._

The goal is to simulate philosophers sitting at a table who alternate between eating, sleeping and thinking — without running into deadlocks or race conditions.  
This project teaches the fundamentals of **multithreading**, **mutex management**, and how to properly design concurrent systems.

---

## Features 🚀

Philosophers implements:

- Simulation of the **Dining Philosophers problem**
- Each philosopher alternates between:
  - Eating 🍝
  - Sleeping 😴
  - Thinking 💭
- Detection of philosopher death (when not eating within `time_to_die`)
- Proper synchronization using **mutexes** to avoid race conditions
- Protection against deadlocks
- Command-line arguments to configure the simulation:
  1. `number_of_philosophers`
  2. `time_to_die`
  3. `time_to_eat`
  4. `time_to_sleep`
  5. `[number_of_times_each_philosopher_must_eat]` (optional)

---

## Usage 📘

### Requirements

- GCC compiler
- Make

### Instructions

**1. Clone the repository**

```bash
git clone https://github.com/TiagoDev88/minishell.git
```

**2. Compile**
```bash
make
```

**3. Run**
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
- Example:
```bash
./philo 5 800 200 200
```
5 philosophers

time_to_die = 800ms

time_to_eat = 200ms

time_to_sleep = 200ms

```bash
./philo 5 800 200 200 7
```
Same as above, but simulation ends when each philosopher has eaten 7 times.

### Author 👤

42 login: tfilipe-  /  GitHub: @TiagoDev88
