# GroundStation Software

This program runs the GroundStation software for Active Controls. Our plan is to be able to upload telemetry,
check for errors, and to have live updating graphs of the data being sent from the rocket.

## Getting Started

As of right now, you will need QtCreator to run the code. Eventually, when we are mostly done,
we'll deploy it to a Windows/Linux module or something. However, in the mean time, here are the
steps to run the code yourself.

- Make a Qt account with the educational license
- Download QtCreator with desktop modules
- Find the Qt Maintenance Tool and download separately these packages (make sure to get the latest 6.62 version)
    * serialport
    * graphs
    * charts
- Build and Run

## Running Code

    Add code blocks with
    four spaces at the front.
    
## Debugging

There tends to be a lot of problems with the building portion of Qt when it comes to QtDesigner, so
if that is sitll in the code, then there might be issues related to it. Check the build folders and
their related moc and ui files.
