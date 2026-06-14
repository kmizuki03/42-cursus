*This project has been created as part of the 42 curriculum by kmizuki, ayamada.*

## Description
This project is cub3D.<br>
This project explores the Ray-casting technique to render a 2D map into a 3D environment in real-time.<br>
The goal is to create a 3D game view using the Ray-casting technique.

 **Key Features**
* Parsing: Read .cub files and validate map data.
* Ray-casting: Calculate distance to walls to render 3D views.
* Graphics: Display textures and handle window events using miniLibX.
* Movement: Player can move (W,A,S,D) and rotate (Arrows).

## Instructions
**Compilation**
* Tocompile, run:
```bash
make
```
**Execution**
* Run the executable with a valid `.cub` scene description file:
```bash
./cub3d maps/subject.cub
```
**Controls**
* `W`,`A`,`S`,`D`: Move the player.
* `Left`/`Right` arrows: Rotate the camera.
* `ESC`or`Red Cross`: Close the window and exit the program.

## Resources
**reference materials**
* [Qiita](https://qiita.com/susasaki/items/c74a228d7ddd48b818bd)
* [blog](https://jun-networks.hatenablog.com/entry/2021/03/04/130629)

**Use of AI**
* Norm correction
* Debugging
* Generate .cub files for test