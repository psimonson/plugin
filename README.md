## Simple Plugin Manager

Very simple plugin manager all of the initial code is done for you. You
just need to make callbacks and register those callbacks in your code. If
you need to execute a plugin at a specific location you can call it like
this:

    PluginManager_exec(PluginManager_search("plugin1"));

Where plugin1 is in double quotes is the basename of the plugin with or
without the extension. If you find bugs please drop me an e-mail. Also do NOT
spam my e-mail with miscellaneous crap, if it is NOT about a bug and pertains
to this code I WILL NOT reply. I never reply to spam e-mail.

### Build Instructions

 - Install basic development tools for your distro of Linux, Mingw-w64 on Linux.
 - This can be cross compiled for windows with mingw-w64 or built on windows with cygwin.
 - Also install git as it's required.

Then run these commands as follows:

    cd plugin
    ./configure <linux|win32>
    make all

Then you can run it like this:

on Linux:
    ./shell-example (for Linux executable)
    WINEARCH=win32 wine shell-example.exe (for Windows executable, if configured with win32).

on Windows:
    shell-example.exe

### Developer

  - Philip R. Simonson <psimonson1988@gmail.com>

### License

  - MIT License

### Disclaimer

I really do NOT care what you use this code in, if you use this code or any
part of this code. Please add me in the credits of your application/program.
This software is provided "AS-IS", I am NOT liable for any damages in relation
to this software.
