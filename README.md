# Discovering Injective Mapping between Relations in Astrophysics Databases

<p> This repository contains the implementation of the article <i> Discovering Injective Mapping between Relations in Astrophysics Databases </i> part of <b>Communications in Computer and Information Science book series (CCIS, volume 760)</b>.</p>

## How to build

### Setup envirnoment
```
sudo apt install curl gnupg
curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor > bazel.gpg
sudo mv bazel.gpg /etc/apt/trusted.gpg.d/
echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list
sudo apt update && sudo apt install bazel
sudo apt update && sudo apt full-upgrade
bazel --version
```
### Build solution
```
bazel run command_line -- "%SOURCE FILE FULL PATH%" "%TARGET FILE FULL PATH%"
```