### 29.10.2015
OTER:

 - Integrate GLEW

### 20.10.2015
OTER:

 - Add GLEW library as submodule.
 - Work on OpenGL helper.

### 19.10.2015
OlehGol260:

 - All necessary stuff from fbx now will be packed in fseq format
 - These work is moved to separate project fbx2fseq
 - Create CMakeLists for new project, minor refactor old ones.
 - As fbx2fseq is difficult to realize without 3FEngine classes, start work on them
 - Begin with mesh lods

### 15.10.2015 
OTER:

 - Configure loggers.
 - Add prefix F to classes.
 - Add FLogger class. Load loggers configuration from file.
 
OlehGol260:
 
 - Add initialization method for fbx_loader
 - Rename namespace FEngine to fengine, Utils to utlis
 - Fix header guards according to Google style guide
 
### 13.10.2015 
OlehGol260:

 - Fix CMakeLists.txt in src folder.
 
OTER:
 
 - Add singleton class.
 
### 12.10.2015  
OTER:

- Filter sources files.
- Attach GLI library. 
- Add roadmap.
- Add Utils namespace for utilite methods. Add ToLower method.
- Add Settings class.
- Work on UML class diagram. 

OlehGol260:

- Add Vertices class
- Add typedefs to Utils
- Partially add blanks for scene and components according to UML

### 11.10.2015  
OTER:

- Added GLI library submodule.  

### 10.10.2015  
OTER:

- Build executables to deploy directory.  
- Added option which determines, whether console enabled or not.  
- Added FBX SDK  
- Set compiler flags /MDd and /MD for debug and release configuration respectively.  
- Fixed error with mismatched flags /MTd and /MDd in libraries.  
- Cut out building tests and examples from libraries.  
- Separate debug and release libs.  
- Add license.  
- Fix CMP0054 messages.  
- Disabled build of a shared SDL library.  
