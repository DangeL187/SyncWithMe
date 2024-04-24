# SyncWithMe
SyncWithMe is a tool that allows you to sync your text files with those of other people.

And there is a perfect tool for this - [JetBrains Code With Me](https://www.jetbrains.com/code-with-me/)

# BUT!
SyncWithMe may be a better option in certain situations:
* Your work does not involve JetBrains products
* You might want to synchronize your text files with those on a remote server or with a friend
* You want full control over shared files, such as building a project on your own device
* You don't want anyone to see what you're doing `xD`

# How does it work?
1. SyncWithMe sends information about recent changes and <b> ONLY </b> sends changes, not the entire file.
2. SyncWithMe tracks changes using [diff template library](https://github.com/cubicdaiya/dtl)
3. SyncWithMe offers fast synchronization because it uses TCP/IP directly.
4. Files are stored on your device, so you will be able to edit them using <b> any tool </b> you want and do <b> whatever you want </b> with them, as you literally own them

# Good to know
1. SyncWithMe uses [DangeL's Client Server Lib](https://github.com/DangeL187/DCSL) for sending and receiving information, DCSL is experimental and can cause some problems.
2. You can rebuild SyncWithMe to use any other method of sending and receiving data if you prefer.
### SyncWithMe is currently in development, so please be aware.

# How to build
### In a good way, it is better to use CMakeLists.txt to search for dependencies, however here is a list of them
1. Boost
2. OpenSSL
3. [DCSL](https://github.com/DangeL187/DCSL)
4. [dtl](https://github.com/cubicdaiya/dtl)
5. [nlohmann json](https://github.com/nlohmann/json)
