This repository contains the open-source code used in the user study for the paper:
"Operationalizing General Mechanical Skill in Time-Pressure Action Esports"

Project Overview
- Engine: Unreal Engine 4.26.2
- Language: C++

Currently, the server used for the user study is closed.
For actual testing, the following edits need to be made to the blueprints:

1. Removing VaRest Plugin Usage 
   
- Open project in Unreal Engine 4.26.2.
- Navigate to the Blueprints of each level and UI element.
- Open the blueprints that utilize the VaRest plugin for web connections.
- Identify the nodes and scripts using the VaRest plugin .
- Delete or comment out these nodes to disable web connections.

2. Skipping the Login Session
- Locate the blueprint responsible for the first UI (where you select to login or register).
- Open the blueprint in the Blueprint Editor.
- Locate the event or function that handles login button.
- Replace the login UI with a direct call to load the main UI.

Notes

- Some interface elements may be written in Korean due to the user study being conducted in Korea.
