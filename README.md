OpenCV Plugin for CSIRO Workspace
======================================

This project is a plugin for the [CSIRO Workspace](https://research.csiro.au/workspace/) scientific workflow framework. Its purpose is to expose [OpenCV](http://opencv.org/) for use in Workspace. 

This plugin is very early in development and only exposes a small percentage of data structures and algorithms available in OpenCV. Feedback and contributions are more than welcome to help expand its capabilities. Binary release of this plugin on supported platforms will be made available from [The Workspace Research Site](https://research.csiro.au/workspace/) in the future. 

Compiling and using the plugin
------------------------------
1. Download and install [CSIRO Workspace](https://research.csiro.au/workspace/download/)
2. Download and install [OpenCV](http://opencv.org/)  (or build a version yourself)
3. Checkout this repository
7. Copy Install\installAreas\installArea-PointClouds.txt from your build directory to Workspace's installAreas directory (Create this directory under the top level Workspace install directory if it doesn't yet exist).
8. Restart Workspace and an OpenCV group should be available in the Workspace operation catalogue

About CSIRO Workspace
---------------------
Workspace is a powerful scientific application framework and workflow editor which has been in development for over 7 years. Originally designed to construct workflows for scientists in the computational fluid dynamics space, Workspace recognises the importance of interactivity, visualisation, scalability, and ease-of-use in a scientific workflow. It ships with out of the box support for things like mesh processing, interactive 3D visualisation, plotting, networking and database access and is designed to be easily extended through plugins. More than just a workflow editor, Workspace offers a natural path from early code development as part of a research workflow right through to the development of standalone applications for deployment to a collaborator or external client.

Workspace is developed by the Computational Modelling and Simulation Group of Australia’s Commonwealth Scientific and Industrial Research Organisation (CSIRO). Workspace has been developed with support from CSIRO eResearch, Computational and Simulation Sciences and Data61.

For more details or to contact the team see the [Workspace research page](https://research.csiro.au/workspace/).

Contributors
------------
- Matt Bolger, James Hilton, Ray Cohen, Yulia Arzhaeva, Clair Miller (CSIRO Data61)

License
-------
See the LICENSE file in this repository