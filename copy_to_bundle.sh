#!/bin/bash

mkdir -p ./bundle/UMLViewer.app/Contents/MacOS/
cp -f Info.plist ./bundle/UMLViewer.app/Contents/Info.plist
cp -f ./cmake-build-debug/uml_viewer_01 ./bundle/UMLViewer.app/Contents/MacOS/umlviewer
