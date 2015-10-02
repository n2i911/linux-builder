# linux-builder

  This would help to build the kernel and u-boot for machine **vexpress** as well as the root filesystem.
  It help me to test the kernel quickly when I do experiments on it.

* prerequisites: mkimage, genromfs, qemu

  apt-get install genromfs u-boot-tools qemu qemu-system

* help:

  **make help** would display the help message

* The default cross compiler:

  - [arm-none-eabi-gcc](https://dl.dropboxusercontent.com/u/105962512/gcc-arm-none-eabi-4_9-2015q2-20150609-linux.tar.bz2)

  - [arm-none-linux-gnueabi-gcc](https://dl.dropboxusercontent.com/u/105962512/arm-2013.05-24-arm-none-linux-gnueabi-i686-pc-linux-gnu.tar.bz2)
