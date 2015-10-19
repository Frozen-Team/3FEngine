##FBX2FSEQ

Converter from fbx format to our custom fseq format. 
We desire to ease the work with the raw data provided by fbx format. Grouping all we need in a sort of sequence of data is what we want to achieve. Moreover the file can be conditionally divided into 2 main parts - header and raw data. For more info proceed to specification.

- - - 

###How to use

- - -

###Specification
What you need to know while reading the specification:

 - TYPE_ID - unique type id, e.g TYPE_ID of Polygon Vertices or Texture coords
 - OBJ_ID - unique object id 
 - offset - offset from the current position in the file to the beginning of corresponding raw data
 - count - number of corresponding elements, i.e how many elements are stored in the afile.

####Header
[4 bytes] - unique ID of the file == 1718838641

**Scenes**

    [4 bytes] - TYPE_ID == 446508053
    [4 bytes] - scenes_count
	    [4 bytes] - Scene header offset 0
	    [4 bytes] - 1
	    ...
	    [4 bytes] - (scenes_count - 1)

**Scene**

    [4 bytes] - TYPE_ID == 541744780
    [4 bytes] - meshes_count
        [4 bytes] - Mesh header offset 0
        [4 bytes] - 1
        ...
        [4 bytes] - (meshes_count - 1)

    [4 bytes] - cameras_count
        [4 bytes] - Camera header offset 0
        [4 bytes] - 1
        ...
        [4 bytes] - (cameras_count - 1)

    [4 bytes] - lights_count
        [4 bytes] - Light header offset 0
        [4 bytes] - 1
        ...
        [4 bytes] - (lights_count - 1)

**Mesh**
    
    [4 bytes] - ID == 830987706
    [4 bytes] - Parent mesh offset
    [4 bytes] - Texture header offset
    [4 bytes] - Mesh transform offset
    [4 bytes] - Mesh lods_count
        [4 bytes] - Mesh LOD header offset 0
        [4 bytes] - 1
        ...
        [4 bytes] - (lods_count - 1)

**Mesh transform**

    [4 bytes] - ID == 516947731
... - matrix 4x4 ?
or store position, rotation and transformation separatly?

**Mesh LOD**
    
    [4 bytes] - ID == 723215762
    [4 bytes] - Vertices3f header offset
    [4 bytes] - Vertex indices header offset
    [4 bytes] - Texture coords header offset
    [4 bytes] - Texture indices header offset

**Vertices3f**
    
    [4 bytes] - ID == 331750911
    [4 bytes] - count
    [4 bytes] - offset

**Vertex indices**
    
    [4 bytes] - ID == 958406796
    [4 bytes] - count
    [4 bytes] - offset

**Texture coords**
    
    [4 bytes] - ID == 213954678
    [4 bytes] - count
    [4 bytes] - offset

**Texture indices**
    
    [4 bytes] - ID == 364779684
    [4 bytes] - count
    [4 bytes] - offset

- - - 

####Raw data		