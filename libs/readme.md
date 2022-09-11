# LIBS directory

In this directory, you are required to place all the external libraries your project depends on.
Although, in principle, you can use git submodules (and place them under this directory),
for the sake of easily compiling your application, placing the source code of the
open source libraries is also fine. However, this approach is not applicable to
large dependencies, such as QT.

# List of External Libs

QT can be downloaded from here: https://www.qt.io/download-open-source?hsCtaTracking=9f6a2170-a938-42df-a8e2-a9f0b1d6cdce%7C6cb0de4f-9bb5-4778-ab02-bfb62735f3e5

The version in use: 6.2.1
Modules:

1. [QtWidgets]
2. [QtCore]
3. [QtGui]

You might need to add these to "includePath" in Visual Studio Code c_cpp_properties.json

> If you are using already compiled library, place it in this folder, and set the linker options appropriately.
> The inlcude files of the dependent library should also be placed in this folder.
