# Fluid Dev Programming Test

**Author:** Roux, Federico Gabriel, Eng. (rouxfederico@gmail.com)

# Repo information:

## Installation

This repo can be built and deployed inside a container based on Debian Jessie Slim

### a) Build and deploy from docker command line:

- Open a terminal(Unix or macOS) or PowerShell in Windows and cd into the project folder

- Build the docker image:

```bash
docker build -t fluid-dev -f .devcontainer/Dockerfile .
```

- Run the container and share the project folder with it:

```bash
docker run -it --rm --name=Fluid-Dev --mount type=bind,source=${PWD},target=/workspace fluid-dev bash
```

### b) Build and deploy inside VSC devcontainer:

The easiest way to set up the container is using the VSC Docker Extension as a [devcontainer](https://code.visualstudio.com/docs/remote/containers).

- Install Visual Studio Code ([VSC](https://code.visualstudio.com/))

- Install [Docker](https://www.docker.com/) 

- Install the following VSC extensions:

    -  Name: Docker

        Id: ms-azuretools.vscode-docker

        Description: Makes it easy to create, manage, and debug containerized applications.

        Version: 1.18.0

        Publisher: Microsoft

        [VS Marketplace Link](https://marketplace.visualstudio.com/items?itemName=ms-azuretools.vscode-docker)


    - Name: Remote - Containers

        Id: ms-vscode-remote.remote-containers

        Description: Open any folder or repository inside a Docker container and take advantage of Visual Studio Code's full feature set.
        
        Version: 0.209.6
        
        Publisher: Microsoft
        
        [VS Marketplace Link](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)

- Usage: Open the current repository using the Dev Container VSC extension, chosing "Open Folder inside container" . The first time, it may take several minutes to build the container.

## Test suite

Unit test are based on Catch2 and FakeIt. These libs are added as submodules. Be sure to clone the repository using 

```git
git clone <URL> --recursive
```

Or once the repository was cloned, then run:

```git
git submodule update --init
```

Catch2 needs to be installed on the container. This can be easily done by executing:

```bash
cd scripts
./install-catch2.sh
```

## Building the sources:

This project is based on cmake. In order to simplify the process, a script called <build-all.sh> is provided. It's a bash script, so it can be run inside the container, or on a Unix-macOS environment. This script will generate all the building files and the docs (based on doxygen). Just run:

```bash
cd scripts
./build-all.sh
```

To compile natively on Windows, please open a cmd.exe or PowerShell terminal, cd into the project folder and run:

```
mkdir -p build
cd build
cmake ..\

```

The executable files can be found at:

- app: build/src/fluid_dev
- test suite: build/test/test_suite

# Programming Test Detail:

**Background:**

You will be working closely with motors on an actuated robot. This challenge is a typical problem that will be encountered when working with this robot.

**Problem:**

You will read the joint position value from an encoder from one of the joints of the robot. The joint position will be given as a number between 0 to 4096, covering 360 degrees of rotation

1. Store that value in a ring buffer
2. Provide functions for calculating the instantaneous velocity and acceleration using the
[finite difference method](https://en.wikipedia.org/wiki/Finite_difference_method).
3. Write unit tests for all funcions

**Requirements:**

- Use modern C++
- Use proper software engineering fundamentals and code hygiene