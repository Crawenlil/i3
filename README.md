## i3-scripts


# brightness.c

1. Compilation:
```bash
gcc brightness.c -o brightness -lm
```

2. Add priviledges:
```
sudo chown root:root brightness
sudo chmod +s brightness
```

3. Usage:
```bash
brightness 1  # Increases brightness
brightness -1 # Decreases brightness
```
