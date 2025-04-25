# How to build Plugins?
#### Marks Docenko

## Overview
I am working on a better way of building plugins for any of gz_ targets. For now, however, here is the only way.

1. Change to a desired plugin's directory
2. Type the following commands
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ``` 
3. Copy the resulted plugin's `*.so` file into `/home/<YOUR_USERNAME>/.gz/sim/plugins`. Create a `plugins` directory if it does not exist.