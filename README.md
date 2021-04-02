# B.Slizr
formerly known as B.Slicer

Description: LV2 audio effect plugin for chopping stereo audio input signals. Each chop can be levelled up or down to get a step sequencer-like effect.

![screenshot](https://raw.githubusercontent.com/sjaehn/bmusic-bslicer/master/Screenshot.png "Screenshot from B.Slizr")


##Installation

a) Install the bslizr package for your system
* [Arch linux](https://www.archlinux.org/packages/community/x86_64/bslizr/) by David Runge
* [NixOS](https://github.com/NixOS/nixpkgs/blob/master/pkgs/applications/audio/bslizr/default.nix) by Bart Brouns
* [Debian](https://kx.studio/Repositories:Plugins) by falkTX
* Check https://repology.org/project/bslizr/versions for other systems

b) Build your own binaries in the following three steps.

Step 1: [Download the latest published version](https://github.com/sjaehn/BSlizr/releases) of B.Slizr. Or clone or
[download the master](https://github.com/sjaehn/BSlizr/archive/master.zip) of this repository.

Step 2: Install pkg-config and the development packages for x11, cairo, and lv2 if not done yet. If you
don't have already got the build tools (compilers, make, libraries) then install them too.

On Debian-based systems you may run:
```
sudo apt-get install build-essential
sudo apt-get install pkg-config libx11-dev libcairo2-dev lv2-dev
```

On Arch-based systems you may run:
```
sudo pacman -S base-devel
sudo pacman -S pkg-config libx11 cairo lv2
```

Step 3: Building and installing into the default lv2 directory (/usr/local/lib/lv2/) is easy using `make` and
`make install`. Simply call:
```
make
sudo make install
```

**Optional:** Standard `make` and `make install` parameters are supported. Compiling using `make CPPFLAGS+=-O3`
is recommended to improve the plugin performance. Alternatively, you may build a debugging version using
`make CPPFLAGS+=-g`. For installation into an alternative directory (e.g., /usr/lib/lv2/), change the
variable `PREFIX` while installing: `sudo make install PREFIX=/usr`. If you want to freely choose the
install target directory, change the variable `LV2DIR` (e.g., `make install LV2DIR=~/.lv2`) or even define
`DESTDIR`.

**Optional:** Further supported parameters are `LANGUAGE` (two letters code) to change the GUI language and
`SKIN` to change the skin (see customize).


##Running

After the installation Ardour, Carla, and any other LV2 host should automatically detect B.Slizr.

If jalv is installed, you can also call it

```
jalv.gtk https://www.jahnichen.de/plugins/lv2/BSlizr
```

to run it stand-alone and connect it to the JACK system.

Notes:

* **Jack transport is required to get information about beat / position**
* If you use an older version (until v0.3) of this plugin, use the URI https://www.jahnichen.de/plugins/lv2/BSlicer instead.


##Usage

The plugin slices a stereo input, amplifies or silences the individual slices and send the whole sequence to the output. Although this affects only the audio signal, it needs a playback running (Jack transport).

The interface is divided into three parts: step controls, monitor and step shape.


###Step controls

* Sequences per bar : Number of sequences in one bar (1..8)
* Number of steps : Number of steps in one sequence (1..16)
* Step control : Coefficient for sound reduction for each individual step


###Monitor

* On/Off switch: Switches monitor and monitor <-> plugin communication on/off. Reduces CPU load.
* Scale : Scales the visualization of the input / output signal
* Monitor : Visualization (l + r signal) the input / output signal for a whole sequence


###Step shape

* Attack
* Decay
* Monitor : Visualization of a single step


###Customize

You can create customized builds of B.Slizr using the parameters `LANGUAGE` and `SKIN` (e.g.,
`make LANGUAGE=RU SKIN=UWU`). To create a new language pack, copy `src/Locale_EN.hpp` and edit
the text for the respective definitions. But do not change or delete any definition symbol!

To create a new skin, duplicate `src/Skin_Default.hpp`, rename it to `src/Skin_Default.hpp` 
and edit the parameters. You can also provide a background image at `./surface_SkinName.png`.


## What's new

* Custom language and skin builds
* Easteregg: UwU

Links
-----
* Video: https://www.youtube.com/watch?v=gLI2ozKdNDk
