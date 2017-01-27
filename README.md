OpenCV Plugin for CSIRO Workspace
======================================

This project is a plugin for the [CSIRO Workspace](https://research.csiro.au/workspace/) scientific workflow framework. Its purpose is to expose [OpenCV](http://opencv.org/) for use in Workspace. It is intended to support compilation against either OpenCV 2.4 or OpenCV 3.2+

This plugin is very early in development and only exposes a small percentage of data structures and algorithms available in OpenCV (but is based on a more extensive legacy plugin developed for specific CSIRO projects). Feedback and contributions are more than welcome to help expand its capabilities. 

Compiling and using the plugin
------------------------------
1. Download and install [CSIRO Workspace](https://research.csiro.au/workspace/download/)
2. Download and install [OpenCV](http://opencv.org/)  (or build a version yourself)
3. Checkout this repository
4. CMake configure this project, OpenCV_DIR should point to your OpenCV build tree (eg. C:\opencv\build)
5. Depending on write permissions to Workspace's install folder you may get a CMake configure message about manually copying installArea-opencvplugin.txt to Workspace's installAreas directory. Ensure you follow this message so Workspace loads your plugin once it's built.
6. Restart Workspace and an OpenCV group should be available in the Workspace operation catalogue

About CSIRO Workspace
---------------------
Workspace is a powerful scientific application framework and workflow editor which has been in development for over 10 years. Originally designed to construct workflows for scientists in the computational fluid dynamics space, Workspace recognises the importance of interactivity, visualisation, scalability, and ease-of-use in a scientific workflow. It ships with out of the box support for things like mesh processing, interactive 3D visualisation, plotting, networking and database access and is designed to be easily extended through plugins. More than just a workflow editor, Workspace offers a natural path from early code development as part of a research workflow right through to the development of standalone applications for deployment to a collaborator or external client.

Workspace is developed by the Computational Modelling and Simulation Group of Australia's Commonwealth Scientific and Industrial Research Organisation (CSIRO). Workspace has been developed with support from CSIRO eResearch, Computational and Simulation Sciences and Data61.

For more details or to contact the team see the [Workspace research page](https://research.csiro.au/workspace/).

Contributors
------------
- Matt Bolger, James Hilton, Ray Cohen, Yulia Arzhaeva, Clair Miller (CSIRO Data61)

License
-------
CSIRO Open Source Software License Agreement (variation of the BSD / MIT License) - See the LICENSE file in this repository