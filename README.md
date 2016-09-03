# QtNodes
QtNodes is a library for the visualization of Nodes for the Qt-framework.

_**Note:** This library is at a very early stage and not fancy nor usable right now_

## Run Showcase
To run the showcase, open the files `src/QtNodesShare.pro`, `src/QtNodes.pro` and `showcase/NodeShowcase.pro`. Then you need to add the dependency of `QtNodesShare` to `QtNodes` and the dependency `QtNodes` to `NodeShowcase`.
Every time you run the project `NodeShowcase`, `QtNodes` and `QtNodesShare` will compile automatically.

## Features

### Implemented
* complete separation of node-implementation and -view
* set custom header and footer per node
* automatic port creation according to node-implementation
  * the different NodePort-types have to be defined only one time for the whole library. Example: If you have defined a NodePortView for the type QString, every time a NodePort is of type QString this found this NodePortView will be automatically used. (Currently the Type selection is static)
* connect nodes via Drag&Drop (QDrag); even between multiple NodeGridScenes, if you want support it. The method to connect NodePorts to each other does not rely on pointers. This adds the possibility to connect nodes between different applications, if you want to do so.


### Planned
* display node connections [how to handle displaying connections to other NodeGridScenes/Applications?]
* choose the NodePortView according to type, not statically
