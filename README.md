# Linux_SystemInfo

A lightweight system monitor for Linux written in C using `ncurses`.  
It displays useful system information such as:

- **CPU model and number of cores**
- **Per-core CPU usage**
- **Memory usage**
- **Swap usage**

---

## 📦 Features
- Reads system data directly from `/proc/cpuinfo`, `/proc/stat`, and `/proc/meminfo`.
- Calculates real-time CPU usage.
- Displays memory and swap statistics.
- Simple and efficient command-line interface.

---

## 🚀 Compilation

Clone the repository and build using `make`:

```bash
git clone https://github.com/your-username/Linux_SystemInfo.git
cd Linux_SystemInfo
make
